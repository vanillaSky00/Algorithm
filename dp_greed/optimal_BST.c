#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
/**
 * @brief Computes the optimal binary search tree for given probabilities of keys and dummy keys.
 *
 * @param p Array of probabilities for actual keys (1-based indexing: p[1] to p[n]).
 * @param q Array of probabilities for dummy keys (1-based indexing: q[0] to q[n]).
 * @param n Number of actual keys.
 * @param expected_cost The p to e[i][j], minimum expected cost for keys i to j.
 * @param weight The p to w[i][j], cumulative probability weight for keys i to j.
 * @param root_result The p to r[i][j], the optimal root index for subtree from i to j.
 */
void optimal_bst(float* p, float* q, int n, float*** expected_cost, float*** weight, int*** root_result){

    //indices 0‥n and one extra dummy row/col (n+1) 
    int sz = n + 2;    
    float** e = (float**) malloc(sizeof(float*) * sz);
    float** w = (float**) malloc(sizeof(float*)* sz);
    int** root = (int**) malloc(sizeof(int*) * sz);
    for(int i = 0; i <= n + 1; i++){
        e[i] = (float*) calloc(sz, sizeof(float));
        w[i] = (float*) calloc(sz, sizeof(float));
        root[i] = (int*) calloc(sz, sizeof(int));
    }

    //base cases
    for(int i = 1; i <= n + 1; i++){
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }

    //len of subproblems(len of containing keys)
    for(int l = 1; l <= n; l++){
        //subtree from ki to kj
        for(int i = 1; i <= n - l + 1; i++){
            //last index for this subproblem
            int j = i + l - 1;
            e[i][j] = INFINITY;
            w[i][j] = w[i][j - 1] + p[j] + q[j];
            
            //kr selected as subtree in ki,kj -> ki...kr-1, kr, kr+1...kj
            for(int r = i; r <= j; r++){
                float cost = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if(cost < e[i][j]){
                    e[i][j] = cost;
                    root[i][j] = r;
                }
            }
        }
    }

    //return value
    *expected_cost = e;
    *weight = w;
    *root_result = root;
}


/** print */

static void print_float_tri(const char *label, float **tbl, int n, int dummy)
{
    printf("%s table:\n", label);
    printf("j\\i ");
    for (int i = 1; i <= n + dummy; ++i) printf("%5d ", i);
    putchar('\n');

    for (int j = n; j >= 0; --j) {
        printf("%2d  ", j);
        for (int i = 1; i <= j + dummy; ++i)
            printf("%5.2f ", tbl[i][j]);
        putchar('\n');
    }
}

static void print_int_tri(const char *label, int **tbl, int n)
{
    printf("%s table:\n", label);
    printf("j\\i ");
    for (int i = 1; i <= n + 1; ++i) printf("%5d ", i);
    putchar('\n');

    for (int j = n; j >= 1; --j) {
        printf("%2d  ", j);
        for (int i = 1; i <= j; ++i)
            printf("%5d ", tbl[i][j]);
        putchar('\n');
    }
}

/**
 * why n + 2
 * 0-based access to q[0]
 * 1-based access to p[1..n]
 * Accesses like e[r + 1][j] → if r == n, then r + 1 == n + 1, so you must allow up to n + 1
 */
int main(void){
    // #define LEN (6)
    // float p[LEN + 1] = {0, 0.15, 0.10, 0.05, 0.10, 0.20};//p[0] is unused
    // float q[LEN + 1] = {0.05, 0.10, 0.05, 0.05, 0.05, 0.10};

    enum { LEN = 7 };
    float p[LEN + 1] = {0, 0.04, 0.06, 0.08, 0.02, 0.10, 0.12, 0.14};//p[0] is unused
    float q[LEN + 1] = {0.06, 0.06, 0.06, 0.06, 0.05, 0.05, 0.05, 0.05};

    float** expected_cost;
    float** weight;
    int** root_result;
   
    optimal_bst(p, q, LEN, &expected_cost, &weight, &root_result);

    print_float_tri("e",    expected_cost, LEN, 1);   putchar('\n');
    print_float_tri("w",    weight, LEN, 1);   putchar('\n');
    print_int_tri  ("root", root_result, LEN);


    for(int i = 0; i <= LEN; i++){
        free(expected_cost[i]); free(weight[i]); free(root_result[i]);
    }
    free(expected_cost); free(weight); free(root_result);

    return 0;
}


