/**
 * 
 */
package tests;

import static org.junit.Assert.*;
import java.util.LinkedList;
import generateWorld.GenerateWorld;
import org.junit.Test;
import agents.Bears;
import agents.SwarmBee;

/**
 * @author EmpereurWilhelm
 *
 */
public class BearsTest
{
	@Test
	public void movementTest()
	{
		int param = 100;
		GenerateWorld world = new GenerateWorld();		
		int x = (int) (Math.random() * param);
		int y = (int) (Math.random() * param);
		Bears bearTest = new Bears (x, y, null);
		bearTest.movement(world.altitude, null);
		assertTrue("Bears : Problem in movementTest.", (
				((bearTest.x == ((x - 1) % param)) && (bearTest.y == ((y - 1) % param))) ||
				((bearTest.x == ((x + 1) % param)) && (bearTest.y == ((y - 1) % param))) ||
				((bearTest.x == ((x + 1) % param)) && (bearTest.y == ((y + 1) % param))) ||
				((bearTest.x == ((x - 1) % param)) && (bearTest.y == ((y + 1) % param)))
				));
	}
	
	@Test
	public void findSalmonTest()
	{
		Bears bearTest = new Bears (50, 50, null);
		int[][] arrayTest = new int[52][52];
		arrayTest[50][50] = -1;
		LinkedList<SwarmBee> swarmTest = new LinkedList<SwarmBee>() ;
		swarmTest.add(new SwarmBee(51, 51, arrayTest.length, arrayTest[0].length, 10));
		
		bearTest.energyAndFoodVariation();
		boolean result = bearTest.findFood(arrayTest, swarmTest);
		assertTrue("Bears : Problem in findFood (Salmon).", (bearTest.getHunger() == 100) && 
				(bearTest.isHungry() == false) && (result == true));
	}
	
	@Test
	public void findHoneyTest()
	{
		Bears bearTest = new Bears (50, 50, null);
		int[][] arrayTest = new int[52][52];
		arrayTest[50][50] = 1;
		LinkedList<SwarmBee> swarmTest = new LinkedList<SwarmBee>() ;
		swarmTest.add(new SwarmBee(50, 50, arrayTest.length, arrayTest[0].length, 10));

		bearTest.energyAndFoodVariation();
		boolean result = bearTest.findFood(arrayTest, swarmTest);
		assertTrue(" Bears : Problem in findFood (honey).", (bearTest.getHunger() == 100) && 
				(bearTest.isHungry() == false) && (result == true));
	}

	@Test
	public void findFoodTest()
	{
		Bears bearTest = new Bears (50, 50, null);
		int[][] arrayTest = new int[52][52];
		arrayTest[50][50] = 1;
		LinkedList<SwarmBee> swarmTest = new LinkedList<SwarmBee>() ;
		swarmTest.add(new SwarmBee(51, 51, arrayTest.length, arrayTest[0].length, 10));

		bearTest.energyAndFoodVariation();
		boolean result = bearTest.findFood(arrayTest, swarmTest);
		assertFalse("Bears : Problem in findFood.", (bearTest.getHunger() != 100) && (result == false));

	}
}
