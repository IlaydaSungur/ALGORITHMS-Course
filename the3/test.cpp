#include <iostream>
#include <fstream>
#include <chrono>
#include "the3.h"

void file_input(int &n, int &G0,
                std::vector<std::vector<int>>& P,
                std::vector<std::vector<int>>& W,
                std::vector<int>& G){
    std::string file_name = "inp01.txt"; // inp01-inp10 are available.
    std::ifstream infile (file_name);

    if(!infile.is_open()){
        std::cout << "Input file cannot be opened" << std::endl;
        std::cout << "File name: " << file_name << std::endl;
        return;
    }

    infile >> n >> G0;
    P.resize(n);
    W.resize(n);
    G.resize(n);
    for(int t=0; t < n; t++){
        P[t].resize(3);
        W[t].resize(3);
        for(int i=0; i < 3; i++){
            infile >> P[t][i];
        }
        for(int i=0; i < 3; i++){
            infile >> W[t][i];
        }
        infile >> G[t];
    }
}

void test(){
    int n, G0;
    int max_attack;
    std::vector<std::vector<int>> P, W;
    std::vector<int> G;
    
    file_input(n, G0, P, W, G);
    std::cout << "n: " << n << std::endl;
    std::cout << "G0: " << G0 << std::endl;
    std::cout << "Data (at most 9 turns are shown): " << std::endl;
    int max_rows = 9;
    if (n < 10) max_rows = n;
    for(int t=0; t < max_rows; t++){
        std::cout << "Turn " << t+1 << " - Prices: ";
        for(int i=0; i < 3; i++){
            std::cout << P[t][i] << " ";
        }
        std::cout << "| Attacks: ";
        for(int i=0; i < 3; i++){
            std::cout << W[t][i] << " ";
        }
        std::cout << "| Gold: " << G[t];
        std::cout << std::endl;
    }
    if (n > 10) std::cout << "..." << std::endl;

    auto begin = std::chrono::high_resolution_clock::now();
    max_attack = find_max_attack(n, G0, P, W, G);
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Found max_attack: " << max_attack << std::endl
              << "Elapsed time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds" << std::endl;

}

int main(){
    test();
    return 0;
}