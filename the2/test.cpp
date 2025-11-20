#include <iostream>
#include <fstream>
#include <chrono>
#include "the2.h"

void random_io_generator(unsigned int*& arr,
                         size_t& size,
                         unsigned int& base,
                         const unsigned int minimum_value = 0,
                         const unsigned int interval = (1 << 14)){
    base = 1 + random() % 10;
    size = random() % 100;
    arr = new unsigned int [size];
    for(unsigned int idx = 0; idx < size; idx++)
        arr[idx] = minimum_value + (random() % interval);
}

bool check_sorted(const unsigned int* arr,
                  const size_t size){
    for(int idx=1; idx < size; idx++)
        if(arr[idx] < arr[idx-1]) return false;
    return true;
}

void test(){
    unsigned int* input_array;
    unsigned int base2;
    size_t size;
    random_io_generator(input_array, size, base2);
    std::cout << "Size: " << size << std::endl <<
                 "Base: " << (1 << base2) << std::endl <<
                 "Array elements: {";
    for(int idx=0; idx < size; idx++)
        std::cout << input_array[idx] << (idx != size-1 ? ", "
                                                        : "}");
    std::cout << std::endl;

    auto begin = std::chrono::high_resolution_clock::now();
    long number_of_iteration = base_x_radix_sort(input_array, size, base2);
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Number of iterations: " << number_of_iteration << std::endl
              << "Elapsed time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " nanoseconds" << std::endl
              << "Is sorted: " << (check_sorted(input_array, size) ? "Yes" : "No") << std::endl
              << "Sorted array: {";
    for(int idx=0; idx < size; idx++)
        std::cout << input_array[idx] << (idx != size-1 ? ", " : "}");
    std::cout << std::endl;
    delete[] input_array;
}

int main(){
    srandom(time(nullptr));
    test();
    return 0;
}