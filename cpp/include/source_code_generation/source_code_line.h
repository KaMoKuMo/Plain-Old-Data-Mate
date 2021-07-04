#pragma once

/** \addtogroup source_code_generation
 * @{
 */

#include "source_code.h"
#include "source_code_generation/line_fragment.h"

/**
 * Models a single line of source code
 **/
class SourceCodeLine final : public SourceCode {
    LineFragment _line;
public:
    explicit SourceCodeLine(std::string /*initalData*/ = std::string());

    SourceCodeLine& append(std::string);
    SourceCodeLine operator+(std::string) const;

    virtual std::ostream& write(std::ostream&, size_t /*indentationLevel*/) const override;
};

/** @} */
