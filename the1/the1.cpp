#include "the1.h"
const int INF = std::numeric_limits<int>::max();

void swap(int &a, int &b, long &n_swaps) {
    int temp = a;
    a = b;
    b = temp;
    n_swaps++;
}

void insert(int**& table, size_t row, size_t col, int value, long& n_swaps)
{
    //SHOULD START FROM BOTTOM LEFT
    int i= row- 1;
    int j= col- 1;
    table[i][j]= value;
    while(i> 0 ||j >0) 
    {
        int upper;
        if(i>0)
        {
            upper =table[i-1][j];
        } 
        else{
            upper = INF;
        }
        //UPPER IS TH PRIOTIRY
        int left;
        if(j >0) {
            left= table[i][j- 1];
        }
        else
        {
            left= INF;
        }
        int current = table[i][j];
        bool need_swap_upper= (i>0) &&(current<upper);
        bool need_swap_left= (j>0) &&(current<left);
        
        if (!need_swap_upper && !need_swap_left)
        {
            break;  
        }
        if (need_swap_upper&& need_swap_left)
        {
            if (upper >=left)
            {
                swap(table[i][j], table[i-1][j], n_swaps);
                i--;
            }
            else
            {
                swap(table[i][j],table[i][j-1],n_swaps);
                j--;
            }
        }
        else if(need_swap_upper)
        {
            swap(table[i][j], table[i-1][j], n_swaps);
            i--;
        }
        else if (need_swap_left)
        {
            swap(table[i][j], table[i][j-1], n_swaps);
            j--;
        }
    }
}

void generate_init(int**& table, size_t row, size_t col) {
    table = new int*[row];
    for (size_t i = 0; i < row; i++) {
        table[i] = new int[col];
        for (size_t j = 0; j < col; j++) {
            table[i][j]= INF;
        }
    }
}

int extract(int**& table, size_t row, size_t col, long& n_swaps) {
    int min_val = table[0][0];
    table[0][0]=INF;
    
    int i=0;
    int j=0;
    
    //THE TOP LEFT IS THE MINIMAL 
    while (i<(int)row -1||j <(int)col-1) 
    {
        int lower;
        if (i < (int)row - 1) {
            lower = table[i + 1][j];
        } else {
            lower = INF;
        }
        
        int right;
        if (j < (int)col - 1) 
        {
            right = table[i][j + 1];
        }
        else
        {
            right = INF;
        }
        int current = table[i][j];
        bool need_swap_lower =(i <(int)row -1) &&(current>lower);
        bool need_swap_right =(j <(int)col -1) &&(current>right);
        if (!need_swap_lower && !need_swap_right)
        {
            break;  
        }
        
        
        if (need_swap_lower && need_swap_right)
        {
            if (lower <= right)
            {
                swap(table[i][j], table[i+1][j], n_swaps);
                i++;
            }
            else
            {
                swap(table[i][j], table[i][j+1], n_swaps);
                j++;
            }
        }
        else if(need_swap_lower)
        {
            swap(table[i][j], table[i+1][j], n_swaps);
            i++;
        }
        else if(need_swap_right)
        {
            swap(table[i][j], table[i][j+1], n_swaps);
            j++;
        }
    }
    return min_val;
}

long sort_with_young_tableau(int* arr,
                             const size_t size,
                             const std::pair<size_t, size_t> table_size){
    // INIT GENERATE -Generate an empty Young Tableau with given dimensions.
    // INSERT– Insert each element into Young Tableau in a given order. (First, insert a new element into the bottom-right position, and swap it with its neighbours until the matrix is a valid YoungTableau.)   
    // EXTRACT- Extract the minimum element repeatedly until your Young Tableau is empty. Change the minimum element with ∞ and swap the element until the tableau is valid.
    int** table;
    size_t r = table_size.first;
    size_t c = table_size.second;
    long n_swaps = 0;
    
    generate_init(table, r, c);
    
    for (size_t t = 0; t < size; ++t) {
        insert(table, r, c, arr[t], n_swaps);
    }
    
    for (size_t t = 0; t < size; ++t) {
        arr[t] = extract(table, r, c, n_swaps);
    }
    
    for(size_t i = 0; i < r; i++) {
        delete[] table[i];
    }
    delete[] table;
    return n_swaps;
}