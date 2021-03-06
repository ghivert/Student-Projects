from reading import Maze, MazeReader

class Node(object):
    """Nodes for evolving in graph."""
    def __init__(self, maze, x, y, parent=None):
        """Initialize node. Keep maze, parent, and position."""
        self.maze = maze
        self.x = x
        self.y = y
        self.parent = parent
        self.up = None
        self.left = None
        self.down = None
        self.right = None

    def lookup_around(self):
        """Look if it's possible to go up, left, right and down. It it is,
        expand properly everything, and put it into self.up, self.left,
        self.right and self.down."""
        x = self.x
        y = self.y
        maze = self.maze.maze

        def around(x, y, maze):
            """Look around to see if cases are occupied."""
            fields = [False, False, False, False]

            # Particular cases.
            # Lefter line.
            if x == 0:
                fields[0] = None
                fields[2] = None
                if y == len(maze):
                    fields[3] = None
                    if maze[y - 1][x] == 0:
                        fields[1] = True
                elif y == 0:
                    fields[1] = None
                    if maze[y][x] == 0:
                        fields[3] = True
                else:
                    if maze[y][x] == 0:
                        fields[3] = True
                    if maze[y - 1][x] == 0:
                        fields[1] = True

            # Upper line.
            elif y == 0:
                fields[0] = None
                fields[1] = None
                if x == len(maze[0]):
                    fields[3] = None
                    if maze[y][x - 1] == 0:
                        fields[2] = True
                else:
                    if maze[y][x] == 0:
                        fields[3] = True
                    if maze[y][x - 1] == 0:
                        fields[2] = True

            # Downer line.
            elif y == len(maze):
                fields[2] = None
                fields[3] = None
                if x == len(maze[0]):
                    fields[1] = None
                    if maze[y - 1][x - 1] == 0:
                        fields[0] = True
                else:
                    if maze[y - 1][x - 1] == 0:
                        fields[0] = True
                    if maze[y - 1][x] == 0:
                        fields[1] = True

            # Righter line.
            elif x == len(maze[0]):
                fields[1] = None
                fields[3] = None
                if y == len(maze):
                    fields[2] = None
                    if maze[y - 1][x - 1] == 0:
                        fields[0] = True
                else:
                    if maze[y - 1][x - 1] == 0:
                        fields[0] = True
                    if maze[y][x - 1] == 0:
                        fields[2] = True

            # General cases.
            else:
                if maze[y - 1][x - 1] == 0:
                    fields[0] = True
                if maze[y - 1][x] == 0:
                    fields[1] = True
                if maze[y][x - 1] == 0:
                    fields[2] = True
                if maze[y][x] == 0:
                    fields[3] = True
            return fields

        def obstacle(cases):
            """Look if there's an obstacle near the point."""
            for case in cases:
                if case is None or case is False:
                    return True
            return False

        fields = around(x, y, maze)
        if fields[0] is True and fields[1] is True:
            if obstacle(around(x, y - 1, maze)) is False:
                self.up = Node(self.maze, x, y - 1, self)
        if fields[0] is True and fields[2] is True:
            if obstacle(around(x - 1, y, maze)) is False:
                self.left = Node(self.maze, x - 1, y, self)
        if fields[2] is True and fields[3] is True:
            if obstacle(around(x, y + 1, maze)) is False:
                self.down = Node(self.maze, x, y + 1, self)
        if fields[3] is True and fields[1] is True:
            if obstacle(around(x + 1, y, maze)) is False:
                self.right = Node(self.maze, x + 1, y, self)

    def spaces(self, number):
        """Affichage du noeud."""
        if self.up:
            up = "Haut !"
        else:
            up = 'None'
        if self.left:
            left = "Gauche !"
        else:
            left = 'None'
        if self.down:
            down = "Bas !"
        else:
            down = 'None'
        if self.right:
            right = "Droite !"
        else:
            right = 'None'
        rstring = number * ' ' + 'Noeud x: ' + str(self.x) + ' et y: ' + str(self.y) + '\n'
        rstring += number * ' ' + up + '\n' + number * ' ' + left + '\n'
        rstring += number * ' ' + down + '\n' + number * ' ' + right
        return rstring
    def __str__(self):
        return self.spaces(0)
