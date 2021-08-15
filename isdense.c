// Bash loadable that checks if an array is dense
// For more information and install instructions, see README.md

#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "bashtypes.h"
#include "shell.h"
#include "builtins.h"
#include "common.h"

int exactly_one(WORD_LIST *list) {
    return list && !list->next;
}

int is_dense(ARRAY *array) {
    // works also for empty arrays, since they have max_index = -1
    return array->max_index < array->num_elements;
}

int isdense_builtin(WORD_LIST *list) {
    if (!exactly_one(list)) {
        builtin_usage();
        return EX_USAGE;
    }   
    char *arrayname = list->word->word;
    SHELL_VAR *var = find_variable(arrayname);
    if (!var || !array_p(var)) {
        builtin_error("%s: Not an array", arrayname);
        return EXECUTION_FAILURE;
    }
    return is_dense(array_cell(var)) ? EXECUTION_SUCCESS : EXECUTION_FAILURE;
}

char *isdense_doc[] = {
    "Check if an indexed array is dense.",
    "",
    "Exit status:",
    "Returns success if ARRAY is a dense indexed array;",
    "fails if ARRAY is sparse or an invalid argument is given.",
    (char *)NULL
};

struct builtin isdense_struct = {
    "isdense",
    isdense_builtin,
    BUILTIN_ENABLED,
    isdense_doc,
    "isdense ARRAY",
    0
};
