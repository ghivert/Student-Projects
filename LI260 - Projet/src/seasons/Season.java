package seasons;

import agents.ListAnimals;
import environmentGestion.ForestGestion;
import environmentGestion.SeaGestion;

public abstract class Season implements SeasonBases
{

	protected double seaExtensionRate, seaEvaporationRate;
	protected double fireRate, birthRate;
	protected int numberReproduce;

	/**
	 * 
	 * Construct the season.
	 * 
	 * @param seaExtensionRate
	 *            Param of sea extension during season.
	 * @param seaEvaporationRate
	 *            Param of sea evaporation during season.
	 * @param fireRate
	 *            Param of forest fire during season.
	 * @param birthRate
	 *            Param of trees generation during season.
	 * @param numberReproduce
	 *            Param of number of trees which could spawn during season.
	 */
	public Season(double seaExtensionRate, double seaEvaporationRate,
	        double fireRate, double birthRate, int numberReproduce)
	{
		this.seaExtensionRate = seaExtensionRate;
		this.seaEvaporationRate = seaEvaporationRate;
		this.fireRate = fireRate;
		this.birthRate = birthRate;
		this.numberReproduce = numberReproduce;
	}

	@Override
	public void changeReproduction(ListAnimals listAnimals)
	{

	}

	@Override
	public void changeMovement(ListAnimals listAnimals)
	{

	}

	/**
	 * 
	 * Changes every rates of target ForestGestion object.
	 * 
	 * @param forest
	 *            Forest object which have rates to be changed.
	 */
	@Override
	public void changeRatesTree(ForestGestion forest)
	{
		forest.setNumberReproduce(this.numberReproduce);
		forest.setBirthRate(this.birthRate);
		forest.setFireRate(this.fireRate);
	}

	/**
	 * 
	 * Changes every rates of target SeaGestion object.
	 * 
	 * @param sea
	 *            Sea object which have rates to be changed.
	 */
	@Override
	public void changeRatesWater(SeaGestion sea)
	{
		sea.setSeaExtensionRate(this.seaExtensionRate);
		sea.setSeaEvaporationRate(this.seaEvaporationRate);
	}

	/**
	 * 
	 * Makes every changes which have to be.
	 * 
	 * @param sea
	 *            Sea object which have rates to be changed.
	 * @param forest
	 *            Forest object which have rates to be changed.
	 * @param listAnimals
	 */
	@Override
	public void update(SeaGestion sea, ForestGestion forest, ListAnimals listAnimals)
	{
		this.changeRatesTree(forest);
		this.changeRatesWater(sea);
	}
}
