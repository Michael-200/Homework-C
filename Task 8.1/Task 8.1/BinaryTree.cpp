#include "BinaryTree.h"
#include <string.h>
#include <stdio.h>

const int maxSize = 20;

struct TreeElement
{
	int key = 0;
	char value[maxSize]{};
	TreeElement* parent = nullptr;
	TreeElement* left = nullptr;
	TreeElement* right = nullptr;
};

struct Tree
{
	TreeElement* head = nullptr;
};

Tree* createTree()
{
	Tree* newTree = new Tree;
	return newTree;
}

TreeElement* getHead(Tree* tree)
{
	return tree->head;
}

void addElementToTree(Tree* tree, int newKey, char newValue[])
{
	TreeElement* newElement = new TreeElement;
	newElement->key = newKey;
	strcpy(newElement->value, newValue);

	TreeElement* cursor = tree->head;
	if (cursor != nullptr)
	{
		while (true)
		{
			if (newKey == cursor->key)
			{
				strcpy(cursor->value, newValue);
				delete newElement;
				break;
			}
			if (newKey < cursor->key)
			{
				if (cursor->left == nullptr)
				{
					cursor->left = newElement;
					newElement->parent = cursor;
					break;
				}
				cursor = cursor->left;
			}
			else if (newKey > cursor->key)
			{
				if (cursor->right == nullptr)
				{
					cursor->right = newElement;
					newElement->parent = cursor;
					break;
				}
				cursor = cursor->right;
			}
			else
			{
				return;
			}
		}
	}
	else
	{
		tree->head = newElement;
	}
}

TreeElement* minimumElement(TreeElement* treeElement)
{
	if (treeElement->left == nullptr)
	{
		return treeElement;
	}
	return minimumElement(treeElement->left);
}

TreeElement* next(TreeElement* treeElement)
{
	if (treeElement->right != nullptr)
	{
		return minimumElement(treeElement->right);
	}
	TreeElement* tempElement = treeElement->parent;
	while (tempElement != nullptr && treeElement == tempElement->right)
	{
		treeElement = tempElement;
		tempElement = tempElement->parent;
	}
	return tempElement;
}

TreeElement* deleteElementFromTree(Tree* tree, TreeElement* treeElement, int keyToDelete)
{
	if (treeElement == nullptr)
	{
		return treeElement;
	}
	if (keyToDelete < treeElement->key)
	{
		treeElement->left = deleteElementFromTree(tree, treeElement->left, keyToDelete);
	}
	else if (keyToDelete > treeElement->key)
	{
		treeElement->right = deleteElementFromTree(tree, treeElement->right, keyToDelete);
	}
	else if (treeElement->left != nullptr && treeElement->right != nullptr)
	{
		TreeElement* tempElement = minimumElement(treeElement->right);
		treeElement->key = tempElement->key;
		strcpy(treeElement->value, tempElement->value);
		treeElement->right = deleteElementFromTree(tree, treeElement->right, treeElement->key);
	}
	else
	{
		if (treeElement->left != nullptr)
		{
			TreeElement* tempElement = treeElement;
			treeElement = treeElement->left;
			if (tree->head->value == tempElement->value)
			{
				tree->head = treeElement;
			}
			delete tempElement;
		}
		else if (treeElement->right != nullptr)
		{
			TreeElement* tempElement = treeElement;
			treeElement = treeElement->right;
			if (tree->head->value == tempElement->value)
			{
				tree->head = treeElement;
			}
			delete tempElement;
		}
		else
		{
			TreeElement* tempElement = treeElement;
			treeElement = nullptr;
			if (tree->head->value == tempElement->value)
			{
				tree->head = treeElement;
			}
			delete tempElement;
		}
	}
	return treeElement;
}

char* getValue(Tree* tree, int keyToReturn)
{
	TreeElement* cursor = tree->head;
	if (cursor != nullptr)
	{
		while (keyToReturn != cursor->key)
		{
			if (keyToReturn < cursor->key)
			{
				if (cursor->left == nullptr)
				{
					return nullptr;
				}
				cursor = cursor->left;
			}
			else if (keyToReturn > cursor->key)
			{
				if (cursor->right == nullptr)
				{
					return nullptr;
				}
				cursor = cursor->right;
			}
		}
		return cursor->value;
	}
	return nullptr;
}

bool isContain(Tree* tree, int keyToChecked)
{
	return getValue(tree, keyToChecked) != nullptr;
}

void deleteTreeElement(TreeElement* treeElement)
{
	if (treeElement->left != nullptr)
	{
		deleteTreeElement(treeElement->left);
	}

	if (treeElement->right != nullptr)
	{
		deleteTreeElement(treeElement->right);
	}

	delete treeElement;
}

void deleteTree(Tree* tree)
{
	if (tree->head == nullptr)
	{
		delete tree;
		return;
	}
	deleteTreeElement(tree->head);

	delete tree;
}