# AVL Tree
C library to implement AVL tree.

Note that `libavl` doesn't actually abstract away the entire AVL tree.
Instead it only takes the job of attaching, detaching and searching nodes.

Therefore things like memory management, node allocation and freeing are to be done manually.

#### Why libavl is minimalistic?
The library attempts to not depend on `libc`.
Therefore it provides the AVL tree algorithm only.
To make things function, one must manually handle the data to be stored in the tree.

This makes it general purpose.

You'll most likely need a few wrapper libraries around `libavl` to get the functionality you want.

## Usage
- Build with `make`.
- Copy library from `target/`.
- See [api](#api) and [example](#code-example) below.

## API
Library defined types:
- [`AVL`](#avl-type)
- [`avlnode_t`](#avlnode_t)

User defined struct types:
- [`avldata_t`](#avldata_t)

Functions:
- [`avl_attach`](#avl_attach)
- [`avl_detach`](#avl_detach)
- [`avl_search`](#avl_search)

Callback function types:
- [`avl_compare_t`](#avl_compare_t)
- [`avl_keycompare_t`](#avl_keycompare_t)

#### AVL type
The data type for the head node of AVL tree.

The head needs to be manually allocated.
Initialization can be handled by `libavl`.

#### avlnode_t
A library defined struct type.
It's the data type for nodes in the AVL tree.

The `data` member of this type should point to the data that you want to put in the AVL tree.
See [example](#code-example).

A node needs to be manually allocated.
Initialization can be handled by `libavl`.

#### avldata_t
A user defined struct type that contains the data to be put in an AVL tree node.

Make sure you define `struct avldata_t`.
As an example of an AVL tree that stores only integers, we will have the following.
```c
struct avldata_t {
    int num;
}
```

#### avl_attach
```c
bool avl_attach(AVL *head, avlnode_t *node, avl_compare_t callback);
```
Attaches a node to the tree and rotates tree around if needed.

- param: AVL head
- param: node to be attached
- param: [`avl_compare_t`](#avl_compare_t) callback function
- return: true on attach success

Calls [`avl_compare_t`](#avl_compare_t) type callback function to compare `avldata_t` b/w two nodes.

#### avl_detach
```c
bool avl_detach(AVL *head, avlnode_t *node, avl_compare_t callback);
```

Detaches a node from the tree and rotates tree around if needed.

- param: AVL head
- param: node to be detached
- param: [`avl_compare_t`](#avl_compare_t) callback function
- return: true on detach success

Calls [`avl_compare_t`](#avl_compare_t) type callback function to compare `avldata_t` b/w two nodes.

Detach doesn't free a node by itself, so you'll need to do the memory cleanup.

#### avl_search
```c
avldata_t *avl_search(AVL *head, void *key, avl_keycompare_t callback);
```

Searches for a key among the tree nodes.

- param: AVL head
- param: pointer to the key to be searched
- param [`avl_keycompare_t`](#avl_keycompare_t) callback function
- return: pointer to data containing `key`

Calls [`avl_keycompare_t`](#avl_keycompare_t) type callback function to compare the `key` and `avldata_t` b/w two nodes.

The `key` is pointer to a member of the `avldata_t` struct.

Search returns pointer to the data which contains that specific `key`.

#### avl_compare_t
```c
int (*)(avldata_t *d1, avldata_t *d2);
```

A `avl_compare_t` type function is a user defined function w/ prototype `int (avldata_t*, avldata_t*)`.

- param: AVL tree node data
- param: AVL tree node data
- return: int

The function is meant to take `avldata_t*` from two nodes and compare them by their member's values.

- If equal return 0
- otherwise return +ve or -ve

If returned value is +ve, `libavl` moves to left subtree.

If returned value is -ve, `libavl` moves to right subtree.

#### avl_keycompare_t
```c
int (*)(void *key, avldata_t *d);
```

A `avl_keycompare_t` type function is a user defined function w/ prototype `int (void*, avldata_t*)`.

- param: pointer of key passed to `alv_search`
- param: AVL tree node data
- return int

The function is meant to take pointer to a member of an `avldata_t` as `key` and a `avldata_t*` and compare them.

- If equal return 0
- otherwise return +ve or -ve

If returned value is +ve, `libavl` moves to left subtree.

If returned value is -ve, `libavl` moves to right subtree.

## Code Example
This is an example showing how to initialize a new tree instance.

```c
struct avldata_t {
    int num;        // example data
};
int num_comp(avldata_t *d1, avldata_t *d2) {
    return d1->num - d2->num;
}
int num_kcomp(void *key, avldata_t *d) {
    return *(int *) key - d->num;
}
in main()
{
    AVL *avl_head = malloc(sizeof(AVL));
    avlnode_t *node1 = malloc(sizeof(avlnode_t));
    avlnode_t *node2 = malloc(sizeof(avlnode_t));
    // create new data (stack allocated in this case)
    avldata_t data1 = { 12 };
    avldata_t data2 = { 23 };
    // initialize nodes
    node1->data = &data1;
    node2->data = &data2;
    // attatch
    avl_attach(avl_head, node1, num_comp);
    avl_attach(avl_head, node2, num_comp);
    // use tree
    free(node1);
    free(node2);
    free(avl_head);
}
```

Note that `libavl` only takes care of attaching, detaching, and searching nodes.
Memory needs to be manually managed by library user.
