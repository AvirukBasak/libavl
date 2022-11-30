# AVL Tree
C library to implement AVL tree.

Note that `libavl` doesn't actually abstract away the entire AVL tree.
Instead it only takes the job of attaching, detaching and searching nodes.

Therefore things like memory management, node allocation and freeing are to be done manually.

## Usage
- Build with `make`.
- Copy library from `target/`.
- See [api](#api) and [example](#code-example) below.

## API
User defined struct types:
- [`avlnode_t`](#avlnode_t)

Functions:
- [`avl_attach`](#avl_attach)
- [`avl_detach`](#avl_detach)
- [`avl_search`](#avl_search)

Callback function types:
- [`avl_compare_t`](#avl_compare)
- [`avl_keycompare_t`](#avl_keycompare)

Callback functions:
- [`avl_compare`](#avl_compare)
- [`avl_keycompare`](#avl_keycompare)

#### avlnode_t
A user defined struct that is the data type for nodes in `libavl` AVL tree.

Your `avlnode_t` struct defination should look something like below:
```C
struct avlnode_t {
    avlnode_t *__pr;     // parent
    avlnode_t *__lc;     // left child
    avlnode_t *__rc;     // right child
    int        __bf;     // balance factor
    // your data
};
```

The members starting with `__` are used by `libavl` to manage the tree.

#### avl_attach
```c
bool avl_attach(AVL *head, avlnode_t *node, avl_compare_t callback);
```
Attaches a node to the tree and rotates tree around if needed.

- param: AVL head
- param: node to be attached
- param: [`int (*)(avlnode_t*, avlnode_t*)`](#avl_compare)
- return: true on attach success

Calls [`avl_compare`](#avl_compare) callback function to compare two nodes.

#### avl_detach
```c
bool avl_detach(AVL *head, avlnode_t *node, avl_compare_t callback);
```

Detaches a node from the tree and rotates tree around if needed.

- param: AVL head
- param: node to be detached
- param: [`int (*)(avlnode_t*, avlnode_t*)`](#avl_compare)
- return: true on detach success

Calls [`avl_compare`](#avl_compare) callback function to compare two nodes.

Detach doesn't free a node by itself, so you'll need to do the memory cleanup.

#### avl_search
```c
avlnode_t *avl_search(AVL *head, void *key, avl_keycompare_t callback);
```

Searches for a key among the tree nodes.

- param: AVL head
- param: key
- param [`int (*)(void*, avlnode_t*)`](#avl_keycompare)
- return: pointer to node containing `key`

The `key` is the value of a member of the `avlnode_t` struct.
Search returns the node that contains that specific `key`.

Calls [`avl_keycompare`](#avl_keycompare) callback function to compare the `key` and different `avlnode_t` nodes.

#### avl_compare
```c
int avl_compare(avlnode_t *node1, avlnode_t *node2);
```

The `avl_compare` function is a user defined function w/ prototype `int (avlnode_t*, avlnode_t*)`.

- param: AVL tree node
- param: AVL tree node
- return: int

The function is meant to take two `avlnode_t*` and compare them by their member's values.

- If equal return 0
- otherwise return +ve or -ve

If `avl_compare` is `NULL`, library calls `abort`.

If returned value is +ve, `libavl` moves to left subtree.

If returned value is -ve, `libavl` moves to right subtree.

#### avl_keycompare
```c
int avl_keycompare(void *key, avlnode_t *node);
```

The `avl_keycompare` function is a user defined function w/ prototype `int (void*, avlnode_t*)`.

- param: key passed to `alv_search`
- param: AVL tree node
- return int

The function is meant to take a member of `avlnode_t` as `key` and a `avlnode_t*` and compare them.

- If equal return 0
- otherwise return +ve or -ve

If returned value is +ve, `libavl` moves to left subtree.

If returned value is -ve, `libavl` moves to right subtree.

## Code Example
This is an example showing how to initialize a new tree instance.

```c
struct avlnode_t {
    avlnode_t *__pr;
    avlnode_t *__lc;
    avlnode_t *__rc;
    int        __bf;
    int data;        // example data
};
int avl_compare(avlnode_t *n1, avlnode_t *n2) {
    return (int) n2->data - (int) n1->data;
}
in main()
{
    AVL *avl_head = malloc(sizeof(AVL));
    avlnode_t *node1 = malloc(sizeof(avlnode_t));
    avlnode_t *node2 = malloc(sizeof(avlnode_t));
    // initialize nodes
    avl_attach(avl_head, node1, avl_compare);
    avl_attach(avl_head, node2, avl_compare);
    // use tree
    free(node1);
    free(node2);
    free(avl_head);
}
```

Note that `libavl` only takes care of attaching, detaching, and searching nodes.
Memory needs to be manually managed by library user.
