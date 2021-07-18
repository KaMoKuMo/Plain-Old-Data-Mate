#include <iostream>
#include "sample_structs.h"
#include "fill.h"
#include "alter.h"
#include "to_string.h"

#include "simdjson.h"

#include <sstream>

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
    bool const copiesAreNotUnequal = !(sample != copy);
    alter(sample);
    return copiesAreEqual && copiesAreNotUnequal && (copy != sample) && !(copy == sample);
}

/**
 * Checks the stream operator by comparing the streamed object with the outcome
 * of the toString() method
 * Prerequisite for the usage of this function for the Type T is the definition two functions
 * with the signature:
 * void fill(T& t);
 * void alter(T& t);
 * std::string toString(T const& t);
 *
 * while fill should fill the given reference with some value,
 * alter should alter some objects.
 **/
template<typename T>
bool
checkStreamOperator() {
    T sample;
    fill(sample);
    std::string expected = toString(sample);
    std::stringstream stream;
    stream << sample;
    if (expected != stream.str()) {
        std::cout << "expected : " << expected <<'\n';
        std::cout << "result : " << stream.str() <<'\n';
        return false;
    }
    return true;
}

template<typename T>
bool
roundTrip() {
    T sample;
    fill(sample);
    std::stringstream stream;
    stream << sample;
    std::string const outputData = stream.str();
    simdjson::dom::parser parser;
    simdjson::padded_string json = simdjson::padded_string(outputData);
    simdjson::dom::element doc = parser.parse(json);
    T output;
    try {
        fromJson(doc, output);
        if (sample != output) {
            throw std::logic_error(std::string(typeid(sample).name()) + " can not complete a roundtrip");
        }
    } catch (std::exception const& exception) {
        std::cout<<exception.what();
        std::cout<<outputData<<'\n';
        return false;
    }

    return true;
}


/**
 * simple wrapper to check the equal operator for an arbitrary number of types
 **/
template<typename ...Ts>
bool
checkOperators() {
    return (checkEqualOperator<Ts>() && ...)
        && (checkStreamOperator<Ts>() && ...)
        && (roundTrip<Ts>() && ...);
}

/**
 * checks the equal operators by invoking checkEqualOperators for the types
 * \see IntWrapper and \see Compound from the file sample_structs.h
 *
 * When successful "SUCCESS\n" is printed to std::cout and the return value is 0,
 * when unsuccessful this function returns "1";
 **/
int main() {
    using namespace OutterNamespace::InnerNamespace;
    if (!checkOperators<IntWrapper, Compound>()) {
        std::cout << "Some operator seems wrong!\n";
        return 1;
    }

    std::cout<<"SUCCESS!\n";
    return 0;
}
