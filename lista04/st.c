#include <stdlib.h>

#include "st.h"

struct Node
{
    int32_t key;
    Node *left, *right;
};

Node* new_node(const int32_t key)
{
    Node *temp = (Node*)malloc(sizeof(Node));

    temp->key = key;
    temp->left = temp->right = NULL;
    return temp;
}

Node* right_rotate(Node *x)
{
    Node *y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

Node* left_rotate(Node *x)
{
    Node *y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

Node* splay(Node *root, int32_t key)
{
    if (root == NULL || root->key == key)
        return root;

    if (root->key > key)
    {
        if (root->left == NULL)
            return root;

        if (root->left->key > key)
        {
            root->left->left = splay(root->left->left, key);
            root = rightRotate(root);
        }
        else if (root->left->key < key)
        {
            root->left->right = splay(root->left->right, key);
            if (root->left->right != NULL)
                root->left = leftRotate(root->left);
        }

        return (root->left == NULL) ? root
                                    : rightRotate(root);
    }
    else
    {
        if (root->right == NULL)
            return root;

        if (root->right->key > key)
        {
            root->right->left = splay(root->right->left, key);
            if (root->right->left != NULL)
                root->right = rightRotate(root->right);
        }
        else if (root->right->key < key)
        {
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }

        return (root->right == NULL) ? root
                                     : leftRotate(root);
    }
}

Node* insert(Node *root, int32_t key)
{
    if (root == NULL)
        return newNode(key);

    root = splay(root, key);

    if (root->key == key)
        return root;

    Node *temp = newNode(key);
    if (root->key > key)
    {
        temp->right = root;
        temp->left = root->left;
        root->left = NULL;
    }
    else
    {
        temp->left = root;
        temp->right = root->right;
        root->right = NULL;
    }
    return temp;
}