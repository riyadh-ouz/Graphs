#Graph representation with Adjanceny matrix

class Graph:

    def __init__(self, size):
        self.adj = []
        for i in range(1, size + 1):
            self.adj.append([0 for i in range(size)])
            self.size = size

    # Adding edges
    def add_edge(self, orig, dest):

        if orig > self.size or dest > self.size: raise ValueError

        self.adj[orig-1][dest-1] = 1
        self.adj[dest-1][orig-1] = 1

    # Removing Edges
    def remove_edge(self, orig, dest):

        if orig > self.size or dest > self.size: raise ValueError

        self.adj[orig-1][dest-1] = 0
        self.adj[dest-1][orig-1] = 0

    # Visualise
    def display(self):
        for row in self.adj:
            print()
            for val in row:
                print('{:4}'.format(val), end = '')
        print()


if __name__ == "__main__":
    
    try:
        graph = Graph(6)
        graph.add_edge(1, 2)
        graph.add_edge(1, 4)
        graph.add_edge(2, 5)
        graph.add_edge(3, 2)
        graph.add_edge(4, 2)
        graph.add_edge(0, 1)
        graph.remove_edge(0, 1)

        graph.display()
        
    except ValueError:
        print("Error: ValueError -> review nodes values!!!")
    except:
        print("An Error Occured")
    finally:
        print('Finished')
    
        
        
