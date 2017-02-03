package tests;

import static org.junit.Assert.*;
import org.junit.Test;
import agents.Wolfs;
import agents.Sheeps;
import java.util.LinkedList;

public class WolfsTest
{
	@Test
	public void findFoodTest()
	{
		Wolfs wolfTest = new Wolfs(25, 25, null);
		int hunger = wolfTest.getHunger();
		LinkedList<Sheeps> sheeps = new LinkedList<Sheeps>();
		sheeps.add(new Sheeps(25, 25, null));
		sheeps.add(new Sheeps(30, 30, null));

		wolfTest.energyAndFoodVariation();
		wolfTest.findFood(sheeps);
		assertTrue("Wolfs : Problem in findFood (eat sheep).", (wolfTest.getHunger() == hunger));
		
		wolfTest.energyAndFoodVariation();
		wolfTest.findFood(sheeps);
		assertFalse("Wolfs : Problem in findFood (don't eat sheep).", (wolfTest.getHunger() == hunger));
	}

}
