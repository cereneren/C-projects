/* Data Structures Project 1 part A 
This program takes an input file and creates a binary search tree with the given key and frequency values.
Then, it sorts the elements according to their frequencies, after that it inserts sorted elements to binaru search tree.
Finally, it prints the binary search tree in pre-order.
Ceren Eren 150121054
Zorbey Onur Ak 150122852 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

FILE *input;

struct Node //create a struct node 
{
	int key;
	int frequency;
	struct Node *leftChild;
	struct Node *rightChild; 
}*root=NULL; //initialize a root value to NULL

struct Node *insert(struct Node *node, int key) //create insert function to insert elements to bst
{
	struct Node *temp=NULL;
	
	//if bst is empty create a root
	if(node==NULL)
	{
		temp=(struct Node *)calloc(1,sizeof(struct Node));
		temp->key=key;
		temp->leftChild=NULL;
		temp->rightChild=NULL;
		return temp;
	}
	//else assign nodes to either left or right child
	if(key > node->key)
		node->rightChild=insert(node->rightChild,key);
	else
		node->leftChild=insert(node->leftChild,key);
		
		
	return node;
}

void sortFrequency(struct Node node[],int length) //sort nodes according to their frequency values in descending order
{
	int i,j;
	struct Node temp;
	
	for(i=0;i<length;i++)
	{
		for(j=i+1; j<length;j++)
		{			
			if(node[j].frequency>node[i].frequency)
			{
				temp=node[i];
				node[i]=node[j];
				node[j]=temp;
			}
		}
	}
}

void preorderPrint(struct Node *node) //print bst in pre-order
{
	if(node)
	{
		printf("%d, ",node->key);
		preorderPrint(node->leftChild);
		preorderPrint(node->rightChild);
	}
}
	
int main(void)
{
	//initialize values to use in FILE IO operations
	char *tokPtr;
	char charr[100];
	int key,frequency;
	int i,j;
	i=0,j=0;
	struct Node nodes[20];
	
	if((input = fopen("input.txt","r"))==NULL)  //open file
		("Input file could not be opened.");

	while(!feof(input)) { //tokenize file element by element
		fgets(charr,100,input);
		tokPtr=strtok(charr,",");
		nodes[i].key = atoi(tokPtr);
		tokPtr = strtok(NULL,"\n");
		nodes[i].frequency= atoi(tokPtr);
		i++;
	}
	sortFrequency(nodes,i);
	
	for(j=0;j<i;j++) //insert sorted nodes to bst
		root = insert(root, nodes[j].key);
	
	printf("Pre-order traversal of constructed tree :");
	preorderPrint(root); //print preorder bst
		
	return 0;
}


