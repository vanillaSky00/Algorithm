#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BAG_CAPACITY 50
#define ITEM_NUM 3
#define DEBUG_LOG(msg,...)
//#define DEBUG_LOG(msg,...) printf("debug: " msg "\n" , ##__VA_ARGS__)

/* ---------- helpers ----------------------------------------------------- */

static int* sort_by_ratio(int* price, int* weight, int len);
static inline float value_ratio(int price, int weight) {return weight ? (float)price / weight: 0.0f;}
//item1 > item2 return true
static bool comp(int* price, int* weight, int item1, int item2){
    return value_ratio(price[item1], weight[item1]) > value_ratio(price[item2], weight[item2]);
}

/* ---------- core -------------------------------------------------------- */

void greedy_fractional_knapsack(int* price, int* weight, int len, int* whole_items, int* whole_cnt, 
                                int *frac_item, float *frac_take, float *total_value){
    //greedy setup
    int* items = sort_by_ratio(price, weight, len);

    int used_capacity = 0;
    float selected_value = 0.0;
    int picked_cnt = 0;

    //will take 0 (the highest, greedy)
    for(int k = 0;  k < len; k++){
        int idx = items[k];

        if((used_capacity + weight[items[idx]]) <= BAG_CAPACITY ){
            whole_items[picked_cnt++] = idx;
            used_capacity += weight[idx];
            selected_value += (float)price[idx];
            DEBUG_LOG("items: %d, w: %d, p: %d, selected_value: %f", \
                idx, weight[idx], price[idx], selected_value);
        }
        else{
            //the remaining space can only take fractional item
            int remaining_capacity = BAG_CAPACITY - used_capacity;
            *frac_item = idx;
            *frac_take = (float)remaining_capacity / weight[idx];
            selected_value += price[items[idx]] * (*frac_take);
            break;
        }
    }

    free(items);
    *whole_cnt = picked_cnt;
    *total_value = selected_value;
}

int* sort_by_ratio(int* price, int* weight, int len){
    int* items = (int*) malloc(sizeof(int) * len);
    for(int i = 0; i < len; i++){
        items[i] = i;
    }

    //sort the item by value_ratio comp
    for(int i = 1; i < len; i++){
        int temp = items[i];
        int j;
        //if i > j then swap because of descending order
        for(j = i - 1; (j >= 0) && comp(price, weight, items[temp], items[j]); j--){
                items[j + 1] = items[j];
        }
        items[j + 1] = temp;
    }
    return items;
}

int main(int args, char* argv[]){
    int price[ITEM_NUM] = {60, 100, 120}; 
    int weigth[ITEM_NUM] = {10, 20, 30};

    int whole[ITEM_NUM];
    int whole_cnt = 0;
    int part_id;
    float part_frac, total;

    greedy_fractional_knapsack(price, weigth, ITEM_NUM, whole, &whole_cnt,
                                &part_id, &part_frac, &total);

    printf("Whole items : ");
    for (int i = 0; i < whole_cnt; ++i) printf("%d ", whole[i]);
    printf("\n");

    if (part_id != -1)
        printf("Fractional : %.2f of item %d\n", part_frac, part_id);

    printf("Total value : %.2f\n", total);
}