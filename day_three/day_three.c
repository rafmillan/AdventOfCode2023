#include "day_three.h"

struct part {
    int num;
    int start;
    int end;
    int line;
};

int is_part(char *str) {
    int res = 0;
    for(int i = 0; str[i] != '\0'; i++) {
        char ch = str[i];
        if (ch != '.') {
            if(ispunct(ch)) {
                res = 1;
                return res;
            }
        }
    }
}

int get_gear_ratios(struct part *gears, struct part *nums, int gear_num, int nums_num) {
    int res = 0;
    for(int i = 0; i < gear_num; i++) {
        // find adjacent parts for gear
        int prev_line = gears[i].line - 1;
        int next_line = gears[i].line + 1;
        int num_adjacent = 0;
        int prod = 1;
        // Line - 1
        if(gears[i].line > 0) {
            for(int j = 0; j < nums_num; j++) {
                if(nums[j].line == prev_line) {
                    int adjacent = 0;
                    for(int x = nums[j].start - 1; x <= nums[j].end; x++) {
                        if(gears[i].start > 0 && x == gears[i].start - 1) {
                            adjacent = 1;
                            break;
                        } else if(x == gears[i].start) {
                            adjacent = 1;
                            break;
                        } else if(gears[i].start < 149 && x == gears[i].start) {
                            adjacent = 1;
                            break; 
                        }
                    }
                    if (adjacent) {
                        prod *= nums[j].num;
                        num_adjacent++;
                    }
                }
            }
        }
        // Line
        for(int j = 0; j < nums_num; j++) {
            if(nums[j].line == gears[i].line) {
                int prev = gears[i].start - 1;
                int next = gears[i].start + 1;
                int adjacent = 0;
                if(prev >= 0 && nums[j].end == prev) {
                    adjacent = 1;
                } else if (next <= 149 && nums[j].start == next) {
                    adjacent = 1;
                }
                if (adjacent) {
                    prod *= nums[j].num;
                    num_adjacent++;
                }
            }
            
        }
        // Line + 1
        if(gears[i].line < 149) {
            for(int j = 0; j < nums_num; j++) {
                if(nums[j].line == next_line) {
                    int adjacent = 0;
                    for(int x = nums[j].start -1; x <= nums[j].end; x++) {
                        if(gears[i].start > 0 && x == gears[i].start - 1) {
                            adjacent = 1;
                            break;
                        } else if(x == gears[i].start) {
                            adjacent = 1;
                            break;
                        } else if(gears[i].start < 149 && x == gears[i].start) {
                            adjacent = 1;
                            break;
                        }
                    }
                    if (adjacent) {
                        prod *= nums[j].num;
                        num_adjacent++;
                    }
                }
            }
        }
        if(num_adjacent == 2) res += prod;

    }
    return res;
}

int run_03() {
    int res = 0;

    FILE *file;
    char *line = NULL;
    size_t len = 0;
    size_t read;

    // Open the file
    file = fopen("day_three/input.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    char schematic[150][150] = {{""}};

    // Read from the file
    int line_num = 0;
    while ((read = getline(&line, &len, file)) != -1) {
        strcpy(schematic[line_num], line);
        line_num++;
    }
    strcpy(schematic[line_num], "\0");

    int part_num = 0;
    struct part parts[2048] = {{0,0,0,0}};

    int gear_num = 0;
    struct part gears[2048] = {{0,0,0,0}};

    // PART 1:
    for(int k = 0; k < 150; k++){
        if(strcmp(schematic[k], "\0") == 0) break;
    
        int start = -1;
        int end = -1;
        char num[150] = "";
    
        for(int j = 0; j < 150; j++){
            char ch = schematic[k][j];

            // PART 2
            if(ch == '*'){
                struct part gear;
                gear.start = j;
                gear.line = k;
                gears[gear_num] = gear;
                gear_num++;
            }
            // end Part 2*

            if(isdigit(ch)) {
                if (start < 0) start = j;
                strncat(num, &ch, 1);
            } else {
                end = j - 1;
                if(strcmp(num, "")) {
                    int size = end - start + 1;
                    char str[150];
                    //printf("%s (%d, %d)\n", num, start, end);

                    // Part 2
                    struct part current_part;
                    current_part.num = atoi(num);
                    current_part.start = start;
                    current_part.end = end;
                    current_part.line = k;

                    parts[part_num] = current_part;
                    part_num++;
                    // End Part 2*

                    // Check adjacent symbols;
                    // Check line - 1
                    if(k > 0) {
                        int n_start = start;
                        int n_end = end;
                        int pad = 2;
                        if(start > 0) {
                            n_start -= 1;
                        } else {
                            pad -= 1;
                        }
                        strncat(str, &schematic[k-1][n_start], size+pad); 
                    }
                    // Check current line
                    int n_start = start;
                    int n_end = end;
                    if(start > 0) {
                        n_start -= 1;
                        strncat(str, &schematic[k][n_start], 1);
                    }
                    if(end < 149) {
                        n_end += 1;
                        strncat(str, &schematic[k][n_end], 1);
                    }
                    // check line + 1
                    if(k < 149) {
                        int n_start = start;
                        int n_end = end;
                        int pad = 2;
                        if(start > 0) {
                            n_start -= 1;
                        } else {
                            pad -= 1;
                        }
                        strncat(str, &schematic[k+1][n_start], size+pad); 
                    }
                    // if(is_part(str)) {
                    //     res += atoi(num);
                    // }
                    strcpy(str, "");
                }
                strcpy(num, ""); 
                start = -1;
                end = -1;
            }
        }
    }

    // PART 2
    res = get_gear_ratios(gears, parts, gear_num, part_num);

    // Close the file
    fclose(file);
    
    return res;
}