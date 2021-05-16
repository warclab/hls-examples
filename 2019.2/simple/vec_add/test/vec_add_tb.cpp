#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "common/xf_headers.hpp"
#include "vec_add.h"

// Pass in txt file for comparison
int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Invalid Number of Arguments!\nUsage:\n");
        fprintf(stderr, "<Executable Name> <input data path> \n");
        return -1;
    }

    /* initialize random seed: */
    srand (time(NULL));
    int random_number = rand() % 10 + 1;
    
    if (err_per > 0.0f) {
        printf("Test failed.\n");
        ret = 1;
    } else {
        printf("Test Passed!\n");
        ret = 0;
    }

    return 0;
}
