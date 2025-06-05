#include<stdio.h>
#include<time.h>
#include<stdlib.h>
int randomized_partition(int a[], int p, int r);
int partition(int a[], int p, int r);
int randomized_select(int a[], int len, int i);
int randomized_select_recursive(int a[], int p, int r, int i);
void swap(int* a, int* b);

int main(){
    int nums1[]= {3, 2, 44, 0, 4, 12, 6, 3, -6};
    int len = sizeof(nums1)/sizeof(nums1[0]);

    for(int i=1; i<=len; i++){
        printf("The %d smallest number: %d\n", i, randomized_select(nums1, len, i));
    }
}


int randomized_select(int a[], int len, int i){
    srand(time(NULL));
    if((i<1) || (i>len)){
        perror("Invalid input");
        exit(EXIT_FAILURE);
    }
    return randomized_select_recursive(a, 0, len-1, i);
}

int randomized_select_recursive(int a[], int p, int r, int i){
    if(p == r){
        return a[p];// 1 <= i <= r-p+1, if p=r then i = 1
    }
    int q = randomized_partition(a, p, r);//pivot large then q-1 elements
    int k = q - p + 1;//relative ranking of the pivot in the subarray;
    if(i == k){
        return a[q];//the pivot is the answer
    }
    //only consider one part of the array
    else if(i < k){// if i is in the left of the pivot
        return randomized_select_recursive(a, p, q-1, i);
    }
    else{//k = pivot = the ranking, so right part is larger have to substract left number
        return randomized_select_recursive(a, q+1, r, i-k);//search the i-k'th largest in the right 
    }
}

int randomized_partition(int a[], int p, int r){
    int i = p + rand() % (r - p + 1);
    swap(&a[i], &a[r]);
    return partition(a, p, r);
}

int partition(int a[], int p, int r){
    int x = a[r];//pivot
    int i = p-1;
    for(int j=p; j<r; j++){
        if(a[j] <= x){
            i++;
            swap(&a[i], &a[j]);
        }
    }
    swap(&a[i+1], &a[r]);
    return i + 1;
}

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}