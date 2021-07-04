#pragma once

#include <exception>
#include <iostream>
#include <optional>
#include <type_traits>
#include <variant>

/**
 * \class Unexpected
 *
 * stores and provides some unexpected value. This class serves mainly the
 * purpose of a helper class for the \see Expected
 **/
template<typename E>
class Unexpected {
public:
    static_assert(!std::is_same_v<E,void>, "E must not be void");

    Unexpected() = delete;

    //! constructs the Unexpected by copying the error
    constexpr explicit Unexpected(E const& e) : error_(e) {}
    //! constructs the Unexpected by moving the error
    constexpr explicit Unexpected(E&& e) : error_(std::move(e)) {}

    //! yields read access to the error
    constexpr E const& error() const& noexcept {return error_;}
    //! yields read and write access to the error
    constexpr E & error() & noexcept {return error_;}
    //! yields the contained error as a readable error
    constexpr E const&& error() const&& noexcept {return std::move(error_);}
    //! yields the contained error
    constexpr E && error() && noexcept {return std::move(error_);}

    //! Compares the error
    constexpr bool operator==(Unexpected const& rRhs) const noexcept {
        return error_ == rRhs;
    }
    //! Compares the error
    constexpr bool operator!=(Unexpected const& rRhs)  const noexcept {
        return error_ != rRhs;
    }
    //! Compares the error
    constexpr bool operator<(Unexpected const& rRhs)  const noexcept {
        return error_ < rRhs;
    }

private:
    E error_; //!< contained error
};

/**
 * Exception thrown by an \see Expected::operator*(), or \see Expected::value(),
 * if the expected value is demanded when the unexpected value is stored
 **/
template<typename E>
class BadExpectedAccess : public std::exception {
public:
    //! saves the error
    explicit BadExpectedAccess(E e) : error_(std::move(e)) {}

    //! yields the reason for the throw
    virtual const char* what() const noexcept override {
        return "Bad Expected access";
    }

    //! yields readable access to the error
    constexpr E const& error() const& noexcept {return error_;}
    //! yields read and write access to the error
    constexpr E & error() & noexcept {return error_;}
    //! yields the contained error as a readable error
    constexpr E const&& error() const&& noexcept {return std::move(error_);}
    //! yields the contained error
    constexpr E && error() && noexcept {return std::move(error_);}

private:
    E error_; //!< saved error
};

template<>
class BadExpectedAccess<void> : public std::exception {
public:
    //! saves the error
    explicit BadExpectedAccess() = default;

    //! yields the reason for the throw
    virtual const char* what() const noexcept override {
        return "Bad Expected access";
    }
};

/**
 * Wrapper around a std::variant<Value, Error> carrying the meaning
 * that the "Value" is expected, but the "Error" unexpected.
 *
 * There are two ways two construct an Expected. Either by implicitly
 * converting an Unexpected<Error1> into some Expected storing the unexpected
 * result, or by converting any number of arguments into the expected value_type.
 * Notice that a default Expected will be initialized with a default
 * initialized expected value.
 *
 * To check whether the expected value is stored the explicit operator bool()
 * is supplied.
 **/
template<typename T, typename E>
class [[nodiscard]] Expected {
public:
    //! the expected value type
    using value_type = T;
    //! the unexpected type
    using error_type = E;

    /**
     * Copies the data from the \see Unexpected object.
     * Constructed with this c'tor the expected will yield false when asked
     * about expected value.
     */
    template<typename TError, std::enable_if_t< std::is_constructible_v<error_type, TError const&>, int > = 0>
    constexpr Expected(Unexpected<TError> const& rE)
        : data_(std::in_place_index_t<eT_error>{}, rE.error())
    {
    }

    /**
     * Moves the data from the \see Unexpected object.
     * Constructed with this c'tor the expected will yield false when asked
     * about expected value.
     */
    template<typename TError, std::enable_if_t<std::is_constructible_v<error_type, TError&&>, int> = 0>
    constexpr Expected(Unexpected<TError> && rE)
        : data_(std::in_place_index_t<eT_error>{}, std::move(std::move(rE).error()))
    {
    }

    /**
     * Initializes an instance of the expected_type with given arguments.
     * Constructed with this c'tor the expected will yield true when asked
     * about the expected value.
     **/
    template<typename ...Args, std::enable_if_t<std::is_constructible_v<value_type, Args...>, int > = 0>
    constexpr Expected(Args&& ...args)
        : data_(std::in_place_index_t<eT_value>{}, std::forward<Args>(args)...)
    {
    }

    //! true if the expected value is stored
    explicit operator bool() const noexcept{
        return std::get_if<eT_value>(&data_);
    }

    //! yields read access to the stored unexpected value, or throws if the expected value is contained
    constexpr E const& error() const& noexcept(false) {
        if (std::get_if<eT_value>(&data_))
            throw BadExpectedAccess<T>(std::get<eT_value>(data_));
        return std::get<eT_error>(data_);
    }
    //! yields read and write access to the stored unexpected value, or throws if the expected value is contained
    constexpr E & error() & noexcept(false) {
        if (std::get_if<eT_value>(&data_))
            throw BadExpectedAccess<T>(std::get<eT_value>(data_));
        return std::get<eT_error>(data_);
    }
    //! yields the stored unexpected value as read only, or throws if the expected value is contained
    constexpr E const&& error() const&& noexcept(false) {
        if (std::get_if<eT_value>(&data_))
            throw BadExpectedAccess<T>(std::move(std::get<eT_value>(data_)));
        return std::move(std::get<eT_error>(data_));
    }
    //! yields the stored unexpected value, or throws if the expected value is contained
    constexpr E && error() && noexcept(false) {
        if (std::get_if<eT_value>(&data_))
            throw BadExpectedAccess<T>(std::move(std::get<eT_value>(data_)));
        return std::move(std::get<eT_error>(data_));
    }

    //! yields read access to the stored expected value, or throws if the unexpected value is contained
    constexpr T const& operator*() const& noexcept(false) {
        if (std::get_if<eT_error>(&data_))
            throw BadExpectedAccess<E>(std::get<eT_error>(data_));
        return std::get<eT_value>(data_);
    }
    //! yields read and write access to the stored expected value, or throws if the unexpected value is contained
    constexpr T & operator*() & noexcept(false) {
        if (std::get_if<eT_error>(&data_))
            throw BadExpectedAccess<E>(std::get<eT_error>(data_));
        return std::get<eT_value>(data_);
    }
    //! yields the stored expected value as read only, or throws if the unexpected value is contained
    constexpr T const&& operator*() const&& noexcept(false) {
        if (std::get_if<eT_error>(&data_))
            throw BadExpectedAccess<E>(std::move(std::get<eT_error>(data_)));
        return std::move(std::get<eT_value>(data_));
    }
    //! yields the stored expected value, or throws if the unexpected value is contained
    constexpr T && operator*() && noexcept(false) {
        if (std::get_if<eT_error>(&data_))
            throw BadExpectedAccess<E>(std::move(std::get<eT_error>(data_)));
        return std::move(std::get<eT_value>(data_));
    }

    //! yields read and write access to the stored expected value, or throws if the unexpected value is contained
    constexpr T* operator->() noexcept(false) {
        if (auto* pData = std::get_if<eT_value>(&data_))
            return pData;
        throw BadExpectedAccess<E>(std::get<eT_error>(data_));
    }
    //! yields read access to the stored expected value, or throws if the unexpected value is contained
    constexpr T const* operator->() const noexcept(false) {
        if (auto* pData = std::get_if<eT_value>(&data_))
            return pData;
        throw BadExpectedAccess<E>(std::get<eT_error>(data_));
    }

    //! compares the state and the contained values
    friend constexpr bool operator==(Expected const& lhs, Expected const& rhs) {
        return lhs.data_ == rhs.data_;
    }

    //! streams the state and the corresponding value in a json format
    friend std::ostream& operator<<(std::ostream& o, Expected<value_type, error_type> const& expectedValue) {
        o << "{";
        if (expectedValue) {
            o << "\"expected value\" : " << *expectedValue;
        } else {
            o << "\"unexpected value\" : " << expectedValue.error();
        }
        return o << "}";
    }
private:
    enum Tag {
        eT_value,
        eT_error
    };
    std::variant<T, E> data_; //!< data storage
};

/**
 * Partial specialization for the Expected<T, E> to allow T == void.
 * Since no value is contained member functions for retrieving or accessing the
 * value are omitted.
 **/
template<typename E>
class [[nodiscard]] Expected<void, E> {
public:
    //! the expected value type
    using value_type = void;
    //! the unexpected type
    using error_type = E;

    /**
     * Copies the data from the \see Unexpected object.
     * Constructed with this c'tor the expected will yield false when asked
     * about expected value.
     */
    template<typename TError, std::enable_if_t< std::is_constructible_v<error_type, TError const&>, int > = 0>
    constexpr Expected(Unexpected<TError> const& rE)
        : data_(rE.error())
    {
    }

    /**
     * Moves the data from the \see Unexpected object.
     * Constructed with this c'tor the expected will yield false when asked
     * about expected value.
     */
    template<typename TError, std::enable_if_t<std::is_constructible_v<error_type, TError&&>, int> = 0>
    constexpr Expected(Unexpected<TError> && rE)
        : data_(std::move(std::move(rE).error()))
    {
    }

    /**
     * The default initialized expected is treated as the expected outcome.
     **/
    constexpr Expected() = default;

    //! true if the expected value is stored
    explicit operator bool() const noexcept{
        return !data_;
    }

    //! yields read access to the stored unexpected value, or throws if the expected value is contained
    constexpr E const& error() const& noexcept(false) {
        if (*this)
            throw BadExpectedAccess<void>();
        return *data_;
    }
    //! yields read and write access to the stored unexpected value, or throws if the expected value is contained
    constexpr E & error() & noexcept(false) {
        if (*this)
            throw BadExpectedAccess<void>();
        return *data_;
    }
    //! yields the stored unexpected value as read only, or throws if the expected value is contained
    constexpr E const&& error() const&& noexcept(false) {
        if (*this)
            throw BadExpectedAccess<void>();
        return std::move(*data_);
    }
    //! yields the stored unexpected value, or throws if the expected value is contained
    constexpr E && error() && noexcept(false) {
        if (*this)
            throw BadExpectedAccess<void>();
        return std::move(*data_);
    }

    //! compares the state and the contained values
    friend constexpr bool operator==(Expected const& lhs, Expected const& rhs) {
        return lhs.data_ == rhs.data_;
    }

    //! streams the state and the corresponding value in a json format
    friend std::ostream& operator<<(std::ostream& o, Expected<value_type, error_type> const& expectedValue) {
        o << "{";
        if (expectedValue) {
            o << "\"expected value\" : void";
        } else {
            o << "\"unexpected value\" : " << expectedValue.error();
        }
        return o << "}";
    }
private:
    std::optional<error_type> data_; //!< data storage
};

