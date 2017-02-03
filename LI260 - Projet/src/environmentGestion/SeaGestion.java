package environmentGestion;

public class SeaGestion
{

	private double seaExtensionRate;
	private double seaEvaporationRate;
	private int levelMax = 5;
	private int level = 0;
	private int baseCycle = 150;
	public int cycle = baseCycle;
	private boolean flood = true;

	public SeaGestion(double seaExtensionRate, double seaEvaporationRate, int levelMax)
	{
		this.seaExtensionRate = seaExtensionRate;
		this.seaEvaporationRate = seaEvaporationRate;
		this.levelMax = levelMax;
	}

	/**
	 * Extends or reduce water. Depends on cycle.
	 * 
	 * @param altitude
	 *            Array of altitude.
	 * @param trees
	 *            Array of trees.
	 */
	public void seaExtensionAndReduction(int[][] altitude, int[][] trees)
	{
		if ((this.level < levelMax) && flood)
		{
			int[][] altitudeCopy = new int[altitude.length][altitude[0].length];
			for (int i = 0 ; i < altitude.length ; i++)
				for (int j = 0 ; j < altitude[0].length ; j++)
				{
					if (altitude[i][j] < 0 || altitude[i][j] > 0)
						altitudeCopy[i][j] = altitude[i][j];
					else if (altitude[i][j] == 0)
					{
						int cpt = 0;
						if (altitude[(i - 1 + altitude.length) % altitude.length][j] < 0) cpt++;
						if (altitude[(i + 1 + altitude.length) % altitude.length][j] < 0) cpt++;
						if (altitude[i][(j + altitude[0].length - 1) % altitude[0].length] < 0) cpt++;
						if (altitude[i][(j + altitude[0].length + 1) % altitude[0].length] < 0) cpt++;

						if (cpt == 1 && (Math.random() < seaExtensionRate))
						{
							altitudeCopy[i][j] = -1;
							if (trees[i][j] > 0) trees[i][j] = 0;
						}
						if (cpt > 1)
						{
							altitudeCopy[i][j] = -1;
							if (trees[i][j] > 0) trees[i][j] = 0;
						}
					}
					else{
						altitudeCopy[i][j] =  altitude[i][j];
					}
				}
			this.level++;
			if (level == levelMax) flood = false;
			for (int i = 0 ; i < altitude.length ; i++)
				for (int j = 0 ; j < altitude[0].length ; j++)
					altitude[i][j] = altitudeCopy[i][j];
		}
		else if ((this.level > 0) && !flood)
		{
			int[][] altitudeCopy = new int[altitude.length][altitude[0].length];
			for (int i = 0 ; i < altitude.length ; i++)
				for (int j = 0 ; j < altitude[0].length ; j++)
				{
					if (altitude[i][j] >= 0)
						altitudeCopy[i][j] = altitude[i][j];
					else
					{
						int cpt = 0;
						if (altitude[(i - 1 + altitude.length) % altitude.length][j] < 0) cpt++;
						if (altitude[(i + 1 + altitude.length) % altitude.length][j] < 0) cpt++;
						if (altitude[i][(j + altitude[0].length - 1) % altitude[0].length] < 0) cpt++;
						if (altitude[i][(j + altitude[0].length + 1) % altitude[0].length] < 0) cpt++;

						if (cpt == 3 && (Math.random() < seaEvaporationRate))
							altitudeCopy[i][j] = 0;
						else if (cpt < 3)
							altitudeCopy[i][j] = 0;
						else
							altitudeCopy[i][j] = altitude[i][j];
					}
				}
			this.level--;
			if (level == 0) flood = true;
			for (int i = 0 ; i < altitude.length ; i++)
				for (int j = 0 ; j < altitude[0].length ; j++)
					altitude[i][j] = altitudeCopy[i][j];
		}
	}

	/**
	 * Function to hide cycle management.
	 * 
	 * @param altitude
	 *            Array of altitude.
	 * 
	 * @param trees
	 *            Array of trees.
	 * */
	public void seaVariation(int altitude[][], int trees[][])
	{
		if ((this.cycle > 0) && (this.cycle <= this.levelMax))
		{
			this.seaExtensionAndReduction(altitude, trees);
			this.cycle--;
		}
		else if (this.cycle > 0)
			this.cycle--;
		else
			this.cycle = baseCycle;
	}

	/**
	 * Function to force flooding or drying. flood and dry have to be different.
	 * 
	 * 
	 * @param flood
	 *            Boolean to set if water have to flood.
	 * @param dry
	 *            Boolean to set if water have to evaporate.
	 */
	public void floodLand(boolean flood, boolean dry)
	{
		if (flood != dry)
		{
			if (flood)
			{
				this.flood = true;
				this.level = 0;
				this.cycle = this.levelMax;
			}
			if (dry)
			{
				this.flood = false;
				this.level = 5;
				this.cycle = this.levelMax;
			}
		}
	}

	/**
	 * Function to delete every water to large or too small.
	 * 
	 * @param altitude
	 *            Array of altitude.
	 * @param pondMinimalSize
	 *            Size minimal of lakes.
	 * @param pondMaximalSize
	 *            Size maximal of lakes.
	 */
	public static void deleteSmallAndLargePond(int[][] altitude, int pondMinimalSize, int pondMaximalSize)
	{
		int[][] world = new int[altitude.length][altitude[0].length];

		for (int i = 0 ; i < altitude.length ; i++)
			for (int j = 0 ; j < altitude[0].length ; j++)
			{
				for (int w = 0 ; w < altitude.length ; w++)
					for (int x = 0 ; x < altitude[0].length ; x++)
						world[w][x] = 0;
				int counter = determinePondSize(altitude, world, i, j, 0, pondMaximalSize);
				if (counter < pondMinimalSize) altitude[i][j] = 0;
				if (counter > pondMaximalSize) altitude[i][j] = 0;
			}
	}

	/**
	 * Determine the size of a pond or a sea. Helps to find which pond have to be killed.
	 * 
	 * @param altitude
	 *            Array of altitude.
	 * @param world
	 *            Temporary array.
	 * @param X
	 *            is square where it is.
	 * @param Y
	 *            is square where it is.
	 * @param counter
	 *            Count how water square is crossed. Allow to faster stop recursion.
	 * @param pondMaximalSize
	 *            Allow to stop recursion faster.
	 * */
	public static int determinePondSize(int[][] altitude, int[][] world, int X, int Y, int counter, int pondMaximalSize)
	{
		if (counter < pondMaximalSize)
		{
			if (world[(X + altitude.length) % altitude.length][(Y + altitude[0].length) % altitude[0].length] != 127)
			{
				world[(X + altitude.length) % altitude.length][(Y + altitude[0].length) % altitude[0].length] = 127;
				if (altitude[(X + altitude.length) % altitude.length][(Y + altitude[0].length) % altitude[0].length] < 0)
				{
					counter++;
					return 1 +
					        determinePondSize(altitude, world, X + 1, Y, counter, pondMaximalSize) +
					        determinePondSize(altitude, world, X - 1, Y, counter, pondMaximalSize) +
					        determinePondSize(altitude, world, X, Y + 1, counter, pondMaximalSize) +
					        determinePondSize(altitude, world, X, Y - 1, counter, pondMaximalSize);
				}
			}
			else
				return 0;
		}
		return 1;
	}

	/**
	 * Generates some ocean. Generates some pond and sea without adding isolated water.
	 * 
	 * @param altitude
	 *            Array of altitude.
	 * @param percentageOfWater
	 *            Percentage of water apparition if there's water beside.
	 * */
	public static void landGenerating(int[][] altitude, double percentageOfWater)
	{
		for (int i = 0 ; i != altitude.length ; i++)
			for (int j = 0 ; j != altitude[0].length ; j++)
				for (int w = -1 ; w < 2 ; w++)
					for (int z = -1 ; z < 2 ; z++)
						if (altitude[(i + w + altitude.length) % altitude.length]
								[(j + z + altitude[0].length) % altitude[0].length] == 0)
						    if (Math.random() < percentageOfWater) altitude[i][j] = 0;

		for (int j = 0 ; j != altitude[0].length ; j++)
			for (int i = 0 ; i != altitude.length ; i++)
				for (int w = -1 ; w < 2 ; w++)
					for (int z = -1 ; z < 2 ; z++)
						if (altitude[(i + w + altitude.length) % altitude.length][(j + z + altitude[0].length)
						                                                          % altitude[0].length] == 0)
							if (Math.random() < percentageOfWater) altitude[i][j] = 0;

		for (int i = 0 ; i < altitude.length ; i++)
			for (int j = 0 ; j < altitude[0].length ; j++)
			{
				int cpt = 0;
				for (int w = -1 ; w < 2 ; w++)
					for (int z = -1 ; z < 2 ; z++)
					{
						if (w == 0 && z == 0)
						    continue;
						if (altitude[(i + w + altitude.length) % altitude.length][(j + z + altitude[0].length)
						        % altitude[0].length] == 0)
						    cpt++;
						if (cpt > 3)
						{
							if (Math.random() < 0.001)
								altitude[i][j] = 0;
							else
								altitude[i][j] = 0;
							break;
						}
					}
			}
		
//		for (int i = 0 ; i < altitude.length ; i++)
//			for (int j = 0 ; j < altitude[0].length ; j++)
//			{
//				if (j == 0 || j == altitude[0].length)
//					altitude[i][j] = -1;
//				else if (i == 0 || i == altitude.length)
//					altitude[i][j] = -1;
//			}
			
	}

	/**
	 * @param baseCycle
	 *            Allow to modify duration between two cycles of seaVariations.
	 */
	public void setBaseCycle(int baseCycle)
	{
		this.baseCycle = baseCycle;
	}

	/**
	 * @param seaExtensionRate the seaExtensionRate to set
	 */
	public void setSeaExtensionRate(double seaExtensionRate)
	{
		this.seaExtensionRate = seaExtensionRate;
	}

	/**
	 * @param seaEvaporationRate the seaEvaporationRate to set
	 */
	public void setSeaEvaporationRate(double seaEvaporationRate)
	{
		this.seaEvaporationRate = seaEvaporationRate;
	}

}
