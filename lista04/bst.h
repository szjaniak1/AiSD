#pragma once

#include <stddef.h>
#include <inttypes.h>

typedef struct Node Node;

Node* new_node(const int32_t value);
Node* insert(Node *node, const int32_t value);
Node* delete(Node *root, const int32_t value);
Node* min_value_node(Node *node);
void free_tree(Node *root);
size_t get_size(void);

void print_bst(const Node* restrict root, const size_t depth, const char prefix);
void init_traces(const size_t size);
void free_traces(void);
