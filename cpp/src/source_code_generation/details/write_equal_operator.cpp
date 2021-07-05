#include "source_code_generation/details/write_equal_operator.h"

#include "source_code_generation/details/write_comparison_operator.h"


/**
 * Transforms a StructSnippets into a Function object modeling a function definition
 * for the equal operator.
 **/
Function
writeEqualOperator(StructSnippets const& structData) {
    return writeComparisonOperator(structData,
                                   "==",
                                   "&&",
                                   "true");
}
