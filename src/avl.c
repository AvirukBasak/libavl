#include "libavl.h"

/**
 * @brief AVL head type
 * Needs to be manually allocated on the heap
 */
struct AVL {
    avlnode_t *root;
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
 * @return avlnode_t* pointer to node containing key
 */
avlnode_t *avl_search(AVL *head, void *key, avl_keycompare_t callback)
{
    return NULL;
}
