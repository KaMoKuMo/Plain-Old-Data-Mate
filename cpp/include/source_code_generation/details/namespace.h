#pragma once

/** \addtogroup source_code_generation
 * @{
 */

#include "source_code_generation/details/source_code.h"
#include "source_code_generation/details/body.h"

/**
 * A Namespace is SourceCode containing other source code
 **/
class Namespace final : public SourceCode {
    std::string _name; //!< name of the namespace
    Body _body; //<! SourceCode Body

public:
    Namespace(std::string /*name*/, Body /*body*/);

private:
    virtual std::ostream& write(std::ostream&, size_t /*indentationLevel*/) const override;
};

/** @} */

