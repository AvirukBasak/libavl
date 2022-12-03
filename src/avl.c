#include "libavl.h"

/**
 * @brief Attaches a node to the tree
 * @param head AVL head
 * @param node Node to be attached
 * @param callback int (*)(avldata_t*, avldata_t*)
 * @return bool true on attach success
 */
bool avl_attach(AVL *head, avlnode_t *node, avl_compare_t callback)
{
    return false;
}

/**
 * @brief Detaches a node from the tree
 * @param head AVL head
 * @param key Pointer to key which is present in the data member of a node
 * @param callback int (*)(void*, avldata_t*)
 * @return avlnode_t* Pointer to node to be freed
 */
avlnode_t *avl_detach(AVL *head, void *key, avl_keycompare_t callback)
{
    return NULL;
}

/**
 * @brief Searches for a key among the tree nodes
 * @param head AVL head
 * @param key Pointer to key which is to be searched
 * @param callback int (*)(void*, avldata_t*)
 * @return avldata_t* Pointer to data containing key
 */
avldata_t *avl_search(AVL *head, void *key, avl_keycompare_t callback)
{
    avlnode_t *p = head->root;
    while (p) {
        /* if key < data, -ve or decrease data, i.e. go to left subtree
         * if key > data, +ve or increase data, i.e. go to right subtree
         * if equal 0, match found
         */
        if (callback(key, p->data) < 0) p = p->lc;
        else if (callback(key, p->data) > 0) p = p->rc;
        else return p->data;
    }
    return NULL;
}
