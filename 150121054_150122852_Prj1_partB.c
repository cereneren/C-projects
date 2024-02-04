/*This program takes an input file and creates a binary search tree with given values.
It assigns frequency values with initial value of 0. It prints the tree in pre-order.
After printing it takes search input from the user and increments the frequency values accordingly.
It shifts the elements in the bst with the new frequency values and prints again.
150121054 Ceren Eren
150122852 Zorbey Onur Ak
*/
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

struct Node *insert(struct Node *node, int key,int frequency) //create insert function to insert elements to bst
{
	struct Node *temp=NULL;
	
	//if bst is empty create a root
	if(node==NULL)
	{
		temp=(struct Node *)calloc(1,sizeof(struct Node));
		temp->key=key;
		temp->frequency=frequency;
		temp->leftChild=NULL;
		temp->rightChild=NULL;
		return temp;
	}
	//else assign nodes to either left or right child
	if(key > node->key)
		node->rightChild=insert(node->rightChild,key,frequency);
	else
		node->leftChild=insert(node->leftChild,key,frequency);
		
		
	return node;
}

void sortFrequency(struct Node node[],int length) //this function sorts the elements by their frequencies
{
	int i,j;
	struct Node temp;
	
	for(i=0;i<length;i++)
	{
		for(j=i+1; j<length;j++)
		{			
			if(node[j].frequency>node[i].frequency) //switch elements
			{
				temp=node[i];
				node[i]=node[j];
				node[j]=temp;
			}
			else if(node[j].frequency==node[i].frequency && node[j].key<node[i].key)
			{
				temp=node[i];
				node[i]=node[j];
				node[j]=temp;
			}
			
		}
	}
}

int incrementFrequency(struct Node node[],int key,int length) //it gives the index of the element to be incremented 
{
	int i;
	for(i=0;i<length;i++)
	{
		if(key==node[i].key)
			return i;
	}
}

void clear(struct Node *node) // this function deketes all the elements in the bst 
{	
	if(node!=NULL)
	{
		clear(node->leftChild);
		clear(node->rightChild);
		free(node);
	}
	return;
}

void preorderPrint(struct Node *node) //this function prints elements in pre-order
{
	if(node!=NULL)
	{
		printf("(%d,%d),",node->key,node->frequency);
		preorderPrint(node->leftChild);
		preorderPrint(node->rightChild);
	}
}
	
int main(void)
{
	//initialize values to be used l8r on
	char *tokPtr;
	char charr[100];
	int key,frequency,var;
	int i,j,k;
	i=0,j=0;
	struct Node nodes[100],temp[100];
	
	if((input = fopen("input.txt","r"))==NULL)  
		("Input file could not be opened.");

	while(!feof(input)) { //open the file and assign values to struct array
		fgets(charr,100,input);
		tokPtr=strtok(charr,"\n");
		nodes[i].key = atoi(tokPtr);
		nodes[i].frequency=0;
		temp[i].frequency=0;
		temp[i].key=nodes[i].key;
		i++;
	}
	
	for(j=0;j<i;j++) //insert nodes to bst
		root = insert(root, nodes[j].key,nodes[j].frequency);
	
	printf("Pre-order traversal of constructed tree :"); //print the bst
		preorderPrint(root); 
		
	while(1)
	{
		printf("\nEnter a value to search:"); //prompt user to enter search value
		scanf("%d",&var);
		temp[incrementFrequency(nodes,var,i)].frequency++; //increment frequency of the searched element
		
		clear(root);
		root=NULL;
		for(j=0;j<i;j++) //copy values to temp array
		{
			nodes[j].frequency=temp[j].frequency;
			nodes[j].key=temp[j].key;
		}
		
		sortFrequency(nodes,i); //sort frequency for the both arrays
		sortFrequency(temp,i);
		
		for(j=0;j<i;j++) //insert values again
			root = insert(root, nodes[j].key,nodes[j].frequency);
			
		printf("\nPre-order traversal of constructed tree :");
		preorderPrint(root); 

	}
	return 0;
}


