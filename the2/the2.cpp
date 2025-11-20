# include "the2.h"
//counting sort logic:
//COUNT range of input = #of bins, check how many of each number accordingly create that many bins
//ADD PREVIOUS
//PLACE from the back of original arr according to index created for that number and decrementing it

//radix sort:
//CHOP THE DIGIT BASED ON RADIX(BASE)like bucket sort but base10:
//use counting sort for each chopped digit
//can use any base
//https://www.youtube.com/watch?v=pJ1IQD5rv4o great video explaining all

long counting_sort(unsigned int* arr,
                   const size_t size, 
                   const unsigned int base, 
                   const unsigned int divisor){
    long iterations_cs = 0;
    
    int *count = new int[base];
    for (int i = 0; i < base; i++) {
        count[i] = 0;
    }
    
    unsigned int *output = new unsigned int[size];
    //??HOW MANY
    for (size_t i = 0; i < size; i++) {
        int digit = (arr[i] / divisor) % base;
        count[digit]++;
        iterations_cs++;
    }
    //INCREMENT FROM PREV
    for ( int i = 1; i < base; i++) {
        count[i] += count[i - 1];
        iterations_cs++;
    }
    //NEW ARRAY FROM BACK
    for (int i = size - 1; i >= 0; i--) {
        int digit = (arr[i] / divisor) % base;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
        iterations_cs++;
    }
    //COPY
    for (size_t i = 0; i < size; i++) {
        arr[i] = output[i];
        iterations_cs++;
    }
    
    delete[] count;
    delete[] output;
    
    return iterations_cs;
}

long base_x_radix_sort(unsigned int* arr,
                       const size_t size,
                       const unsigned int base2){
    int base = pow(2, base2);
    long iterations = 0;
    int max_num = 0;
    for (size_t i = 0; i < size; i++) {
        if (arr[i] > max_num) {
            max_num = arr[i];
        }
    }
    int num_buckets = 0;
    if (max_num > 0) {
        unsigned int temp = max_num;
        while (temp > 0) {
            temp /= base;  
            num_buckets++;
        }
    } else {
        num_buckets = 1;
    }
    int divisor = 1;
    for (int i = 0; i < num_buckets; i++) {
        iterations += counting_sort(arr, size, base, divisor);
        divisor *= base; 
    }
    
    return iterations;
}

