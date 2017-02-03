package seasons;

import environmentGestion.ForestGestion;
import environmentGestion.SeaGestion;
import agents.ListAnimals;

public interface SeasonBases
{
    // Farah
    public void changeReproduction (ListAnimals listAnimals);
    public void changeMovement (ListAnimals listAnimals);

    // Guillaume
    // Done
    public void changeRatesTree (ForestGestion forest);
    // Done
    public void changeRatesWater (SeaGestion sea);
    
    public void update (SeaGestion sea, ForestGestion forest, ListAnimals listAnimals);
}
