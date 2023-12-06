#include "day_two.h"

const int MAX_R = 12;
const int MAX_G = 13;
const int MAX_B = 14;

void print_set(int *set) {
    printf("> Set: ");
    for(int i = 0; i < 3; i++) {
        printf("%d ", set[i]);
    }
    printf("\n");
}

int is_possible(int *set) {
    return set[0] <= MAX_R && set[1] <= MAX_G && set[2] <= MAX_B;
}

int get_power(int *set) {
    int res = 1;
    for(int i = 0; i < 3; i++) {
        res *= set[i];
    }
} 

int run_02() {
    int res = 0;

    FILE *file;
    char *line = NULL;
    size_t len = 0;
    size_t read;

    // Open the file
    file = fopen("day_two/input.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    int game_count = 1;
    // Read from the file
    while ((read = getline(&line, &len, file)) != -1) {
        // Get each Game in input as string
        char *token = strtok(line, ":");
        char *game;
        while (token != 0) {
            // Use of strtok
            // go through other tokens
            game = token;
            token = strtok(0, ":");
        }

        char *save_set = NULL;
        int valid_game = 1;
        int maximums[3] = {0};
        char *set = strtok_r(game, ";\n", &save_set);
        while (set != 0) {
            int set_i[3] = {0};
            char *save_set_vals = NULL;
            char* set_vals = strtok(set, ",");
            while(set_vals != 0) {
                int val = atoi(set_vals);
                if(strstr(set_vals, "red") != NULL) {
                    set_i[0] = val;
                    if(val > maximums[0]) {
                        maximums[0] =  val;
                    }
                } else if(strstr(set_vals, "green") != NULL) {
                    set_i[1] = val;
                    if(val > maximums[1]) {
                        maximums[1] =  val;
                    }
                } else {
                    set_i[2] = val;
                    if(val > maximums[2]) {
                        maximums[2] =  val;
                    }
                }
                set_vals = strtok(0, ",");
            }
            // PART 1
            // if(!is_possible(set_i)){
            //     valid_game = 0;
            // }
            set = strtok_r(0, ";\n", &save_set);
        }
        // Part 1
        // if(valid_game) {
        //     res += game_count;
        // }

        //Part 2
        int power = get_power(maximums);
        res += power;
        game_count++;
    }
    // Close the file
    fclose(file);
    
    return res;
}