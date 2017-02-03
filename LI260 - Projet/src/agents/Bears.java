package agents;

import java.util.LinkedList;

public class Bears extends Animals
{

	// 0 = N, 1 = E, 2 = S, 3 = W.
	public Bears(int x, int y, ListAnimals list)
	{
		super(x, y, list);
		this.speed = 1;
		this.energy = 450;
		this.hunger = 100;
	}


	/**
	 * 
	 * Gives direction to Animal if this one is hungry. Look around all prey which one is the nearest.
	 * 
	 * @param treeArray
	 * @param listAnimal
	 */

	public void changeOrientationHungry(int[][] tree, LinkedList<Sheeps> listPrey)
	{

		for (Animals prey: listPrey){
			if (calculateDistance(x,y, prey.x, prey.y) <= 1){
				if (prey.x == x){
					if (prey.y < y){
						orientation = 1;
					}
					else{
						orientation = 3;
					}
				}
				else{
					if (prey.y < y){
						orientation = 0;
					}
					else{
						orientation = 1;
					}
				}
				return;
			}
		}


	}



	/**
	 * 
	 * if a predator is near, go in the opposite direction.
	 * 
	 * @param arrayTree
	 *             
	 * @param listPredator
	 */
	public void runAwayFromPredator(int [][] arrayTree, LinkedList<Wolfs> listPredator){	
		for (Animals predator: listPredator){
			if (calculateDistance(x,y, predator.x, predator.y) <= 2){
				//System.out.println(" I have to run away from wolf !");
				if (predator.x < x ){
					if (predator.y < y)

						orientation = 0;
					else
						orientation = 1;
				}
				else{
					if (predator.y < y){
						if (Math.random()< 0.5)
							orientation = 2;
						else 
							orientation = 1;

					}else{
						if (Math.random()< 0.5)
							orientation = 2;
						else 
							orientation = 3;

					}
				}
				return;
			}
		}
	} 

	/**
	 * changeOrientation
	 * 
	 * @param array
	 * @param listPrey
	 * @param listPredator
	 */
	
	public void changeOrientation(int[][] array, LinkedList<Sheeps> listPrey, LinkedList<Wolfs> listPredator){
		if(Math.random() < probabilityOfChangeOrientation)
			orientation = (int) (Math.random() * 4);
		if(isHungry())
			changeOrientationHungry(array, listPrey);
		runAwayFromPredator(array, listPredator);	
		this.energyAndFoodVariation();
	}



	@Override
	public Animals searchPartners(int[][] array, LinkedList<Animals> animalsList)
	{
		return null;
	}

	/**
	 * Update movement and orientation of bear 
	 * 
	 * @param altitude
	 * @param tree
	 * @param listPrey
	 * @param listPredator
	 */

	public void update(int [][] altitude, int[][] tree, LinkedList<Sheeps> listPrey, LinkedList<Wolfs> listPredator, LinkedList<SwarmBee> swarms)
	{
		this.findWater(altitude);
		this.findFood(tree, swarms);
		this.movement(altitude, tree);
		this.changeOrientationWater(tree, waterMemory);
		this.changeOrientation(tree, listPrey, listPredator);
		this.energyAndFoodVariation();
	}

	public boolean findFood(int[][] array, LinkedList<SwarmBee> swarms)
	{
		if (this.findWater(array))
		{
			this.hunger = 100;
			this.isHungry = false;
			return true;
		}
		for (SwarmBee temporary : swarms)
		{
			if (((temporary.x == x) || (temporary.x == x + 1) || (temporary.x == x - 1))
					&& ((temporary.y == y) || (temporary.y == y + 1) || (temporary.y == y - 1)))
			{
				this.hunger = 100;
				this.isHungry = false;
				return true;
			}
		}

		if (this.hunger < 50)
			this.isHungry = true;
		return false;

	}





}
