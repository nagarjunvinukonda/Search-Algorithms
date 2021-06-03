"""
Created on Mon Mar  2 13:14:16 2020

@author: NAGARJUN
"""

'''
My graph for dfs, The following numbers are vertices
[           0
           /  \
          1    2
         /    / \
        3    4   5
            /
           6
]


'''
'''
Few Notations:

adjacencyList:       It is a list that takes appends neighbors of each vertex
stack:               A list that inputs each vertex order that we follow
current:             It is a temporary list that inputs current vertex that we follow
visitedVertex        It is a list that notes the complete path we followed

'''
############### Depth first search #####################################

vertexList = ['0', '1', '2', '3', '4', '5', '6']
edgeList = [(0,1), (0,2), (1,0) , (1,3) , (2,0) , (2,4) , (2,5) , (3,1), (4,2) , (4,6), (5,2), (6,4)]
graphs = (vertexList, edgeList)

def dfs(graph, start):
    vertexList, edgeList = graph
    visitedVertex = []
    stack = [start]
    adjacencyList = [[] for vertex in vertexList] # This prints 7 empty lists inside adjacencyList i.e. for each vertex

    for edge in edgeList:
        adjacencyList[edge[0]].append(edge[1])  #this function selects a edge from edgeList and appends 2nd element of edge
                                                # into position of first element of edge


        '''
            The above method creates an adjacency list as follows:
            adjacencyList:
            [
                    [1,2],   // vertex 0
                    [0,3],   // vertex 1
                    [0,4,5], // vertex 2
                    [1],     // vertex 3
                    [2,6],   // vertex 4
                    [2],     // vertex 5
                    [4]      // vertex 6


            ]

        '''

    while stack:
        current = stack.pop()    #pop function pops out the last element of the list
        for neighbor in adjacencyList[current]:
            if not neighbor in visitedVertex:
                stack.append(neighbor)        #If the neighbors of vertex (i.e. adjancencyList edge elements) are not available
                                              # in visited list then add the neighbors in stack and later add the current vertex
                                              # into visitedVertex list  ## The appends adds elements last of the list
        visitedVertex.append(current)
    return visitedVertex

#Note: the append() function here when we expanded the code make sures the neighbours visited are depth wise not wide searching like bfs

print(dfs(graphs, 0))

# Reference: https://www.youtube.com/watch?v=iaBEKo5sM7w

