#include "stdhead.h"
#include "avl.h"

void __avl_calcbf(avlnode_t *node)
{
    if (!node) node->bf = 0;
    else node->bf __avl_height(node->lc) - __avl_height(node->rc);
}

int __avl_height(avlnode_t *node)
{
    if (!node) return 0;
    int ltHt = __avl_height(node->lc);
    int rtHt = __avl_height(node->rc);
    return MAX(ltHt +1, rtHt +1);
}

void __avl_balance(AVL *head, avlnode_t *node)
{
    while (abs(node->bf) <= 1)
        node = node->pr;
    if (!node) return;
    // left left case
    if (node->bf > 1 && node->lc->bf >= 0)
        __avl_ll_rot(head, node);
    // left right case
    else if (node->bf > 1 && node->lc->bf < 0)
        __avl_lr_rot(head, node);
    // right right case
    else if (node->bf < -1 && node->rc <= 0)
        __avl_rr_rot(head, node);
    // right left case
    else if (node->bf < -1 && node->rc > 0)
        __avl_rl_rot(head, node);
}

void __avl_ll_rot(AVL *head, avlnode_t *node)
{
    if (!node) return;
    avlnode_t *parent = node->pr;
    avlnode_t *nroot = node->lc;
    avlnode_t *tmp = nroot->rc;
    parent->lc == node ? (parent->lc = nroot) : (parent->rc = nroot);
    nroot->pr = parent;
    nroot->rc = node;
    node->pr = nroot;
    node->lc = tmp;
    tmp->pr = node;
}

void __avl_lr_rot(AVL *head, avlnode_t *node)
{
    
}

void __avl_rr_rot(AVL *head, avlnode_t *node)
{
    if (!node) return;
    avlnode_t *parent = node->pr;
    avlnode_t *nroot = node->rc;
    avlnode_t *tmp = nroot->lc;
    parent->lc == node ? (parent->lc = nroot) : (parent->rc = nroot);
    nroot->pr = parent;
    nroot->lc = node;
    node->pr = nroot;
    node->rc = tmp;
    tmp->pr = node;
}

void __avl_rl_rot(AVL *head, avlnode_t *node);
