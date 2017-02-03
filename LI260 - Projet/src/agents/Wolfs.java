package agents;

import java.util.LinkedList;

import agents.Sheeps;

public class Wolfs extends Animals
{

	private boolean alpha;

	public Wolfs(int x, int y, boolean alpha, ListAnimals list)
	{
		super(x, y, list);
		this.alpha = alpha;
		this.speed = 1;
		this.energy = 450;
		this.hunger = 100;
		this.thirsty = 300;
	}

	public Animals searchPartners(int[][] array, LinkedList<Animals> animalsList)
	{
		return null;
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
		int min;
		if (!listPrey.isEmpty())
			min = calculateDistance(x, y, listPrey.get(0).x, listPrey.get(0).y);
		else 
			min =  20;
		int index = 0;
		for (Animals prey: listPrey){
			if (calculateDistance(x,y, prey.x, prey.y) < min){
				min = calculateDistance(x,y, prey.x, prey.y);
				index = listPrey.indexOf(prey);		
			}
		}
		if (index < listPrey.size()) {
			if (listPrey.get(index).x < x ){
				if (listPrey.get(index).y < y)
					if (tree[x][(y-2)%tree[0].length] > 0)
						orientation = 1;
					else
						orientation = 0;
				else
					if(tree[x][(y+2)%tree[0].length] > 0)
						orientation = 1;
					else
						orientation = 2;
			}
			else{
				if (listPrey.get(index).y < y){
					if(tree[x][(y+2)%tree[0].length] > 0)
						orientation = 1;
					else
						orientation = 2;
				}else{
					if(tree[x][(y+2)%tree[0].length] > 0)
						orientation = 3;
					else
						orientation = 2;
				}
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
	public void runAwayFromPredator(int [][] tree, LinkedList<Bears> listPredator){	
		for (Animals predator: listPredator){
			if (calculateDistance(x,y, predator.x, predator.y) <= 2){
				if (predator.x < x ){
					if (predator.y < y){

					}
					else{

					}

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

	public void changeOrientation(int[][] tree, LinkedList<Sheeps> listPrey, LinkedList<Bears> listPredator){
		if (Math.random() < probabilityOfChangeOrientation)
			orientation = (int) (Math.random() * 4);
		if(isHungry())
			changeOrientationHungry(tree, listPrey);
		runAwayFromPredator(tree, listPredator);
	}

	public boolean findFood(LinkedList<Sheeps> sheeps)
	{
		for (Sheeps temporary : sheeps)
		{
			if (((temporary.x == x) /* || (temporary.x == x + 1) || (temporary.x == x - 1) */)
					&& ((temporary.y == y) /* || (temporary.y == y + 1) || (temporary.y == y - 1) */))
			{
				this.hunger = 100;
				this.isHungry = false;
				sheeps.remove(temporary);
				return true;
			}
		}

		if (this.hunger < 50)
			this.isHungry = true;
		return false;

	}

	public void update(int[][] altitude, int [][] tree, LinkedList<Bears> listPredator, LinkedList<Sheeps> listPrey)
	{
		this.findFood(listPrey);
		this.findWater(altitude);
		this.movement(altitude, tree);
		this.changeOrientation(tree, listPrey, listPredator);
		this.runAwayFromPredator(tree, listPredator);
		this.energyAndFoodVariation();
	}

}
