#include "day_four.h"

#define NUM_WINNING 10
#define NUM_CARDS 25
#define TOTAL_CARDS 199

// #define NUM_WINNING 5
// #define NUM_CARDS 10
// #define TOTAL_CARDS 6

// Part 1
int get_card_value(int *nums, int *winners) {
    int res = 0;
    int win = 0;
    int num_match = 0;
    for(int i = 0; i < NUM_CARDS; i++) {
        for(int j = 0; j < NUM_WINNING; j++) {
            if(nums[i] == winners[j]) {
                num_match++;
            }
        }
    }
    if(num_match > 0) {
        win = 1;
    }
    //printf("Matching Cards (%d): %d\n", win, num_match);
    res = win;
    for(int i = 0; i < num_match - 1; i++) {
        res *= 2;
    }
    //printf("Card Value: %d\n", res);
    return res;
}

int get_extra_cards(int *nums, int *winners) {
    int num_match = 0;
    for(int i = 0; i < NUM_CARDS; i++) {
        for(int j = 0; j < NUM_WINNING; j++) {
            if(nums[i] == winners[j]) {
                num_match++;
            }
        }
    }
    //printf("Matching Cards: %d\n", num_match);
    return num_match;
}

void update_totals(int *totals, int *donate, int card) {
    int num = donate[card];
    for(int i = 1; i <= num ; i++) {
        totals[card + i] += (1 * totals[card]);
    }
}

int run_04() {
    int res = 0;

    FILE *file;
    char *line = NULL;
    size_t len = 0;
    size_t read;

    // Open the file
    file = fopen("day_four/input.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    int donate_to_next[TOTAL_CARDS] = {0};
    int totals[TOTAL_CARDS];
    for(int i = 0; i < TOTAL_CARDS; i++) {
        totals[i] = 1;
    }

    // Read from the file
    int card_num = 0;
    while ((read = getline(&line, &len, file)) != -1) {
        //printf("%s", line);

        // Get each Game in input as string
        char *token = strtok(line, ":\n\0");
        char *card;
        while (token != 0) {
            card = token;
            token = strtok(0, ":\n\0");
        }
        //printf("%s\n", card);

        char *winners = strtok(card, "|");
        char *numbers = strtok(0, "|");

        // printf("Winners: %s\n", winners);
        // printf("Numbers: %s\n\n", numbers);

        int winning_count = 0;
        int arr_winner[NUM_WINNING] = {0};
        char *winner = strtok(winners, " ");
        while(winner != 0) {
            arr_winner[winning_count] = atoi(winner);
            winning_count++;
            winner = strtok(0, " ");
        }

        int nums_count = 0;
        int arr_nums[NUM_CARDS] = {0};
        char *num = strtok(numbers, " ");
        while(num != 0) {
            arr_nums[nums_count] = atoi(num);
            nums_count++;
            num = strtok(0, " ");
        }

        //int card_value = get_card_value(arr_nums, arr_winner);
        //res += card_value;
        int extra_cards = get_extra_cards(arr_nums, arr_winner);
        donate_to_next[card_num] = extra_cards;
        update_totals(totals, donate_to_next, card_num);
        
        // for(int j = 0; j < TOTAL_CARDS; j++) {
        //     printf("%d ", totals[j]);
        // }
        // printf("\n");
        card_num++;
    }
    // Close the file
    fclose(file);

    for(int j = 0; j < TOTAL_CARDS; j++) {
        res += totals[j];
    }
    
    return res;
}