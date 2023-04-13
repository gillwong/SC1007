#include <stdio.h>
#include <stdlib.h>

typedef enum { SOURCE, PROJECT, STUDENT, MENTOR, SINK } SET;

typedef struct _graphnode
{
    SET to;
    int vertex;
    struct _graphnode *next;
} GraphNode;

typedef struct _graph
{
    int project_cnt;
    int student_cnt;
    int mentor_cnt;
    GraphNode **project;
    GraphNode **student;
    GraphNode **mentor;
} Graph;

typedef struct {
    int project_cnt;
    int student_cnt;
    int mentor_cnt;
    char *project;
    char *student;
    char *mentor;
} Visited;

int main()
{
    int Prj, Std, Mtr;
    int maxMatch;
    scanf("%d %d %d", &Std, &Prj, &Mtr);

    int np, nm;

    Graph g;
    g.project_cnt = Prj;
    g.student_cnt = Std;
    g.mentor_cnt = Mtr;
    g.project = malloc(Prj * sizeof(GraphNode *));
    g.student = malloc(Std * sizeof(GraphNode *));
    g.mentor = malloc(Mtr * sizeof(GraphNode *));

    for (int i = 0; i < Prj; ++i) g.project[i] = NULL;
    for (int i = 0; i < Mtr; ++i) g.mentor[i] = NULL;

    for (int student_id = 0; student_id < Std; ++student_id) {
        int student_num = student_id + 1;
        g.student[student_id] = NULL;
        scanf("%d %d", &np, &nm);

        for (int j = 0; j < np; ++j) {
            int project_num;
            scanf("%d", &project_num);
            int project_id = project_num - 1;

            GraphNode *new = malloc(sizeof(GraphNode));
            new->to = STUDENT;
            new->vertex = student_num;
            new->next = g.project[project_id];

            g.project[project_id] = new;
        }
        for (int j = 0; j < nm; ++j) {
            int mentor_num;
            scanf("%d", &mentor_num);
            int mentor_id = mentor_num - 1;

            GraphNode *new = malloc(sizeof(GraphNode));
            new->to = MENTOR;
            new->vertex = mentor_num;
            new->next = g.student[student_id];

            g.student[student_id] = new;
        }
    }

    maxMatch = matching(&g);
    printf("%d\n", maxMatch);
    return 0;
}

int matching(Graph *g)
{
    Graph *gf = malloc(sizeof(Graph));
    graphcpy(g, gf);
    
    int max_matches = 0;
    for (int i = 0; i < gf->project_cnt; ++i) {
        Visited v;
        v.project_cnt = gf->project_cnt;
        v.student_cnt = gf->student_cnt;
        v.mentor_cnt = gf->mentor_cnt;
        v.project = malloc(gf->project_cnt * sizeof(char));
        for (int i = 0; i < gf->project_cnt; ++i) v.project[i] = 0;
        v.student = malloc(gf->student_cnt * sizeof(char));
        for (int i = 0; i < gf->student_cnt; ++i) v.student[i] = 0;
        v.mentor = malloc(gf->mentor_cnt * sizeof(char));
        for (int i = 0; i < gf->mentor_cnt; ++i) v.mentor[i] = 0;

        int res = dfs(g, &v, gf->project[i], SOURCE);
        if (res != 0) ++max_matches;
    }
    return max_matches;
}

int dfs(Graph *g, Visited *v, GraphNode *start, SET from)
{
    if (from == STUDENT && start->vertex == NULL) return 1;

    GraphNode *search;
    switch (start->to)
    {
    case SOURCE:
        return 0;
    case PROJECT:
        if (v->project[start->vertex - 1] == 1) {
            return 0;
        } else {
            v->project[start->vertex - 1] = 1;
            search = g->project[start->vertex - 1];
        }
        break;
    case STUDENT:
        if (v->student[start->vertex - 1] == 1) {
            return 0;
        } else {
            v->student[start->vertex - 1] = 1;
            search = g->student[start->vertex - 1];
        }
        break;
    case MENTOR:
        if (v->mentor[start->vertex - 1] == 1) {
            return 0;
        } else {
            v->mentor[start->vertex - 1] = 1;
            search = g->mentor[start->vertex - 1];
        }
        break;
    case SINK:
    default:
        break;
    }
    
    while (search) {
        int res = dfs(g, v, )
        start = start->next;
    }
}

void graphcpy(Graph *source, Graph *dest)
{
    dest->project_cnt = source->project_cnt;
    dest->student_cnt = source->student_cnt;
    dest->mentor_cnt = source->mentor_cnt;

    GraphNode **adj[][2] = { 
        { source->project, dest->project }, 
        { source->student, dest->student }, 
        { source->mentor, dest->mentor } 
    };

    int adj_sz[] = { source->project_cnt, source->student_cnt, source->mentor_cnt };

    for (int i = 0; i < 3; ++i) {
        GraphNode **dest_adj = adj[i][1],
                  **source_adj = adj[i][0];

        for (int j = 0; j < adj_sz[i]; ++j) {
            dest_adj[j] = NULL;
            
            if (source_adj[j] != NULL) {
                GraphNode *ptr = source_adj[j];
                GraphNode *head = malloc(sizeof(GraphNode));
                GraphNode *ptr_new = head;
                head->to = ptr->to;
                head->vertex = ptr->vertex;
                head->next = NULL;

                ptr = ptr->next;
                while (ptr) {
                    GraphNode *new = malloc(sizeof(GraphNode));
                    new->to = ptr->to;
                    new->vertex = ptr->vertex;
                    new->next = NULL;

                    ptr_new->next = new;
                    ptr_new = ptr_new->next;
                    ptr = ptr->next;
                }
                dest_adj[j] = head;
            }
        }
    }

    // ListNode **sf = malloc(s_sz * sizeof(ListNode *));
    // for (int i = 0; i < s_sz; ++i) {
    //     sf[i] = NULL;

    //     if (s[i] != NULL) {
    //         ListNode *ptr = s[i];
    //         ListNode *head = malloc(sizeof(ListNode));
    //         head->vertex = ptr->vertex;
    //         head->next = NULL;
    //         ListNode *ptr_new = head;
    //         ptr = ptr->next;

    //         while (ptr) {
    //             ListNode *new = malloc(sizeof(ListNode));
    //             new->vertex = ptr->vertex;
    //             new->next = NULL;
    //             ptr_new->next = new;

    //             ptr_new = ptr_new->next;
    //             ptr = ptr->next;
    //         }
    //         sf[i] = head;
    //     }
    // }

    // ListNode **tf = malloc(t_sz * sizeof(ListNode *));
    // for (int i = 0; i < t_sz; ++i) {
    //     tf[i] = NULL;

    //     if (t[i] != NULL) {
    //         ListNode *ptr = t[i];
    //         ListNode *head = malloc(sizeof(ListNode));
    //         head->vertex = ptr->vertex;
    //         head->next = NULL;
    //         ListNode *ptr_new = head;
    //         ptr = ptr->next;

    //         while (ptr) {
    //             ListNode *new = malloc(sizeof(ListNode));
    //             new->vertex = ptr->vertex;
    //             new->next = NULL;
    //             ptr_new->next = new;

    //             ptr_new = ptr_new->next;
    //             ptr = ptr->next;
    //         }
    //         tf[i] = head;
    //     }
    // }
}