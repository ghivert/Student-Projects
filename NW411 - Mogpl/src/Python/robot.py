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
        """Evolve through the graph. Dynamically expand nodes, without walking on previous visited nodes. Find shortest path."""
        class HeapObject(object):
            """docstring for HeapObject"""
            def __init__(self, node, move, cost, orient):
                self.node = node
                self.move = move
                self.cost = cost
                self.orient = orient.strip()
            # Sort for the heap.
            def __lt__(self, other):
                return self.cost < other.cost
        # For keeping already view nodes.
        passed = []
        for i in range(len(self.maze.maze) + 1):
            li = []
            for j in range(len(self.maze.maze[0]) + 1):
                li.append({'nord': False, 'ouest': False, 'sud': False, 'est':         False})
            passed.append(li)
        # To find the cheapest node.
        heap = []
        heappush(heap, HeapObject(self.start, [], 0, self.orient))
        current = heappop(heap)
        # Search while not on ending point.
        while (current.node.x != self.maze.end_x) or (current.node.y != self.maze.end_y):
            # Keep trace of node.
            passed[current.node.x][current.node.y][current.orient] = True
            current.node.lookup_around() # Expand.
            if current.node.up is not None and passed[current.node.x][current.node.y - 1]['nord'] is False:
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
            if current.node.down is not None and passed[current.node.x][current.node.y + 1]['sud'] is False:
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
            if current.node.right is not None and passed[current.node.x + 1][current.node.y]['est'] is False:
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
            if current.node.left is not None and passed[current.node.x - 1][current.node.y]['ouest'] is False:
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
            # If heapq is empty, return -1 (no way found).
            try:
                current = heappop(heap)
            except Exception:
                return -1
        rstring = str(current.cost) + ' '
        for move in current.move:
            rstring += str(move) + ' '
        return rstring

def resolve_maze(file, output=None):
    """Resolve the given maze file."""
    mr = MazeReader()
    for i in mr.read_maze(file):
        i.print_maze()
        robot = Robot(i)
        if output is not None:
            fh = open(output, 'a')
            fh.write(robot.dijkstra())
            fh.close()
        else:
            print(robot.dijkstra())
