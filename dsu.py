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
        self.__parent = [ -1 for i in range(n_vertices)]
        self.__groupSize = [ 0 for i in range(n_vertices)]

        for i in range(n_vertices):
            self.__parent[i] = i
            self.__groupSize[i] = 1


    def findLeader(self, x):
        
        if x >= self.__n_vertices: raise ValueError

        if self.__parent[x] == x:  return x

        return self.findLeader(self.__parent[x])


    def sameGroup(self, x, y):
        leader1 = self.findLeader(x);
        leader2 = self.findLeader(y);

        return leader1 == leader2


    def mergeGroups(self, x, y):
        leader1 = self.findLeader(x);
        leader2 = self.findLeader(y);

        if leader1 == leader2:  return

        if self.__groupSize[leader1] > self.__groupSize[leader2]:
            
            self.__parent[leader2] =  leader1
            self.__groupSize[leader1] += self.__groupSize[leader2]

        else:
            self.__parent[leader1] =  leader2
            self.__groupSize[leader2] += self.__groupSize[leader1]


    def getSize(self, x):
        leader = self.findLeader(x)
        return self.__groupSize[leader]

if __name__ == "__main__":
    
    try:
        dsu = DSU(9)
        dsu.mergeGroups(4, 3)
        dsu.mergeGroups(2, 1)

        dsu.mergeGroups(1, 3)
        dsu.mergeGroups(6, 5)

        while True:
            x = int(input("x = "))
            y = int(input("y = "))
            print(dsu.sameGroup(x, y))
            if dsu.sameGroup(x, y): print("Size = " + str(dsu.getSize(x)))
            if (x == 99): break
        
    except ValueError:
        print("Error: argument value error -> (DSU: i >= m_n_vertices)...\n")
    except:
        print("An Error Occured")
    finally:
        print('Finished')
