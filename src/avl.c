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
    if (!head->__root) {
        head->__root = node;
        node->__pr = NULL;
        goto avl_attach_node_init;
    }
    avlnode_t *p = head->__root;
    avlnode_t *trail = NULL;
    while (p) {
        /* if key < data, -ve or decrease data, i.e. go to left subtree
         * if key > data, +ve or increase data, i.e. go to right subtree
         * if equal 0, match found
         */
        if (callback(node->data, p->data) < 0) {
            trail = p;
            p = p->__lc;
        } else if (callback(node->data, p->data) > 0) {
            trail = p;
            p = p->__rc;
        } else return false;
    }
    if (callback(node->data, trail->data) < 0)
        trail->__lc = node;
    else
        trail->__rc = node;
    node->__pr = trail;
avl_attach_node_init:
    node->__lc = NULL;
    node->__rc = NULL;
    node->__bf = 0;
    return true;
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
    avlnode_t *p = head->__root;
    while (p)
        /* if key < data, -ve or decrease data, i.e. go to left subtree
         * if key > data, +ve or increase data, i.e. go to right subtree
         * if equal 0, match found
         */
        if (callback(key, p->data) < 0) p = p->__lc;
        else if (callback(key, p->data) > 0) p = p->__rc;
        else return p->data;
    return NULL;
}
