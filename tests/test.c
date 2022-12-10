#include <stdio.h>
#include <stdlib.h>

#include "libavl.h"

typedef struct {
    int id;
    const char *name;
} datanode;

int num_comp(void *d1, void *d2) {
    return ((datanode*) d1)->id - ((datanode*) d2)->id;
}

int num_kcomp(void *key, void *d) {
    /* if key < data, -ve or decrease data, i.e. go to left subtree
     * if key > data, +ve or increase data, i.e. go to right subtree
     * if equal 0, match found
     */
    return *(int*)key - ((datanode*) d)->id;
}

int main()
{
    // allocate tree head
    AVL *avlh = malloc(sizeof(AVL));
    // create new data (stack allocated in this case)
    datanode data1 = { 12, "John" };
    datanode data2 = { 23, "Joe" };
    {
        // allocate nodes in heap
        avlnode_t *node1 = malloc(sizeof(avlnode_t));
        avlnode_t *node2 = malloc(sizeof(avlnode_t));
        // initialize nodes
        node1->data = &data1;
        node2->data = &data2;
        // attatch nodes to tree
        avl_attach(avlh, node1, num_comp);
        avl_attach(avlh, node2, num_comp);
    }
    // use tree; get name whose id = 12
    int searchId = 12;
    const char* name12 = ((datanode*) avl_search(avlh, &searchId, num_kcomp))->name;
    // delete id 23
    int delId = 23;
    avlnode_t *node23 = avl_detach(avlh, &delId, num_kcomp);
    const char* name23 = ((datanode*) node23->data)->name;
    // resuls
    printf("%d => %s\n"
           "%d => %s\n", searchId, name12, delId, name23);
    /* free node and data
     * in this case data is not heap allocated so data not freed
     */
    free(node23);
    // free nodes and tree
    free(avlh);
}
