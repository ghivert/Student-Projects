package the.incredible.maze

import scala.collection.mutable.Map
import scala.collection.mutable.ArrayBuffer
import scala.util.Random

class Maze {
  abstract class CardinalDirection
  case class North() extends CardinalDirection
  case class South() extends CardinalDirection
  case class East()  extends CardinalDirection
  case class West()  extends CardinalDirection

  class Cell (val x: Int, val y: Int) {
    // North, East, South, West.
    private val walls = Map("North" -> true,
      "East" -> true, "South" -> true, "West" -> true)
    private var visited = false

    def removeWall(card: CardinalDirection): Unit = {
      card match {
        case North() => walls("North") = false
        case South() => walls("South") = false
        case East()  => walls("East")  = false
        case West()  => walls("West")  = false
        case _     => throw new Exception
      }
    }

    def hasWall(card: CardinalDirection): Boolean = {
      card match {
        case North() => if (walls("North") == true) true else false
        case South() => if (walls("South") == true) true else false
        case East()  => if (walls("East")  == true) true else false
        case West()  => if (walls("West")  == true) true else false
        case _     => throw new Exception
      }
    }

    def hasBeenVisited(): Boolean = {
      visited
    }

    def visit(): Unit = { visited = true }
  }

  private val maze = Array ofDim[Cell](100, 100)
  for (i <- 0 to maze.length) {
    for (j <- 0 to maze(0).length) {
      maze(i)(j) = new Cell(i, j)
    }
  }

  private val stack = new ArrayBuffer()

  /* Take a cell, explode a wall, and return its neighbour. */
  def explodeWall(cell: Cell): Cell = {
    val generator = new Random(System.currentTimeMillis)
    var x = 0
    var y = 0

    // Random neighbour cell.
    generator nextInt(4) match {
      case 0 => x = cell.x
                y = cell.y - 1
      case 1 => x = cell.x + 1
                y = cell.y
      case 2 => x = cell.x
                y = cell.y + 1
      case 3 => x = cell.x - 1
                y = cell.y
    }

    var dir: CardinalDirection = North()
    (x, y) match {
      case (cell.x + 1, cell.y) => dir = East()
      case (cell.x, cell.y + 1) => dir = South()
      case (cell.x - 1, cell.y) => dir = West()
    }

    // Verify bounds.
    if (x < 0) x = 0
    if (x > maze.length - 1) x = maze.length - 1
    if (y < 0) y = 0
    if (y > maze(0).length - 1) y = maze.length -1

    val neighbour = maze(x)(y)
    cell removeWall dir
    neighbour visit()
    neighbour
  }
}
