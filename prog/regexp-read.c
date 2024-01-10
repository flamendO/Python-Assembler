#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pyas/queue.h>
#include <pyas/chargroup.h>
#include <pyas/regexp.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <regular_expression>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *regexp = argv[1];
    
    return re_read(regexp);
}
