package environmentGestion;

public class ForestGestion
{

	private double birthRate;
	private double fireRate;
	private int numberReproduce;

	/** 
	 * @param birthRate
	 *            Set the rate of generations of trees.
	 * @param fireRate
	 *            Set the rate of burning trees.
	 */
	public ForestGestion(double birthRate, double fireRate, int numberReproduce)
	{
		this.birthRate = birthRate;
		this.fireRate = fireRate;
		this.numberReproduce = numberReproduce;
	}

	/**
	 * @param birthRate
	 *            Set the rate of generations of trees.
	 */
	public void setBirthRate(double birthRate)
	{
		this.birthRate = birthRate;
	}

	/**
	 * @param fireRate
	 *            Set the rate of burning trees.
	 */
	public void setFireRate(double fireRate)
	{
		this.fireRate = fireRate;
	}

	/**
	 * @param numberReproduce
	 *            Gives the number of trees generated each second.
	 */
	public void setNumberReproduce(int numberReproduce)
	{
		this.numberReproduce = numberReproduce;
	}

	public void treesGenerating(int[][] trees, int[][] altitude)
	{
		for (int i = 0 ; i < numberReproduce ; i++)
		{
			if (Math.random() < birthRate)
			{
				int ab = (int) (Math.random() * altitude.length);
				int ord = (int) (Math.random() * altitude[0].length);
				if (altitude[ab][ord] > -1) trees[ab][ord] = 1;
			}
		}
	}

	/**
	 * Generates some forest. Half hazard generation, which creates some forest, and adds some trees elsewhere.
	 * 
	 * @param dx
	 *            Is height of array.
	 * @param dy
	 *            Is width of array.
	 * */
	public static void forestGenerating(int[][] altitude, int[][] trees, double percentageOfTree, double percentageOfTreeSecond)
	{
		for (int i = 0 ; i != altitude.length ; i++)
			for (int j = 0 ; j != altitude[0].length ; j++)
			{
				if ((altitude[i][j] >= 0) && (Math.random() < percentageOfTree)){
					if (altitude[i][j] == 0)
						trees[i][j] = 1;
				}
				else
					trees[i][j] = 0;
			}

		for (int i = 0 ; i != altitude.length ; i++)
			for (int j = 0 ; j != altitude[0].length ; j++)
				if (altitude[i][j] >= 0)
				    for (int w = -1 ; w < 2 ; w++)
					    for (int z = -1 ; z < 2 ; z++)
					    {
						    if (w == 0 && z == 0)
						        continue;
						    if ((trees[(i + w + altitude.length) % altitude.length][(j + z + altitude[0].length) % altitude[0].length] > 0) &&
						            (Math.random() < percentageOfTreeSecond)) trees[i][j] = 1;
					    }

		for (int i = 0 ; i != altitude.length ; i++)
			for (int j = 0 ; j != altitude[0].length ; j++)
				if (Math.random() < 0.1)
				    if (altitude[i][j] >= 0)
				        trees[i][j] = 1;
	}
	
	public void forestFire(int dx, int dy, int[][] trees, int[][] altitude)
	{
		int[][] temporary = new int[dx][dy];
		int delai = 10;// 100;
		boolean burn;

		// update array of trees with hazardous forest fire and trees generating
		for (int x = 0 ; x != trees.length ; x++)
			for (int y = 0 ; y != trees[0].length ; y++)
			{
				burn = false;
				//if a tree have in his neighborhood (Von Newmann's one) a burning tree he burns also
				if (trees[(x - 1 + dx) % dx][y] == 3 || trees[((x + 1) + dx) % dx][y] == 3
										|| trees[x][(y - 1 + dy) % dy] == 3 
										|| trees[x][(y + 1 + dy) % dy] == 3)
					burn = true;

				if ((trees[x][y] == 1 && burn) || (trees[x][y] == 2 && burn))
					temporary[x][y] = 3;
				 else
				{
					if (trees[x][y] == 1) // in case it doesn't burn 
					{
						// staying a tree
						temporary[x][y] = 1;
					} else
					{
						if (trees[x][y] == 2) 
						    temporary[x][y] = 2;
						if (trees[x][y] >= 3) temporary[x][y] = trees[x][y] + 1;
						if (trees[x][y] == 12) temporary[x][y] = 0;
					}
				}

				// Hazardous burning tree
				if ((trees[x][y] == 1 || trees[x][y] == 2) && (Math.random() < fireRate))
				{
					temporary[x][y] = 3;
				}
				// Generating Forest
				if (trees[x][y] == 0 && (Math.random() < birthRate) ) 
					if (altitude[x][y] == 0)
						temporary[x][y] = 1;
					if (altitude[x][y] > 0)
						temporary[x][y] = 2;
			}

		// update trees' array

		for (int x = 0 ; x != trees.length ; x++)
			for (int y = 0 ; y != trees[0].length ; y++)
				trees[x][y] = temporary[x][y];

		try
		{
			Thread.sleep(delai);
		} catch (InterruptedException e)
		{
		}

	}

}
