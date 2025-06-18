#include <stdio.h>
#include <stdlib.h>


int coinChange_bottom_up(int* coins, int coinsSize, int amount){
    int* c = (int*) malloc(sizeof(int) * (amount + 1));
    for(int i = 0; i <= amount; i++){
        c[i] = INT32_MAX;
    }

    c[0] = 0;
    for(int i = 1; i <= amount; i++){
        for(int j = 0; j < coinsSize; j++){
            if(coins[j] <= i && c[i - coins[j]] != INT32_MAX){
                c[i] = (c[i] < c[i - coins[j]] + 1) ? c[i] : c[i - coins[j]] + 1;
            }
        }
    }

    int result = (c[amount] == INT32_MAX) ? -1 : c[amount];
    free(c);
    return result;
}


void coinChange_recursive_aux(int* coins, int coinsSize, int amount, int idx, int q, int* min_len, int* record){
    if(idx >= coinsSize || amount < 0) return;
    
    if(amount == 0){
        *min_len = (*min_len < q) ? *min_len : q;
        for(int i = 0; i < q; i++){
            printf("%d, ",record[i]);
        }
        printf("\n");
        return;
    }

    if(coins[idx] <= amount){
        //include this coin
        record[q] = coins[idx];
        coinChange_recursive_aux(coins, coinsSize, amount - coins[idx], idx, q + 1, min_len, record);
    }

    //exclude this coin
    coinChange_recursive_aux(coins, coinsSize, amount, idx + 1, q, min_len, record);
}

int coinChange_recursive(int* coins, int coinsSize, int amount){
    int result = INT16_MAX;
    int* record = (int*) calloc(amount, sizeof(int));
    //start from item0 to recursive, q is each cost if the money is changed all validly
    coinChange_recursive_aux(coins, coinsSize, amount, 0, 0, &result, record); 
    result = (result == INT16_MAX) ? -1 : result;
    return result;
}

#define TEST(name) test = name;
#define ASSERT(expr) \
  do { \
    if (!(expr)) { \
      fprintf(stderr, "Assertion failed: %s, file %s, line %d\n", #expr, __FILE__, __LINE__); \
      exit(1); \
    } else { \
      putchar('.'); \
    } \
  } while(0)

//unit test
void test_basic_cases() {
    int test1[3] = {1,2,5}, test2[1] = {2}, test3[1] = {1}, test4[4] = {186,419,83,408};
    printf("test coinChange_recursive\n");
    ASSERT(coinChange_recursive(test1, 3, 11) == 3);  printf("\nPassed test1.\n");    
    ASSERT(coinChange_recursive(test2, 1, 3) == -1); printf("\nPassed test2.\n");     
    ASSERT(coinChange_recursive(test3, 1, 0) == 0); printf("\nPassed test3.\n");
    printf("test coinChange_bottom_up\n");
    ASSERT(coinChange_bottom_up(test1, 3, 11) == 3);  printf("\nPassed test1.\n");    
    ASSERT(coinChange_bottom_up(test2, 1, 3) == -1); printf("\nPassed test2.\n");     
    ASSERT(coinChange_bottom_up(test3, 1, 0) == 0); printf("\nPassed test3.\n");
    ASSERT(coinChange_bottom_up(test4, 4, 6249) == 20); printf("\nPassed test4.\n");
}


int main(){
    const char* test = "";

    TEST("basic_cases") test_basic_cases();

    printf("\n********  All tests passed.  ********\n");
    return 0;
}


/**
 * bad code:
 * 
int coinChange(int* coins, int coinsSize, int amount) {
    int* c = (int*) malloc(sizeof(int) * (10001));
    for(int i = 0; i <= amount; i++){
        c[i] = INT32_MAX;
    }

    c[0] = 0;
    for(int i = 0; i < coinsSize; i++){
        if(coins[i] > 10000) continue;
        c[coins[i]] = 1;
    }

    for(int i = 1; i <= amount; i++){
        int current_amount = i;
        int q = INT32_MAX;
        for(int j = 0; j < coinsSize; j++){
            if(coins[j] <= current_amount){
                int lsub_sol = c[current_amount - coins[j]];
                int rsub_sol = c[coins[j]];
                if( lsub_sol != INT32_MAX && rsub_sol != INT32_MAX){
                    q = (q < lsub_sol + rsub_sol) ? q : lsub_sol + rsub_sol;
                }
            }
        }
        c[i] = q;
    }

    int result = (c[amount] == INT32_MAX) ? -1 : c[amount];
    free(c);
    return result;
}
 */