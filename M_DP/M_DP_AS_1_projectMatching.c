#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int V;
    int prjCnt;
    int stdCnt;
    int mtrCnt;
    char **adj;  // adj[from][to]
} Graph;

int matching(Graph *g);
int dfs(Graph *const g, Graph *gf, char* visited, int start);
void graphcpy(Graph *src, Graph *dest);

int main()
{
    int Prj, Std, Mtr;
    int maxMatch;
    scanf("%d %d %d", &Std, &Prj, &Mtr);

    int np, nm;

    Graph g;
    g.V = Prj + Std + Mtr + 2;  // 2: source node & sink node
    g.prjCnt = Prj;
    g.stdCnt = Std;
    g.mtrCnt = Mtr;
    g.adj = malloc(g.V * sizeof(char *));
    for (int i = 0; i < g.V; ++i) {
        g.adj[i] = malloc(g.V * sizeof(char));
        for (int j = 0; j < g.V; ++j) {
            g.adj[i][j] = 0;
        }
    }

    for (int i = 1; i <= Prj; ++i) {
        g.adj[0][i] = 1;
    }

    for (int i = 0; i < Std; ++i) {
        scanf("%d %d", &np, &nm);
        for (int j = 0; j < np; ++j) {
            int prj_num;
            scanf("%d", &prj_num);
            g.adj[1 + (prj_num - 1)][1 + Prj + i] = 1;
        }
        for (int j = 0; j < nm; ++j) {
            int mtr_num;
            scanf("%d", &mtr_num);
            g.adj[1 + Prj + i][1 + Prj + Std + (mtr_num - 1)] = 1;
        }
    }

    for (int i = 1 + Prj + Std; i < g.V - 1; ++i) {
        g.adj[i][g.V - 1] = 1;
    }

    maxMatch = matching(&g);
    printf("%d\n", maxMatch);
    return 0;
}

int matching(Graph *g)
{
    Graph *gf = malloc(sizeof(Graph));  // residual graph
    graphcpy(g, gf);
    char *visited = malloc(g->V * sizeof(char));

    do {
        graphcpy(gf, g);
        for (int i = 0; i < g->V; ++i) visited[i] = 0;
    } while (dfs(g, gf, visited, 0));

    int matches = 0;
    for (int i = 1; i <= g->prjCnt; ++i) {
        if (g->adj[i][0]) ++matches;
    }

    free(visited);
    free(gf);
    return matches;
}

int dfs(Graph *const g, Graph *gf, char* visited, int start)
{
    if (start == g->V - 1) return 1;
    if (visited[start]) return 0;
    visited[start] = 1;

    for (int i = 0; i < g->V; ++i) {
        if (g->adj[start][i] == 1) {
            int res = dfs(g, gf, visited, i);
            if (res) {
                gf->adj[start][i] = 0;
                gf->adj[i][start] = 1;
                return 1;
            }
        }
    }
    return 0;
}

void graphcpy(Graph *src, Graph *dest)
{
    dest->V = src->V;
    dest->prjCnt = src->prjCnt;
    dest->stdCnt = src->stdCnt;
    dest->mtrCnt = src->mtrCnt;
    dest->adj = malloc(dest->V * sizeof(char *));
    for (int i = 0; i < dest->V; ++i) {
        dest->adj[i] = malloc(dest->V * sizeof(char));
        for (int j = 0; j < dest->V; ++j) {
            dest->adj[i][j] = src->adj[i][j];
        }
    }
}