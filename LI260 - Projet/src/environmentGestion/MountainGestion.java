package environmentGestion;

public class MountainGestion{
	private int x;
	private int y; 
	private int width;
	public int [][] mountain;

	public MountainGestion(int dx, int dy){

		this.width = (int) ((Math.random()*10) + 7);
		if (width % 2 == 0)
			width++;
		x = (int) (Math.random() * (dx -  width));
		y = (int) (Math.random() * (dy -  width));
		mountain = new int[width][width];
		int m = 0;
		int length = mountain.length;
		while(m < (mountain.length/2 - 1)){
			for (int i=m; i < length ; i++){
				for (int j=m; j < length; j++ ){ 
						mountain[i][j] = m + 1; 
				}
			}
			length--;
			m++;
		}
	}


	public static void visualiseMountain(int [][] mountain){
		for(int i=0;i<mountain.length;i++){
			for(int j=0;j<mountain[0].length; j++){
				System.out.print(mountain[i][j]+"  ");
			}
			System.out.println();
		}
	}

	public int getX(){
		return x;
	}

	public int getY(){
		return y; 
	}

}
