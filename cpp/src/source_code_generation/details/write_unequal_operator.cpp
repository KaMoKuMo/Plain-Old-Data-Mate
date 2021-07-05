#include "source_code_generation/details/write_unequal_operator.h"

#include "source_code_generation/details/write_comparison_operator.h"


/**
 * Transforms a StructSnippets into a Function object modeling a function definition
 * for the unequal operator.
 **/
Function
writeUnequalOperator(StructSnippets const& structData) {
    return writeComparisonOperator(structData,
                                   "!=",
                                   "||",
                                   "false");
}

