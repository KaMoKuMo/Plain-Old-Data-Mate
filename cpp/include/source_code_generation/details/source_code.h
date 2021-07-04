#pragma once

/** \addtogroup source_code_generation
 * @{
 */

#include <iostream>

/**
 * Base class for writable source code types
 **/
class SourceCode {
public:
    virtual ~SourceCode() = default;

    friend std::ostream& operator<<(std::ostream&, SourceCode const&);

    std::string asString() const;
    
    //! derived class have to write the source code with the passed in indentation level into the passed in stream and return a reference to this very stream
    virtual std::ostream& write(std::ostream&, size_t indentationLevel) const = 0;
};

/** @} */
