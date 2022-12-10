#include <stdlib.h>

#include "stdhead.h"
#include "avl.h"

void __avl_calcbf(avlnode_t *node)
{
    if (!node) return;
    else {
        node->bf = __avl_height(node->lc) - __avl_height(node->rc);
        __avl_calcbf(node->pr);
    }
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
    if (!node) return;
    __avl_calcbf(node);
    while (node->pr && abs(node->bf) <= 1)
        node = node->pr;
    // left left case
    if (node->bf > 1 && node->lc->bf >= 0)
        __avl_ll_rot(head, node);
    // left right case
    else if (node->bf > 1 && node->lc->bf < 0)
        __avl_lr_rot(head, node);
    // right right case
    else if (node->bf < -1 && node->rc->bf <= 0)
        __avl_rr_rot(head, node);
    // right left case
    else if (node->bf < -1 && node->rc->bf > 0)
        __avl_rl_rot(head, node);
}

void __avl_ll_rot(AVL *head, avlnode_t *node)
{
    if (!node) return;
    avlnode_t *parent = node->pr;
    avlnode_t *nroot = node->lc;
    avlnode_t *tmp = nroot->rc;
    if (parent)
        parent->lc == node ? (parent->lc = nroot) : (parent->rc = nroot);
    else head->root = nroot;
    nroot->pr = parent;
    nroot->rc = node;
    if (node) node->pr = nroot;
    node->lc = tmp;
    if (tmp) tmp->pr = node;
}

void __avl_lr_rot(AVL *head, avlnode_t *node)
{
   /*
    *        parent                       parent
    *          |                            |
    *          n0                        __ n2 __
    *         /  \                     /          \
    *       n1    n0rc      =>       n1            n0
    *      /  \                     /  \          /  \
    *  n1lc    n2               n1lc    n2lc  n2rc    n0rc
    *         /  \
    *     n2lc    n2rc
    */
    if (!node) return;
    avlnode_t *parent = node->pr;
    avlnode_t *n0 = node;
    avlnode_t *n1 = n0->lc;
    avlnode_t *n2 = n1->rc;
    // n2 becomes new root of the subtree
    if (parent)
        parent->lc == n0 ? (parent->lc = n2) : (parent->rc = n2);
    else head->root = n2;
    n2->pr = parent;
    // n1 and n0 take custody of n2's present children
    n1->rc = n2->lc;
    if (n2->lc) n2->lc->pr = n1;
    n0->lc = n2->rc;
    if (n2->rc) n2->rc->pr = n0;
    // new children of n2: n1 and n0
    n2->lc = n1;
    n1->pr = n2;
    n2->rc = n0;
    n0->pr = n2;
}

void __avl_rr_rot(AVL *head, avlnode_t *node)
{
    if (!node) return;
    avlnode_t *parent = node->pr;
    avlnode_t *nroot = node->rc;
    avlnode_t *tmp = nroot->lc;
    if (parent)
        parent->lc == node ? (parent->lc = nroot) : (parent->rc = nroot);
    else head->root = nroot;
    nroot->pr = parent;
    nroot->lc = node;
    if (node) node->pr = nroot;
    node->rc = tmp;
    if (tmp) tmp->pr = node;
}

void __avl_rl_rot(AVL *head, avlnode_t *node)
{
    /*
    *        parent                       parent
    *          |                            |
    *          n0                        __ n2 __
    *         /  \                     /          \
    *     n0lc    n1        =>       n0            n1
    *            /  \               /  \          /  \
    *          n2    n1rc       n0lc    n2lc  n2rc    n1rc
    *         /  \
    *     n2lc    n2rc
    */
    if (!node) return;
    avlnode_t *parent = node->pr;
    avlnode_t *n0 = node;
    avlnode_t *n1 = n0->rc;
    avlnode_t *n2 = n1->lc;
    // n2 becomes new root of the subtree
    if (parent)
        parent->lc == n0 ? (parent->lc = n2) : (parent->rc = n2);
    else head->root = n2;
    n2->pr = parent;
    // n0 and n1 take custody of n2's present children
    n0->rc = n2->lc;
    if (n2->lc) n2->lc->pr = n0;
    n1->lc = n2->rc;
    if (n2->rc) n2->rc->pr = n1;
    // new children of n2: n0 and n1
    n2->lc = n0;
    n0->pr = n2;
    n2->rc = n1;
    n1->pr = n2;
}
