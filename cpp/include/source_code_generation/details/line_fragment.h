#pragma once

/** \addtogroup source_code_generation
 * @{
 */

#include "source_code_generation/details/source_code.h"

/**
 * Models the most fundamental building block of SourceCode:
 * Some line part which can be written with indentation.
 **/
class LineFragment : public SourceCode {
    std::string _lineFragment; //<! Data to be written
public:
    explicit LineFragment(std::string /*initalData*/ = std::string());

    LineFragment& append(std::string);

    virtual std::ostream& write(std::ostream&, size_t /*indentationLevel*/) const override;
};

/** @} */
