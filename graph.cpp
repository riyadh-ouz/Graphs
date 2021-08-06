#include "graph.h"
using namespace std;


/// the Graph class

Graph::Graph(unsigned int n_vertices, unsigned int n_edges, bool weighted, bool directed, std::istream& input_stream)
:m_n_vertices{n_vertices}, m_n_edges{n_edges}, m_weighted{weighted}, m_directed{directed}
{
    if (weighted) {
        m_edges = vector<vii>(n_vertices);

        while (n_edges--)
        {
            int u, v, w;	input_stream >> u >> v >> w;

            if (u >= (int)n_vertices || v >= (int)n_vertices) throw Error("Error: value error -> (Node value >= n_vertices)...\n");

            if (u != v) {
                m_edges[u].push_back(make_pair(v, w));
                if (!directed) m_edges[v].push_back(make_pair(u, w));
            }
        }
    }
    else {
        m_unweighted_edges = vector<vi>(m_n_vertices);

        while (n_edges--)
        {
            int u, v;	input_stream >> u >> v;

            if (u >= (int)n_vertices || v >= (int)n_vertices) throw Error("Error: value error -> (Node value >= n_vertices)...\n");

            if (u != v) {
                m_unweighted_edges[u].push_back(v);
                if (!directed) m_unweighted_edges[v].push_back(u);
            }
        }
	}

}

void Graph::visualise(std::ostream& output_stream) const
{
    output_stream << "\n";
    if (m_weighted)
        for (int node = 0; node < (int)m_n_vertices; node++) {
            output_stream << node << ": ";
            for (ii neighbor: m_edges[node]) output_stream << "(" << neighbor.first << " ," << neighbor.second << ") ";

            output_stream << "\n";
        }
    else
        for (int node = 0; node < (int)m_n_vertices; node++) {
            output_stream << node << ": ";
            for (int neighbor: m_unweighted_edges[node]) output_stream << neighbor << " ";

            output_stream << "\n";
        }
    output_stream << "\n";
}


vii Graph::bfs(int source) const
{
    // m_n_vertices paths from the source initialized with distance -1 and previous -1
    vii paths(m_n_vertices, make_pair(-1 ,-1));

    paths[source].first = 0; // the cost from the source to the source
    //paths[source] = make_pair(sourec, 0);

    queue<int> q;
    q.push(source);

    while (!q.empty())
    {
        int node = q.front();   q.pop();
        int cost = paths[node].first; // cost refers the the distance

        if (m_weighted) {
            for(ii neighbor: m_edges[node])
                if(paths[neighbor.first].first == -1) // not visited
                {
                    q.push(neighbor.first);
                    paths[neighbor.first] = make_pair(cost + 1, node); // stores the cost and the previous
                }
        }
        else {
            for(int neighbor: m_unweighted_edges[node])
                if(paths[neighbor].first == -1) // not visited
                {
                    q.push(neighbor);
                    paths[neighbor] = make_pair(cost + 1, node); // stores the cost and the previous
                }
        }

    }

    return paths;
    // Nodes of other components (unreachable from the source node) still have paths of {-1, -1}.
}

vii Graph::Dijkstra(int source) const
{
    if (m_weighted) {

        vi parent(m_n_vertices), cost(m_n_vertices, INF); // cost is initialized with INF
        vector<bool> expanded(m_n_vertices, false);

        parent[source] = source;
        cost[source] = 0;


        // queue of pairs: <cost, node>
        priority_queue<ii, vii, greater<ii>> q;

        q.push(make_pair(0, source));

        while(!q.empty())
        {
            int node = q.top().second;
            q.pop();

            // we should control for the duplicated elements in the queue
            if(expanded[node])  continue;

            else    expanded[node] = true;

            for(int i = 0; i < (int)m_edges[node].size(); i++)
            {
                ii edge = m_edges[node][i];
                int neighbor = edge.first, edgeCost = edge.second;

                if(cost[node] + edgeCost < cost[neighbor])
                {
                    parent[neighbor] = node;
                    cost[neighbor] = cost[node] + edgeCost;

                    q.push(make_pair(cost[neighbor], neighbor));
                }
            }
        }

        vii result(m_n_vertices);
        for(int i = 0; i < (int)m_n_vertices; i++)  result[i] = make_pair(cost[i], parent[i]);

        return result;
    }
    else
        // dijkstra = bfs in case of unweighted graph
        return bfs(source);

}


vi Graph::path(int to, int from) const
{
    vi path;
    vii paths;

    if (m_weighted) paths = Dijkstra(from);
    else paths = bfs(from);

    path.push_back(to);
    int node = to;

    while (node != from) {
        node = paths[node].second; // get the previous for the current node
        path.push_back(node);
    };

    reverse(path.begin(), path.end()); // to get the path from "from" to "to"
    return path;
}


vi Graph::path_without_cost(int to, int from) const
{
    vi path;

    vii paths = bfs(from);

    path.push_back(to);
    int node = to;

    while (node != from) {
        node = paths[node].second; // get the previous for the current node
        path.push_back(node);
    }

    reverse(path.begin(), path.end()); // to get the path from "from" to "to"
    return path;
}


void Graph::dfs(int source, ostream& output_stream) {

    m_visited = new bool[m_n_vertices];
    for (int i = 0; i < (int)m_n_vertices; i++) m_visited[i] = false; // initialize m_visited to false

    stack<int> s;
    s.push(source);

    output_stream << "\nDFS traverse\n";

    if (m_weighted)
        while (!s.empty())
        {
            int u = s.top();    s.pop();
            if (!m_visited[u]) {
                output_stream << u << " ";
                m_visited[u] = true;
            }

            for (ii v: m_edges[u])
                if (!m_visited[v.first])
                    s.push(v.first);
        }

    else
        while (!s.empty())
        {
            int u = s.top();    s.pop();
            if (!m_visited[u]) {
                output_stream << u << " ";
                m_visited[u] = true;
            }

            for (int v: m_unweighted_edges[u])
                if (!m_visited[v])
                    s.push(v);
        }
    output_stream << "\n";

    delete[] m_visited;

}

unsigned int Graph::number_of_components() {
    unsigned int number_of_components = 0;

    m_visited = new bool[m_n_vertices];
    for (int i = 0; i < (int)m_n_vertices; i++) m_visited[i] = false; // initialize m_visited to false

    if (m_directed) throw Error("Warning: number_of_components should be used with undirected graphs...\n");

    for (int node = 0; node < (int)m_n_vertices; node++)
        if (!m_visited[node]) {
            number_of_components ++;

            // start dfs[node]
            stack<int> s;
            s.push(node);

            if (m_weighted)
                while (!s.empty())
                {
                    int u = s.top();    s.pop();
                    m_visited[u] = true;

                    for (ii v: m_edges[u])
                        if (!m_visited[v.first])
                            s.push(v.first);
                }

            else
                while (!s.empty())
                {
                    int u = s.top();    s.pop();
                    m_visited[u] = true;

                    for (int v: m_unweighted_edges[u])
                        if (!m_visited[v])
                            s.push(v);
                }
            // end dfs[node]

        }

    delete[] m_visited;
    return number_of_components;
}

unsigned int Graph::height_tree(int root, int parent) const
{
    unsigned int height = 0;
    if (m_weighted) {
        for (ii child: m_edges[root]) if (child.first != parent)
        {
            unsigned int temp = height_tree(child.first, root); // parent is crucial because we are in graph like tree
            height = (height < temp)? temp : height;
        }

    }
    else {

        for (int child: m_unweighted_edges[root]) if (child != parent)
        {
            unsigned int temp = height_tree(child, root); // parent is crucial because we are in graph like tree
            height = (height < temp)? temp : height;
        }

    }
    return 1 + height;
}


/// 1- Graph (Representation)
// Implementation with adjacency list (using vector from the STL).
// See also implementation with the Adjacency matrix.

vector<vii> initializer_graph(unsigned int n_vertices, unsigned int n_edges, bool directed, istream& input_stream) {

    vector<vii> edges(n_vertices);

    while (n_edges--)
	{
		int u, v, w;	input_stream >> u >> v >> w;

        if (u >= (int)n_vertices || v >= (int)n_vertices) throw Error("Error: value error -> (Node value >= n_vertices)...\n");

        if (u != v) {
            edges[u].push_back(make_pair(v, w));
            if (!directed) edges[v].push_back(make_pair(u, w));
        }

	}

	return edges;

}

vector<vi> initializer_unweighted_graph(unsigned int n_vertices, unsigned int n_edges, bool directed, istream& input_stream) {

    vector<vector<int>> edges(n_vertices);

    while (n_edges--)
	{
		int u, v;	input_stream >> u >> v;
        if (u >= (int)n_vertices || v >= (int)n_vertices) throw Error("Error: value error -> (Node value >= n_vertices)...\n");

        if (u != v) {
            edges[u].push_back(v);
            if (!directed) edges[v].push_back(u);
        }

	}

	return edges;

}

void visualise_graph(const vector<vii>& edges, ostream& output_stream) {
    //system("cls"); // to clear the console for windows
    output_stream << "\n";
    int n = edges.size();
	for (int node = 0; node < n; node ++) {
		output_stream << node << ": ";
        for (ii neighbor: edges[node]) output_stream << "(" << neighbor.first << " ," << neighbor.second << ") ";

		output_stream << "\n";
	}
	output_stream << "\n";
}

void visualise_unweighted_graph(const vector<vi>& edges, ostream& output_stream) {
    //system("cls"); // to clear the console for windows
    output_stream << "\n";
    int n = edges.size();
	for (int node = 0; node < n; node ++) {
		output_stream << node << ": ";

		for (int neighbor: edges[node]) output_stream << neighbor << " ";

		output_stream << "\n";
	}
	output_stream << "\n";
}



/// 2- DFS for unweighted graphs

/// Using recursion
void dfs_graph_recursion(const vector<vi>& edges, int source, vector<bool>& visited) {
    int n_vertices = edges.size();

    if ((int)visited.size() < n_vertices) throw Error("Error: argument value error -> (visited.size() < n_vertices...)\n");

	visited[source] = true;

	for (int neighbor: edges[source])
        if (!visited[neighbor]) dfs_graph_recursion(edges ,neighbor, visited);

}

int number_of_components_graph(const vector<vi>& edges) {

    int number_of_components = 0, n_vertices = edges.size();

    vector<bool> visited(n_vertices, false);

    for (int node = 0; node < n_vertices; node++)
        if (!visited[node]) {
            number_of_components ++;
            dfs_graph_recursion(edges, node, visited);
        }

    return number_of_components;

}
// case graph like tree
int height_tree(int root, const vector<vi>& edges, int parent) {
    int height = 0;
	for (int child: edges[root]) if (child != parent)
	{
	    int temp = height_tree(child, edges, root); // parent is crucial because we are in graph like tree
	    height = (height < temp)? temp : height;
	}
	return 1 + height;
}

/// Using stacks
void dfs_graph(const vector<vi>& edges, int source, vector<bool>& visited) {
    int n_vertices = edges.size();

    if ((int)visited.size() < n_vertices) throw Error("Error: argument value error -> (visited.size() < n_vertices...)\n");

    stack<int> s;
    s.push(source);
    cout << "\nDFS traverse\n";
    while (!s.empty())
    {
        int u = s.top();    s.pop();
        if (!visited[u]) {
            cout << u << " ";
            visited[u] = true;
        }

        for (int v: edges[u])
            if (!visited[v])
                s.push(v);
    }
    cout << "\n";

}



/// 3- BFS for unweighted graphs

/// Find the shortest path using BFS. (One to many)
vii bfs_unweighted_graph(const vector<vi>& edges, int source) {

    int n_vertices = edges.size();

    // n_vertices paths from the source initialized with distance -1 and previous -1
    vii paths(n_vertices, make_pair(-1 ,-1));

    paths[source].first = 0; // the cost from the source to the source
    //paths[source] = make_pair(sourec, 0);

    queue<int> q;
    q.push(source);

    while (!q.empty())
    {
        int node = q.front();   q.pop();
        int cost = paths[node].first; // cost refers the the distance

        for(int neighbor: edges[node])
            if(paths[neighbor].first == -1) // not visited
                {
                    q.push(neighbor);
                    paths[neighbor] = make_pair(cost + 1, node); // stores the cost and the previous
                }
    }

    return paths;
    // Nodes of other components (unreachable from the source node) still have paths of {-1, -1}.
}

/// Find the shortest path using BFS. (many to one)
/* To implement the shortest path (many to one):

0* if the graph is "directed" we should "inverse" the edges before calculating the path from many to one;
1* we inverse the arguments (the destination become the source "many to one");
2* we inverse the result paths (many paths);

*/

/// Construct the paths with BFS
vi path_unweighted_graph(const vector<vi>& edges, int to, int from) {

    vii paths = bfs_unweighted_graph(edges, from);

    vi path;

    path.push_back(to);
    int node = to;

    while (node != from) {

        node = paths[node].second; // get the previous for the current node
        path.push_back(node);

    };

    reverse(path.begin(), path.end()); // to get the path from "from" to "to"

    return path;
}



/// 4- Graph (Dijkstra)

/*
>>> Finds the shortest path in weighted graphs.

// Complexity: O((n+m)log(n)), similar to BFS but with an extra log(n)

// NOTES:
1- Non-negative weights (Dijkstra is not applicable for negative weights)
2- One to many, One to one, Many to one or many to many by adding more than one source
3- Build the path
*/

/// Using priority_queue from STL
vii Dijkstra(const vector<vii> &edges, int source) {
    int n_vertices = edges.size();

    vi parent(n_vertices), cost(n_vertices, INF); // cost is initialized with INF
    vector<bool> expanded(n_vertices, false);

    parent[source] = source;
    cost[source] = 0;


    // queue of pairs: <cost, node>
    priority_queue<ii, vii, greater<ii>> q;

    q.push(make_pair(0, source));

    while(!q.empty())
    {
        int node = q.top().second;
        q.pop();

        // we should control for the duplicated elements in the queue
        if(expanded[node])  continue;

        else    expanded[node] = true;

        for(int i = 0; i < (int)edges[node].size(); i++)
        {
            ii edge = edges[node][i];
            int neighbor = edge.first, edgeCost = edge.second;

            if(cost[node] + edgeCost < cost[neighbor])
            {
                parent[neighbor] = node;
                cost[neighbor] = cost[node] + edgeCost;

                q.push(make_pair(cost[neighbor], neighbor));
            }
        }
    }

    vii result(n_vertices);
    for(int i = 0; i < n_vertices; i++)  result[i] = make_pair(cost[i], parent[i]);

    return result;
}

/// Using set of pairs as the priority queue from the STL
vii Dijkstra1(const vector<vii>& edges, int source) {
    int n_vertices = edges.size();

    vi cost(n_vertices, -1); // n_vertices costs for each destination initialized with -1
    vi previous(n_vertices, -1); // n_vertices previous to track the path initialized with -1

    set<ii> q; // set<pair<totalCost, node>>
    q.insert(make_pair(0, source));

    while(!q.empty())
    {
        ii p = *(q.begin()); // pop the node with the smallest cost
        q.erase(p);

        int node = p.second, nodeCost = p.first;

        // we should control for the duplicated elements in the queue
        // or we can use a vector of booleans
        if(cost[node] != -1)    continue;

        cost[node] = nodeCost;

        for(ii edge: edges[node])   if(cost[edge.first] == -1) // not visited
        {
            q.insert(make_pair(nodeCost + edge.second, edge.first));
            previous[edge.first] = node;
        }
    }

    vii result(n_vertices);
    for(int i = 0; i < n_vertices; i++)  result[i] = make_pair(cost[i], previous[i]);

    return result;
}

/// Construct the path dijkstra
vi path_graph(const vector<vii>& edges, int to, int from) {

    vii paths = Dijkstra(edges, from);

    vi path;

    path.push_back(to);
    int node = to;

    while (node != from) {

        node = paths[node].second; // get the previous for the current node
        path.push_back(node);

    };

    reverse(path.begin(), path.end()); // to get the path from "from" to "to"

    return path;
}



/// 5- Disjoint set union (DSU)
/*
>>> Used to answer queries about graph components
1- How many connected components?
2- Do u and v belong to the same component?
3- What is the size of the component to which u belongs?

>>> This algorithm is used whenever needed (before or after graph manipulation)
*/

DSU::DSU(int n_vertices) :m_n_vertices{n_vertices}, parent{new int[n_vertices]}, groupSize{new int[n_vertices]}
{
    for(int i = 0; i < n_vertices; i++)
    {
        parent[i] = i;
        groupSize[i] = 1;
    }
}

DSU::~DSU() {
    delete[] parent;
    delete[] groupSize;
}

int DSU::findLeader(int i) {

    if (i >= m_n_vertices) throw Error("Error: argument value error -> (DSU: i >= m_n_vertices)...\n");

    if(parent[i] == i)  return i;

    // This technique of returning will store all the leaders in the first traverse -> reduce the complexity
    return parent[i] = findLeader(parent[i]);
}

bool DSU::sameGroup(int x, int y)
{
    int leader1 = findLeader(x);
    int leader2 = findLeader(y);

    return leader1 == leader2;
}

void DSU::mergeGroups(int x, int y)
{
    int leader1 = findLeader(x);
    int leader2 = findLeader(y);

    if(leader1 == leader2)  return;

    if(groupSize[leader1] > groupSize[leader2])
    {
        parent[leader2] =  leader1;
        groupSize[leader1] += groupSize[leader2];
    }

    else
    {
        parent[leader1] =  leader2;
        groupSize[leader2] += groupSize[leader1];
    }
}

int DSU::getSize(int x) {
    int leader = findLeader(x);
    return groupSize[leader];
}


// Utility Error class
Error::Error(string const& desc) throw() :m_desc(desc) {}

const char* Error::what() const throw() {return m_desc.c_str();}

Error::~Error() throw() {}


