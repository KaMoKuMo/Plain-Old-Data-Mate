#include "file_parsing/details/calculate_surrounding_namespaces.h"

#include <algorithm>

/**
 * Calculates the namespaces containing the given position.
 * The resulting namespaces are sorted such that the first
 * namespace in the result range, will be the outtermost namespace.
 * Since namespace ranges don't interleave, the result range
 * can unambigously be interpreted.
 * The namespace vector might be shuffled.
 **/
std::vector<std::string>
calculateSurroundingNamespaces(size_t position, std::vector<NamespaceData>& namespaces) {

    //search for every namespaces containing the position
    auto const itM = std::partition(
                         namespaces.begin(), namespaces.end(),
                         [&](NamespaceData const& namespaceData)
                         {
                            return namespaceData.range.start < position
                                && namespaceData.range.end > position;
                         }
                     );

    //Since namespaces don't interleave and all namespaces in the range
    //begin() -> itM contain a common position, they contain each other.
    //Sorting by their starting position sortes them such that the
    //first namespace will be the outtermost namespace.
    std::sort(namespaces.begin(), itM,
              [](auto const& lhs, auto const& rhs)
              {
                  return lhs.range.start < rhs.range.start;
              });

    //extract the names
    std::vector<std::string> result;
    std::transform(
        namespaces.begin(), itM,
        std::back_inserter(result),
        [](auto const& namespaceData) {
            return namespaceData.name;
        }
    );
    return result;
}
