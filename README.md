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
- See the [api](#api) and [example](tests/test.c).

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
The data type for the head node of the AVL tree.

The head needs to be manually allocated and freed. See [example](tests/test.c).
Initialization can be handled by `libavl`.

#### avlnode_t
A library defined struct type.
It's the data type for nodes in the AVL tree.

The `data` member of this type should point to the data that you want to put in the AVL tree.
See [example](tests/test.c).

A node needs to be manually allocated and freed.
Initialization can be handled by `libavl`.

#### avldata_t
A user defined struct type that contains the data to be put in an AVL tree node.

Make sure you define `struct avldata_t` in your code.
As an example of an AVL tree that stores only integers, we will have the following data struct.
```c
struct avldata_t {
    int num;
}
```

#### avl_attach
```c
bool avl_attach(AVL *head, avlnode_t *node, avl_compare_t callback);
```

Attaches a node to the tree.

- param: `head` AVL head
- param: `node` Node to be attached
- param: `callback` Function [`avl_compare_t`](#avl_compare_t)
- return: `true` On attach success

Calls [`avl_compare_t`](#avl_compare_t) type callback function to compare `avldata_t` b/w two nodes.

#### avl_detach
```c
avlnode_t *avl_detach(AVL *head, void *key, avl_keycompare_t callback);
```

Detaches a node from the tree.

- param: `head` AVL head
- param: `key` Pointer to key which is present in the data member of a node
- param: `callback` Function [`avl_keycompare_t`](#avl_keycompare_t)
- return: `avlnode_t*` Pointer to node to be freed

Calls [`avl_keycompare_t`](#avl_keycompare_t) type callback function to compare `key` to `avldata_t` b/w two nodes.

Detach doesn't free a node by itself, so you'll need to do the memory cleanup.

#### avl_search
```c
avldata_t *avl_search(AVL *head, void *key, avl_keycompare_t callback);
```

Searches for a key among the tree nodes.

- param: `head` AVL head
- param: `key` Pointer to key which is to be searched
- param: `callback` Function [`avl_keycompare_t`](#avl_keycompare_t)
- return: `avldata_t*` Pointer to data containing `key`

Calls [`avl_keycompare_t`](#avl_keycompare_t) type callback function to compare `key` to `avldata_t` b/w two nodes.

#### avl_compare_t
```c
int (*)(avldata_t *d1, avldata_t *d2);
```

Callback function type.
Compares data to data b/w nodes.

Has prototype `int (avldata_t*, avldata_t*)`.

- param: `avldata_t*` AVL tree node data
- param: `avldata_t*` AVL tree node data
- return: `int` If 0, match found
- return: `int` If -ve i.e. decrease, `libavl` goes to left subtree
- return: `int` If +ve i.e. increase, `libavl` goes to right subtree

#### avl_keycompare_t
```c
int (*)(void *key, avldata_t *d);
```

Callback function type.
Compares a key to data b/w nodes.

Has prototype `int (void*, avldata_t*)`.

- param: `void*` Pointer to key which is to be searched
- param: `avldata_t*` AVL tree node data
- return: `int` If 0, match found
- return: `int` If -ve i.e. decrease, `libavl` goes to left subtree
- return: `int` If +ve i.e. increase, `libavl` goes to right subtree
