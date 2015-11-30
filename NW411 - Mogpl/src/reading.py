class Maze(object):
    """Representent a Maze object. Contains an array representing the ground."""
    def __init__(self):
        self.maze = []

    def starting_point(self, point):
        """Define the starting point of robot."""
        self.start_x = point[0]
        self.start_y = point[1]

    def ending_point(self, point):
        """Define the ending point of robot."""
        self.end_x = point[0]
        self.end_y = point[1]

    def orientation(self, orient):
        """Define the orientation of robot."""
        self.orient = orient

    def print_maze(self):
        """Print the maze."""
        string = ''
        for j in self.maze[0]:
            string += '----'
        string += '-\n'
        for i in self.maze:
            string += '| '
            for j in i:
                if j == 0:
                    string += "  | "
                else:
                    string += "X | "
            string += '\n'
            for j in i:
                string += '----'
            string += '-\n'
        print(string)

class MazeReader(object):
    """Read a maze file and return an initialized Maze."""
    def read_maze(self, maze_file):
        """Read a maze file (.maze), and return a list of all mazes of the file."""
        mazes = []
        file = open(maze_file, 'r')
        while True:
            maze = Maze()
            size = list(map(lambda x: int(x), file.readline().split(' ')))
            if size[0] == 0 and size[1] == 0:
                break
            for i in range(size[0]):
                line = list(map(lambda x: int(x), file.readline().split(' ')))
                if len(line) != size[1]:
                    raise Exception
                maze.maze.append(line)
            directions = file.readline().split(' ')
            for i in range(4):
                directions[i] = int(directions[i])
            maze.starting_point(directions[0:2])
            maze.ending_point(directions[2:4])
            maze.orientation(directions[4])
            mazes.append(maze)
        file.close()
        return mazes

mr = MazeReader()
for i in mr.read_maze('../instances/small.maze'):
    i.print_maze()
    print('')
