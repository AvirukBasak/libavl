#include "stdhead.h"
#include "avl.h"

void __avl_calcbf(avlnode_t *node)
{
    if (!node) node->bf = 0;
    else node->bf __avl_height(node->left) - __avl_height(node->right);
}

int __avl_height(avlnode_t *node)
{
    if (!node) return 0;
    int ltHt = __avl_height(node->left);
    int rtHt = __avl_height(node->right);
    return MAX(ltHt +1, rtHt +1);
}

void __avl_balance(AVL *head, avlnode_t *node)
{
    while (abs(node->bf) <= 1)
        node = node->pr;
    if (!node) return;
    // left left case
    if (node->bf > 1 && node->left->bf >= 0)
        __avl_ll_rot(head, node);
    // left right case
    else if (node->bf > 1 && node->left->bf < 0)
        __avl_lr_rot(head, node);
    // right right case
    else if (node->bf < -1 && node->right <= 0)
        __avl_rr_rot(head, node);
    // right left case
    else if (node->bf < -1 && node->right > 0)
        __avl_rl_rot(head, node);
}

void __avl_ll_rot(AVL *head, avlnode_t *node);
void __avl_lr_rot(AVL *head, avlnode_t *node);
void __avl_rr_rot(AVL *head, avlnode_t *node);
void __avl_rl_rot(AVL *head, avlnode_t *node);
