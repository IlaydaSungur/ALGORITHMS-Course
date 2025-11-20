#include "the4.h"

// DO NOT CHANGE ABOVE THIS LINE!
// you may implement helper functions below
int maximum(int a, int b) {
    return (a > b) ? a : b;
}
// Chocolate Value Solution
array<unsigned int, 2> chocolate_value(
    const unsigned short chocolate_width,
    const unsigned short chocolate_height,
    int **values){// = -1 not valuable, >0 vluable
    
    unsigned int total_area = chocolate_width * chocolate_height;
    unsigned int sell_value = 0;
    unsigned int waste = 0;
    // your code here
    int** max =new int*[chocolate_width + 1];
    for (int i = 0;i <= chocolate_width; i++) {
        max[i] =new int[chocolate_height + 1];
        for (int j= 0; j <=chocolate_height; j++) {
            max[i][j] = 0;
        }
    }
    int** area = new int*[chocolate_width + 1];
    for (int i = 0;i <= chocolate_width; i++) {
        area[i] =new int[chocolate_height + 1];
        for (int j= 0; j <=chocolate_height; j++) {
            area[i][j] = 0;
        }
    }
    //filling the init table
    for (int i = 1; i <= chocolate_width; i++) {
        for (int j = 1; j <= chocolate_height; j++) {
            if (i < chocolate_width && j < chocolate_height && values[i][j] > 0) {
                max[i][j] = values[i][j];
                area[i][j] = i * j;
            }
        }
    }
    for (int i = 1; i <= chocolate_width; i++) {
        for (int j = 1; j <= chocolate_height; j++) {
            for (int v_cut = 1; v_cut < i; v_cut++) {
                int new_value = max[v_cut][j] + max[i - v_cut][j];
                if (new_value > max[i][j]) { //strictly greater
                    max[i][j] = new_value;
                    area[i][j] = area[v_cut][j] + area[i - v_cut][j];
                }
            }
            for (int h_cut = 1; h_cut < j; h_cut++) {
                int new_value = max[i][h_cut] + max[i][j - h_cut];
                if (new_value > max[i][j]) {
                    max[i][j] = new_value;
                    area[i][j] = area[i][h_cut] + area[i][j - h_cut];
                }
            }
        }
    }
    
    sell_value = max[chocolate_width][chocolate_height];
    waste = total_area - area[chocolate_width][chocolate_height];
    
    // do not forget to update the return value!
    array<unsigned int, 2> result;
    result[0] = sell_value;
    result[1] = waste;
    return result;
}