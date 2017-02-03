package agents;

import java.util.LinkedList;

public class SwarmBee implements BugsBases
{
	public int orientation;

	public int energy;
	public int hunger;
	public int x, y;
	public int numberBugs;
	private LinkedList<Bees> bees;

	int[][] traceToFood;

	/**
	 * 
	 * Construct swarm. Add some bees to swarm.
	 * 
	 * @param x
	 *            Abscissa of swarm.
	 * @param y
	 *            ordinate of swarm.
	 * @param dx
	 *            Width of world.
	 * @param dy
	 *            Height of world.
	 * @param numberBugs
	 *            Number of traveling bees into swarm.
	 */
	public SwarmBee(int x, int y, int dx, int dy, int numberBugs)
	{
		this.x = x;
		this.y = y;
		this.numberBugs = numberBugs;

		this.traceToFood = new int[dx][dy];
		bees = new LinkedList<Bees>();

		for (int i = 0 ; i < this.numberBugs ; i++)
		{
			Bees temporary = new Bees(x, y);
			bees.add(temporary);
		}
	}

	/**
	 * Movement of swarm.
	 * 
	 * @param array
	 *            Represents the world.
	 */
	public void movement(int[][] array)
	{

	}

	/**
	 * Change orientation of swarm.
	 * 
	 * @param array
	 *            Represents the world.
	 */
	public void changeOrientation(int[][] array)
	{

	}

	/**
	 * findFood send traveling bees to find some food for queen and swarm.
	 * 
	 * @param array
	 *            Is the land where bees have to search (here, altitude, to determine if there's, or not, flowers).
	 */
	public boolean findFood(int[][] array)
	{
		for (Bees beeInSwarm : bees)
		{
			beeInSwarm.update(array, traceToFood, this.x, this.y);
		}
		return false;
	}

	/**
	 * Do everything that swarm have to do.
	 * 
	 * @param array
	 *            Represents the world.
	 */
	// TODO Swarm : Complete the update methods.
	public void update(int[][] array)
	{
		// TODO Auto-generated method stub

	}
}
