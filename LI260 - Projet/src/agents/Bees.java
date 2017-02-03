package agents;

public class Bees implements BugsBases
{
	public int orientation;
	public int x, y;
	private boolean haveFood;

	public Bees(int x, int y)
	{
		this.orientation = (int) (Math.random() * 4);
		this.x = x;
		this.y = y;
	}

	/**
	 * Force the bee to come back to swarm.
	 * 
	 * @param x
	 *            Abscissa of swarm.
	 * @param y
	 *            Ordinate of swarm.
	 */
	private void backToSwarm(int x, int y)
	{

	}

	/**
	 * Update bee as it have to be.
	 * 
	 * Update position, watch if there's foodon place, and come back to swarm if answer is yes.
	 * 
	 * @param array
	 *            Array used to know where are flowers.
	 * @param traceToFood
	 *            Array used to indicate where bees often pass to gain time.
	 * @param x
	 *            Abscissa of swarm.
	 * @param y
	 *            Ordinate of swarm.
	 */
	public void update(int[][] array, int[][] traceToFood, int x, int y)
	{
		this.movement(array);
		this.findFood(array);
		if (this.haveFood) this.backToSwarm(x, y);
	}

	public void movement(int[][] array)
	{
		// TODO Bee movement.
	}

	public void changeOrientation(int[][] array)
	{
		// TODO Bee changing orientation.
	}

	/**
	 * If there's flower on tile, so bee find food and come back to swarm.
	 * 
	 * @param array
	 *            Represents the array which contains flower.
	 */
	public boolean findFood(int[][] array)
	{
		if (array[this.x][this.y] > 0)
		{
			array[this.x][this.y]--;
			this.haveFood = true;
			if (array[this.x][this.y] > 0)
				return true;
			else
				return false;
		}
		else
			return false;
	}

	public void update(int[][] array)
	{
		// TODO Bee update.

	}
}
