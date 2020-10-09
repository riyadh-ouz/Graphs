#from collections import deque
from queue import LifoQueue
from queue import Queue
from queue import PriorityQueue


# the Graph class (represented with adjacency list)
class Graph:
    
    def __init__(self, n_vertices, n_edges, weighted, directed, input_stream = input):
        self.__n_vertices = n_vertices
        self.__n_edges = n_edges
        self.__weighted = weighted
        self.__directed = directed
        
        self.__edges = [[] for i in range(n_vertices)]

        for i in range(n_edges):
                                
            u = int(input_stream())
            v = int(input_stream())
            
            if weighted: w = int(input_stream())
                
            if u >= n_vertices or v >= n_vertices: raise ValueError
                
            if u != v:
                if weighted:
                    self.__edges[u].append([v, w])
                    if not directed: self.__edges[v].append([u, w])
                else:
                    self.__edges[u].append(v)
                    if not directed: self.__edges[v].append(u)



    def visualise(self, output_stream = print):
        
        output_stream("\n", end = '', sep = '')
    
        for node in range(self.__n_vertices):
                
            output_stream(str(node) + " : ", end = '', sep = '')
            for neighbor in self.__edges[node]:
                if self.__weighted:
                    output_stream("(" + str(neighbor[0]) + " ," + str(neighbor[1]) + ") ", end = '', sep = '')
                else:
                    output_stream(str(neighbor) + " ", end = '', sep = '')
                
            output_stream("\n", end = '', sep = '')
            
        output_stream("\n", end = '', sep = '')


    # Warning: bfs for weighted graphs treats it as unweighted graph (edgeCost = 1) use dijkstra instead
    def bfs(self, source = 0):

        if source >= self.__n_vertices: raise ValueError
        
        # __n_vertices paths from the source initialized with distance -1 and previous -1
        paths = [ [-1, -1] for i in range(self.__n_vertices)]

        paths[source][0] = 0 # the cost from the source to the source

        #q = deque()
        q = Queue()

        #q.append(source)
        q.put(source)

        while not q.empty():
        
            #node = q.popleft()
            node = q.get()
            cost = paths[node][0] # cost refers the the distance

            
            for neighbor in self.__edges[node]:
                if self.__weighted:
                    if paths[neighbor[0]][0] == -1: # not visited
                        q.put(neighbor[0])
                        paths[neighbor[0]] = [cost + 1, node] # stores the cost and the previous
                else:
                    if paths[neighbor][0] == -1: # not visited
                        q.put(neighbor)
                        paths[neighbor] = [cost + 1, node] # stores the cost and the previous

        # Nodes of other components (unreachable from the source node) still have paths of {-1, -1}.
        return paths


    def Dijkstra(self, source = 0):

        if source >= self.__n_vertices: raise ValueError

        if self.__weighted:

            parent = [ -1 for i in range(self.__n_vertices)]
            cost = [ 1000000 for i in range(self.__n_vertices)] # cost is initialized with INF = 1000000
            expanded = [ False for i in range(self.__n_vertices)]

            parent[source] = source
            cost[source] = 0


            # PriorityQueue of pairs: (cost, node)
            q = PriorityQueue()

            q.put((0, source))

            while not q.empty():
                
                node = q.get()[1]

                # we should control for the duplicated elements in the queue
                if expanded[node]: continue

                else: expanded[node] = True

                for i in range(len(self.__edges[node])):
                               
                    edge = self.__edges[node][i]
                    neighbor = edge[0]
                    edgeCost = edge[1]

                    if (cost[node] + edgeCost) < cost[neighbor]:
                               
                        parent[neighbor] = node
                        cost[neighbor] = cost[node] + edgeCost

                        q.put((cost[neighbor], neighbor))
                    

            result = [ 0 for i in range(self.__n_vertices)]
            for i in range(self.__n_vertices):  result[i] = [cost[i], parent[i]];

            return result
        
        else:
            # dijkstra = bfs in case of unweighted graph
            return bfs(source)


    def path(self, dest, src = 0):

        if dest >= self.__n_vertices or src >= self.__n_vertices: raise ValueError
        
        path = []

        if self.__weighted: paths = self.Dijkstra(src)
        else: paths = self.bfs(src)
            
        path.append(dest)
        node = dest

        while node != src:
            node = paths[node][1] # get the previous for the current node
            path.append(node)
            
        path.reverse() # to get the path from "from" to "to"
        
        return path

    # Warning: the following functions treat the graph as unweighted
    def path_without_cost(self, dest, src = 0):

        if dest >= self.__n_vertices or src >= self.__n_vertices: raise ValueError

        path = []

        paths = self.bfs(src)
            
        path.append(dest)
        node = dest

        while node != src:
            node = paths[node][1] # get the previous for the current node
            path.append(node)
            
        path.reverse() # to get the path from "from" to "to"
        
        return path

    def dfs(self, source = 0, output_stream = print):

        if source >= self.__n_vertices: raise ValueError
        
        self.__visited = [ False for i in range(self.__n_vertices)]

        s = LifoQueue()
        s.put(source)

        output_stream("\nDFS traverse\n", end = '', sep = '')
        
        while not s.empty():
                
            u = s.get()
            
            if not self.__visited[u]:
                output_stream(str(u) + " ", end = '', sep = '')
                self.__visited[u] = True

            for v in self.__edges[u]:
                if self.__weighted:
                    if not self.__visited[v[0]]:
                            s.put(v[0]);
                else:
                    if not self.__visited[v]:
                        s.put(v);
                
        output_stream("\n")


    # Warning: avoid calling numberOfComponents for directed graphs;
    def numberOfComponents(self):
        
        numberOfComponents = 0
        self.__visited = [ False for i in range(self.__n_vertices)]

        if self.__directed: raise  ValueError

        for node in range(self.__n_vertices):
            if not self.__visited[node]:
                numberOfComponents += 1

                # start dfs[node]
                
                s = LifoQueue()
                s.put(node)

                while not s.empty():
                
                    u = s.get()

                    if not self.__visited[u]:
                        self.__visited[u] = True

                    for v in self.__edges[u]:
                        if self.__weighted:
                            if not self.__visited[v[0]]:
                                    s.put(v[0]);
                        else:
                            if not self.__visited[v]:
                                s.put(v);
                                
                # end dfs[node]
                
        return numberOfComponents


    # Case: graph like tree (no matter directed or undirected)
    def height_tree(self, root = 0,parent = -1):

        if root >= self.__n_vertices: raise ValueError
        
        height = 0
        
        for child in self.__edges[root]:
            if self.__weighted:
                if child[0] != parent:
                    temp = self.height_tree(child[0], root) # parent is crucial because we are in graph like tree
                    height = max(temp, height)

            else:
                if child != parent:
                    temp = self.height_tree(child, root)
                    height = max(temp, height)


        return 1 + height

        
