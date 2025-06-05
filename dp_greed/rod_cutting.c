#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
//p = price table, n = length we want know the optimal price
int max(int x, int y);
int cut_rod(int *p, int n, int* time);
int memoized_cut_rod(int* p, int n, int* time);
int memoized_cut_rod_aux(int *p, int n, int* r, int* time);
int bottom_up_cut_rod(int*p, int n, int* time);

//top-down with memoization

int memoized_cut_rod(int* p, int n, int* time){
    int* r = (int*) malloc(sizeof(int) * (n+1));
    for(int i = 0; i <= n; i++){
        r[i] = INT32_MIN;
    }
    int result = memoized_cut_rod_aux(p, n, r, time);
    free(r);
    return result;
}

int memoized_cut_rod_aux(int *p, int n, int* r, int* time){
    (*time)++;
    if(r[n] >= 0){
        return r[n];
    }
    if(n == 0){
        return 0;
    }

    int q = INT32_MIN;
    for(int i = 1; i <= n; i++){
        q = max(q, p[i] + memoized_cut_rod_aux(p, n - i, r, time));
    }
    r[n] = q;
    return q;
}

//bottom-up
int bottom_up_cut_rod(int*p, int n, int* time){
    int *r = (int*) malloc(sizeof(int) * (n+1));
    r[0] = 0;
    for(int j = 1; j <= n; j++){ //rod length increasing
        int q = INT32_MIN;
        for(int i = 1; i <= j; i++){
            (*time)++;
            q = max(q, p[i] + r[j - i]);
        }
        r[j] = q;
    }
    
    int result = r[n];
    free(r);
    return result;
}


//not efficient 2^n
int cut_rod(int *p, int n, int* time){
    (*time)++; // count the calling
    if(n == 0){
        return 0;
    }

    int q = INT32_MIN;
    for(int i = 1; i <= n; i++){// 1 <= i <= n
        q = max(q, p[i] + cut_rod(p, n - i, time));
    }

    return q;
}

int max(int x, int y){
    return (x > y) ? x : y;
}

int main(){
    //p[0] is dummy head
    int p[] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    int len = sizeof(p) / sizeof(p[0]);
    int time_org = 0; 
    int time_top = 0;
    int time_bottom = 0;

    for(int s=0; s<len; s++){
        printf("r%d optimal_price: %d\n", s, cut_rod(p, s, &time_org));
        printf("time_org: %d\n", time_org);

        printf("r%d optimal_price: %d\n", s, memoized_cut_rod(p, s, &time_top));
        printf("time_top: %d\n", time_top);

        printf("r%d optimal_price: %d\n", s, bottom_up_cut_rod(p, s, &time_bottom));
        printf("time_bottom: %d\n", time_bottom);
    }
    return 0;
}

//improved could be bound the input n to be 0<= n <= len_price_table
