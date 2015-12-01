from reading import Maze, MazeReader
from graph import Node
from heapq import heappush, heappop

class Robot(object):
    """Robot traveling the graph to find the correct optimum answer."""
    def __init__(self, maze):
        self.maze = maze
        self.orient = maze.orient
        self.start = Node(maze, maze.start_x, maze.start_y)

    def dijkstra(self):
        class HeapObject(object):
            """docstring for HeapObject"""
            def __init__(self, node, move, cost, orient):
                self.node = node
                self.move = move
                self.cost = cost
                self.orient = str(orient)
            def __lt__(self, other):
                return self.cost < other.cost
        heap = []
        heappush(heap, HeapObject(self.start, [], 0, self.orient))
        current = heappop(heap)
        while (current.node.x != self.maze.end_x) or (current.node.y != self.maze.end_y):
            current.node.lookup_around()
            if current.node.up is not None:
                if current.orient.startswith('nord'):
                    if len(current.move) >= 1:
                        if current.move[-1] == 'a1':
                            heappush(heap, HeapObject(current.node.up, current.move[:-1] + ['a2'], current.cost, 'nord'))
                        elif current.move[-1] == 'a2':
                            heappush(heap, HeapObject(current.node.up, current.move[:-1] + ['a3'], current.cost, 'nord'))
                        else:
                            heappush(heap, HeapObject(current.node.up, current.move + ['a1'], current.cost + 1, 'nord'))
                    else:
                        heappush(heap, HeapObject(current.node.up, current.move + ['a1'], current.cost + 1, 'nord'))
                elif current.orient.startswith('est'):
                    heappush(heap, HeapObject(current.node.up, current.move + ['G'] + ['a1'], current.cost + 2, 'nord'))
                elif current.orient.startswith('ouest'):
                    heappush(heap, HeapObject(current.node.up, current.move + ['D'] + ['a1'], current.cost + 2, 'nord'))
            if current.node.down is not None:
                if current.orient.startswith('sud'):
                    if len(current.move) >= 1:
                        if current.move[-1] == 'a1':
                            heappush(heap, HeapObject(current.node.down, current.move[:-1] + ['a2'], current.cost, 'sud'))
                        elif current.move[-1] == 'a2':
                            heappush(heap, HeapObject(current.node.down, current.move[:-1] + ['a3'], current.cost, 'sud'))
                        else:
                            heappush(heap, HeapObject(current.node.down, current.move + ['a1'], current.cost + 1, 'sud'))
                    else:
                        heappush(heap, HeapObject(current.node.down, current.move + ['a1'], current.cost + 1, 'sud'))
                elif current.orient.startswith('est'):
                    heappush(heap, HeapObject(current.node.down, current.move + ['D'] + ['a1'], current.cost + 2, 'sud'))
                elif current.orient.startswith('ouest'):
                    heappush(heap, HeapObject(current.node.down, current.move + ['G'] + ['a1'], current.cost + 2, 'sud'))
            if current.node.right is not None:
                if current.orient.startswith('est'):
                    if len(current.move) >= 1:
                        if current.move[-1] == 'a1':
                            heappush(heap, HeapObject(current.node.right, current.move[:-1] + ['a2'], current.cost, 'est'))
                        elif current.move[-1] == 'a2':
                            heappush(heap, HeapObject(current.node.right, current.move[:-1] + ['a3'], current.cost, 'est'))
                        else:
                            heappush(heap, HeapObject(current.node.right, current.move + ['a1'], current.cost + 1, 'est'))
                    else:
                        heappush(heap, HeapObject(current.node.right, current.move + ['a1'], current.cost + 1, 'est'))
                elif current.orient.startswith('nord'):
                    heappush(heap, HeapObject(current.node.right, current.move + ['D'] + ['a1'], current.cost + 2, 'est'))
                elif current.orient.startswith('sud'):
                    heappush(heap, HeapObject(current.node.right, current.move + ['G'] + ['a1'], current.cost + 2, 'est'))
            if current.node.left is not None:
                if current.orient.startswith('ouest'):
                    if len(current.move) >= 1:
                        if current.move[-1] == 'a1':
                            heappush(heap, HeapObject(current.node.left, current.move[:-1] + ['a2'], current.cost, 'ouest'))
                        elif current.move[-1] == 'a2':
                            heappush(heap, HeapObject(current.node.left, current.move[:-1] + ['a3'], current.cost, 'ouest'))
                        else:
                            heappush(heap, HeapObject(current.node.left, current.move + ['a1'], current.cost + 1, 'ouest'))
                    else:
                        heappush(heap, HeapObject(current.node.left, current.move + ['a1'], current.cost + 1, 'ouest'))
                elif current.orient.startswith('nord'):
                    heappush(heap, HeapObject(current.node.left, current.move + ['G'] + ['a1'], current.cost + 2, 'ouest'))
                elif current.orient.startswith('sud'):
                    heappush(heap, HeapObject(current.node.left, current.move + ['D'] + ['a1'], current.cost + 2, 'ouest'))
            current = heappop(heap)
        print(current.cost)
        print(current.move)

mr = MazeReader()
for i in mr.read_maze('../instances/exemple.maze'):
    i.print_maze()
    robot = Robot(i)
    robot.dijkstra()
