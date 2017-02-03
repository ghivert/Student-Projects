package agents;

import java.util.LinkedList;

public interface AnimalsBases
{
    // Guillaume
	// Done
    public void energyAndFoodVariation();
    
    // Farah
    //Done
    public void movement(int[][] altitude, int [][] tree);
    public void changeOrientationWater(int[][] array, int [][] waterPosition);
    
    // Guillaume
    // Done
    public boolean findWater(int[][] altitude);
    
    // Farah
    public Animals searchPartners(int[][] array, LinkedList<Animals> animalsList);
    
 
}
