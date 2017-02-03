package agents;

import java.util.LinkedList;

public abstract class Animals implements AnimalsBases {
	// 0 = N, 1 = E, 2 = S, 3 = W.
	public int orientation;
	public int walk;
	public int[][] waterMemory;
	protected int energy = 500, hunger = 100, thirsty = 100;
	protected int speed = 1;
	protected ListAnimals listAnimals;
	public double probabilityOfChangeOrientation = 0.2;
	public int x, y;
	public boolean alive = true;
	protected boolean isHungry = false, isThirsty = false;

	// private static double probabilyOrientChange = 0.2;

	/**
	 * 
	 * Construct Animals.
	 * 
	 * @param x
	 *            Abscissa of Animals.
	 * @param y
	 *            Ordinate of Animals.
	 */
	public Animals(int x, int y, ListAnimals listAnimals) {
		this.x = x;
		this.y = y;
		this.orientation = (int) (Math.random() * 4);
		this.walk = (int) (Math.random() * 3);
		this.waterMemory = new int[4][2];
		waterMemory[0][0] = 45;
		waterMemory[0][1] = 0;
		waterMemory[1][0] = 0;
		waterMemory[1][1] = 85;
		waterMemory[2][0] = 90;
		waterMemory[2][0] = 85;
		waterMemory[3][0] = 45;
		waterMemory[3][1] = 169;
		this.listAnimals = listAnimals;
	}

	/**
	 * Move animal on earth. Randomize next orientation.
	 * 
	 * @param dx
	 *            : width of the earth
	 * @param dy
	 *            : height of the earth
	 * @param altitude
	 *            : array of height above sea level in earth
	 * @param trees
	 *            : array of trees in earth
	 * 
	 *            determine the movement of the animal depending on his
	 */
	public void movement(int altitude[][], int trees[][]) {
		int dx = altitude.length;
		int dy = altitude[0].length;
		if (this.orientation == 0) {
			if (altitude[(x + dx) % dx][(y - 2 * speed + dy) % dy] < 0) {
				speed = 0;
				orientation = (int) (Math.random() * 4);
			}
			this.y = (this.y - 2 * this.speed + dy) % dy;
		} else if (this.orientation == 1) {
			if (altitude[(x + speed + dx) % dx][(y + dy) % dy] < 0) {
				speed = 0;
				orientation = (int) (Math.random() * 4);
			}
			this.x = (this.x - this.speed + dx) % dx;
		} else if (this.orientation == 2) {
			if (altitude[(x) % dx][(y + 1 + speed + dy) % dy] < 0) {
				speed = 0;
				orientation = (int) (Math.random() * 4);
			}
			this.y = (this.y + 2 * this.speed + dy) % dy;
		} else if (this.orientation == 3) {
			if (altitude[(x - speed + dx) % dx][(y + dy) % dy] < 0) {
				speed = 0;
				orientation = (int) (Math.random() * 4);
			}
			this.x = (this.x + this.speed + dx) % dx;
		}

		walk = (walk + 1) % 3;
		if (speed == 0) {
			walk = 0;
		}
		if (isThirsty())
			changeOrientationWater(trees, waterMemory);

		/* go back to earlier value of speed */
		this.speed = 1;
	}

	/**
	 * Gives direction to Animal if this one is thirsty. Make sure that Animal
	 * can't go back on his way.
	 * 
	 * @param array
	 *            Represents the world.
	 */
	public void changeOrientationWater(int[][] tree, int[][] waterPosition) {
		int result = 0;
		int min = calculateDistance(this.x, this.y, this.waterMemory[0][0],
				waterMemory[0][1]);
		for (int i = 1; i < 4; i++) {
			if (calculateDistance(this.x, this.y, this.waterMemory[i][0],
					waterMemory[i][1]) < min) {
				result = i;
				min = calculateDistance(this.x, this.y, this.waterMemory[i][0],
						waterMemory[i][1]);
			}
		}
		if (waterMemory[result][0] < x) {
			if (waterMemory[result][1] < y)
				if (tree[x][(y - 2 + tree[0].length) % tree[0].length] > 0)
					orientation = 1;
				else
					orientation = 0;
			else if (tree[x][(y + 2 + tree[0].length) % tree[0].length] > 0)
				orientation = 1;
			else
				orientation = 2;
		} else {
			if (waterMemory[result][1] < y)
				if (tree[x][(y - 2 + tree[0].length) % tree[0].length] > 0)
					orientation = 3;
				else
					orientation = 0;
			else if (tree[x][(y + 2 + tree[0].length) % tree[0].length] > 0)
				orientation = 3;
			else
				orientation = 2;
		}
		return;
	}

	public int calculateDistance(int x, int y, int waterX, int waterY) {
		return (int) Math.sqrt(Math.pow(x - waterX, 2)
				+ Math.pow(y - waterY, 2));
	}

	public Animals searchPartners(int[][] array, LinkedList<Animals> animalsList) {

		return null;
	}

	/**
	 * Indicates if animal is near water tile. If it is, he drinks and thirsty
	 * gauge up.
	 * 
	 * @param array
	 *            Represents the world.
	 * 
	 * @return Boolean indicates if water has been found.
	 * */
	public boolean findWater(int[][] array) {
		if ((array[(this.x + 1 + array.length) % array.length][this.y] < 0)
				|| (array[(this.x - 1 + array.length) % array.length][this.y] < 0)
				|| (array[this.x][(this.y + 2 + array[0].length)
						% array[0].length] < 0)
				|| (array[this.x][(this.y - 2 + array[0].length)
						% array[0].length] < 0)) {
			this.thirsty = 300;
			this.waterMemory[0][0] = this.x;
			this.waterMemory[0][1] = this.y;
			this.isThirsty = false;
			return true;
		}

		if (this.thirsty < 50)
			this.isThirsty = true;
		return false;
	}

	/**
	 * 
	 * Modify the energy of animals. Decrease energy, thirsty, and hunger from
	 * 1. If energy or hunger are equal to zero, animal die.
	 * 
	 * */
	public void energyAndFoodVariation() {
		this.energy--;
		this.thirsty--;
		this.hunger--;
		if ((this.energy < 1) || (this.hunger < 1))
			this.alive = false;
	}

	/* Getters and setters for class. */
	public int getHunger() {
		return this.hunger;
	}

	public int getThirsty() {
		return this.thirsty;
	}

	public int getEnergy() {
		return energy;
	}

	public boolean isThirsty() {
		return this.isThirsty;
	}

	public boolean isHungry() {
		return this.isHungry;
	}

}
