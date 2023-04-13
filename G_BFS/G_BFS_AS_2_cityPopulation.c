#include<stdio.h>
#include <stdlib.h>
  
int* city_population (int N, int* population, int** road, int Q, int** cities) ;

int main() {
    int N;
    scanf("%d", &N);
    int i_population;
    int *population = (int *)malloc(sizeof(int)*(N));
    for(i_population = 0; i_population < N; i_population++)
    	scanf("%d", &population[i_population]);
    int i_road, j_road;
    int **road = (int **)malloc((N-1)*sizeof(int *));
    for(i_road = 0; i_road < N-1; i_road++)
    {
    	road[i_road] = (int *)malloc((2)*sizeof(int));
    }
    for(i_road = 0; i_road < N-1; i_road++)
    {
    	for(j_road = 0; j_road < 2; j_road++)
    	{
    		scanf("%d", &road[i_road][j_road]);
    	}
    }
    int Q;
    scanf("%d", &Q);
    int i_cities, j_cities;
    int **cities = (int **)malloc((Q)*sizeof(int *));
    for(i_cities = 0; i_cities < Q; i_cities++)
    {
    	cities[i_cities] = (int *)malloc((3)*sizeof(int));
    }
    for(i_cities = 0; i_cities < Q; i_cities++)
    {
    	for(j_cities = 0; j_cities < 3; j_cities++)
    	{
    		scanf("%d", &cities[i_cities][j_cities]);
    	}
    }

    int* out_ = city_population(N, population, road, Q, cities);
    printf("%d", out_[0]);
    int i_out_;
    for(i_out_ = 1; i_out_ < Q; i_out_++)
    	printf("\n%d", out_[i_out_]);
}

typedef struct _listNode{
    struct _treeNode *node;
    struct _listNode *next;
} ListNode;

typedef struct _treeNode{
    int val;
    ListNode *head;
} TreeNode;

/** \brief Constructs a tree from parrent array.
 *  \return Pointer to the root of the tree.
*/
TreeNode *construct_tree(int N, int *parent)
{
    TreeNode *root;
    TreeNode **created = malloc(N * sizeof(TreeNode *));
    for (int i = 0; i != N; ++i) created[i] = NULL;

    for (int i = 0; i != N; ++i) {
        if (created[i] == NULL) {
            TreeNode *new = malloc(sizeof(TreeNode));
            new->val = i + 1;
            new->head = NULL;
            created[i] = new;
        }
        if (parent[i] != 0) {
            if (created[parent[i] - 1] == NULL) {
                TreeNode *new = malloc(sizeof(TreeNode));
                new->val = parent[i];

                ListNode *child = malloc(sizeof(ListNode));
                child->node = created[i];
                child->next = NULL;

                new->head = child;
                created[parent[i] - 1] = new;
            } else {
                TreeNode *ptr = created[parent[i] - 1];

                ListNode *child = malloc(sizeof(ListNode));
                child->node = created[i];
                child->next = ptr->head;

                ptr->head = child;
            }
        } else {
            root = created[i];
        }
    }
    return root;
}

int dfs_hld(int N, int **edges, int* parent, int* depth, int* heavy)
{
    int size = 1, max_subtree_size = 0;
    
}

int query_graph(int start, int stop, int target)
{

}

/** \brief For each query Q(U, V, W), finds the number the cities from city-U to city-V whose population is at most W.
 * 
 *  \param N Number of cities labelled 1 to N.
 *  \param population Array of population for city-1 to city-N.
 *  \param road Array of N - 1 roads, which is a pair/int[2] of cities.
 *  \param Q Number of queries.
 *  \param cities Array of Q queries, which is an array in the form [U, V, W].
 *  \return An array of query results.
 */
int* city_population (int N, int* population, int** road, int Q, int** cities)
{
	int *parent = malloc(N * sizeof(int)),
        *depth = malloc(N * sizeof(int)),
        *heavy = malloc(N * sizeof(int)),
        *segtree_root = malloc(N * sizeof(int)),
        *segtree_id = malloc(N * sizeof(int));
    
    for (int i = 0; i != N; ++i) {
        parent[i] = -1;
        heavy[i] = -1;
    }

    parent[road[0][0] - 1] = 0;
    for (int i = 0; i != N - 1; ++i) {
        int node1 = road[i][0], node2 = road[i][1];
        if (parent[node1 - 1] == -1) {  // node1 has no parent
            parent[node1 - 1] = node2;
        } else {
            parent[node2 - 1] = node1;
        }
    }

    TreeNode *root = construct_tree(N, parent);
    dfs_hld(N, road, parent, depth, heavy);
    return NULL;
}