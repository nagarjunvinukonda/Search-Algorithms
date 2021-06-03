# """
# Created on Mon Mar  2 15:02:31 2020
#
# @author: NAGARJUN
# """
#
# # dijkstra's algorithm
# """
# 1. Assign to every node a distance value. Set it to zero for our initial node
#    and to infinity for all other nodes.
# 2. Mark all nodes as unvisited. Set initial node as current.
# 3. For current node, consider all its unvisited neighbors and calculate their
#    tentative distance (from the initial node). For example, if current node
#    (A) has distance of 6, and an edge connecting it with another node (B)
#    is 2, the distance to B through A will be 6+2=8. If this distance is less
#    than the previously recorded distance (infinity in the beginning, zero
#    for the initial node), overwrite the distance.
# 4. When we are done considering all neighbors of the current node, mark it as
#    visited. A visited node will not be checked ever again; its distance
#    recorded now is final and minimal.
# 5. If all nodes have been visited, finish. Otherwise, set the unvisited node
#    with the smallest distance (from the initial node) as the next "current
#    node" and continue from step 3.
#  - source: wikipedia http://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
# """


'''
The following is our graph visualization at start:
# All the nodes except start node is provided as infinity cost

[start(0)]  A----7---D---6---G
            | \     / \     /|
            |  4   2   3   3 |
            |   \ /     \ /  |
            3    C       E   2
            |   / \     / \  |
            |  1   6   1   4 |
            | /     \ /     \|
            B---5----F---8---H [destination(infinity)]
'''

# Dictionary to represent the graph (at start)
# This graph matrix is like an adjacencyList as described in my bfs and dfs.py files
graph = {
'a':{'b':3,'c':4, 'd':7},
'b':{'c':1,'f':5},
'c':{'f':6,'d':2},
'd':{'e':3, 'g':6},
'e':{'g':3, 'h':4},
'f':{'e':1, 'h':8},
'g':{'h':2},
'h':{'g':2}
}

def dijkstra(graph,start,goal):

    shortest_distance = {} #dictionary to record the cost to reach to node. We will constantly update this dictionary as we move along the graph.
    track_predecessor = {} #dictionary to keep track of path that led to that node.
    unseenNodes = graph    #let the graph be unseenNodes in order iterate through all nodes.
    infinity = 777         #a very large number can be considered instead of infinity.
    track_path = []        #dictionary to record as we trace back our journey to source node ---optimal route.

# Initially we want to assign 0 as the cost to reach to source node and infinity as cost to all other nodes
    for node in unseenNodes:
        shortest_distance[node] = infinity

    shortest_distance[start] = 0


# The loop will keep running until we have entirely exhausted the graph, until we have seen all the nodes-
#-to iterate through the graph, we need to determine the min_distance_node every time.

    while unseenNodes:
        min_distance_node = None

        for node in unseenNodes:              #here node is key of dictionary graph
            if min_distance_node is None:
                min_distance_node = node      #specifying it as start node
            #     Pick the minimum distance vertex from the set of vertices not yet processed.
            elif shortest_distance[node] < shortest_distance[min_distance_node]:
                min_distance_node = node      #swaping the value of min_distance node to make sure we can check all the nodes




# From the minimum node, what are our possible paths
        path_options = graph[min_distance_node].items()  #This opens values of that particular key in dictionary

# We have to calculate the cost each time for each path we take and only update it if it is lower than the existing cost
        for child_node, weight in path_options: #taking key and values of that pathoptions in deictionary
            if weight + shortest_distance[min_distance_node] < shortest_distance[child_node]:  # for example: lets take between A and B, as A(0) +weight(3) < B(777). B is now A +weight
                shortest_distance[child_node] = weight + shortest_distance[min_distance_node]
                track_predecessor[child_node] = min_distance_node

# We want to pop out the nodes that we have just visited so that we dont iterate over them again.
        unseenNodes.pop(min_distance_node)

# Once we have reached the destination node, we want trace back our path and calculate the total accumulated cost.
    currentNode = goal

    while currentNode != start:
        try:
            track_path.insert(0,currentNode) #track_path is like a queue as described in bfs.py
            currentNode = track_predecessor[currentNode]
        except KeyError:
            print('we cant reach path')
            break
    track_path.insert(0,start)

#  If the cost is infinity, the node had not been reached.
    if shortest_distance[goal] != infinity:
        print('shortest available distance: ' + str(shortest_distance[goal]))
        print('path: ' + str(track_path))

dijkstra(graph, 'a', 'h')


#Refernce: https://www.youtube.com/watch?v=KfbS6c9LneE


