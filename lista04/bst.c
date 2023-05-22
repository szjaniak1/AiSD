#include <stdlib.h>
#include <stdio.h>

#include "bst.h"

struct Node
{
    int32_t value;
    int32_t padding;
    Node *right;
    Node *left;
};

Node* new_node(const int32_t value)
{
    Node* temp = (Node*)malloc(sizeof(Node));

    temp->value = value;
    temp->left = NULL;
    temp->right = NULL;

    return temp;
}

Node* insert(Node *node, const int32_t value)
{
    if (node == NULL) return new_node(value);

    if (value < node->value)
    {
        node->left = insert(node->left, value);
    }
    else
    {
        node->right = insert(node->right, value);
    }

    return node;
}

Node *delete(Node *root, const int32_t value)
{
    if (root == NULL) return root;

    if (value < root->value)
    {
        root->left = delete(root->left, value);
    }
    else if (value > root->value)
    {
        root->right = delete(root->right, value);
    }
    else
    {
        if (root->left == NULL)
        {
            struct Node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct Node *temp = root->left;
            free(root);
            return temp;
        }

        struct Node *temp = min_value_node(root->right);
        root->value = temp->value;
        root->right = delete(root->right, temp->value);
    }

    return root;
}

Node *min_value_node(Node *node)
{
    struct Node *current = node;

    while (current && current->left != NULL)
    {
        current = current->left;
    }

    return current;
}

void free_tree(Node *node)
{
    if (node == NULL) return;

    free_tree(node->left);
    free_tree(node->right);

    free(node);
    node = NULL;
}

static char *left_trace;
static char *right_trace;

void print_bst(const Node* restrict root, const int32_t depth, const char prefix)
{
    if (root == NULL) return;

    if (root->left != NULL)
    {
        print_bst(root->left, depth + 1, '/');
    }

    if (prefix == '/') left_trace[depth - 1] = '|';
    if (prefix == '\\') right_trace[depth - 1] = ' ';

    if (depth == 0) printf("-");
    if (depth > 0) printf(" ");

    for (int32_t i = 0; i < depth - 1; i++)
    {
        if (left_trace[i] == '|' || right_trace[i] == '|')
        {
            printf("| ");
        }
        else
        {
            printf("  ");
        }
    }

    if (depth > 0) printf("%c-", prefix);

    printf("[%d]\n", root->value);

    left_trace[depth] = ' ';

    if (root->right != NULL)
    {
        right_trace[depth] = '|';
        print_bst(root->right, depth + 1, '\\');
    }
}

void init_traces(const size_t size)
{
    left_trace = malloc(size * sizeof(char));
    right_trace = malloc(size * sizeof(char));

    for (size_t i = 0; i < size; i++)
    {
        left_trace[i] = ' ';
        right_trace[i] = ' ';
    }
}

void free_traces(void)
{
    free(left_trace);
    free(right_trace);
}

size_t get_size(void)
{
    return sizeof(Node);
}
