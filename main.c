#include <stdio.h>
#include <stdlib.h>
#include "day_one/day_one.c"
#include "day_two/day_two.c"
#include "day_three/day_three.c"
#include "day_four/day_four.c"

int main(int argc, char *argv[]) {
    int day = 0;

    // Check if the user has passed any command line options
    if (argc > 1) {
        // Print the command line options
        for (int i = 1; i < argc; i++) {
            day = atoi(argv[i]);
            printf("Advent Of Code - Day: %d\n", day);
        }
    } else {
        printf("No command line options passed.\n");
        return 1;
    }

    int res;
    switch(day) {
        case 1:
            res = run_01();
            break;
        case 2:
            res = run_02();
            break;
        case 3:
            res = run_03();
            break;
        case 4:
            res = run_04();
            break;
        default:
            printf("No day selected!\n");
            return 1;
    }
    printf("\nResult: %d\n", res);
    return 0;
}