#include <iostream>
#include "sample_structs.h"
#include "fill.h"
#include "alter.h"

/**
 * Checks the equal operator by comparing copies and an altered copy to the
 * original.
 * Prerequisite for the usage of this function for the Type T is the definition two functions
 * with the signature:
 * void fill(T& t);
 * void alter(T& t);
 *
 * while fill should fill the given reference with some value,
 * alter should alter some objects.
 **/
template<typename T>
bool
checkEqualOperator() {
    T sample;
    fill(sample);
    T copy = sample;

    bool const copiesAreEqual = sample == copy;
    alter(sample);
    return copiesAreEqual && !(copy == sample);
}

/**
 * simple wrapper to check the equal operator for an arbitrary number of types
 **/
template<typename ...Ts>
bool
checkEqualOperators() {
    return (checkEqualOperator<Ts>() && ...);
}

/**
 * checks the equal operators by invoking checkEqualOperators for the types
 * \see IntWrapper and \see Compound from the file sample_structs.h
 *
 * When successful "SUCCESS\n" is printed to std::cout and the return value is 0,
 * when unsuccessful this function returns "1";
 **/
int main() {
    if (!checkEqualOperators<IntWrapper, Compound>()) {
        std::cout << "Equal operator seems wrong!\n";
        return 1;
    }

    std::cout<<"SUCCESS!\n";
    return 0;
}
