#include <fstream>
#include "graph.h"

using namespace std;

int main(int argc, char* argv[])
{
    try {

        ifstream is {argv[1]};
        int n, m;	is >> n >> m;

        //used with dijkstra.txt
        // Weighted directed graph
        Graph graph(n, m, true, true, is);
        graph.visualise();

        graph.dfs(0);

        cout << "\nEnter the source ... ";
        int from;   cin >> from;
        cout << "\nnode | distance from " << from << " | path\n";

        vii distances = graph.Dijkstra(from);

        for (int i = 0; i < n; i++) {

            vi path = graph.path(i, from);
            vi path1 = graph.path_without_cost(i, from);

            cout << i << "      " << distances[i].first << "                 ";

            for (int j = 0; j < (int)path.size(); j++) {
                if (j != 0) cout << "->";
                cout << path[j];
            }

            cout << "\n";
        }


        /* used with tree.txt
        // Graph with two components one is like tree with root = 1
        Graph graph1(n, m, false, false, is);
        graph1.visualise();
        graph1.dfs(1);
        cout << "Components: " << graph1.numberOfComponents() << "\n";
        cout << "Height: " << graph1.height_tree(1, -1) << "\n";
        */


        /* // used with tree.txt
        vector<vi> edges = initializer_unweighted_graph(n, m, true, is);
        visualise_unweighted_graph(edges);

        vector<bool> visited(n);
        dfs_graph(edges, 1, visited);

        cout << "Components: " << numberOfComponents_graph(edges) << "\n";
        cout << "Height: " << height_tree(1, edges, -1) << "\n";
        */


        /* // unweighted graph used with unweighted.txt
        vector<vi> edges = initializer_unweighted_graph(n, m, false, is);
        visualise_unweighted_graph(edges);

        cout << "Components: " << numberOfComponents_graph(edges) << "\n";

        cout << "\nEnter the source ... ";
        int from;   cin >> from;
        cout << "\nnode | distance from " << from << " | path\n";

        vii distances = bfs_unweighted_graph(edges, from);

        for (int i = 0; i < n; i++) {

            if (distances[i].first == -1) {
                cout << i << " Unaccessible from " << from << "\n";
                continue;
            }

            vi path = path_unweighted_graph(edges, i, from);

            cout << i << "      " << distances[i].first << "                 ";

            for (int j = 0; j < (int)path.size(); j++) {
                if (j != 0) cout << "->";
                cout << path[j];
            }

            cout << "\n";
        }
        */

        /* // weighted graph used with dijkstra.txt
        vector<vii> edges = initializer_graph(n, m, true, is);
        visualise_graph(edges);

        cout << "\nEnter the source ... ";
        int from;   cin >> from;
        cout << "\nnode | distance from " << from << " | path\n";

        vii distances = Dijkstra(edges, from);

        for (int i = 0; i < n; i++) {

            vi path = path_graph(edges, i, from);

            cout << i << "      " << distances[i].first << "                 ";

            for (int j = 0; j < (int)path.size(); j++) {
                if (j != 0) cout << "->";
                cout << path[j];
            }

            cout << "\n";
        }
        */


        /*
        // DSU
        DSU dsu(9);
        dsu.mergeGroups(4, 3);
        dsu.mergeGroups(2, 1);

        dsu.mergeGroups(1, 3);
        dsu.mergeGroups(6, 5);

        int x, y;
        cin >> x >> y;
        do {
            cout << boolalpha << dsu.sameGroup(x, y) << endl;
            cin >> x >> y;
        } while (x != 9);
        */

    }
    catch (std::exception const& e) {
        cerr << "Error: " << e.what();
    }

	return 0;
}
