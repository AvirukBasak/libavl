#include "stdhead.h"
#include "avl.h"

/**
 * @brief Attaches a node to the tree
 * @param head AVL head
 * @param node Node to be attached
 * @param callback int (*)(avldata_t*, avldata_t*)
 * @return bool true on attach success
 */
bool avl_attach(AVL *head, avlnode_t *node, avl_compare_t callback)
{
    if (!callback) abort();
    if (!head || !node) return NULL;
    if (!head->root) {
        head->root = node;
        node->pr = NULL;
        goto avl_attach_node_init;
    }
    avlnode_t *p = head->root;
    avlnode_t *trail = NULL;
    while (p) {
        /* if key < data, -ve or decrease data, i.e. go to left subtree
         * if key > data, +ve or increase data, i.e. go to right subtree
         * if equal 0, match found
         */
        if (callback(node->data, p->data) < 0) {
            trail = p;
            p = p->lc;
        } else if (callback(node->data, p->data) > 0) {
            trail = p;
            p = p->rc;
        } else return false;
    }
    if (callback(node->data, trail->data) < 0)
        trail->lc = node;
    else
        trail->rc = node;
    node->pr = trail;
avl_attach_node_init:
    node->lc = NULL;
    node->rc = NULL;
    node->bf = 0;
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
    if (!callback) abort();
    if (!head || !head->root || !key) return NULL;
    // if at root
    avlnode_t *root = head->root;
    if (callback(key, root->data) == 0
        && !root->lc
        && !root->rc) return root;
    // find key
    avlnode_t *p = root;
    while (p)
        /* if key < data, -ve or decrease data, i.e. go to left subtree
         * if key > data, +ve or increase data, i.e. go to right subtree
         * if equal 0, match found
         */
        if (callback(key, p->data) < 0) p = p->lc;
        else if (callback(key, p->data) > 0) p = p->rc;
        else break;
    if (!p) return NULL;
    if (p->rc) {
        avlnode_t *tmp = p->rc;
        while (tmp->lc)
            tmp = tmp->lc;
        p->data = tmp->data;
        if (tmp->pr == p) tmp->pr->rc = tmp->rc;
        else tmp->pr->lc = tmp->rc;
        return tmp;
    } else if (p->pr) {
        avlnode_t *tmp;
        if (p->pr->lc == p) {
            tmp = p->pr->lc;
            p->pr->lc = p->lc;
        } else {
            tmp = p->pr->rc;
            p->pr->rc = p->lc;
        }
        return tmp;
    } else {
        avlnode_t *tmp = p;
        p = p->lc;
        return tmp;
    }
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
    if (!callback) abort();
    if (!head || !head->root || !key) return NULL;
    avlnode_t *p = head->root;
    while (p)
        /* if key < data, -ve or decrease data, i.e. go to left subtree
         * if key > data, +ve or increase data, i.e. go to right subtree
         * if equal 0, match found
         */
        if (callback(key, p->data) < 0) p = p->lc;
        else if (callback(key, p->data) > 0) p = p->rc;
        else return p->data;
    return NULL;
}
