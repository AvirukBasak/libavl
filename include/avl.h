#ifndef __AVL_H__
#define __AVL_H__

#include "stdhead.h"

typedef struct AVL AVL;
typedef struct avlnode_t avlnode_t;
typedef struct avldata_t avldata_t;

struct AVL {
    avlnode_t *root;
};

struct avlnode_t {
    avldata_t *data;  // data
    avlnode_t *pr;    // parent
    avlnode_t *lc;    // left child
    avlnode_t *rc;    // right child
    size_t     bf;    // balance factor
};

typedef int (*avl_compare_t)(avldata_t*, avldata_t*);
typedef int (*avl_keycompare_t)(void*, avldata_t*);

// helper functions
void __avl_calcbf(AVL *head);
void __avl_balance(AVL *head, avlnode_t *node);
void __avl_ll_rot(AVL *head, avlnode_t *node);
void __avl_lr_rot(AVL *head, avlnode_t *node);
void __avl_rr_rot(AVL *head, avlnode_t *node);
void __avl_rl_rot(AVL *head, avlnode_t *node);

bool avl_attach(AVL *head, avlnode_t *node, avl_compare_t callback);
avlnode_t *avl_detach(AVL *head, void *key, avl_keycompare_t callback);
avldata_t *avl_search(AVL *head, void *key, avl_keycompare_t callback);

#endif
