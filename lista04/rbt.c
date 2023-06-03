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

RbNode *create_node(register const int32_t data)
{
    RbNode *new_node;
    new_node = (struct RbNode *)malloc(sizeof(struct RbNode));

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

void deletion(int data)
{
    RbNode *stack[98], *ptr, *x_ptr, *y_ptr;
    RbNode *p_ptr, *q_ptr, *r_ptr;
    int32_t dir[98], ht = 0, diff, i;
    enum node_color color;

    if (!root)
    {
        printf("Tree not available\n");
        return;
    }

    ptr = root;
    while (ptr != NULL)
    {
        if ((data - ptr->data) == 0) break;

        diff = (data - ptr->data) > 0 ? 1 : 0;
        stack[ht] = ptr;
        dir[ht++] = diff;
        ptr = ptr->link[diff];
    }

    if (ptr->link[1] == NULL)
    {
        if ((ptr == root) && (ptr->link[0] == NULL))
        {
            free(ptr);
            root = NULL;
        }
        else if (ptr == root)
        {
            root = ptr->link[0];
            free(ptr);
        }
        else
        {
            stack[ht - 1]->link[dir[ht - 1]] = ptr->link[0];
        }
    }
    else
    {
        x_ptr = ptr->link[1];
        if (x_ptr->link[0] == NULL)
        {
            x_ptr->link[0] = ptr->link[0];
            color = x_ptr->color;
            x_ptr->color = ptr->color;
            ptr->color = color;

            if (ptr == root)
            {
                root = x_ptr;
            }
            else
            {
                stack[ht - 1]->link[dir[ht - 1]] = x_ptr;
            }

            dir[ht] = 1;
            stack[ht++] = x_ptr;
        }
        else
        {
            i = ht++;
            while (1)
            {
                dir[ht] = 0;
                stack[ht++] = x_ptr;
                y_ptr = x_ptr->link[0];

                if (!y_ptr->link[0]) break;

                x_ptr = y_ptr;
            }

            dir[i] = 1;
            stack[i] = y_ptr;

            if (i > 0) stack[i - 1]->link[dir[i - 1]] = y_ptr;

            y_ptr->link[0] = ptr->link[0];

            x_ptr->link[0] = y_ptr->link[1];
            y_ptr->link[1] = ptr->link[1];

            if (ptr == root)
            {
                root = y_ptr;
            }

            color = y_ptr->color;
            y_ptr->color = ptr->color;
            ptr->color = color;
        }
    }

    if (ht < 1) return;

    if (ptr->color == BLACK)
    {
        while (1)
        {
            p_ptr = stack[ht - 1]->link[dir[ht - 1]];
            if (p_ptr && p_ptr->color == RED)
            {
                p_ptr->color = BLACK;
                break;
            }

            if (ht < 2)
                break;

            if (dir[ht - 2] == 0)
            {
                r_ptr = stack[ht - 1]->link[1];

                if (!r_ptr)
                    break;

                if (r_ptr->color == RED)
                {
                    stack[ht - 1]->color = RED;
                    r_ptr->color = BLACK;
                    stack[ht - 1]->link[1] = r_ptr->link[0];
                    r_ptr->link[0] = stack[ht - 1];

                    if (stack[ht - 1] == root)
                    {
                        root = r_ptr;
                    }
                    else
                    {
                        stack[ht - 2]->link[dir[ht - 2]] = r_ptr;
                    }

                    dir[ht] = 0;
                    stack[ht] = stack[ht - 1];
                    stack[ht - 1] = r_ptr;
                    ht++;

                    r_ptr = stack[ht - 1]->link[1];
                }

                if ((!r_ptr->link[0] || r_ptr->link[0]->color == BLACK) &&
                    (!r_ptr->link[1] || r_ptr->link[1]->color == BLACK))
                {
                    r_ptr->color = RED;
                }
                else
                {
                    if (!r_ptr->link[1] || r_ptr->link[1]->color == BLACK)
                    {
                        q_ptr = r_ptr->link[0];
                        r_ptr->color = RED;
                        q_ptr->color = BLACK;
                        r_ptr->link[0] = q_ptr->link[1];
                        q_ptr->link[1] = r_ptr;
                        r_ptr = stack[ht - 1]->link[1] = q_ptr;
                    }

                    r_ptr->color = stack[ht - 1]->color;
                    stack[ht - 1]->color = BLACK;
                    r_ptr->link[1]->color = BLACK;
                    stack[ht - 1]->link[1] = r_ptr->link[0];
                    r_ptr->link[0] = stack[ht - 1];

                    if (stack[ht - 1] == root)
                    {
                        root = r_ptr;
                    }
                    else
                    {
                        stack[ht - 2]->link[dir[ht - 2]] = r_ptr;
                    }
                    break;
                }
            }
            else
            {
                r_ptr = stack[ht - 1]->link[0];
                if (!r_ptr)
                    break;

                if (r_ptr->color == RED)
                {
                    stack[ht - 1]->color = RED;
                    r_ptr->color = BLACK;
                    stack[ht - 1]->link[0] = r_ptr->link[1];
                    r_ptr->link[1] = stack[ht - 1];

                    if (stack[ht - 1] == root)
                    {
                        root = r_ptr;
                    }
                    else
                    {
                        stack[ht - 2]->link[dir[ht - 2]] = r_ptr;
                    }

                    dir[ht] = 1;
                    stack[ht] = stack[ht - 1];
                    stack[ht - 1] = r_ptr;
                    ht++;

                    r_ptr = stack[ht - 1]->link[0];
                }
                if ((!r_ptr->link[0] || r_ptr->link[0]->color == BLACK) &&
                    (!r_ptr->link[1] || r_ptr->link[1]->color == BLACK))
                {
                    r_ptr->color = RED;
                }
                else
                {
                    if (!r_ptr->link[0] || r_ptr->link[0]->color == BLACK)
                    {
                        q_ptr = r_ptr->link[1];
                        r_ptr->color = RED;
                        q_ptr->color = BLACK;
                        r_ptr->link[1] = q_ptr->link[0];
                        q_ptr->link[0] = r_ptr;
                        r_ptr = stack[ht - 1]->link[0] = q_ptr;
                    }

                    r_ptr->color = stack[ht - 1]->color;
                    stack[ht - 1]->color = BLACK;
                    r_ptr->link[0]->color = BLACK;
                    stack[ht - 1]->link[0] = r_ptr->link[1];
                    r_ptr->link[1] = stack[ht - 1];

                    if (stack[ht - 1] == root)
                    {
                        root = r_ptr;
                    }
                    else
                    {
                        stack[ht - 2]->link[dir[ht - 2]] = r_ptr;
                    }
                    break;
                }
            }
            ht--;
        }
    }
}

void inorderTraversal(register const RbNode *const restrict node)
{
    if (node)
    {
        inorderTraversal(node->link[0]);

        printf("%d  ", node->data);

        inorderTraversal(node->link[1]);
    }

    return;
}