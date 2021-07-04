#pragma once

#include "output_file_parameters.h"

#include <iostream>
#include <string>
/**
 * Main input parameter for the podmate project. 
 **/
struct InputParameter {
    std::string inputFileName; //<! to be parsed file
    OutputFileParameters outputData; //<! Data for the outputfiles

    friend bool operator==(InputParameter const&, InputParameter const&);
    friend bool operator!=(InputParameter const&, InputParameter const&);
    friend std::ostream& operator<<(std::ostream&, InputParameter const&);
};
