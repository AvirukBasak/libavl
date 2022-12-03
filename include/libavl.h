#ifndef __LIBAVL_H__
#define __LIBAVL_H__

#include <stddef.h>
#include <stdbool.h>

/**
 * @brief AVL head type
 * Needs to be manually allocated on the heap.
 */
typedef struct AVL AVL;

/**
 * @brief AVL tree node
 * Needs to be manually allocated on the heap.
 */
typedef struct avlnode_t avlnode_t;

/**
 * @brief AVL tree node data
 * Needs to be manually allocated and linked with a node.
 */
typedef struct avldata_t avldata_t;

/**
 * @brief AVL head type
 * Needs to be manually allocated on the heap.
 */
struct AVL {
    avlnode_t *__root;
};

/**
 * @brief AVL tree node type
 * Needs to be manually allocated on the heap.
 */
struct avlnode_t {
    avldata_t *data;  // data
    avlnode_t *__pr;  // parent
    avlnode_t *__lc;  // left child
    avlnode_t *__rc;  // right child
    size_t    __bf;   // balance factor
};

/**
 * @brief Callback function, compares data to data b/w nodes.
 * @param avldata_t* AVL tree node data
 * @param avldata_t* AVL tree node data
 * @return int If 0, match found
 * @return int If -ve i.e. decrease, libavl goes to left subtree
 * @return int If +ve i.e. increase, libavl goes to right subtree
 */
typedef int (*avl_compare_t)(avldata_t*, avldata_t*);

/**
 * @brief Callback function, compares a key to data b/w nodes.
 * @param void* Pointer to key which is to be searched
 * @param avldata_t* AVL tree node data
 * @return int If 0, match found
 * @return int If -ve i.e. decrease, libavl goes to left subtree
 * @return int If +ve i.e. increase, libavl goes to right subtree
 */
typedef int (*avl_keycompare_t)(void*, avldata_t*);

/**
 * @brief Attaches a node to the tree
 * @param head AVL head
 * @param node Node to be attached
 * @param callback int (*)(avldata_t*, avldata_t*)
 * @return bool true on attach success
 */
bool avl_attach(AVL *head, avlnode_t *node, avl_compare_t callback);

/**
 * @brief Detaches a node from the tree
 * @param head AVL head
 * @param key Pointer to key which is present in the data member of a node
 * @param callback int (*)(void*, avldata_t*)
 * @return avlnode_t* Pointer to node to be freed
 */
avlnode_t *avl_detach(AVL *head, void *key, avl_keycompare_t callback);

/**
 * @brief Searches for a key among the tree nodes
 * @param head AVL head
 * @param key Pointer to key which is to be searched
 * @param callback int (*)(void*, avldata_t*)
 * @return avldata_t* Pointer to data containing key
 */
avldata_t *avl_search(AVL *head, void *key, avl_keycompare_t callback);

#endif
