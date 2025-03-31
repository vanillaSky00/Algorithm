#include<stdio.h>

#include<time.h>
#include<stdlib.h>

void swap(int *i, int *j){
    int temp = *i;
    *i = *j;
    *j = temp;
}

//Always the last element
int partition(int arr[], int l, int r){
    int pivot = arr[r];
    int i = l - 1;
    for(int j = l; j < r; j++){
        if(arr[j] <= pivot){
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i+1], &arr[r]);
    
    return i + 1;
}

void quicksort(int arr[], int l, int r){
    if(l < r){
        int p = partition(arr, l, r);
        quicksort(arr, l, p - 1);
        quicksort(arr, p + 1, r);
    }
}

//Always the last element
int randomized_partition(int arr[], int l, int r){
    int i = l + rand() % (r - l + 1);
    swap(&arr[r], &arr[i]);
    return partition(arr, l, r);
}

void randomized_quicksort(int arr[], int l, int r){
    if(l < r){
        int p = randomized_partition(arr, l, r);
        randomized_quicksort(arr, l, p - 1);
        randomized_quicksort(arr, p + 1, r);
    }
}

int main(){
    srand(time(NULL));
    int arr[8] = {2,8,7,1,3,5,6,4};
    int len = sizeof(arr)/sizeof(arr[0]);
    quicksort(arr, 0, len - 1);
    for(int i =0; i < len; i++){
        printf("%d,", arr[i]);
    }

    printf("\n");

    int brr[8] = {2,8,7,1,3,5,6,4};
    randomized_quicksort(brr, 0, len - 1);
    for(int i =0; i < len; i++){
        printf("%d,", brr[i]);
    }
}

//Randomized?