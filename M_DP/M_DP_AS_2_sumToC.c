#include <stdio.h>
#include <stdlib.h>

typedef struct _arraynode
{
    int *itemArray;
    int sizeArray;
    struct _arraynode *next;
} ArrayNode;

typedef struct _arraylist
{
    int size; // the size of a possible sequence
    ArrayNode *head;
} ArrayList;

typedef struct _listnode
{
    int item;
    struct _listnode *next;
} ListNode;

typedef struct _linkedlist
{
    int sum; // the number of possible sequences
    int size;
    ListNode *head;
} LinkedList;

// You should not change the prototypes of these functions
//////LinkedList///////////////////////////////////////////
int insertNode(LinkedList *ll, int index, int coin);
int removeNode(LinkedList *ll, int index);
ListNode *findNode(LinkedList ll, int index);
void removeAllItems(LinkedList *ll);
///////////////////////////////////////////////////

void sumToC(LinkedList *ll, int C, ArrayList *al);
int main()
{
    int C;
    printf("Enter a number:\n");
    scanf("%d", &C);

    LinkedList ll;
    ll.head = NULL;
    ll.sum = 0;
    ll.size = 0;
    ArrayList al;
    al.head = NULL;
    al.size = 0;

    sumToC(&ll, C, &al);
    ArrayNode *temp;
    int i, j;
    temp = al.head;
    for (i = 0; i < al.size; i++)
    {
        for (j = 0; j < temp->sizeArray; j++)
            printf(" %d ", temp->itemArray[j]);
        printf("\n");
        temp = temp->next;
    }

    return 0;
}

///////////////////////////////////////////////////////
int insertNode(LinkedList *ll, int index, int value)
{

    ListNode *pre, *cur;

    if (ll == NULL || index < 0 || index > ll->size)
        return 0;

    if (index == 0)
    {
        cur = ll->head;
        ll->head = (ListNode *)malloc(sizeof(ListNode));
        ll->head->item = value;
        ll->head->next = cur;
        ll->sum += value;
        ll->size++;
        return 1;
    }

    // Find the nodes before and at the target position
    // Create a new node and reconnect the links
    if ((pre = findNode(*ll, index - 1)) != NULL)
    {
        cur = pre->next;
        pre->next = malloc(sizeof(ListNode));
        pre->next->item = value;
        pre->next->next = cur;
        ll->sum += value;
        ll->size++;
        return 1;
    }

    return 0;
}

int removeNode(LinkedList *ll, int index)
{

    ListNode *pre, *cur;

    // Highest index we can remove is size-1
    if (ll == NULL || index < 0 || index > ll->size)
        return 0;

    // If removing first node, need to update head pointer
    if (index == 0)
    {
        cur = ll->head->next;
        ll->sum -= ll->head->item;
        free(ll->head);
        ll->head = cur;
        ll->size--;
        return 1;
    }

    // Find the nodes before and after the target position
    // Free the target node and reconnect the links
    if ((pre = findNode(*ll, index - 1)) != NULL)
    {

        if (pre->next == NULL)
            return 0;

        cur = pre->next;
        ll->sum -= cur->item;
        pre->next = cur->next;
        free(cur);
        ll->size--;
        return 1;
    }

    return 0;
}

ListNode *findNode(LinkedList ll, int index)
{

    ListNode *temp;

    if (index < 0 || index >= ll.size)
        return NULL;

    temp = ll.head;

    if (temp == NULL || index < 0)
        return NULL;

    while (index > 0)
    {
        temp = temp->next;
        if (temp == NULL)
            return NULL;
        index--;
    }

    return temp;
}

void removeAllItems(LinkedList *ll)
{
    ListNode *cur = ll->head;
    ListNode *tmp;

    while (cur != NULL)
    {
        tmp = cur->next;
        free(cur);
        cur = tmp;
    }
    ll->head = NULL;
    ll->size = 0;
    ll->sum = 0;
}

void listSumC(ArrayList **memo, int C, ArrayList *al);
void arrayListcpy(ArrayList *src, ArrayList *dest);

void sumToC(LinkedList *ll, int C, ArrayList *al)
{
    ArrayList **memo = malloc(C * sizeof(ArrayList *));
    for (int i = 0; i < C; ++i) {
        memo[i] = NULL;
    }

    listSumC(memo, C, al);
}

void listSumC(ArrayList **memo, int C, ArrayList *al)
{
    // Write your code here
    al->size = 0;
    al->head = NULL;
    ArrayNode *alPtr = al->head;

    for (int i = 1; i < C - i; ++i) {
        ArrayList *temp = malloc(sizeof(ArrayList));
        temp->size = 0;
        temp->head = NULL;

        if (memo[C - i - 1]) {
            arrayListcpy(memo[C - i - 1], temp);
        } else {
            listSumC(memo, C - i, temp);
        }

        ArrayNode *ptr = temp->head;

        for (int j = 0; j < temp->size; ++j, ptr = ptr->next) {
            if (ptr->itemArray[0] > i) {
                ArrayNode *new = malloc(sizeof(ArrayNode));
                new->sizeArray = 1 + ptr->sizeArray;
                new->itemArray = malloc(new->sizeArray * sizeof(int));
                new->itemArray[0] = i;
                for (int k = 0; k < ptr->sizeArray; ++k) {
                    new->itemArray[k + 1] = ptr->itemArray[k];
                }
                new->next = NULL;

                if (al->head == NULL) {
                    al->head = new;
                    alPtr = al->head;
                } else {
                    alPtr->next = new;
                    alPtr = alPtr->next;
                }
                ++(al->size);
            }
        }
        free(temp);
    }
    
    ArrayNode *new = malloc(sizeof(ArrayNode));
    new->sizeArray = 1;
    new->itemArray = malloc(sizeof(int));
    new->itemArray[0] = C;
    new->next = NULL;

    if (al->head == NULL) {
        al->head = new;
        alPtr = al->head;
    } else {
        alPtr->next = new;
        alPtr = alPtr->next;
    }
    ++(al->size);

    memo[C - 1] = malloc(sizeof(ArrayList));
    arrayListcpy(al, memo[C - 1]);
}

void arrayListcpy(ArrayList *src, ArrayList *dest)
{
    dest->size = src->size;
    dest->head = NULL;
    if (src->head == NULL) return;

    ArrayNode *destPtr = dest->head;
    ArrayNode *srcPtr = src->head;
    
    for (int i = 0; i < src->size; ++i, srcPtr = srcPtr->next) {
        ArrayNode *new = malloc(sizeof(ArrayNode));
        new->sizeArray = srcPtr->sizeArray;
        new->itemArray = malloc(new->sizeArray * sizeof(int));
        for (int j = 0; j < srcPtr->sizeArray; ++j) {
            new->itemArray[j] = srcPtr->itemArray[j];
        }
        new->next = NULL;

        if (dest->head == NULL) {
            dest->head = new;
            destPtr = dest->head;
        } else {
            destPtr->next = new;
            destPtr = destPtr->next;
        }
    }
}