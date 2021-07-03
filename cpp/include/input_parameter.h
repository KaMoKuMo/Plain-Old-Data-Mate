#pragma once

#include <string>

#include <iostream>
/**
 * Main input parameter for the podmate project. 
 **/
struct InputParameter {
    std::string inputFileName; //<! to be parsed file
    std::string outputHeaderFileName; //<! name of the header file to be generated
    std::string outputSourceFileName; //<! name of the source file to be generated

    friend bool operator==(InputParameter const&, InputParameter const&);
    friend bool operator!=(InputParameter const&, InputParameter const&);
    friend std::ostream& operator<<(std::ostream&, InputParameter const&);
};
