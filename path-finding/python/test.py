from Graph import *
from Queue import *
from path_finder import *
from SquareGrid import *
from GridWithWeights import *

#section breadth_first_search start from some point(node)
example_graph = Graph()

example_graph.edges = {
    'A' : ['B'],
    'B' : ['A', 'C', 'D'],
    'C' : ['A'],
    'D' : ['E', 'A'],
    'E' : ['B']
}

print("breadth_first_search from one start point:")
breadth_first_search(example_graph, 'A')

#section breadth_first_search from start to goal
DIAGRAM1_WALLS = [from_id_width(id, width=30) for id in [21,22,51,52,81,82,93,94,111,112,123,124,133,134,141,142,153,154,163,164,171,172,173,174,175,183,184,193,194,201,202,203,204,205,213,214,223,224,243,244,253,254,273,274,283,284,303,304,313,314,333,334,343,344,373,374,403,404,433,434]]

g = SquareGrid(30, 15)
g.walls = DIAGRAM1_WALLS

start = (8, 7)
goal = (18, 8)
parents = breadth_first_search(g, start, goal)
print("bread_first_search from %r to %r" % (start, goal))
draw_grid(g, width=2, point_to=parents, start=start, goal=goal)

#section dijkstra_search
diagram4 = GridWithWeights(10, 10)
diagram4.walls = [(1, 7), (1, 8), (2, 7), (2, 8), (3, 7), (3, 8)]
diagram4.weights = {loc: 5 for loc in [(3, 4), (3, 5), (4, 1), (4, 2),
                                       (4, 3), (4, 4), (4, 5), (4, 6), 
                                       (4, 7), (4, 8), (5, 1), (5, 2),
                                       (5, 3), (5, 4), (5, 5), (5, 6), 
                                       (5, 7), (5, 8), (6, 2), (6, 3), 
                                       (6, 4), (6, 5), (6, 6), (6, 7), 
                                       (7, 3), (7, 4), (7, 5)]}

start = (1, 4)
goal = (7, 8)
came_from, cost_so_far = dijkstra_search(diagram4, start, goal)
print("came_from in dijkstra_search from %r to %r" % (start, goal))
draw_grid(diagram4, width=3, point_to=came_from, start=start, goal=goal)
print("cost_so_far in dijkstra_search from %r to %r" %(start, goal))
draw_grid(diagram4, width=3, number=cost_so_far, start=start, goal=goal)
print("path in dijkstra_search from %r to %r" %(start, goal))
draw_grid(diagram4, width=3, path=reconstruct_path(came_from, start=start, goal=goal))

#section a_star_search
came_from, cost_so_far = a_star_search(diagram4, start, goal)
print("came_from in a_star_search from %r to %r" % (start, goal))
draw_grid(diagram4, width=3, point_to=came_from, start=start, goal=goal)
print("cost_so_far in a_star_search from %r to %r" % (start, goal))
draw_grid(diagram4, width=3, number=cost_so_far, start=start, goal=goal)
