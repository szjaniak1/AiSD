#include "rbt.h"

#include <stdio.h>
#include <stdlib.h>

enum node_color
{
    RED,
    BLACK
};

struct RbNode
{
    uint8_t color;
    int32_t data;
    struct RbNode *link[2];
};

RbNode *root = NULL;

RbNode* create_node(register const int32_t data)
{
    RbNode *new_node;
    new_node = (struct RbNode*)malloc(sizeof(struct RbNode));

    new_node->data = data;
    new_node->color = RED;
    new_node->link[0] = new_node->link[1] = NULL;

    return new_node;
}

void insertion(register const int32_t data)
{
    RbNode *stack[98], *ptr, *new_node, *x_ptr, *y_ptr;
    int32_t dir[98], ht = 0, index;

    ptr = root;
    if (!root)
    {
        root = create_node(data);
        return;
    }

    stack[ht] = root;
    dir[ht++] = 0;

    while (ptr != NULL)
    {
        if (ptr->data == data)
        {
            return;
        }

        index = (data - ptr->data) > 0 ? 1 : 0;
        stack[ht] = ptr;
        ptr = ptr->link[index];
        dir[ht++] = index;
    }

    stack[ht - 1]->link[index] = new_node = create_node(data);

    while ((ht >= 3) && (stack[ht - 1]->color == RED))
    {
        if (dir[ht - 2] == 0)
        {
            y_ptr = stack[ht - 2]->link[1];

            if (y_ptr != NULL && y_ptr->color == RED)
            {
                stack[ht - 2]->color = RED;
                stack[ht - 1]->color = y_ptr->color = BLACK;
                ht = ht - 2;
            }
            else
            {
                if (dir[ht - 1] == 0)
                {
                    y_ptr = stack[ht - 1];
                }
                else
                {
                    x_ptr = stack[ht - 1];
                    y_ptr = x_ptr->link[1];
                    x_ptr->link[1] = y_ptr->link[0];
                    y_ptr->link[0] = x_ptr;
                    stack[ht - 2]->link[0] = y_ptr;
                }

                x_ptr = stack[ht - 2];
                x_ptr->color = RED;
                x_ptr->color = BLACK;
                x_ptr->link[0] = y_ptr->link[1];
                y_ptr->link[1] = x_ptr;

                if (x_ptr == root)
                {
                    root = y_ptr;
                }
                else
                {
                    stack[ht - 3]->link[dir[ht - 3]] = y_ptr;
                }

                break;
            }
        }
        else
        {
            y_ptr = stack[ht - 2]->link[0];

            if ((y_ptr != NULL) && (y_ptr->color == RED))
            {
                stack[ht - 2]->color = RED;
                stack[ht - 1]->color = y_ptr->color = BLACK;
                ht = ht - 2;
            }
            else
            {
                if (dir[ht - 1] == 1)
                {
                    y_ptr = stack[ht - 1];
                }
                else
                {
                    x_ptr = stack[ht - 1];
                    y_ptr = x_ptr->link[0];
                    x_ptr->link[0] = y_ptr->link[1];
                    y_ptr->link[1] = x_ptr;
                    stack[ht - 2]->link[1] = y_ptr;
                }

                x_ptr = stack[ht - 2];
                y_ptr->color = BLACK;
                x_ptr->color = RED;
                x_ptr->link[1] = y_ptr->link[0];
                y_ptr->link[0] = x_ptr;

                if (x_ptr == root)
                {
                    root = y_ptr;
                }
                else
                {
                    stack[ht - 3]->link[dir[ht - 3]] = y_ptr;
                }

                break;
            }
        }
    }

    root->color = BLACK;
}