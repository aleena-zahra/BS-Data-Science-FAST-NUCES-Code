#include <iostream>
using namespace std;
struct TreeNode
{
    int data;
    TreeNode *right;
    TreeNode *left;
    TreeNode(int data = 0)
    {
        this->data = data;
        this->right = this->left = NULL;
    }
};
class BinarySearchTree
{
public:
    TreeNode *root;
    BinarySearchTree()
    {
        root = NULL;
    }
    // insert
    void insertNode(TreeNode *&root, int value)
    {

        if (root == NULL)
        {
            root = new TreeNode(value);
            return;
        }
        if (root->data == value)
        {
            cout << "Value already exists";
            return;
        }
        if (value < root->data)
        {
            insertNode(root->left, value);
        }
        else
        {
            insertNode(root->right, value);
        }
    }
    // delete
    void deleteNode(TreeNode *&root, int value)
    {
        TreeNode *temp;
        temp = searchValue(root, value);
        if (temp == NULL)
        {
            cout << "Value not found";
            return;
        }
        if (value < root->data)
        {
            deleteNode(root->left, value);
        }
        else if (value > root->data)
        {
            deleteNode(root->right, value);
        }
        else{
            // Node found

            // no children
            if (root->left == NULL && root->right == NULL)
            {
                delete root;
                root = NULL;
            }
            // one child
            else if (root->left == NULL)
            {
                TreeNode *temp = root;
                root = root->right;
                delete temp;
            }
            else if (root->right == NULL)
            {
                TreeNode *temp = root;
                root = root->left;
                delete temp;
            }
            // two children
            else
            {
                TreeNode *temp = getMinimum(root->right);
                root->data = temp->data;
                deleteNode(root->right, temp->data);
            }
        }
    }
    TreeNode *getMinimum(TreeNode *&root)
    {
        TreeNode *temp = root;
        while (temp && temp->left != NULL)
        {
            temp = temp->left;
        }
        return temp;
    }
    // print
    void printTree(TreeNode *root)
    {
        if (root == NULL)
        {
            return;
        }
        printTree(root->left);
        cout << root->data << " ";
        printTree(root->right);
    }
    // search
    TreeNode *searchValue(TreeNode *&root, int value)
    {
        if (root == NULL)
        {
            cout << "Value not found";
            return NULL;
        }
        if (root->data == value)
        {
            return root;
        }
        if (value < root->data)
        {
            searchValue(root->left, value);
        }
        else
        {
            searchValue(root->right, value);
        }
    }
};
int main()
{
    BinarySearchTree tree;
    tree.insertNode(tree.root, 20);
    tree.insertNode(tree.root, 7);
    tree.insertNode(tree.root,12);
    tree.insertNode(tree.root,28);
    cout<<"initially the bst is \n";
    tree.printTree(tree.root);
    tree.deleteNode(tree.root, 12);
    cout<<"\nafter deleting 12\n";
    tree.printTree(tree.root);
    tree.deleteNode(tree.root,7);
    cout<<"\nafter deleting 7\n";
    tree.printTree(tree.root);
    return 0;
}