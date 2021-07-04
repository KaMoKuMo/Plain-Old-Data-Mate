
#include "collect_statements.h"
#include "trim.h"

/**
 * Collects statements within a struct scope
 *
 * \param innerStructString , e.g. "int i;\n double d;\n" from struct example{int i;\n double d;};
 * \return collection of member definitions, e.g. ["int i", "double d"];
 */
 
std::vector<std::string>
collectStatements(std::string const& innerStructString) {
    std::vector<std::string> statements;
    auto itB = innerStructString.begin();
    auto itM = itB;
    auto const itE = innerStructString.end();
    while (itM != itE) {
        if (*itM == ';') {
            statements.push_back(trim(std::string(itB, itM)));
            itB = ++itM;
        }
        else {
            ++itM;
        }
    }
    return statements;
}
