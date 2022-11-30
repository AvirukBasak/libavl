#include "libavl.h"

/**
 * @brief AVL head type
 * Needs to be manually allocated on the heap
 */
struct AVL {
    avlnode_t *root;
};

/**
 * @brief AVL tree node type
 * Needs to be manually allocated on the heap
 */
struct avlnode_t {
    avldata_t *data;  // data
    avlnode_t *pr;    // parent
    avlnode_t *lc;    // left child
    avlnode_t *rc;    // right child
    size_t    bf;     // balance factor
};

/**
 * @brief Attaches a node to the tree and rotates tree around if needed
 * @param head AVL head
 * @param node Node to be attached
 * @param callback int (*)(avlnode_t*, avlnode_t*)
 * @return bool true on attach success
 */
bool avl_attach(AVL *head, avlnode_t *node, avl_compare_t callback)
{
    return false;
}

/**
 * @brief Detaches a node from the tree and rotates tree around if needed
 * @param head AVL head
 * @param node Node to be detached
 * @param callback int (*)(avlnode_t*, avlnode_t*)
 * @return bool true on detach success
 */
bool avl_detach(AVL *head, avlnode_t *node, avl_compare_t callback)
{
    return false;
}

/**
 * @brief Searches for a key among the tree nodes
 * @param head AVL head
 * @param key Key to be searched
 * @param callback int (*)(void*, avlnode_t*)
 * @return avlnode_t* pointer to data containing key
 */
avldata_t *avl_search(AVL *head, void *key, avl_keycompare_t callback)
{
    return NULL;
}
