#pragma once

#include <iostream>
#include <exception>
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

    constexpr explicit Unexpected(E const& e) : error_(e) {}
    constexpr explicit Unexpected(E&& e) : error_(std::move(e)) {}

    constexpr E const& error() const& noexcept {return error_;}
    constexpr E & error() & noexcept {return error_;}
    constexpr E const&& error() const&& noexcept {return std::move(error_);}
    constexpr E && error() && noexcept {return std::move(error_);}

    constexpr bool operator==(Unexpected const& rRhs) const noexcept {
        return error_ == rRhs;
    }
    constexpr bool operator!=(Unexpected const& rRhs)  const noexcept {
        return error_ != rRhs;
    }
    constexpr bool operator<(Unexpected const& rRhs)  const noexcept {
        return error_ < rRhs;
    }

private:
    E error_;
};

/**
 * \class BadExpectedAccess
 *
 * Exception thrown by an \see Expected::operator*(), or \see Expected::value(),
 * if the expected value is demanded when the unexpected value is stored
 **/
template<typename E>
class BadExpectedAccess : public std::exception {
public:
    explicit BadExpectedAccess(E e) : error_(std::move(e)) {}

    virtual const char* what() const noexcept override {
        return "Bad Expected access";
    }

    constexpr E const& error() const& noexcept {return error_;}
    constexpr E & error() & noexcept {return error_;}
    constexpr E const&& error() const&& noexcept {return std::move(error_);}
    constexpr E && error() && noexcept {return std::move(error_);}

private:
    E error_;
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

    template<typename TError, std::enable_if_t< std::is_constructible_v<error_type, TError const&>, int > = 0>
    constexpr Expected(Unexpected<TError> const& rE)
        : data_(std::in_place_index_t<eT_error>{}, rE.error())
    {
    }

    template<typename TError, std::enable_if_t<std::is_constructible_v<error_type, TError&&>, int> = 0>
    constexpr Expected(Unexpected<TError> && rE)
        : data_(std::in_place_index_t<eT_error>{}, std::move(std::move(rE).error()))
    {
    }

    template<typename ...Args, std::enable_if_t<std::is_constructible_v<value_type, Args...>, int > = 0>
    constexpr Expected(Args&& ...args)
        : data_(std::in_place_index_t<eT_value>{}, std::forward<Args>(args)...)
    {
    }

    //! true if the expected value is stored
    explicit operator bool() const noexcept{
        return std::get_if<eT_value>(&data_);
    }

    //! yields the stored unexpected value, or throws if the expected value is contained
    constexpr E const& error() const& noexcept(false) {
        if (std::get_if<eT_value>(&data_))
            throw BadExpectedAccess<T>(std::get<eT_value>(data_));
        return std::get<eT_error>(data_);
    }
    //! yields the stored unexpected value, or throws if the expected value is contained
    constexpr E & error() & noexcept(false) {
        if (std::get_if<eT_value>(&data_))
            throw BadExpectedAccess<T>(std::get<eT_value>(data_));
        return std::get<eT_error>(data_);
    }
    //! yields the stored unexpected value, or throws if the expected value is contained
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

    //! yields the stored expected value, or throws if the unexpected value is contained
    constexpr T const& operator*() const& noexcept(false) {
        if (std::get_if<eT_error>(&data_))
            throw BadExpectedAccess<E>(std::get<eT_error>(data_));
        return std::get<eT_value>(data_);
    }
    //! yields the stored expected value, or throws if the unexpected value is contained
    constexpr T & operator*() & noexcept(false) {
        if (std::get_if<eT_error>(&data_))
            throw BadExpectedAccess<E>(std::get<eT_error>(data_));
        return std::get<eT_value>(data_);
    }
    //! yields the stored expected value, or throws if the unexpected value is contained
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
private:
    enum Tag {
        eT_value,
        eT_error
    };
    std::variant<T, E> data_;
};

/**
 * Convinient partial specialization for defacto Expected of this project
 **/
template<typename Value>
using ExpectedOrMessage = Expected<Value, std::string>;

