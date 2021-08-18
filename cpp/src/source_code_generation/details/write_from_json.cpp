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
bool isProblematicType(std::string const& type) {
    return type == "short"
        || type == "short int"
        || type == "signed short int"
        || type == "unsigned short"
        || type == "unsigned short int"
        || type == "signed"
        || type == "int"
        || type == "signed int"
        || type == "unsigned"
        || type == "unsigned int"
        || type == "long int"
        || type == "signed long"
        || type == "signed long int"
        || type == "unsigned long"
        || type == "unsigned long int"
        || type == "long long"
        || type == "long long int"
        || type == "signed long long"
        || type == "signed long long int"
        || type == "unsigned long long"
        || type == "unsigned long long int";
}

/**
 * Transforms a StructSnippets into a Function object modeling a function definition
 * for the fromJson function
 **/
Expected<Function, std::string>
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
        if (isProblematicType(member.type)) {
            return Unexpected(member.type + " is not guaranteed to work for simdjson. Use fixed size integer");

        }
        else if (isFundamentalType(member.type)) {
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

