#include <iostream>
#include <chrono>
#include <ctime>
#include <array>
#include "the4.h"

const unsigned short CHOCOLATE_LIMIT = 300;

// Randomly generate sell values for each possible chocolate piece size
// Some sizes get -1 meaning "not sellable directly".
void random_input_generator(unsigned short &chocolate_width,
                            unsigned short &chocolate_height,
                            int **&values) {
    chocolate_width = random() % CHOCOLATE_LIMIT;
    chocolate_height = random() % CHOCOLATE_LIMIT;

    int max_dim = (chocolate_width > chocolate_height) ? chocolate_width : chocolate_height;

    float prob_of_sellable = 0.1f/max_dim + ((float)((random() % 10000) / 10000.0) / (max_dim*2));

    values = new int *[chocolate_width + 1];
    for (int w = 0; w <= chocolate_width; w++) {
        values[w] = new int[chocolate_height + 1];
        for (int h = 0; h <= chocolate_height; h++) {
            if (w < 2 || h < 2 || w > chocolate_width - 3 || h > chocolate_height - 3) {
                values[w][h] = -1;
                continue;
            }
            bool sellable = ((float)(random() % 10000) / 10000.0) < prob_of_sellable;
            if (sellable) {
                int min_dim = (w < h) ? w : h;
                int min_range = min_dim * min_dim;
                values[w][h] = 1 + (random() % (min_range));
            } else {
                values[w][h] = -1;
            }
        }
    }
}

void test() {
    unsigned short chocolate_width, chocolate_height;
    int **values;
    unsigned int sellable_count = 0;

    random_input_generator(chocolate_width, chocolate_height, values);

    std::cout << "Chocolate Width: " << chocolate_width << " - Height: " << chocolate_height << std::endl
              << "Sellable sizes: {";
    for (int w = 1; w <= chocolate_width; w++) {
        for (int h = 1; h <= chocolate_height; h++) {
            if (values[w][h] != -1) {
                std::cout << "(" << w << "×" << h << ": " << values[w][h] << ") ";
                sellable_count++;
            }
        }
    }
    std::cout << "}" << std::endl
              << "Number of sellable sizes: " << sellable_count << std::endl
              << std::endl;

    // Start timing
    auto begin = std::chrono::high_resolution_clock::now();

    // Run DP and get both results
    std::array<unsigned int, 2> result = chocolate_value(chocolate_width, chocolate_height, values);

    auto end = std::chrono::high_resolution_clock::now();

    unsigned int max_sell_value = result[0];
    unsigned int total_waste = result[1];

    // Output results
    std::cout << "Maximum total sell value: " << max_sell_value << std::endl
              << "Total wasted area: " << total_waste << std::endl
              << "Elapsed time: "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()
              << " microseconds" << std::endl;

    // Free memory
    for (int w = 0; w <= chocolate_width; w++)
        delete[] values[w];
    delete[] values;
}

int main() {
    srandom(time(nullptr));
    test();
    return 0;
}
