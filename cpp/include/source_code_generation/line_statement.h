#pragma once

/** \addtogroup source_code_generation
 * @{
 */

#include "source_code_line.h"

/**
 * Models a line statement, i.e. a line of source code ending with a semicolon, \see SourceCodeLine.
 **/
class LineStatement final : public SourceCode {
private:
    SourceCodeLine _lineStatment;

public:
    explicit LineStatement(std::string /*initalData*/ = std::string());
    LineStatement& append(std::string);

    virtual std::ostream& write(std::ostream&, size_t /*indentationLevel*/) const override;
};

/** @} */
