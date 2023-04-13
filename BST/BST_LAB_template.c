//////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

///////////////////////////////////////////////////////////////////////

typedef struct _btnode{
	int item;
	struct _btnode *left;
	struct _btnode *right;
} BTNode;

///////////////////////////////////////////////////////////////////////

void insertBSTNode(BTNode **node, int value);
void printBSTInOrder(BTNode *node);
int isBST(BTNode *node, int min, int max);
BTNode *removeBSTNode(BTNode *node, int value);
BTNode *findMin(BTNode *p);

///////////////////////////////////////////////////////////////////////

int main(){
	int i=0;

	BTNode *root=NULL;

	//question 1
	do{
		printf("input a value you want to insert(-1 to quit):");

		scanf("%d",&i);
		if (i!=-1)
			insertBSTNode(&root,i);
	}while(i!=-1);

	//question 2
	printf("\n");
	printBSTInOrder(root);

	//question 3
	if ( isBST(root,-1000000, 1000000)==1)
		printf("It is a BST!\n");
	else
		printf("It is not a BST!\n");

	//question 4
	do{
		printf("\ninput a value you want to remove(-1 to quit):");
		scanf("%d",&i);
		if (i!=-1)
		{
			root=removeBSTNode(root,i);
			printBSTInOrder(root);
		}
	}while(i!=-1);


	return 0;
}

//////////////////////////////////////////////////////////////////////

void insertBSTNode(BTNode **node, int value)
{
	// write your code here
	BTNode *new = malloc(sizeof(BTNode));
	new->item = value;
	new->left = NULL;
	new->right = NULL;

	if(*node == NULL) {
		*node = new;
		return;
	}
	BTNode *curr = *node;
	while(curr != NULL) {
		if(value < curr->item) {
			if(curr->left != NULL) {
				curr = curr->left;
				continue;
			}
			curr->left = new;
			return;
		} else if(value > curr->item) {
			if(curr->right != NULL) {
				curr = curr->right;
				continue;
			}
			curr->right = new;
			return;
		} else
			return;
	}
}

//////////////////////////////////////////////////////////////////////

void printBSTInOrder(BTNode *node)
{
	// write your code here
	if(node == NULL) return;
	
	printBSTInOrder(node->left);
	printf("%d ", node->item);
	printBSTInOrder(node->right);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int isBST(BTNode *node, int min, int max) // the item stored in node has to be smaller than max and larger than min
{
	// write your code here
	if(node == NULL) return 1;
	if(isBST(node->left, min, node->item) && isBST(node->right, node->item, max)) {
		return min < node->item && node->item < max ? 1 : 0;
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BTNode *removeBSTNode(BTNode *node, int value)
{
	// write your code here
	if(node == NULL) return NULL;

	if(value < node->item) 
		node->left = removeBSTNode(node->left, value);
	else if(value > node->item) 
		node->right = removeBSTNode(node->right, value);
	else
		if(node->left == NULL && node->right == NULL) {
			free(node);
			return NULL;
		} else if(node->left != NULL) {
			BTNode *temp = node;
			node = node->left;
			free(temp);
		} else if(node->right != NULL) {
			BTNode *temp = node;
			node = node->right;
			free(temp);
		} else {
			BTNode *temp = findMin(node->right);
			node->item = temp->item;
			temp->item = value;
			node->right = removeBSTNode(node->right, value);
		}
	return node;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BTNode *findMin(BTNode *p)
{
	// write your code here
	if(p == NULL) return NULL;
	while(p->left != NULL) {
		p = p->left;
	}
	return p;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
