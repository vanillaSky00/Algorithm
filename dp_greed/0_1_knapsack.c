#include <stdio.h>
#include <stdlib.h>

#define BAG_CAPACITY 50
#define ITEM_NUM 3
/**
 * greedy alg is not applied to 0/1 knapsack problem 
 */


static inline int max(int x, int y) {return (x > y) ? x : y;}

int recursive_01knapsack(int* price, int* weight, int len, int capacity){
    if(capacity == 0 || len == 0){
        return 0;
    }

    int pick = 0;
    //pick nth item
    if(weight[len - 1] <= capacity){
        pick = price[len - 1] + recursive_01knapsack(price, weight, len - 1, capacity - weight[len - 1]);
    }
    
    //do not pick nth item
    int not_pick = recursive_01knapsack(price, weight, len - 1, capacity);

    return max(pick, not_pick);
}

void dp_01knapsack(int* price, int* weight, int len, int* selected_items, int* selected_cnt, 
                    float *total_value){
    int* dp = (int*) malloc(sizeof(int) * ITEM_NUM);
    for(int i = 0; i < ITEM_NUM; i++){
        dp[i] = -1;
    }  
}

int main(int args, char* argv[]){
    int price[ITEM_NUM] = {60, 100, 120}; 
    int weigth[ITEM_NUM] = {10, 20, 30};

    int select[ITEM_NUM];
    int select_cnt = 0;

    int total = recursive_01knapsack(price, weigth, ITEM_NUM, BAG_CAPACITY);

    // printf("Whole items : ");
    // for (int i = 0; i < whole_cnt; ++i) printf("%d ", whole[i]);
    // printf("\n");

    // if (part_id != -1)
    //     printf("Fractional : %.2f of item %d\n", part_frac, part_id);

    printf("Total value : %d\n", total);
}


