package generateWorld;

import environmentGestion.ForestGestion;
import agents.Bears;
import agents.Sheeps;
import agents.Wolfs;

public class Main
{
	private static int delay = 200; 
		
	//private static int levelMax = 5;

	public static void main(String[] args)
	{

		GenerateWorld World = new GenerateWorld();
		ForestGestion forestGestion = new ForestGestion (0.0001, 0.001,50);
		while (true)
		{
			try
			{
				
				Thread.sleep(delay);
			} catch (InterruptedException e)
			{
				System.out.print("Error.");
				System.exit(-1);
			}
			
			for (Bears bear : World.ListAnimals.bears){
				bear.update( World.altitude, World.trees, World.ListAnimals.sheeps, World.ListAnimals.wolfs.get(0), World.ListAnimals.swarms);
				}
			for(int i=0; i< World.ListAnimals.wolfs.size(); i++)
				for(Wolfs wolf : World.ListAnimals.wolfs.get(i)){
					wolf.update(World.altitude, World.trees, World.ListAnimals.bears, World.ListAnimals.sheeps);
				}
			for (Sheeps sheep : World.ListAnimals.sheeps){
				sheep.update( World.altitude, World.trees, World.trace, World.ListAnimals.wolfs.get(0));
				}
					
			forestGestion.forestFire(World.trees.length, World.trees[0].length, World.trees, World.altitude);
			World.repaint();
		}
	}

}
