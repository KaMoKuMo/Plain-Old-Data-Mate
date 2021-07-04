#pragma once

/** \addtogroup source_code_generation
 * @{
 */

#include "source_code_generation/source_code.h"
#include <memory>

/**
 * A Body is SourceCode surrounded by curly brackets with an additional
 * indentationLevel.
 *
 * Notice that the opening bracket is not indented and the closing bracket is
 * not following a linefeed.
 **/
class Body final : public SourceCode {
    std::unique_ptr<SourceCode> _body; //<! To be indented source code

public:
    Body(std::unique_ptr<SourceCode> /*body*/ = nullptr);

    virtual std::ostream& write(std::ostream&, size_t /*indentationLevel*/) const override;
};


/** @} */
