package tests;

import static org.junit.Assert.*;
import org.junit.Test;
import agents.Bears;

public class AnimalsTest
{
	@Test
	public void energyAndFoodVariationTest()
	{
		Bears bearTest = new Bears (50, 50, null);
		int energy = bearTest.getEnergy();
		int hunger = bearTest.getHunger();
		int thirsty = bearTest.getThirsty();
		bearTest.energyAndFoodVariation();
		assertTrue("Animals : Problem in energyAndFoodVariation.", ((bearTest.getEnergy() == (energy - 1)) && 
				(bearTest.getHunger() == (hunger - 1)) && 
				(bearTest.getThirsty() == (thirsty - 1))));
	}
	
	@Test
	public void findWaterTest()
	{
		Bears bearTest = new Bears(50, 50, null);
		int[][] arrayTest = new int[100][100];
		int thirsty = bearTest.getThirsty();
		arrayTest[50][50] = -1;
		arrayTest[51][50] = 0;
		arrayTest[49][50] = 0;
		arrayTest[50][51] = 0;
		arrayTest[50][49] = 0;
		
		bearTest.energyAndFoodVariation();
		bearTest.findWater(arrayTest);
		assertTrue("Animals : Problem in findWaterTest.", (bearTest.getThirsty() == (thirsty - 1)));
		
		arrayTest[50][50] = 0;
		arrayTest[51][50] = -1;
		arrayTest[49][50] = 0;
		arrayTest[50][51] = 0;
		arrayTest[50][49] = 0;
		bearTest.energyAndFoodVariation();
		bearTest.findWater(arrayTest);
		assertTrue("Not Perfect.", (bearTest.getThirsty() == thirsty));

		arrayTest[50][50] = 0;
		arrayTest[51][50] = 0;
		arrayTest[49][50] = -1;
		arrayTest[50][51] = 0;
		arrayTest[50][49] = 0;
		bearTest.energyAndFoodVariation();
		bearTest.findWater(arrayTest);
		assertTrue("Not Perfect.", (bearTest.getThirsty() == thirsty));

		arrayTest[50][50] = 0;
		arrayTest[51][50] = 0;
		arrayTest[49][50] = 0;
		arrayTest[50][51] = -1;
		arrayTest[50][49] = 0;
		bearTest.energyAndFoodVariation();
		bearTest.findWater(arrayTest);
		assertTrue("Not Perfect.", (bearTest.getThirsty() == thirsty));

		arrayTest[50][50] = 0;
		arrayTest[51][50] = 0;
		arrayTest[49][50] = 0;
		arrayTest[50][51] = 0;
		arrayTest[50][49] = -1;
		bearTest.energyAndFoodVariation();
		bearTest.findWater(arrayTest);
		assertTrue("Not Perfect.", (bearTest.getThirsty() == thirsty));
		
		arrayTest[50][50] = 0;
		arrayTest[51][50] = 0;
		arrayTest[49][50] = 0;
		arrayTest[50][51] = 0;
		arrayTest[50][49] = 0;
		bearTest.energyAndFoodVariation();
		bearTest.findWater(arrayTest);
		assertFalse("Not Perfect.", (bearTest.getThirsty() == thirsty));
	}

}
