#include <stdio.h>
#include <stdlib.h>

#define TABLESIZE 37
#define PRIME     13

enum Marker {EMPTY,USED,DELETED};

typedef struct _slot{
    int key;
    enum Marker indicator;
} HashSlot;

int HashInsert(int key, HashSlot hashTable[]);
int HashDelete(int key, HashSlot hashTable[]);


int hash1(int key);
int hash2(int key);

int main()
{
    int opt;
    int i;
    int key;
    int comparison;
    HashSlot hashTable[TABLESIZE];

    for(i=0;i<TABLESIZE;i++){
        hashTable[i].indicator = EMPTY;
        hashTable[i].key = 0;
    }

    printf("============= Hash Table ============\n");
    printf("|1. Insert a key to the hash table  |\n");
    printf("|2. Delete a key from the hash table|\n");
    printf("|3. Print the hash table            |\n");
    printf("|4. Quit                            |\n");
    printf("=====================================\n");
    printf("Enter selection: ");
    scanf("%d",&opt);
    while(opt>=1 && opt <=3){
        switch(opt){
        case 1:
            printf("Enter a key to be inserted:\n");
            scanf("%d",&key);
            comparison = HashInsert(key,hashTable);
            if(comparison <0)
                printf("Duplicate key\n");
            else if(comparison < TABLESIZE)
                printf("Insert: %d Key Comparisons: %d\n",key, comparison);
            else
                printf("Key Comparisons: %d. Table is full.\n",comparison);
            break;
        case 2:
            printf("Enter a key to be deleted:\n");
            scanf("%d",&key);
            comparison = HashDelete(key,hashTable);
            if(comparison <0)
                printf("%d does not exist.\n", key);
            else if(comparison <= TABLESIZE)
                printf("Delete: %d Key Comparisons: %d\n",key, comparison);
            else
                printf("Error\n");
            break;
        case 3:
            for(i=0;i<TABLESIZE;i++) printf("%d: %d %c\n",i, hashTable[i].key,hashTable[i].indicator==DELETED?'*':' ');
            break;
        }
        printf("Enter selection: ");
        scanf("%d",&opt);
    }
    return 0;
}

int hash1(int key)
{
    return (key % TABLESIZE);
}

int hash2(int key)
{
    return (key % PRIME) + 1;
}

int HashInsert(int key, HashSlot hashTable[])
{
	//Write your code here
	unsigned increment = abs(hash2(key)),
			 cnt = 0;  // number of key comparisons
	int insertIndex = -1;

	for (unsigned i = 0; i < TABLESIZE; ++i) {
		unsigned index = abs(hash1(key + i * increment));
		if (hashTable[index].indicator == EMPTY) {
			if (insertIndex == -1)
				insertIndex = index;
			break;
		} else if (hashTable[index].indicator == DELETED) {
			if (insertIndex == -1)
				insertIndex = index;
		} else {  // if (hashTable[index].indicator == USED)
			if (hashTable[index].key == key)
				return -1;
			else
				++cnt;
		}
	}
	// The condition i == TABLESIZE does not imply that the table is full.
	// Counterexample: key to be inserted at a DELETED slot. 
	// 				   The loop continues to search for duplicates until 
	// 				   all of the slots are checked, i.e., until i == TABLESIZE.
	if (insertIndex == -1)  // table is full
		return TABLESIZE;
	hashTable[insertIndex].key = key;
	hashTable[insertIndex].indicator = USED;
	return cnt;
}

int HashDelete(int key, HashSlot hashTable[])
{
	//Write your code here
	// int ii = 0;
    // for ( ; ii < TABLESIZE; ++ii) {
    //     if (hashTable[ii].key == key && hashTable[ii].indicator == USED) break;
    // }
    // if (ii == TABLESIZE) return -1;
	unsigned i = 0, cnt = 0;
	unsigned index;

	do {
		index = abs(hash1(key + i++ * abs(hash2(key))));
		if (hashTable[index].indicator == DELETED) {
			if (hashTable[index].key == key)
				return -1;
			continue;
		}
		if (hashTable[index].indicator == EMPTY) {
			return -1;
		}
		if (hashTable[index].indicator == USED) {
			++cnt;
			if (hashTable[index].key == key) {
				hashTable[index].indicator = DELETED;
				return cnt;
			} else {
				continue;
			}
		}
	} while (i < TABLESIZE);
	if (i == TABLESIZE)  // table is full
		return -1;
	return cnt;
}