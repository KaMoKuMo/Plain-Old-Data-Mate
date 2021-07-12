#pragma once

#include <array>
#include <iostream>

/**
 * @class CopyMoveTracer
 *
 * Zählt copy c'tor und assignment, und move c'tor und assignment mittels
 * statischer Variablen.
 **/
template<typename T>
class CopyMoveTracer {
public:
    CopyMoveTracer(T t) : _t(t) {}

    //! Erhöht den copy c'tor Zähler um +1
    CopyMoveTracer(CopyMoveTracer const& other)
        : _t(other._t)
    {
        ++c_counter[_copyCtor];
    }

    //! Erhöht den move c'tor Zähler um +1
    CopyMoveTracer(CopyMoveTracer&& other)
        : _t(std::move(other._t))
    {
        ++c_counter[_moveCtor];
    }

    //! Erhöht den copy assignment Zähler um +1
    CopyMoveTracer& operator=(CopyMoveTracer const& rhs) {
        _t = rhs._t;
        ++c_counter[_copyAssignment];
        return *this;
    }
    //! Erhöht den move assignment Zähler um +1
    CopyMoveTracer& operator=(CopyMoveTracer&& rhs) {
        _t = std::move(rhs._t);
        ++c_counter[_moveAssignment];
        return *this;
    }

    //! liefert true, falls alle Zähler auf 0 sind
    static bool nothingCopiedOrMoved() {
        return totalCount();
    }

    //! liefert den Gesamtzählerstand
    static uint32_t totalCount() {
        uint32_t result = 0;
        for (uint32_t counter : c_counter)
            result += counter;
        return result;
    }

    //! setzt alle Zähler auf 0
    static void clear() {
        for (uint32_t& counter : c_counter)
            counter = 0;
    }

    //! liefert alle Zähler in der Reihenfolge copyCtor, copyAssignment, moveCtor, moveAssignmet
    static void print() {
        for (uint32_t counter : c_counter)
            std::cout << counter <<'\t';
        std::cout<<'\n';
    }

    //! liefert den copy c'tor Zähler
    static uint32_t copyCtor() { return c_counter[_copyCtor]; }
    //!  liefert den move c'tor Zähler
    static uint32_t moveCtor() { return c_counter[_moveCtor]; }
    //!  liefert den copy assignment Zähler
    static uint32_t copyAssignment() { return c_counter[_copyAssignment]; }
    //!  liefert den move assignment Zähler
    static uint32_t moveAssigment() { return c_counter[_moveAssignment]; }

private:
    enum ETag {
        _copyCtor,
        _copyAssignment,
        _moveCtor,
        _moveAssignment
    };

    static std::array<uint32_t, 4> c_counter;

    T _t;
};

template<typename T>
std::array<uint32_t, 4> CopyMoveTracer<T>::c_counter = {0, 0, 0, 0};
