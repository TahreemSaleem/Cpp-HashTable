/*
*  hash-map-chaining.c - Daniel "bodom_lx" Graziotin <http://daniel.graziotin.net>
*      An implementation in C of search and insertion operations for a hash table with chaining
*  compile with: gcc -lm hash-map-chaining.c
*/

#include <iostream>
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"

#define TRUE 1
#define FALSE !TRUE
#define SIZE_HASH_MAP 10
#define HASH_CONSTANT .7

typedef struct node{
	int value;
	struct node *next;
}t_hashTableNode;

static t_hashTableNode* hashMapChained[SIZE_HASH_MAP];              // hash table
/* HASH FUNCTIONS */
int sum= 0;
int count1 = 0;
int hash(int value);                                                /* hash function */
void chainedHashInsert(int value);                                  /* inserts a value in the hash table, using chaining */
int chainedHashSearch(int value);                                   /* searches for a value in the hash table */
/* AUXILIARY FUNCTIONS */
void populateHashMap(int numbersToBeGenerated);                     /* AUX: inserts random integer numbers in the hash table */
void printList(int i);                                              /* AUX: prints the linked list stored in hashMapChained[i] */
void printHashMap();                                                /* AUX: prints the whole hash hashMapChained */
void searchNumbers(int numbersToBeSearched);                        /* AUX: searches random numbers in the hash map */
void avgcollisions();												/*calculates average collisions*/
/* HASH FUNCTIONS */
int hash(int value){
	return (SIZE_HASH_MAP * fmod((value * HASH_CONSTANT), 1));
}

void chainedHashInsert(int value){
	int probe = hash(value);                                        // stores the hash value of the number to be inserted
	if (hashMapChained[probe] == NULL){                              // if the list in hashMapChained[probe] is empty
		hashMapChained[probe] = (node*)malloc(sizeof(t_hashTableNode));    // then creates a new list
		hashMapChained[probe]->value = value;
		hashMapChained[probe]->next = NULL;
	}
	else{                                                          // if the list in hashMapChained[probe] is not empty
		t_hashTableNode *hashTableNode = hashMapChained[probe];
		while (hashTableNode->next != NULL){                           // scrolls down the list
			hashTableNode = hashTableNode->next;
		}
		hashTableNode->next = (node*)malloc(sizeof(t_hashTableNode));      // insert the value as the last element of the list
		hashTableNode->next->value = value;
		hashTableNode->next->next = NULL;
	}

}



/* MAIN FUNCTION */
int main(int argc, char const *argv[]){
	srand(time(NULL));
	populateHashMap(25);
	printf("\nsituation after insertion of random integers:\n");
	printHashMap();
	avgcollisions();
	return 0;
}


/* AUXILIARY FUNCTIONS */
void populateHashMap(int numbersToBeGenerated){                     // generates random numbers
	int k = 1;
	int randomNumber;
	for (k = 1; k <= numbersToBeGenerated; k++){
		randomNumber = rand() % 1000 + 1;
		chainedHashInsert(randomNumber);                            // inserts them in the hash map
	}
}

void printList(int hashMapRow){
	t_hashTableNode *hashMapNode = hashMapChained[hashMapRow];      // pointer to the linked list stored in hashMapChained[hashMapRow]
	int count = 0;
	while (hashMapNode != NULL){
		printf("%d ", hashMapNode->value);                           // prints out the value of the nodes
		hashMapNode = hashMapNode->next;
	
	}
	
	
}

void printHashMap(){
	int i;
	
	for (i = 0; i<SIZE_HASH_MAP; i++){                                   // for every row of the hash map
		printf("hashMapChained[%d]:\t", i);
		printList(i);                                               // prints the list contained in it
		printf("\n");
	}
	
}
void  avgcollisions() {		//This function is traversing the nodes in each slot and counting the collisions
	 int sum=0,count;
	

	for (int i = 0; i < SIZE_HASH_MAP; i++)
	{
		t_hashTableNode *hashMapNode = hashMapChained[i];      // pointer to the linked list stored in hashMapChained[hashMapRow]
		count = 0;
		while (hashMapNode != NULL){
			hashMapNode = hashMapNode->next;
				count++;
		}
		if (count != 0)
			sum += count - 1;
		
	}
	float avg = (float)sum / (SIZE_HASH_MAP);
	printf("Average collisions per slot is: %.2f \n", avg);
}
