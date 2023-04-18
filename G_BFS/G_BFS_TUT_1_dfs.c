#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode
{
    int vertex;
    struct _listnode *next;
} ListNode;

typedef struct _graph
{
    int V;
    int E;
    ListNode **list;
} Graph;

void printGraphList(Graph *g);
ListNode *dfs(Graph *g, int start, int goal, char* visited);

int main()
{
    Graph g;

    printf("Enter the number of vertices: ");
    scanf("%d", &g.V);

    char *visited = malloc(g.V * sizeof(char));
    g.list = malloc(g.V * sizeof(ListNode *));

    for (int i = 0; i < g.V; ++i) {
        g.list[i] = NULL;
        visited[i] = 0;
    }

    int v1, v2;
    printf("Enter two vertices which are adjacent to each other: ");
    while (scanf("%d %d", &v1, &v2) == 2) {
        --v1;
        if (g.list[v1] == NULL) {
            g.list[v1] = malloc(sizeof(ListNode));
            g.list[v1]->vertex = v2;
            g.list[v1]->next = NULL;
        } else {
            ListNode *temp = malloc(sizeof(ListNode));
            temp->next = g.list[v1];
            temp->vertex = v2;
            g.list[v1] = temp;
        }
        ++(g.E);
        printf("Enter two vertices which are adjacent to each other: ");
    }
    scanf("%*c");  // read and ignore a character

    printf("Resulting graph:\n");
    printGraphList(&g);
    printf("\n");

    int v, w;
    printf("Enter starting vertex: ");
    scanf("%d", &v);
    printf("Enter goal vertex: ");
    scanf("%d", &w);

    ListNode *path = dfs(&g, v, w, visited);
    if (path == NULL) {
        printf("No path found from %d to %d.", v, w);
    } else {
        printf("Path found from %d to %d:\t ", v, w);
        while (path) {
            printf("%d -> ", path->vertex);
            path = path->next;
        }
    }
    return 0;
}

void printGraphList(Graph *g)
{
    int i;
    ListNode *ptr;

    for (int i = 0; i < g->V; ++i) {
        printf("%d:\t", i+1);
        ptr = g->list[i];
        while (ptr) {
            printf("%d -> ", ptr->vertex);
            ptr = ptr->next;
        }
        printf("\n");
    }
}

ListNode *dfs(Graph *g, int start, int goal, char *visited)
{
    if (visited[start-1] == 1) {
        return NULL;
    }
    visited[start-1] = 1;

    ListNode *result = malloc(sizeof(ListNode));
    result->vertex = start;
    result->next = NULL;

    if (start == goal) {
        return result;
    }
    
    ListNode *adj = g->list[start-1];
    while (adj) {
        ListNode *path = dfs(g, adj->vertex, goal, visited);
        if (path) {
            result->next = path;
            return result;
        }
        adj = adj->next;
    }
    return NULL;
}