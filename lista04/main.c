#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "bst.h"

int main(void)
{
    const int seed = 123;
    const size_t size = 10;
    const int32_t max_num = 2 * size - 1;
    int32_t value;

    init_traces(size);

    srandom(seed);

    Node *root = NULL;
    root = insert(root, 10);

    for (size_t i = 0; i < size; i++)
    {
        value = random() % (max_num);
        insert(root, value);
    }

    print_bst(root, 0, '-');

    free_tree(root);
    free_traces();

    return 0;
}
