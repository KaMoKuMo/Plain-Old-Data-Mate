#include "source_code_generation/details/source_code_collection.h"
#include "source_code_generation/details/line_fragment.h"

SourceCodeCollection&
SourceCodeCollection::add(std::unique_ptr<SourceCode> sourceCode) {
    if (sourceCode)
        _collection.emplace_back(std::move(sourceCode));
    return *this;
}

std::ostream&
SourceCodeCollection::write(std::ostream& o, size_t indentationLevel) const {
    for (auto const& sourceCode : _collection) {
        sourceCode->write(o, indentationLevel);
    }
    return o;
}


