from graph import Graph

try:

    # data from dijkstra.txt
    # Weighted directed graph

    print("Enter edges with costs")
    
    graph  = Graph(5, 10, True, True)
    graph.visualise()

    graph.dfs(0)

    src = int(input("\nEnter the source ... "))
    
    print("\nnode | distance src " + str(src) + " | path\n", end = '', sep = '')

    distances = graph.Dijkstra(src)

    for i in range(5):

        path = graph.path(i, src)
        # path = graph.path_without_cost(i, src)

        print(str(i) + "      " + str(distances[i][0]) + "                 ", end = '', sep = '')

        for j in range(len(path)):
            if j != 0: print("->", end = '', sep = '')
            print(path[j], end = '', sep = '')

        print("\n", end = '', sep = '')

    # used with tree.txt
    # Graph with two components one is like tree with root = 1
    print("Enter edges with costs")
    graph1 = Graph(9, 7, False, False)
    graph1.visualise()
    graph1.dfs(1)
    print("Components: " + str(graph1.number_of_components()))
    print("Height: " + str(graph1.height_tree(1, -1)))


except ValueError:
        print("Error: ValueError -> review nodes values!!!")
except:
        print("An Error Occured")
finally:
        print('Finished')
