#pragma once

#include <stddef.h>
#include <inttypes.h>

typedef struct RbNode RbNode;

RbNode* create_node(register const int32_t data);
void insertion(register const int32_t data);
void deletion(const register int32_t data);
void inorderTraversal(register const RbNode *const node);