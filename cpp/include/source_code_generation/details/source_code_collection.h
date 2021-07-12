#pragma once

/** \addtogroup source_code_generation
 * @{
 */

#include "source_code_generation/details/source_code.h"
#include "source_code_generation/details/body.h"

#include <vector>

/**
 * A SourceCodeCollection is SourceCode containing other source code
 **/
class SourceCodeCollection final : public SourceCode {
    std::vector<std::unique_ptr<SourceCode>> _collection;
public:

    SourceCodeCollection& add(std::unique_ptr<SourceCode>);

private:
    virtual std::ostream& write(std::ostream&, size_t /*indentationLevel*/) const override;
};

/** @} */


