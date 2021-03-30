#include <stdlib.h>
#include <stdio.h>
#include "avl_tree.h"
#include "generic_vector.h"
#include "my_string.h"
#include "status.h"
#include "max.h"

struct node
{
	MY_STRING key;
	GENERIC_VECTOR word_family;
	Node* left;
	Node* right;
};

Status tree_insert(Node** pRoot, MY_STRING hWord, MY_STRING hKey)
{
	if (*pRoot == NULL)
	{
		*pRoot = (Node*)malloc(sizeof(Node));
		if (*pRoot == NULL)
		{
			return FAILURE;
		}
		(*pRoot)->key = my_string_init_c_string(my_string_c_str(hKey));
		(*pRoot)->word_family = generic_vector_init_default(my_string_assignment, my_string_destroy);
		(*pRoot)->left = NULL;
		(*pRoot)->right = NULL;
		generic_vector_push_back((*pRoot)->word_family, hWord);
		return SUCCESS;
	}
	else
	{
		if (my_string_compare((*pRoot)->key, hKey) < 0)
		{
			tree_insert(&((*pRoot)->left), hWord, hKey);
		}
		else if (my_string_compare((*pRoot)->key, hKey) > 0)
		{
			tree_insert(&((*pRoot)->right), hWord, hKey);
		}
		else
		{
			generic_vector_push_back((*pRoot)->word_family, hWord);
		}

		if (check_balance(*pRoot) > 1 || check_balance(*pRoot) < -1) //if we find an imbalance...
		{
			if (check_balance(*pRoot) > 1 && check_balance((*pRoot)->right) > 0) //case for basic left rotate (right heavy)
			{
				left_rotate(pRoot);
			}

			else if (check_balance(*pRoot) < -1 && check_balance((*pRoot)->left) < 0) //case for basic right rotate (left heavy)
			{
				right_rotate(pRoot);
			}

			else if (check_balance(*pRoot) > 1 && check_balance((*pRoot)->right) < 0) //case for right left rotate
			{
				right_left_rotate(pRoot);
			}
			else if (check_balance(*pRoot) < -1 && check_balance((*pRoot)->left) > 0) //case for left right rotate
			{
				left_right_rotate(pRoot);
			}
		}
	}
	return SUCCESS;
}

void node_insert(Node** pRoot, Node* node)
{
	if (*pRoot == NULL)
	{
		*pRoot = node;
	}
	else
	{
		if (my_string_compare((*pRoot)->key, node->key) < 0)
		{
			node_insert(&((*pRoot)->left), node);
		}
		else if (my_string_compare((*pRoot)->key, node->key) > 0)
		{
			node_insert(&((*pRoot)->right), node);
		}
	}
}

void left_rotate(Node** pRoot)
{
	//make some temp variables for swapping
	Node* temp_root = NULL;
	Node* temp_root_right = NULL;
	Node* temp_node = NULL;
	
	//in case there is a hanging node that inteferes with rotating (will be lost if not taken care of)
	if ((*pRoot)->right->left != NULL)
	{
		temp_node = (*pRoot)->right->left; //store the hanging node
		(*pRoot)->right->left = NULL; //clear the hanging node from the tree
	}
	 
	//left rotating (basically swapping?)
	temp_root = *pRoot;
	temp_root_right = (*pRoot)->right;

	*pRoot = NULL;
	temp_root->right = NULL;

	temp_root_right->left = temp_root;

	*pRoot = temp_root_right;

	if (temp_node != NULL)
	{
		node_insert(pRoot, temp_node); //re-insert the hanging node into the new tree
	}
}

void right_rotate(Node** pRoot)
{
	//make some temp variables for swapping
	Node* temp_root = NULL;
	Node* temp_root_left = NULL;
	Node* temp_node = NULL;

	//in case there is a hanging node that inteferes with rotating (will be lost if not taken care of)
	if ((*pRoot)->left->right != NULL)
	{
		temp_node = (*pRoot)->left ->right; //store the hanging node
		(*pRoot)->left->right = NULL; //clear the hanging node from the tree
	}

	//right rotating (basically swapping?)
	temp_root = *pRoot;
	temp_root_left = (*pRoot)->left;

	*pRoot = NULL;
	temp_root->left = NULL;

	temp_root_left->right = temp_root;

	*pRoot = temp_root_left;

	if (temp_node != NULL)
	{
		node_insert(pRoot, temp_node); //re-insert the hanging node into the new tree
	}
}

void right_left_rotate(Node** pRoot)
{
	//a temp variable in case there is a hanging node
	Node* temp_node = NULL;
	if ((*pRoot)->right->left->left != NULL)
	{
		temp_node = (*pRoot)->right->left->left; //store the hanging node
		(*pRoot)->right->left->left = NULL; //clear the hanging node from the tree
	}
	right_rotate(&((*pRoot)->right));
	left_rotate(pRoot);
	if (temp_node != NULL)
	{
		node_insert(pRoot, temp_node); //re-insert the hanging node into the new tree
	}
}

void left_right_rotate(Node** pRoot)
{
	//a temp variable in case there is a hanging node
	Node* temp_node = NULL;
	if ((*pRoot)->left->right->right != NULL)
	{
		temp_node = (*pRoot)->left->right->right;//store the hanging node
		(*pRoot)->left->right->right = NULL; //clear the hanging node from the tree
	}
	left_rotate(&((*pRoot)->left));
	right_rotate(pRoot);
	if (temp_node != NULL)
	{
		node_insert(pRoot, temp_node); //re-insert the hanging node into the new tree
	}
}

int check_balance(Node* pRoot)
{
	if (pRoot == NULL)
	{
		return 0;
	}

	return (height(pRoot->right) - height(pRoot->left));
}

int height (Node* pRoot)
{
	if (pRoot == NULL)
	{
		return 0;
	}

	return max(height(pRoot->left), height(pRoot->right)) + 1;
}

Node* get_largest_family(Node* pRoot)
{
	if (pRoot == NULL)
	{
		return NULL;
	}

	Node* largest_left = get_largest_family(pRoot->left);
	Node* largest_right = get_largest_family(pRoot->right);
	Node* largest;

	if (largest_left == NULL && largest_right == NULL)
	{
		return pRoot;
	}	
	else if (largest_left == NULL && largest_right != NULL)
	{
		return (generic_vector_get_size(pRoot->word_family) > generic_vector_get_size(largest_right->word_family) ? pRoot : largest_right);
	}
	else if (largest_left != NULL && largest_right == NULL)
	{
		return (generic_vector_get_size(pRoot->word_family) > generic_vector_get_size(largest_left->word_family) ? pRoot : largest_left);
	}
	else
	{
		largest = (generic_vector_get_size(largest_left->word_family) > generic_vector_get_size(largest_right->word_family) ? largest_left : largest_right);
		return (generic_vector_get_size(pRoot->word_family) > generic_vector_get_size(largest->word_family) ? pRoot : largest);
	}	
}


GENERIC_VECTOR get_word_family(Node* pRoot)
{
	return pRoot->word_family;
}

MY_STRING get_key(Node* pRoot)
{
	return pRoot->key;
}


void tree_destroy(Node** pRoot)
{
	if (*pRoot != NULL)
	{
		tree_destroy(&((*pRoot)->left));
		tree_destroy(&((*pRoot)->right));
		my_string_destroy(&((*pRoot)->key));
		generic_vector_destroy(&((*pRoot)->word_family));
		free(*pRoot);
		*pRoot = NULL;
	}
}

void print_inorder_traversal(Node* root)
{
	if (root != NULL)
	{
		print_inorder_traversal(root->left);
		printf("%s %d\n", my_string_c_str(root->key), generic_vector_get_size(root->word_family));
		print_inorder_traversal(root->right);
	}
}

