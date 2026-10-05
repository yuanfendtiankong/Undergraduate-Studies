#ifdef LOCAL
#include "local.hpp"
#endif

// 示例题：https://leetcode.com/problems/maximum-depth-of-binary-tree/
class Solution
{
public:
    int maxDepth(TreeNode* root)
    {
        if (root == nullptr) return 0;
        queue<TreeNode*> q;
        q.push(root);
        int depth = 0;
        while (!q.empty())
        {
            int count = static_cast<int>(q.size());
            ++depth;
            while (count--)
            {
                TreeNode* node = q.front();
                q.pop();
                if (node->left != nullptr) q.push(node->left);
                if (node->right != nullptr) q.push(node->right);
            }
        }
        return depth;
    }
};

#ifdef LOCAL
int main()
{
    vector<pair<vector<optional<int>>, int>> cases{
        {{3, 9, 20, nullopt, nullopt, 15, 7}, 3},
        {{1, nullopt, 2}, 2}, {{}, 0}, {{nullopt}, 0},
        {{1}, 1}, {{1, nullopt, 2, 3}, 3}, {{1, 2, nullopt, 3}, 3}
    };
    Solution solution;
    for (auto [values, expected] : cases)
    {
        TreeNode* root = local::make_tree(values);
        assert(solution.maxDepth(root) == expected);
        while (!values.empty() && !values.back().has_value()) values.pop_back();
        assert(local::tree_values(root) == values);
        local::free_tree(root);
    }
    TreeNode* sparse = local::make_tree({1, nullopt, 2, 3});
    assert(sparse->left == nullptr);
    assert(sparse->right->val == 2 && sparse->right->left->val == 3);
    assert(sparse->right->right == nullptr);
    local::free_tree(sparse);
    cout << "PASS max_depth: " << cases.size() << " cases + sparse tree structure\n";
}
#endif
