#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <algorithm>
#include <iostream>
#include <exception>

#define INF 1000000

typedef std::vector<int> vi;
typedef std::pair<int, int> ii;
typedef std::vector<ii> vii;


// the Graph class
class Graph
{
public:
    Graph(unsigned int n_vertices, unsigned int n_edges, bool weighted = true, bool directed = true, std::istream& input_stream = std::cin);
    void visualise(std::ostream& output_stream = std::cout) const;

    /// Warning: bfs for weighted graphs treats it as unweighted graph (edgeCost = 1) use dijkstra instead
    vii bfs(int source = 0) const;
    vii Dijkstra(int source = 0) const;

    vi path(int to, int from = 0) const;

/// Warning: the following functions treat the graph as unweighted
    vi path_without_cost(int to, int from = 0) const;
    void dfs(int source = 0, std::ostream& output_stream = std::cout);

    /// Warning: avoid calling number_of_components for directed graphs;
    unsigned int number_of_components();
    /// Case: graph like tree (no matter directed or undirected)
    unsigned int height_tree(int root = 0, int parent = -1) const;

private:
    unsigned int m_n_vertices;
    unsigned int m_n_edges;
    bool m_weighted;
    bool m_directed;

    bool* m_visited; // to use with dfs algorithms

    std::vector<vii> m_edges;
    // case of unweighted graph
    std::vector<vi> m_unweighted_edges;
};

// graph representation
std::vector<vii> initializer_graph(unsigned int n_vertices, unsigned int n_edges, bool directed = true, std::istream& input_stream = std::cin);
std::vector<vi> initializer_unweighted_graph(unsigned int n_vertices, unsigned int n_edges, bool directed = true, std::istream& input_stream = std::cin);

void visualise_graph(const std::vector<vii>& edges, std::ostream& output_stream = std::cout);
void visualise_unweighted_graph(const std::vector<vi>& edges, std::ostream& output_stream = std::cout);


// dfs for unweighted graphs
void dfs_graph_recursion(const std::vector<vi>& edges, int source, std::vector<bool>& visited);
void dfs_graph(const std::vector<vi>& edges, int source, std::vector<bool>& visited);
// warning: the graph passed to the following function should be undirected
int number_of_components_graph(const std::vector<vi>& edges);
// case of a graph like tree
int height_tree(int root, const std::vector<vi>& edges, int parent = -1);


// bfs for unweighted graphs
vii bfs_unweighted_graph(const std::vector<vi>& edges, int source = 0);
vi path_unweighted_graph(const std::vector<vi>& edges, int to, int from = 0);


// Dijkstra & weighted graphs
vii Dijkstra(const std::vector<vii> &edges, int source = 0);
vii Dijkstra1(const std::vector<vii>& edges, int source = 0);
vi path_graph(const std::vector<vii>& edges, int to, int from = 0);


// DSU
class DSU
{
public:
    DSU(int n_vertices);
    int find_leader(int i);
    bool same_group(int x, int y);
    void merge_groups(int x, int y);
    int get_size(int x);
    ~DSU();

private:
    int m_n_vertices;
    int* parent;
    int* group_size;
};


// Utility Error class
class Error : public std::exception
{
public:
    Error(std::string const& desc = "Unknown Error") throw();
    virtual const char* what() const throw();

    virtual ~Error() throw();

private:
    std::string m_desc;
};

#endif // GRAPH_H_INCLUDED
