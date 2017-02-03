package tests;

import static org.junit.Assert.*;
import org.junit.Test;
import seasons.Winter;
import seasons.Season;
import environmentGestion.*;

public class SeasonTest
{
	@Test
	public void changeRatesTreeTest()
	{
		Season season = new Winter(0.012, 0.013, 0.14, 0.15, 23);
		ForestGestion forest = new ForestGestion(1, 1, 1);
		
		season.changeRatesTree(forest);
		assertTrue("Seasons : Problem in changeRatesTree.", (forest.getBirthRate() == 0.15) && (forest.getFireRate() == 0.14) && (forest.getNumberReproduce() == 23));
	}
	
	@Test
	public void changesRatesWaterTest()
	{
		Season season = new Winter(0.12, 0.13, 0.14, 0.15, 23);
		SeaGestion sea = new SeaGestion(1, 1, 1);
		
		season.changeRatesWater(sea);
		assertTrue("Seasons : Problem in changeRatesWater.", (sea.getSeaExtensionRate() == 0.12) && (sea.getSeaEvaporationRate() == 0.13));
	}
}
