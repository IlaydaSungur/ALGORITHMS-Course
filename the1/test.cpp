#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>

#include "the1.h"


void random_input_generator(int*& arr,
                            const std::pair<size_t, size_t>& table_size,
                            const int minimum_value,
                            const int interval){
    arr = new int [table_size.first * table_size.second];
    for(int idx=0; idx < (table_size.first * table_size.second); idx++)
        arr[idx] = minimum_value + (random() % interval);
}


bool check_sorted(const int* arr,
                  const size_t size){
    for(int idx=1; idx < size; idx++)
        if(arr[idx] < arr[idx-1]) return false;
    return true;
}
    

void random_test(size_t n = 4, size_t m = 4){
    size_t size = m * n;
    int* input_array;
    int min_value = 0;
    int interval = ((1 << 14) - 1);

    random_input_generator(input_array, {n, m}, min_value, interval);

    std::cout << "Size: " << size << std::endl <<
                 "Table size: (" << n << ", " << m  << ")" << std::endl <<
                 "Array elements: {";
    for(int idx=0; idx < size; idx++)
        std::cout << input_array[idx] << (idx != size-1 ? ", " : "}");
    std::cout << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    long swap_count = sort_with_young_tableau(input_array, size, std::make_pair(n, m));
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Swap: " << swap_count << std::endl <<
                 "Elapsed time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() << " ns" << std::endl <<
                 "Is sorted: " << (check_sorted(input_array, size) ? "Yes" : "No") << std::endl <<
                 "Sorted array elements: {";
    for(int idx=0; idx < size; idx++)
        std::cout << input_array[idx] << (idx != size-1 ? ", " : "}");
    std::cout << std::endl;
    std::cout << "----------------------------------------------" << std::endl;

    delete[] input_array;
}


void random_batch_test(){
    random_test(5, 5);
    random_test(10, 10);
    random_test(4, 2);
    random_test(10, 1);
    random_test(3, 3);
}


int main(){
    srandom(time(nullptr));
    random_batch_test();
    return 0;
}