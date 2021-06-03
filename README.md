# Search-Algorithms:
* Programming Search Algorithms namely BFS, DFS, Dijkstra, A* and RRT* using Python

* Made simple implmentations with annoted explanation of planning algorithms.  

* Further I have worked on implementing A* search Algorithm on Open Street Map (OSM) using Io2D libraries and C++. 

# A* search on Open-Street Map:
[Route Planning Project](https://github.com/nagarjunvinukonda/CppOSMproject)


# Random_planner:

* The time Time complexity of algorithm is around  no_of_operations_for_4_connectivity*(sqrt(max_number_of_steps)^1.5). The no_of_operations are constant i.e. 4. Hence, sqrt(max_number_of_steps)^1.5.
* The planner path is not optimal sometimes same path might repeat again. 
* Here array are used for fatser insertion and deletion. 


# Optimal_planner:
* The A_star search Algorithm is implemneted using linked Lists.
* Linked lists have fast insertions/deletions(constatnt time) at any point in the list than compared to vectors. For vectors insertions/deletions in the middle/beginning of the vector are slow.
* This provides optimal path if one exists on grid. 
* The Complexity of Algorithm is depends on size of the grid(row*col) since we are having constant hurestic.

### Note:- Optimal planner is also been implemnted python. 


# Running:

### Note:- Dont forget to change the location of input board according to your system in both test_random.cpp and test_astar.cpp.  

* Run the test_random.cpp
* Run the test_astar.cpp
