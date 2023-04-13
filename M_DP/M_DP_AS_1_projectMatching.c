#include <stdio.h>
#include <stdlib.h>

typedef enum { SOURCE, PROJECT, STUDENT, MENTOR, SINK } SET;

typedef struct _listnode
{
    int vertex;
    struct _listnode *next;
} ListNode;
typedef ListNode StackNode;

typedef struct _graphnode
{
    SET to;
    int vertex;
} GraphNode;
typedef struct _graph
{
    int V;
    int E;
    ListNode **list;
    // int project_cnt;
    // int student_cnt;
    // int mentor_cnt;
} Graph;

typedef ListNode QueueNode;

typedef struct _queue
{
    int size;
    QueueNode *head;
    QueueNode *tail;
} Queue;

typedef struct _stack
{
    int size;
    StackNode *head;
} Stack;

void insertAdjVertex(ListNode **AdjList, int vertex);
void removeAdjVertex(ListNode **AdjList, int vertex);
// int matching(Graph g);
int matching(int s_sz, ListNode **s, int t_sz, ListNode **t);

int dfs(int s_sz, ListNode **s, int t_sz, ListNode **t, int start);

void enqueue(Queue *qPtr, int item);
int dequeue(Queue *qPtr);
int getFront(Queue q);
int isEmptyQueue(Queue q);
void removeAllItemsFromQueue(Queue *qPtr);
void printQ(QueueNode *cur);
//////STACK///////////////////////////////////////////
void push(Stack *sPtr, int vertex);
int pop(Stack *sPtr);
int peek(Stack s);
int isEmptyStack(Stack s);
void removeAllItemsFromStack(Stack *sPtr);
//////////////////////////////////

int main()
{
    int Prj, Std, Mtr; // Project, Student and Mentor;
    int maxMatch;
    scanf("%d %d %d", &Std, &Prj, &Mtr);

    int np, nm; // number of projects and number of mentors

    // build graph
    // Graph g;
    // Write your code
    ListNode **source = malloc(Prj * sizeof(ListNode *));
    for (int i = 0; i < Prj; ++i) source[i] = NULL;

    ListNode **student = malloc(Std * sizeof(ListNode *));
    for (int student_id = 0; student_id < Std; ++student_id) {
        int student_num = student_id + 1;
        student[student_id] = NULL;
        
        scanf("%d %d", &np, &nm);

        for (int j = 0; j < np; ++j) {
            int proj_num;
            scanf("%d", &proj_num);
            int proj_id = proj_num - 1;

            ListNode *new = malloc(sizeof(ListNode));
            new->vertex = student_num;
            new->next = source[proj_id];
            source[proj_id] = new;
        }

        for (int j = 0; j < nm; ++j) {
            int mentor_num;
            scanf("%d", &mentor_num);
            int mentor_id = mentor_num - 1;

            ListNode *new = malloc(sizeof(ListNode));
            new->vertex = mentor_num;
            new->next = student[student_id];
            student[student_id] = new;
        }
    }


    // apply Ford Fulkerson algorithm
    //  use DFS or BFS to find a path
    maxMatch = matching(Prj, source, Std, student);
    printf("%d\n", maxMatch);
    return 0;
}

// int matching(Graph g)
int matching(int s_sz, ListNode **s, int t_sz, ListNode **t)
{
    // Write your code
    // copy network to residual network
    ListNode **sf = malloc(s_sz * sizeof(ListNode *));
    for (int i = 0; i < s_sz; ++i) {
        sf[i] = NULL;

        if (s[i] != NULL) {
            ListNode *ptr = s[i];
            ListNode *head = malloc(sizeof(ListNode));
            head->vertex = ptr->vertex;
            head->next = NULL;
            ListNode *ptr_new = head;
            ptr = ptr->next;

            while (ptr) {
                ListNode *new = malloc(sizeof(ListNode));
                new->vertex = ptr->vertex;
                new->next = NULL;
                ptr_new->next = new;

                ptr_new = ptr_new->next;
                ptr = ptr->next;
            }
            sf[i] = head;
        }
    }

    ListNode **tf = malloc(t_sz * sizeof(ListNode *));
    for (int i = 0; i < t_sz; ++i) {
        tf[i] = NULL;

        if (t[i] != NULL) {
            ListNode *ptr = t[i];
            ListNode *head = malloc(sizeof(ListNode));
            head->vertex = ptr->vertex;
            head->next = NULL;
            ListNode *ptr_new = head;
            ptr = ptr->next;

            while (ptr) {
                ListNode *new = malloc(sizeof(ListNode));
                new->vertex = ptr->vertex;
                new->next = NULL;
                ptr_new->next = new;

                ptr_new = ptr_new->next;
                ptr = ptr->next;
            }
            tf[i] = head;
        }
    }

    int max_match = 0;
    for (int i = 0; i < s_sz; ++i) {
        if (dfs(s_sz, sf, t_sz, tf, i) != 0) ++max_match;
    }
    return max_match;
}

int dfs(int s_sz, ListNode **s, int t_sz, ListNode **t, int start)
{
    if (start < 0) return 0;
    ListNode *ptr = s[start];
    if (ptr == NULL) return 0;

    while (ptr && dfs(s_sz, s, t_sz, t, ptr->vertex - 1) == 0) {
        ptr = ptr->next;
    }

    if (ptr != NULL) {
        ptr->vertex = -ptr->vertex;
    } else {
        return 0;
    }

    return 1;
}

void removeAdjVertex(ListNode **AdjList, int vertex)
{
    ListNode *temp, *preTemp;
    if (*AdjList != NULL)
    {
        if ((*AdjList)->vertex == vertex)
        { // first node
            temp = *AdjList;
            *AdjList = (*AdjList)->next;
            free(temp);
            return;
        }
        preTemp = *AdjList;
        temp = (*AdjList)->next;
        while (temp != NULL && temp->vertex != vertex)
        {
            preTemp = temp;
            temp = temp->next;
        }
        preTemp->next = temp->next;
        free(temp);
    }
}

void insertAdjVertex(ListNode **AdjList, int vertex)
{
    ListNode *temp;
    if (*AdjList == NULL)
    {
        *AdjList = (ListNode *)malloc(sizeof(ListNode));
        (*AdjList)->vertex = vertex;
        (*AdjList)->next = NULL;
    }
    else
    {
        temp = (ListNode *)malloc(sizeof(ListNode));
        temp->vertex = vertex;
        temp->next = *AdjList;
        *AdjList = temp;
    }
}

void enqueue(Queue *qPtr, int vertex)
{
    QueueNode *newNode;
    newNode = malloc(sizeof(QueueNode));
    if (newNode == NULL)
        exit(0);

    newNode->vertex = vertex;
    newNode->next = NULL;

    if (isEmptyQueue(*qPtr))
        qPtr->head = newNode;
    else
        qPtr->tail->next = newNode;

    qPtr->tail = newNode;
    qPtr->size++;
}

int dequeue(Queue *qPtr)
{
    if (qPtr == NULL || qPtr->head == NULL)
    { // Queue is empty or NULL pointer
        return 0;
    }
    else
    {
        QueueNode *temp = qPtr->head;
        qPtr->head = qPtr->head->next;
        if (qPtr->head == NULL) // Queue is emptied
            qPtr->tail = NULL;

        free(temp);
        qPtr->size--;
        return 1;
    }
}

int getFront(Queue q)
{
    return q.head->vertex;
}

int isEmptyQueue(Queue q)
{
    if (q.size == 0)
        return 1;
    else
        return 0;
}

void removeAllItemsFromQueue(Queue *qPtr)
{
    while (dequeue(qPtr))
        ;
}

void printQ(QueueNode *cur)
{
    if (cur == NULL)
        printf("Empty");

    while (cur != NULL)
    {
        printf("%d ", cur->vertex);
        cur = cur->next;
    }
    printf("\n");
}

void push(Stack *sPtr, int vertex)
{
    StackNode *newNode;
    newNode = malloc(sizeof(StackNode));
    newNode->vertex = vertex;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr)
{
    if (sPtr == NULL || sPtr->head == NULL)
    {
        return 0;
    }
    else
    {
        StackNode *temp = sPtr->head;
        sPtr->head = sPtr->head->next;
        free(temp);
        sPtr->size--;
        return 1;
    }
}

int isEmptyStack(Stack s)
{
    if (s.size == 0)
        return 1;
    else
        return 0;
}

int peek(Stack s)
{
    return s.head->vertex;
}

void removeAllItemsFromStack(Stack *sPtr)
{
    while (pop(sPtr))
        ;
}