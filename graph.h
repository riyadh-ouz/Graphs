#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <algorithm>
#include <iostream>

#define INF 1000000

typedef std::vector<int> vi;
typedef std::pair<int, int> ii;
typedef std::vector<ii> vii;

// graph representation
std::vector<vii> initializer_graph(int n_vertices, int n_edges, bool directed = false, std::istream& input_stream = std::cin);
std::vector<vi> initializer_unweighted_graph(int n_vertices, int n_edges, bool directed = false, std::istream& input_stream = std::cin);

void visualise_graph(const std::vector<vii>& edges, std::ostream& output_stream = std::cout);
void visualise_unweighted_graph(const std::vector<vi>& edges, std::ostream& output_stream = std::cout);


// dfs
void dfs_graph_recursion(const std::vector<vi>& edges, int src, std::vector<bool>& visited);
void dfs_graph(const std::vector<vi>& edges, int src, std::vector<bool>& visited);

int numberOfComponents_graph(const std::vector<vi>& edges);
// Case of a tree
int height_tree(int node, const std::vector<vi>& edges, int parent = -1);


// bfs
vii bfs_graph(const std::vector<vi>& edges, int source = 0);
vi path_unweighted_graph(const std::vector<vi>& edges, int to, int from = 0);


// Dijkstra & weighted graphs
vii Dijkstra(const std::vector<vii> &edges, int source = 0);
vii Dijkstra1(const std::vector<vii>& edges, int source = 0);
vi path_graph(const std::vector<vii>& edges, int to, int from);


// DSU
class DSU
{
public:
    DSU(int n_vertices);
    int findLeader(int i);
    bool sameGroup(int x, int y);
    void mergeGroups(int x, int y);
    int getSize(int x);
    ~DSU();

private:
    int* parent;
    int* groupSize;
};

#endif // GRAPH_H_INCLUDED
