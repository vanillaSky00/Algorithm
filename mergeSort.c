#include<stdio.h>

void merge_sort(int a[], int len);
void merge_sort_recurssion(int a[], int l, int r);
void merge_sort_arrays(int a[], int l, int m, int r);

int main(){
    int arr[] = {9, 4, 8, 1, 7, 0, 3, 2, 5, 6};
    int len = sizeof(arr)/sizeof(arr[0]);

    merge_sort(arr, len);
    for(int i=0; i<len; i++){
        printf("%d, ", arr[i]);
    }
}


void merge_sort(int a[], int len){
    merge_sort_recurssion(a, 0, len-1);
}

void merge_sort_recurssion(int a[], int l, int r){
    if(l >= r){
        return;
    }

    int m = l + (r - l)/ 2;

    merge_sort_recurssion(a, l, m);  //sort left
    merge_sort_recurssion(a, m+1, r);//sort right

    merge_sort_arrays(a, l, m, r);   //combine
}

void merge_sort_arrays(int a[], int l, int m, int r){
    int left_len = m - l + 1;
    int right_len = r -  m;

    int left_arr[left_len];
    int right_arr[right_len];

    int i, j, k;

    for(i=0; i<left_len; i++){
        left_arr[i] = a[l+i];
    }
    for(j=0; j<right_len; j++){
        right_arr[j] = a[m+1+j];
    }
    // put back into array from l to r -> a[l] to a[r]
    for(i=0, j=0, k=l; k<=r; k++){
        //we either put element back from the left arr or right arr
        //if we run out of left then put right one back to
        //but if right one run out first, len we do not have to compare left_arr[i] < right_arr[j]
        //just put back right 

        if((i < left_len) && 
           (j >= right_len || left_arr[i] < right_arr[j])){
            a[k] = left_arr[i];
            i++;
        }
        else{
            a[k] = right_arr[j];
            j++;
        }
    }
}