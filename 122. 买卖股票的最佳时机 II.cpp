#include "leetcode.h"

class Solution {
public:
    static int maxProfit(vector<int> &prices) {
        if (prices.empty()) { return 0; }

        int profit = 0;

        for (size_t i = 1; i < prices.size(); ++i) {
            if (prices[i] - prices[i - 1] > 0) {
                profit += prices[i] - prices[i - 1]; // 每次(相较于前一天的)价格提升 都可以赚等同于差价的利润
            }
        }

        return profit;
    }
};
