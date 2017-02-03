package agents;

public interface BugsBases
{
    public void movement(int[][] array);
    public void changeOrientation(int[][] array);
    public boolean findFood(int[][] array);
    public void update(int[][] array);
}
