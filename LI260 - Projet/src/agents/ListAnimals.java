package agents;

import java.util.ArrayList;
import java.util.LinkedList;

public class ListAnimals
{
	public LinkedList<Bears> bears;
	public LinkedList<Sheeps> sheeps;

	public ArrayList<LinkedList<Wolfs>> wolfs;
	
	public LinkedList<SwarmBee> swarms;

	private static int numberAnimals = 10;
	private static int numberPack = 2;

	public ListAnimals(int [][] altitude)
	{
		bears = new LinkedList<Bears>();
		sheeps = new LinkedList<Sheeps>();
		wolfs = new ArrayList<LinkedList<Wolfs>>();
		swarms = new LinkedList<SwarmBee>();

		for (int i = 0 ; i < numberAnimals ; i++)
		{
			int x = (int) (Math.random() * altitude.length);
			int y = (int) (Math.random() * altitude[0].length );
			while(altitude[x][y] == -1){
				x = (int) (Math.random() * altitude.length);
				y = (int) (Math.random() * altitude[0].length );
			}
			this.bears.add(new Bears(x, y,this));
			x = 0; y = 0;
			while(altitude[x][y] == -1){
				x = (int) (Math.random() * altitude.length);
				y = (int) (Math.random() * altitude[0].length);
			}
			this.sheeps.add(new Sheeps(x, y, this));
		}

		for (int i = 0 ; i < numberPack; i++)
		{
			this.wolfs.add(new LinkedList<Wolfs>());
			
			int x_alpha=0;int y_alpha =0;
			while(altitude[x_alpha][y_alpha] == -1){
				x_alpha = (int) (Math.random() * altitude.length);
				y_alpha = (int) (Math.random() * altitude[0].length );
			}
			this.wolfs.get(i).add(new Wolfs(x_alpha, y_alpha,true, this));
		
			for(int j = 1 ; j < numberAnimals ; j++)
			{
				int x = x_alpha ; int y = y_alpha;
				while(altitude[x][y] == -1){
					x = (int) (Math.random() * 25 + x_alpha);
					y = (int) (Math.random() * 25 + y_alpha );
				}
				this.wolfs.get(i).add(new Wolfs(x, y,false, this));			
			}
		}
	}

	/**
	 * @return the bear
	 */
	public LinkedList<Bears> getBears()
	{
		return this.bears;
	}

	/**
	 * @param bears
	 *            the bears to set
	 */
	public void setBears(LinkedList<Bears> bears)
	{
		this.bears = bears;
	}

	/**
	 * @return the Sheeps
	 */
	public LinkedList<Sheeps> getSheep()
	{
		return this.sheeps;
	}

	/**
	 * @param beeeeeeeh
	 *            the beeeeeeeh to set
	 */
	public void setBeeeeeeeh(LinkedList<Sheeps> Sheeps)
	{
		this.sheeps = Sheeps;
	}

	/**
	 * @return the Wolfs
	 */
	public ArrayList<LinkedList<Wolfs>> getWolfs()
	{
		return this.wolfs;
	}

	/**
	 * @param Wolfs
	 *            the Wolfs to set
	 */
	public void setWolfs(ArrayList<LinkedList<Wolfs>> Wolfs)
	{
		this.wolfs = Wolfs;
	}
}
