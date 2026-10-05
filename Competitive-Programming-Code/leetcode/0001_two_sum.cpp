#ifdef LOCAL
#include "local.hpp"
#endif

// 示例题：https://leetcode.com/problems/two-sum/
// 提交时复制此 Solution 类；本地测试代码放在下方 LOCAL 区域。
class Solution
{
public:
    vector<int> twoSum(vector<int>& nums, int target)
    {
        unordered_map<long long, int> position;
        for (int i = 0; i < static_cast<int>(nums.size()); ++i)
        {
            long long need = static_cast<long long>(target) - nums[i];
            auto it = position.find(need);
            if (it != position.end()) return {it->second, i};
            position[nums[i]] = i;
        }
        return {}; // 题面保证有解。
    }
};

#ifdef LOCAL
int main()
{
    vector<pair<vector<int>, int>> cases{
        {{2, 7, 11, 15}, 9}, {{3, 2, 4}, 6}, {{3, 3}, 6},
        {{-3, 4, 3, 90}, 0}, {{0, 4, 3, 0}, 0},
        {{1000000000, -1000000000}, 0}
    };
    Solution solution;
    for (auto [nums, target] : cases)
    {
        auto answer = solution.twoSum(nums, target);
        // 本题允许任意顺序返回，所以验证答案性质，不固定写死 [0,1]。
        assert(answer.size() == 2);
        int i = answer[0], j = answer[1];
        assert(0 <= i && i < static_cast<int>(nums.size()));
        assert(0 <= j && j < static_cast<int>(nums.size()) && i != j);
        assert(1LL * nums[i] + nums[j] == target);
    }
    cout << "PASS two_sum: " << cases.size() << " cases\n";
}
#endif
