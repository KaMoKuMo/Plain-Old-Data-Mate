#pragma once

/** \addtogroup source_code_generation
 * @{
 */

#include "source_code_generation/details/source_code.h"
#include "source_code_generation/details/variable_declaration.h"
#include "source_code_generation/details/body.h"

#include <optional>
#include <memory>
#include <vector>

/**
 * A Function is SourceCode and can model either a function declaration
 * or a function definition.
 *
 * A Function models a declaration if no body is given.
 * To generate a function declaration from a function definition \see asDeclaration()
 **/
class Function final : public SourceCode {
    std::string _returnType; //!< return type of the function
    std::string _name; //!< name of the function
    std::vector<VariableDeclaration> _arguments; //!< Argument list \see VariableDeclaration
    std::optional<Body> _body; //<! SourceCode Body if the function models a definition

public:
    Function(std::string /*returnType*/, std::string /*name*/,
             std::vector<VariableDeclaration> /*arguments*/ = {},
             std::unique_ptr<SourceCode> /*body*/ = nullptr);

    Function asDeclaration() const;

private:
    virtual std::ostream& write(std::ostream&, size_t /*indentationLevel*/) const override;
};

/** @} */
