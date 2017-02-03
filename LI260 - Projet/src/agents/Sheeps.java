package agents;

import java.util.LinkedList;

public class Sheeps extends Animals
{
	// 0 = N, 1 = E, 2 = S, 3 = W.
	public Sheeps(int x, int y, ListAnimals list)
	{
		super(x, y, list);
		this.hunger = 100;
		this.energy = 450;
		this.thirsty = 300;
		this.speed = 1;
	}

	
	/**
	 * 
	 * Gives direction to Animal if this one is hungry. Look around all which one is the nearest.
	 * 
	 * @param treeArray
	 * @param listAnimal
	 */
	public void changeOrientationHungry(int[][] tree, boolean[][] trace)
	{
		int dx = trace.length;
		int dy = trace[0].length;
		/* Search the nearest grass in Moore x 2 neiborhood */
		for (int i = (this.x - 2 + dx)%dx; i < (this.x + 2 + dx)% dx; i++){
			for(int j = (this.y - 2 + dy)%dy; j < (this.y + 2 + dy)%dy; j++){
				if (trace[i][j]){
					if(i < x){
						if (j < y){
							if (Math.random() < 0.5)
								orientation = 0;
							else 
								orientation = 1;
						}
						else if (j == y){
							orientation = 1;
						}
						else {
							if (Math.random() < 0.5)
								orientation = 2;
							else 
								orientation = 1;
						}
					}
					else if (i == x){
						if (j < y){
							orientation = 0;
						}
						else if (j == y){
							this.findFood(trace);
						}
						else {
							orientation = 2;
						}
					}
					else{
						if (j < y){
							if (Math.random() < 0.5)
								orientation = 0;
							else 
								orientation = 3;
						}
						else if (j == y){
							orientation = 3;
						}
						else {
							if (Math.random() < 0.5)
								orientation = 2;
							else 
								orientation = 3;
						}
					}
						
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
	 * 
	 * @param tree
	 * @param listPrey
	 * @param listPredator
	 */
	public void changeOrientation(int[][] tree, boolean [][] trace, LinkedList<Wolfs> listPredator){
		if(Math.random() < probabilityOfChangeOrientation)
			orientation = (int) (Math.random() * 4);
		if(isHungry())
			changeOrientationHungry(tree, trace);
		runAwayFromPredator(tree, listPredator);	
	}

	
	public void update(int [][] altitude, int[][] tree, boolean[][] trace, LinkedList<Wolfs> listPredator)
	{
		movement(altitude, tree);
		changeOrientationWater(tree, waterMemory);
		changeOrientation(tree, trace, listPredator);
		this.findWater(altitude);
		this.energyAndFoodVariation();
	}
	
	
	@Override
	public Animals searchPartners(int[][] array, LinkedList<Animals> animalsList)
	{
		// TODO Auto-generated method stub
		return null;
	}
	
	

	public void findFood (boolean[][] array)
	{
		if (array[this.x][this.y] == true)
		{
			array[this.x][this.y] = false;
			this.hunger = 100;
			this.isHungry = false;
		}
	}


}
