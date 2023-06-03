#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "bst.h"

int32_t* take_input(const size_t size);

int32_t* take_input(const size_t size)
{
    int32_t *arr = malloc(size * sizeof(int32_t));

    for (size_t i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
    }

    return arr;
}

// n = size
int main(void)
{
    size_t size;
    int32_t value;
    scanf("%zu", &size);
    const int32_t max_num = 2 * (int32_t)size - 1;
    int32_t *insert_arr = take_input(size);
    int32_t *delete_arr = take_input(size);

    init_traces(size);

    srand((unsigned)time(NULL));

    Node *root = NULL;
    root = insert(root, insert_arr[0]);

    size_t i;
    for (i = 1; i < size; i++)
    {
        value = insert_arr[i];
        insert(root, value);
        //print_bst(root, 0, '-');
    }

    print_bst(root, 0, '_');
    printf("\n\n\n\n");

    for (i = 0; i < size; i++)
    {
        value = delete_arr[i];
        delete(root, value);
        //print_bst(root, 0, '_');
    }

    print_bst(root, 0, '_');

    free(insert_arr);
    free(delete_arr);
    free_tree(root);
    free_traces();

    return 0;
}
