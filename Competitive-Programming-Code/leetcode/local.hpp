#pragma once
#include <bits/stdc++.h>
using namespace std;

// 只在本地提供这些定义；在线提交使用题面给定的类型。
struct ListNode
{
    int val;
    ListNode* next;
    ListNode(int value = 0, ListNode* next_node = nullptr) : val(value), next(next_node) {}
};

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int value = 0, TreeNode* left_node = nullptr, TreeNode* right_node = nullptr)
        : val(value), left(left_node), right(right_node) {}
};

namespace local
{
// 以下链表助手只用于普通无环单链表。
inline ListNode* make_list(const vector<int>& values)
{
    ListNode* head = nullptr;
    for (auto it = values.rbegin(); it != values.rend(); ++it)
        head = new ListNode(*it, head);
    return head;
}

inline vector<int> list_values(const ListNode* head)
{
    vector<int> values;
    for (; head != nullptr; head = head->next) values.push_back(head->val);
    return values;
}

inline void free_list(ListNode* head)
{
    while (head != nullptr)
    {
        ListNode* next = head->next;
        delete head;
        head = next;
    }
}

// 使用 LeetCode 常见的层序表示；缺失节点用 nullopt。
// 空节点不再分配孩子槽位，不能按完全二叉树的 2*i+1 去解释稀疏输入。
inline TreeNode* make_tree(const vector<optional<int>>& values)
{
    if (values.empty()) return nullptr;
    if (!values[0].has_value())
    {
        for (const auto& value : values) assert(!value.has_value());
        return nullptr;
    }
    TreeNode* root = new TreeNode(*values[0]);
    queue<TreeNode*> q;
    q.push(root);
    size_t i = 1;
    while (!q.empty() && i < values.size())
    {
        TreeNode* node = q.front();
        q.pop();
        if (values[i].has_value())
        {
            node->left = new TreeNode(*values[i]);
            q.push(node->left);
        }
        ++i;
        if (i < values.size())
        {
            if (values[i].has_value())
            {
                node->right = new TreeNode(*values[i]);
                q.push(node->right);
            }
            ++i;
        }
    }
    // 队列耗尽后只允许多余的空占位，不允许无父节点的非空节点。
    while (i < values.size()) { assert(!values[i].has_value()); ++i; }
    return root;
}

inline vector<optional<int>> tree_values(const TreeNode* root)
{
    if (root == nullptr) return {};
    vector<optional<int>> values;
    queue<const TreeNode*> q;
    q.push(root);
    while (!q.empty())
    {
        const TreeNode* node = q.front();
        q.pop();
        if (node == nullptr) { values.push_back(nullopt); continue; }
        values.push_back(node->val);
        q.push(node->left);
        q.push(node->right);
    }
    while (!values.empty() && !values.back().has_value()) values.pop_back();
    return values;
}

// 仅用于普通树：节点不能共享，也不能有环。
inline void free_tree(TreeNode* root)
{
    if (root == nullptr) return;
    vector<TreeNode*> pending{root};
    while (!pending.empty())
    {
        TreeNode* node = pending.back();
        pending.pop_back();
        if (node->left != nullptr) pending.push_back(node->left);
        if (node->right != nullptr) pending.push_back(node->right);
        delete node;
    }
}
} // namespace local
