#pragma once

/** \addtogroup source_code_generation
 * @{
 */

#include "source_code_generation/details/source_code.h"
#include <string>

/**
 * Models a declarition of a variable.
 *
 * Notice since a variable declaration can be part of a function signature
 * it is not treated as a line statement.
 **/
class VariableDeclaration final : public SourceCode {
    std::string _type;
    std::string _name;
public:
    VariableDeclaration(std::string /*type*/, std::string /*name*/);

    virtual std::ostream& write(std::ostream&, size_t /*indentationLevel*/) const override;
};

/** @} */
