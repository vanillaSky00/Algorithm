#include<stdio.h>
#include<stdlib.h>

//need to revise, no need to add a new struct heap
typedef struct heap{
    int* heap_h;
    int capacity;
    int heap_size;
} heap;

heap* heapSort(int a[], int len);
heap* build_maxHeap(int a[], int size);
void max_heapify(heap* h, int i);
void swap(int* a, int* b);


int main(){
    int nums1[]= {3, 2, 44, 0, 4, 12, 6, 3, -6};
    int len = sizeof(nums1)/sizeof(nums1[0]);
    heap* h = heapSort(nums1, len);

    for(int i=0; i<len; i++){
        printf("%d,", h->heap_h[i]);
    }
    return 0;
}


heap* heapSort(int a[], int len){
    heap* h = build_maxHeap(a, len);
    for(int i=len-1; i>0; i--){
        swap(&h->heap_h[0], &h->heap_h[i]);
        h->heap_size--;
        max_heapify(h, 0);
    }
    return h;
}

heap* build_maxHeap(int a[], int size){
    heap* h = (heap*)malloc(sizeof(heap));
    h->heap_size = size;
    h->heap_h = (int*)malloc(sizeof(int) * h->heap_size);
    for(int i=0; i<h->heap_size; i++){
        h->heap_h[i] = a[i];
    }
    for(int i=h->heap_size/2 - 1; i>=0; i--){
        max_heapify(h, i);
    }
    return h;
}

void max_heapify(heap* h, int i){
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;
    if(left < h->heap_size && h->heap_h[left] > h->heap_h[largest]){
        largest = left;
    }
    if(right < h->heap_size && h->heap_h[right] > h->heap_h[largest]){
        largest = right;
    }

    if(largest != i){
        swap(&(h->heap_h[largest]), &(h->heap_h[i]));
        max_heapify(h, largest);
    }
}

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}