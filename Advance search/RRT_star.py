"""
Created on Thur Feb 27 12:02:31 2020

@author: NAGARJUN
"""
# This program generates a asymptotically optimal rapidly exploring random tree (RRT*)
# Note: If run again if you are facing any problem and the path is not optimal
'''
Basic idea is:
First initialise all the variables, i.e. set the start and end nodes, etc.
Find the point that is at lesser distance than nearest vertex of tree 
update nodes
Draw the edge of that point to nearest point in tree
rewire the edges
display the final path



'''


import sys, random, math, pygame
from pygame.locals import *
from math import sqrt, cos, sin, atan2

# constants
XDIM = 640
YDIM = 480
WINSIZE = [XDIM, YDIM]
EPSILON = 7.0   #Different epsilon values have little effect on graph size or the transfer of information > epsilon.
                #The most noticeable effect is that smaller epsilon values improve short-term convergence rates in static environments (i.e., when
                #maintenance rewiring causes cost changes < epsilon).
NUMNODES = 5000 #stopping criteria for RRT* is user defined; common choices include: (1) a time-out,
                # (2) a predefined number of nodes sampled, or (3) a predefined number of nodes added to the search-tree/graph.
RADIUS = 15     #radius of nearest vertex

# function to find distance between two points(p1 & p2) of its x,y coordinates
def dist(p1, p2):
    return sqrt((p1[0] - p2[0]) * (p1[0] - p2[0]) + (p1[1] - p2[1]) * (p1[1] - p2[1]))


def step_from_to(p1, p2):
    if dist(p1, p2) < EPSILON: #if the distance between two points is less than epsilon then take return new node position (interpolated node)
        return p2
    else:  # if distance between two points is greater than threshold then return its minimum distance from first node(p1) as position i.e. projection x+rcos(theta)
        theta = atan2(p2[1] - p1[1], p2[0] - p1[0])
        return p1[0] + EPSILON * cos(theta), p1[1] + EPSILON * sin(theta)


def chooseParent(nn, newnode, nodes):
    # nodes is the tree to destination, nn is nearest vertex of tree
    # Get nearby vertices to new vertex and their associated path costs from the root of tree
    #-as if new vertex is connected to each one separately.
    for p in nodes:
        # if a point or node of tree vertex satisfies the following condition w.r.t to nearby vertex (nn) of tree then assume that point is nearest vertex
        if dist([p.x, p.y], [newnode.x, newnode.y]) < RADIUS and p.cost + dist([p.x, p.y],
                                                                               [newnode.x, newnode.y]) < nn.cost + dist(
                [nn.x, nn.y], [newnode.x, newnode.y]):
            nn = p
    #updating newnode cost
    newnode.cost = nn.cost + dist([nn.x, nn.y], [newnode.x, newnode.y])
    newnode.parent = nn
    return newnode, nn


def reWire(nodes, newnode, pygame, screen):
    #Rewire tree to shorten edges if possible

    white = 255, 255, 255
    black = 20, 20, 40
    for i in range(len(nodes)):
        p = nodes[i]
        if p != newnode.parent and dist([p.x, p.y], [newnode.x, newnode.y]) < RADIUS and newnode.cost + dist([p.x, p.y],
                                                                                                             [newnode.x,
                                                                                                              newnode.y]) < p.cost:
            # for a sample in tree is not nearby vertex and less than the radius
            # It cuts the sampling edge of tree that is long than edge formed with new node
            pygame.draw.line(screen, white, [p.x, p.y], [p.parent.x, p.parent.y])
            p.parent = newnode
            p.cost = newnode.cost + dist([p.x, p.y], [newnode.x, newnode.y])
            nodes[i] = p
            # It draws the sampling edge of tree that is shorter than edge formed with new node
            pygame.draw.line(screen, black, [p.x, p.y], [newnode.x, newnode.y])
    return nodes


def drawSolutionPath(start, goal, nodes, pygame, screen):
    green = 0, 255, 0
    nn = nodes[0]
    for p in nodes:
        if dist([p.x, p.y], [goal.x, goal.y]) < dist([nn.x, nn.y], [goal.x, goal.y]):
            nn = p
    # draw the final path along the root tree i.e path along nearest vertex to goal
    while nn != start:
        pygame.draw.line(screen, green, [nn.x, nn.y], [nn.parent.x, nn.parent.y], 5)
        nn = nn.parent

class Node:
    x = 0
    y = 0
    cost = 0
    parent = None
    #Each time I call Node() it appends given xcoord, ycoord to x,y
    def __init__(self, xcoord, ycoord):
        self.x = xcoord
        self.y = ycoord


def main():
    # initialize and prepare screen
    pygame.init()
    screen = pygame.display.set_mode(WINSIZE)
    pygame.display.set_caption('RRTstar')
    white = 255, 255, 255
    black = 20, 20, 40
    screen.fill(white)

    nodes = []

    # nodes.append(Node(XDIM/2.0,YDIM/2.0)) # Start in the center (If we want to start our position at center)
    nodes.append(Node(0.0, 0.0))  # Start in the corner #tree that we will follow
    start = nodes[0]
    goal = Node(630.0, 470.0) #goal position
    for i in range(NUMNODES):
        #Note: random.random returns a random float number between 0.0 and 1.0 i.e. [0,1):
        #taking any random point in from the screen
        rand = Node(random.random() * XDIM, random.random() * YDIM)
        nn = nodes[0]
        # making sure, if distance of random node and initial node is greater than random node and node in nodes list, to start drawing tree from that point
        # this make sure to lessen the distance between random point and sample point.
        for p in nodes:
            if dist([p.x, p.y], [rand.x, rand.y]) < dist([nn.x, nn.y], [rand.x, rand.y]):
                nn = p
        interpolatedNode = step_from_to([nn.x, nn.y], [rand.x, rand.y]) #finding a node that is less than the cost

        newnode = Node(interpolatedNode[0], interpolatedNode[1])
        [newnode, nn] = chooseParent(nn, newnode, nodes)

        #adding the new node into the tree
        nodes.append(newnode)
        #reprsenting balck line as edge of tree # where edge is distance between nearby vertex(nn) and newnode
        pygame.draw.line(screen, black, [nn.x, nn.y], [newnode.x, newnode.y])
        #provides the shorthened edges
        nodes = reWire(nodes, newnode, pygame, screen)
        pygame.display.update()
        #printing the node count
        print(i, "    ", nodes)

        #if we press Esc it quits and gives following message
        for e in pygame.event.get():
            if e.type == QUIT or (e.type == KEYUP and e.key == K_ESCAPE):
                sys.exit("You pressed escape")
    drawSolutionPath(start, goal, nodes, pygame, screen)
    pygame.display.update()


# if python says run, then we should run
if __name__ == '__main__':
    main()
    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

# Reference:
# https://www.researchgate.net/publication/324975415_Sampling-Based_Planning_Algorithms_for_Multi-Objective_Missions,
# https://www.youtube.com/watch?v=M5Q6Fywd36w


