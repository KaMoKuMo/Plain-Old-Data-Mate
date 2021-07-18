#include "source_code_generation/details/write_from_json.h"

#include "source_code_generation/details/source_code_collection.h"
#include "source_code_generation/details/source_code_line.h"

bool isFundamentalType(std::string const& type) {
    return type == "int"
        || type == "bool"
        || type == "unsigned int"
        || type == "int32_t"
        || type == "int64_t"
        || type == "uint32_t"
        || type == "uint64_t"
        || type == "size_t"
        || type == "char"
        || type == "double"
        || type == "std::string";
}

/**
 * Transforms a StructSnippets into a Function object modeling a function definition
 * for the fromJson function
 **/
Function
writeFromJson(StructSnippets const& structData) {
    std::string const variableName = "data";
    std::string const jsonName = "json";

    auto body = std::make_unique<SourceCodeCollection>();

    auto writeFundamental = [&](std::string name) {
        return std::make_unique<SourceCodeLine>(
            variableName + "." + name + " = " + jsonName + "[\"" + name + "\"];"
        );
    };
    auto writeComposite = [&](std::string name) {
        return std::make_unique<SourceCodeLine>(
            "fromJson(" + jsonName + "[\"" + name + "\"], " + variableName + "." + name + ");"
        );
    };

    for (auto const& member : structData.member) {
        if (isFundamentalType(member.type)) {
            body->add(writeFundamental(member.name));
        } else {
            body->add(writeComposite(member.name));
        }
    }

    return Function(
            "void",
            "fromJson",
            {
                VariableDeclaration("simdjson::dom::element const&", jsonName),
                VariableDeclaration(structData.name + "&", variableName)
            },
            std::move(body)
        );
}

