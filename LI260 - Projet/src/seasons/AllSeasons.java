package seasons;

import agents.ListAnimals;
import environmentGestion.ForestGestion;
import environmentGestion.SeaGestion;

public class AllSeasons
{
    Season seasons[];
    int actualSeason = 0;

    SeaGestion sea;
    ForestGestion forest;
    ListAnimals listAnimals;

    public AllSeasons(SeaGestion sea, ForestGestion forest, ListAnimals listAnimals) 
    {
	seasons = new Season[4];
	seasons[0] = new Winter(0.012, 0.012, 0.012, 0.12, 23);
	seasons[1] = new Spring(0.012, 0.012, 0.012, 0.12, 23);
	seasons[2] = new Summer(0.012, 0.012, 0.012, 0.12, 23);
	seasons[3] = new Autumn(0.012, 0.012, 0.012, 0.12, 23);
    }

    public void changeSeason()
    {
	actualSeason = (actualSeason + 1) % 4;
    }

    public void effectSeason()
    {
	seasons[actualSeason].update(this.sea, this.forest, this.listAnimals);
    }
}
