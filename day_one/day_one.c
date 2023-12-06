#include "day_one.h"

int run_01() {
    int res = 0;

    FILE *file;
    char *line = NULL;
    size_t len = 0;
    size_t read;

    char nums[9][6] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    // Open the file
    file = fopen("day_one/input.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    // Read from the file
    while ((read = getline(&line, &len, file)) != -1) {
        //printf("%s", line);
        int first = -1;
        int last = 0;

        char *ptr;
        for (ptr = line; *ptr != '\0'; ptr++) {
            char ch = *ptr;
            if(isdigit(ch)) {
                if(first < 0) {
                    first = ch - '0';
                    last = ch - '0';
                } else {
                    last = ch - '0';
                }
            } else {
                for(int i = 0; i < 9; i++) {
                    char *needle = nums[i];
                    if(ch == needle[0]) {
                        char *result = strstr(ptr, needle);
                        int position = result - ptr;
                        if(result != NULL && position == 0) {
                            if(first < 0) {
                                first = i + 1;
                                last = i + 1;
                            } else {
                                last = i + 1;
                            }
                        }
                    }
                }
            }
        }
        int total = (first * 10) + last;
        res += total;
    }

    // Close the file
    fclose(file);
    
    return res;
}