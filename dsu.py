# - Disjoint set union (DSU) class
"""
>>> Used to answer queries about graph components
1- How many connected components?
2- Do u and v belong to the same component?
3- What is the size of the component to which u belongs?

>>> This algorithm is used whenever needed (before or after graph manipulation)
"""

class DSU:
    
    def __init__(self, n_vertices):
        
        self.__n_vertices = n_vertices
        self.__parent = [ i for i in range(n_vertices)]
        self.__group_size = [ 1 for i in range(n_vertices)]


    def find_leader(self, x):
        
        if x >= self.__n_vertices: raise ValueError

        if self.__parent[x] == x:  return x

        return self.find_leader(self.__parent[x])


    def same_group(self, x, y):
        leader1 = self.find_leader(x)
        leader2 = self.find_leader(y)

        return leader1 == leader2


    def merge_groups(self, x, y):
        leader1 = self.find_leader(x)
        leader2 = self.find_leader(y)

        if leader1 == leader2:  return

        if self.__group_size[leader1] > self.__group_size[leader2]:
            
            self.__parent[leader2] =  leader1
            self.__group_size[leader1] += self.__group_size[leader2]

        else:
            self.__parent[leader1] =  leader2
            self.__group_size[leader2] += self.__group_size[leader1]


    def get_size(self, x):
        leader = self.find_leader(x)
        return self.__group_size[leader]

if __name__ == "__main__":
    
    try:
        dsu = DSU(9)
        dsu.merge_groups(4, 3)
        dsu.merge_groups(2, 1)

        dsu.merge_groups(1, 3)
        dsu.merge_groups(6, 5)

        while True:
            x = int(input("x = "))
            y = int(input("y = "))
            print(dsu.same_group(x, y))
            if dsu.same_group(x, y): print("Size = " + str(dsu.get_size(x)))
            if (x == 99): break
        
    except ValueError:
        print("Error: argument value error -> (DSU: i >= m_n_vertices)...\n")
    except:
        print("An Error Occured")
    finally:
        print('Finished')
