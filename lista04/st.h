#pragma once

#include <stddef.h>
#include <inttypes.h>

typedef struct Node Node;

Node* new_node(const int32_t value);
Node* right_rotate(Node *x);
Node* left_rotate(Node *x);
Node* splay(Node *root, int32_t key);
Node* insert(Node *root, int32_t key);