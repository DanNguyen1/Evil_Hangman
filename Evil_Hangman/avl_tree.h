#ifndef AVL_TREE_H
#define AVL_TREE_H

struct node;
typedef struct node Node;

#include "my_string.h"
#include "status.h"
#include "generic_vector.h"

Status tree_insert(Node** pRoot, MY_STRING word, MY_STRING key);
void node_insert(Node** pRoot, Node* node);

void left_rotate(Node** pRoot);
void right_rotate(Node** pRoot);
void right_left_rotate(Node** pRoot);
void left_right_rotate(Node** pRoot);

int check_balance(Node* pRoot);
int height (Node* pRoot);

Node* get_largest_family(Node* pRoot);
GENERIC_VECTOR get_word_family(Node* pRoot);
MY_STRING get_key(Node* pRoot);

void tree_destroy(Node** pRoot);

void print_inorder_traversal(Node* root);

#endif//AVL_TREE_H
