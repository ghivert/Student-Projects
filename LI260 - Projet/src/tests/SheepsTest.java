package tests;

import static org.junit.Assert.*;
import org.junit.Test;
import agents.Sheeps;

public class SheepsTest
{
	@Test
	public void findFoodTest()
	{
		Sheeps sheepTest = new Sheeps(30, 30, null);
		int hunger = sheepTest.getHunger();
		boolean[][] arrayTest = new boolean[50][50];
		arrayTest[30][30] = true;
		
		sheepTest.energyAndFoodVariation();
		sheepTest.findFood(arrayTest);
		assertTrue("Sheeps : Problem in findFood (get grass).", (sheepTest.getHunger() == hunger));
		
		sheepTest.energyAndFoodVariation();
		sheepTest.findFood(arrayTest);
		assertFalse("Sheeps : Problem in findFood (don't get grass).", (sheepTest.getHunger() == hunger));
	}
}
