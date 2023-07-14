#include <iostream>
#include <queue>
using namespace std;

class TreeNode
{
public:
    int val;
    int depth = 0;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// This will be called in main to construct the tree
TreeNode* insert(TreeNode* root, int data)
{
    if (root == nullptr)
        return new TreeNode(data);
    if (root->val < data)
        root->right = insert(root->right, data);
    else
        root->left = insert(root->left, data);
    return root;
}

// This will be called in main to deallocate memory
void destruct(TreeNode* root)
{
    if (root->left)
        destruct(root->left);
    if (root->right)
        destruct(root->right);
    delete root;
}

void assignDepth(TreeNode* root, int depth) {
    root->depth = depth;
    if (root->left != nullptr) {
        depth += 1;
        assignDepth(root->left, depth);
        depth -= 1;
    }
    if (root->right != nullptr) {
        depth += 1;
        assignDepth(root->right, depth);
        depth -= 1;
    }
}

int sumOfLevel(TreeNode* root, int level)
{
    int sum = 0;
    int depth = 0;
    assignDepth(root, depth);
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        if (q.front()->left != nullptr) {
            q.push(q.front()->left);
        }
        if (q.front()->right != nullptr) {
            q.push(q.front()->right);
        }
        if (q.front()->depth == level) {
            sum += q.front()->val;
        }
        q.pop();
    }
    return sum;
}

int main() {
    TreeNode* root = new TreeNode(91);
    insert(root,97);
    insert(root,93);
    insert(root,64);
    insert(root,87);
    insert(root,17);
    insert(root,16);
    insert(root,47);
    insert(root,24);
    insert(root,63);
    cout << sumOfLevel(root, 4) << endl;
    destruct(root);
}