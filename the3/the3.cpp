#include "the3.h"

// DO NOT CHANGE ABOVE THIS LINE!
// you may implement helper functions below

int find_max_attack(int n, int G0,
                   const vector<vector<int>>& P,
                   const vector<vector<int>>& W,
                   const vector<int>& G) {

    int max_attack = 0;
    // your code here
    int max_gold = G0;
    for (int i= 0; i < n; i++) {
        max_gold+= G[i];
    }
    vector<vector<int>> dp(n + 1, vector<int>(max_gold + 1, -1));
    dp[0][G0] = 0;
    
    for (int t = 0; t < n; t++) {
        for (int gold = 0; gold <= max_gold; gold++) {

            int attack = dp[t][gold];
            if (dp[t][gold] == -1) continue;
            // POTIONS
            if (gold >= P[t][0]) {
                int new_gold = gold - P[t][0];
                int new_attack = attack + W[t][0];
                dp[t+1][new_gold] = max(dp[t+1][new_gold], new_attack);
            }
            
            //ELIXIR
            if (gold >= P[t][1]) {
                int new_gold= gold - P[t][1];
                int new_attack = attack + W[t][1];
                dp[t+1][new_gold] = max(dp[t+1][new_gold], new_attack);
            }
            
            //SCROLL
            if (gold >= P[t][2]) {
                int new_gold = gold - P[t][2];
                int new_attack= attack + W[t][2];
                dp[t+1][new_gold] = max(dp[t+1][new_gold], new_attack);
            }
            
            //nothing
            int new_gold = gold + G[t];
            if (new_gold<= max_gold) {
                dp[t+1][new_gold] = max(dp[t+1][new_gold], attack);
            }
        }
    }
    
    for (int gold = 0; gold <= max_gold; gold++) {
        if (dp[n][gold] != -1) {
            max_attack = max(max_attack, dp[n][gold]);
        }
    }
    

    // do not forget to update the return value!
    return max_attack;
}


