#ifndef __LIBAVL_H__
#define __LIBAVL_H__

/**
 * @brief AVL head type
 * Needs to be manually allocated on the heap
 */
typedef struct AVL AVL;

/**
 * @brief AVL tree node type
 * Needs to be manually allocated on the heap
 */
typedef struct avlnode_t avlnode_t;

/**
 * @brief Callback function pointer
 */
typedef int (*avl_keycompare)(void*, avlnode_t*) avl_keycompare_t;

/**
 * @brief Callback function pointer
 */
typedef int (*avl_compare)(avlnode_t*, avlnode_t*) avl_compare_t;

/**
 * @brief Attaches a node to the tree and rotates tree around if needed
 * @param head AVL head
 * @param node Node to be attached
 * @param callback int (*)(avlnode_t*, avlnode_t*)
 * @return true on attach success
 */
bool avl_attach(AVL *head, avlnode_t *node, avl_compare_t callback);

/**
 * @brief Detaches a node from the tree and rotates tree around if needed
 * @param head AVL head
 * @param node Node to be detached
 * @param callback int (*)(avlnode_t*, avlnode_t*)
 * @return bool true on detach success
 */
bool avl_detach(AVL *head, avlnode_t *node, avl_compare_t callback);

/**
 * @brief Searches for a key among the tree nodes
 * @param head AVL head
 * @param key Key to be searched
 * @param callback int (*)(void*, avlnode_t*)
 * @return avlnode_t* pointer to node containing key
 */
avlnode_t *avl_search(AVL *head, void *key, avl_keycompare_t callback);

#endif
