#include <fstream>
#include "graph.h"

using namespace std;

int main(int argc, char* argv[])
{
    try {

        ifstream is {argv[1]};
        int n, m;	is >> n >> m;

        /* ///unweighted graph
        vector<vi> edges = initializer_unweighted_graph(n, m, false, is);
        visualise_unweighted_graph(edges);

        cout << numberOfComponents_graph(edges) << "\n";

        //cout << height_tree(0, edges);

        int from;

        cout << "\nEnter the source ... ";
        cin >> from;
        cout << "\nnode distance from " << from << " path\n";

        for (int i = 0; i < n; i++) {

            vi path = path_unweighted_graph(edges, i, from);

            cout << i << "    " <<path.size() - 1 << "               ";

            for (int j = 0; j < (int)path.size(); j++) {
                if (j != 0) cout << "->";
                cout << path[j];
            }

            cout << "\n";
        }

        */

        ///weighted graph
        vector<vii> edges = initializer_graph(n, m, true, is);
        visualise_graph(edges);

        int from;

        cout << "\nEnter the source ... ";
        cin >> from;
        cout << "\nnode distance from " << from << " path\n";

        vii paths = Dijkstra(edges, from);

        for (int i = 0; i < n; i++) {

            vi path = path_graph(edges, i, from);

            cout << i << "    " << paths[i].first << "               ";

            for (int j = 0; j < (int)path.size(); j++) {
                if (j != 0) cout << "->";
                cout << path[j];
            }

            cout << "\n";
        }

    }
    catch (int e) {
        cerr << e << '\n';
    }

	return 0;
}
