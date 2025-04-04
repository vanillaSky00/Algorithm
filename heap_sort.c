#include<stdio.h>

void heap_sort(int a[], int n);
void max_heapify(int a[], int n, int i);
void swap(int* x, int* y);

int main(){
    int nums1[]= {3, 2, 44, 0, 4, 12, 6, 3, -6};
    int len = sizeof(nums1)/ sizeof(nums1[0]);
    heap_sort(nums1, len);
    for(int i=0; i<len; i++){
        printf("%d,", nums1[i]);
    }
}

void heap_sort(int a[], int n){
    //get a max heap first, consider n/2 - 1, not n, more quicker
    for(int i= n/2 - 1; i>=0; i--){
        max_heapify(a, n, i); 
    }

    //swap the max and adjust to max heap again
    for(int j=n-1; j>0; j--){
        swap(&a[0], &a[j]);
        max_heapify(a, j, 0);
    }
}

// use bubble down method, in contrast to my_heapsort
void max_heapify(int a[], int n, int i){
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if(left < n && a[left] > a[largest]){
        largest = left;
    }

    if(right < n && a[right] > a[largest]){
        largest = right;
    }

    if(largest != i){
        swap(&a[largest], &a[i]);
        max_heapify(a, n, largest);
    }
}

void swap(int* x, int* y){
    int temp = *x;
    *x = *y;
    *y = temp;
}