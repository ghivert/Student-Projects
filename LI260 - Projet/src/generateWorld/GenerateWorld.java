package generateWorld;

import java.awt.Graphics;
import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Image;
import java.io.File;
import java.util.ArrayList;

import javax.imageio.ImageIO;
import javax.swing.JFrame;
import javax.swing.JPanel;

import agents.Animals;
import agents.Bears;
import agents.ListAnimals;
import agents.Sheeps;
import agents.Wolfs;
import environmentGestion.SeaGestion;
import environmentGestion.ForestGestion;
import environmentGestion.MountainGestion;

/** Generation of world and main window. */
public class GenerateWorld extends JPanel
{
	public ListAnimals ListAnimals;
	public Animals animal;
	private static final long serialVersionUID = 1L;
	private JFrame frame;

	private Image seaSprites[][][][], bear[][], wolf[][], sheep[][], treeSprites[], mountainSprites[][][][], grassSprite, seaSpriteRock;
	private static int spriteHeight = 8, spriteWidth = 16;
	private static int decalTree = 25, decalAnimal = 8;
	/* spriteHeight, spriteWidth and decalTree are useful to paint world. Only used to know how to place sprites on map. */
	private static int abPoint = -5, ordPoint = -5; // Beginning of world (during paint).
	private static int dx = 90, dy = 190; // Size of world.
	private static int numberOfMountain ;
	public ArrayList<MountainGestion> mountainList;
	private static double percentageOfTree = 0.0005, percentageOfTreeSecond = 0.28; // Percentage of trees on map.
	private static double percentageOfWater = 0.0014, percentageOfWaterSecond = 0.34; // Percentage of sea on map.
	//  private static int pondMinimalSize = 500, pondMaximalSize = 5000; // Minimal size for ponds.
	public boolean [][] trace; 
	public int[][] trees, altitude, snow;
	
	/*
	 * Array for place of trees, of sea and earth. Array which gives the level of
	 * snow on one square.
	 */

	/**
	 * Initiate the world, creates an entire World of size [dx][dy] and fill it with trees and sea.
	 * 
	 * Creates a window and displays it to screen.
	 */
	public GenerateWorld()
	{
		this.trees = new int[dx][dy];
		this.altitude = new int[dx][dy];
		this.snow = new int[dx][dy];
		this.trace = new boolean[dx][dy];

		this.bear = new Image[4][3];
		this.wolf = new Image[4][3];
		this.sheep = new Image[4][3];
		this.treeSprites = new Image[13];
		this.seaSprites = new Image[2][2][2][2];
		this.mountainSprites = new Image[2][2][2][2];


		/* Getting sprites */
		this.GetSpritesLand();
		this.GetSpritesBear();
		this.GetSpritesWolfes();
		this.GetSpritesSheeps();
		this.GetsSpritesTrees();
		this.GetSpritesMountain();

		/* Initialisation of the world */
		numberOfMountain = (int) (Math.random() * 5 + 1);
		this.landGenerating();
		SeaGestion.landGenerating(altitude, percentageOfWaterSecond);
		//SeaGestion.deleteSmallAndLargePond(altitude, pondMinimalSize, pondMaximalSize);
		ForestGestion.forestGenerating(altitude, trees, percentageOfTree, percentageOfTreeSecond);
		ListAnimals = new ListAnimals(altitude);

		this.frame = new JFrame("Life in Sprites");
		this.frame.add(this);
		this.frame.setSize(1400, 850);
		this.frame.setVisible(true);
		this.frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

	}

	/**
	 * Give a value to each spare of land. Determines if earth, water or mountain. -1 is water, 0 is earth, otherwise the value
	 * of the spare is the altitude of the earth.
	 * Half Generated mountain copied in altitude array.
	 * 
	 * */
	public void landGenerating()
	{
		for (int i = 0 ; i != altitude.length ; i++)
			for (int j = 0 ; j != altitude[0].length; j++)
				if (i == 0 || j == 0 || j == altitude[0].length -1 || i == altitude.length -1)
					altitude[i][j] = -1;
				else if (Math.random() > percentageOfWater)
					altitude[i][j] = -1;
				else
					altitude[i][j] = 0;

		/* Initialization of an random number of mountain and copy of the mountain in altitude array*/
		mountainList = new ArrayList<MountainGestion>();
		for (int i=0; i< numberOfMountain; i++)
			mountainList.add(new MountainGestion(dx, dy));

		for(int m=0; m< mountainList.size();m++) {
			for(int i = mountainList.get(m).getX(); i != mountainList.get(m).getX() + mountainList.get(m).mountain.length; i++ ){
				for(int j = mountainList.get(m).getY()   ; j != mountainList.get(m).getY() + mountainList.get(m).mountain[0].length;  j++ ){
					if(mountainList.get(m).mountain[i-mountainList.get(m).getX()][j - mountainList.get(m).getY()] > 0)
						altitude[(i + dx)%dx][(j+dy)%dy]= mountainList.get(m).mountain[i-mountainList.get(m).getX()][j -mountainList.get(m).getY()];
				}
			}	
		}
	}

	/** Gets all sprites necessary to paint bears. */
	public void GetSpritesSheeps()
	{
		try
		{
			sheep[0][0] = ImageIO.read(new File("pictures/sheeps/BackSheep_0.png"));
			sheep[0][1] = ImageIO.read(new File("pictures/sheeps/BackSheep_1.png"));
			sheep[0][2] = ImageIO.read(new File("pictures/sheeps/BackSheep_2.png"));
			sheep[3][0] = ImageIO.read(new File("pictures/sheeps/LeftSideSheep_0.png"));
			sheep[3][1] = ImageIO.read(new File("pictures/sheeps/LeftSideSheep_1.png"));
			sheep[3][2] = ImageIO.read(new File("pictures/sheeps/LeftSideSheep_2.png"));
			sheep[2][0] = ImageIO.read(new File("pictures/sheeps/FrontSheep_0.png"));
			sheep[2][1] = ImageIO.read(new File("pictures/sheeps/FrontSheep_1.png"));
			sheep[2][2] = ImageIO.read(new File("pictures/sheeps/FrontSheep_2.png"));
			sheep[1][0] = ImageIO.read(new File("pictures/sheeps/RigthSideSheep_0.png"));
			sheep[1][1] = ImageIO.read(new File("pictures/sheeps/RigthSideSheep_1.png"));
			sheep[1][2] = ImageIO.read(new File("pictures/sheeps/RigthSideSheep_2.png"));
		} catch (Exception e)
		{
			e.printStackTrace();
			System.exit(-1);
		}
	}

	public void GetSpritesBear()
	{
		try
		{
			bear[0][0] = ImageIO.read(new File("pictures/bear/backBear0_16.png"));
			bear[0][1] = ImageIO.read(new File("pictures/bear/BackBear1_16.png"));
			bear[0][2] = ImageIO.read(new File("pictures/bear/BackBear2_16.png"));
			bear[3][0] = ImageIO.read(new File("pictures/bear/FrontBearE0_16.png"));
			bear[3][1] = ImageIO.read(new File("pictures/bear/FrontBearE1_16.png"));
			bear[3][2] = ImageIO.read(new File("pictures/bear/FrontBearE2_16.png"));
			bear[2][0] = ImageIO.read(new File("pictures/bear/faceBear0_16.png"));
			bear[2][1] = ImageIO.read(new File("pictures/bear/faceBear1_16.png"));
			bear[2][2] = ImageIO.read(new File("pictures/bear/faceBear2_16.png"));
			bear[1][0] = ImageIO.read(new File("pictures/bear/frontBear0_16.png"));
			bear[1][1] = ImageIO.read(new File("pictures/bear/frontBear1_16.png"));
			bear[1][2] = ImageIO.read(new File("pictures/bear/frontBear2_16.png"));
		} catch (Exception e)
		{
			e.printStackTrace();
			System.exit(-1);
		}
	}

	/** Gets all sprites necessary to paint wolfes. */
	public void GetSpritesWolfes()
	{
		try
		{
			wolf[0][0] = ImageIO.read(new File("pictures/wolfes/backWolf1.png"));
			wolf[0][1] = ImageIO.read(new File("pictures/wolfes/backWolf2.png"));
			wolf[0][2] = ImageIO.read(new File("pictures/wolfes/backWolf3.png"));
			wolf[3][0] = ImageIO.read(new File("pictures/wolfes/eastWolf1.png"));
			wolf[3][1] = ImageIO.read(new File("pictures/wolfes/eastWolf2.png"));
			wolf[3][2] = ImageIO.read(new File("pictures/wolfes/eastWolf3.png"));
			wolf[2][0] = ImageIO.read(new File("pictures/wolfes/frontWolf1.png"));
			wolf[2][1] = ImageIO.read(new File("pictures/wolfes/frontWolf2.png"));
			wolf[2][2] = ImageIO.read(new File("pictures/wolfes/frontWolf2.png"));
			wolf[1][0] = ImageIO.read(new File("pictures/wolfes/westWolf1.png"));
			wolf[1][1] = ImageIO.read(new File("pictures/wolfes/westWolf2.png"));
			wolf[1][2] = ImageIO.read(new File("pictures/wolfes/westWolf3.png"));
		} catch (Exception e)
		{
			e.printStackTrace();
			System.exit(-1);
		}

	}

	/** Gets all sprites necessary to paint the world. */
	public void GetSpritesLand()
	{
		try
		{

			seaSpriteRock = ImageIO.read(new File("pictures/water/wideSeaRock.png"));

			seaSprites[0][0][0][0] = ImageIO.read(new File("pictures/water/wideSea.png"));
			seaSprites[1][0][0][0] = ImageIO.read(new File("pictures/water/seaSpriteN.png"));
			seaSprites[0][1][0][0] = ImageIO.read(new File("pictures/water/seaSpriteE.png"));
			seaSprites[1][1][0][0] = ImageIO.read(new File("pictures/water/seaSpriteNE.png"));
			seaSprites[0][0][1][0] = ImageIO.read(new File("pictures/water/seaSpriteS.png"));
			seaSprites[0][0][0][1] = ImageIO.read(new File("pictures/water/seaSpriteW.png"));
			seaSprites[1][0][0][1] = ImageIO.read(new File("pictures/water/seaSpriteNW.png"));
			seaSprites[0][1][1][0] = ImageIO.read(new File("pictures/water/seaSpriteSE.png"));
			seaSprites[0][0][1][1] = ImageIO.read(new File("pictures/water/seaSpriteSW.png"));
			seaSprites[1][1][0][1] = ImageIO.read(new File("pictures/water/seaSpriteNEW.png"));
			seaSprites[1][1][1][0] = ImageIO.read(new File("pictures/water/seaSpriteNES.png"));
			seaSprites[0][1][1][1] = ImageIO.read(new File("pictures/water/seaSpriteESW.png"));
			seaSprites[1][0][1][1] = ImageIO.read(new File("pictures/water/seaSpriteNSW.png"));
			seaSprites[1][1][1][1] = ImageIO.read(new File("pictures/water/wideSea.png"));

			grassSprite = ImageIO.read(new File("pictures/grass/grassSprite.png"));

		} catch (Exception e)
		{
			e.printStackTrace();
			System.exit(-1);
		}
	}

	/** Gets all sprites necessary to paint trees. */
	public void GetsSpritesTrees()
	{
		try
		{
			treeSprites[1] = ImageIO.read(new File("pictures/trees/treeSprite.png"));
			treeSprites[2] = ImageIO.read(new File("pictures/trees/pinSprite.png"));
			treeSprites[3] = ImageIO.read(new File("pictures/trees/treeInFire.png"));
			treeSprites[4] = ImageIO.read(new File("pictures/trees/treeInFire.png"));
			treeSprites[5] = ImageIO.read(new File("pictures/trees/treeInFire.png"));
			treeSprites[6] = ImageIO.read(new File("pictures/trees/ashTree.png"));
			treeSprites[7] = ImageIO.read(new File("pictures/trees/ashTree.png"));
			treeSprites[8] = ImageIO.read(new File("pictures/trees/ashTree.png"));
			treeSprites[9] = ImageIO.read(new File("pictures/trees/littleAshTree.png"));
			treeSprites[10] = ImageIO.read(new File("pictures/trees/littleAshTree.png"));
			treeSprites[11] = ImageIO.read(new File("pictures/trees/littleAshTree.png"));
			treeSprites[12] = ImageIO.read(new File("pictures/trees/littleAshTree.png"));
		} catch (Exception e)
		{
			e.printStackTrace();
			System.exit(-1);
		}
	}

	public void GetSpritesMountain()
	{
		try{

			// 0 = north  ;  1 = east  ;  2 = south   ;  3 = west  
			mountainSprites[0][0][0][0] = ImageIO.read(new File("pictures/mountain/grassSprite.png"));
			mountainSprites[1][0][0][0] = ImageIO.read(new File("pictures/mountain/mountainSpriteN.png"));
			mountainSprites[0][1][0][0] = ImageIO.read(new File("pictures/mountain/mountainSpriteE.png"));
			mountainSprites[1][1][0][0] = ImageIO.read(new File("pictures/mountain/mountainSpriteNE.png"));
			mountainSprites[0][0][1][0] = ImageIO.read(new File("pictures/mountain/mountainSpriteS.png"));
			mountainSprites[0][0][0][1] = ImageIO.read(new File("pictures/mountain/mountainSpriteW.png"));
			mountainSprites[1][0][0][1] = ImageIO.read(new File("pictures/mountain/mountainSpriteNW.png"));
			mountainSprites[0][1][1][0] = ImageIO.read(new File("pictures/mountain/mountainSpriteSE.png"));
			mountainSprites[0][0][1][1] = ImageIO.read(new File("pictures/mountain/mountainSpriteSW.png"));
			mountainSprites[1][1][1][1] = ImageIO.read(new File("pictures/mountain/wideMountain.png"));

		} catch (Exception e){
			e.printStackTrace();
			System.exit(-1);
		}
	}

	/** Paint animals. */
	public void animalsPaint(Graphics2D g2, Animals animal)
	{
	//	for(Animals animal in list ){
			if (animal instanceof Bears)
			{
				try
				{
					if(animal.y %2 == 0)
						g2.drawImage(this.bear[animal.orientation][animal.walk],
								abPoint + animal.x * spriteWidth,
								animal.y * spriteHeight/2 - decalAnimal + ordPoint,
								frame);
					else
						g2.drawImage(this.bear[animal.orientation][animal.walk],
								abPoint + animal.x * spriteWidth + spriteWidth/2,
								animal.y * spriteHeight/2 - decalAnimal + ordPoint,
								frame);
				} catch (NullPointerException e)
				{
				}
			}
			else if(animal instanceof Wolfs)
			{
				try
				{
					if(animal.y %2 == 0)
						g2.drawImage(this.wolf[animal.orientation][animal.walk],
								abPoint + animal.x * spriteWidth,
								animal.y * spriteHeight/2 + ordPoint,
								frame);
					else
						g2.drawImage(this.wolf[animal.orientation][animal.walk],
								abPoint + animal.x * spriteWidth + spriteWidth/2 ,
								animal.y * spriteHeight/2  - decalAnimal + ordPoint ,
								frame);
				} catch (NullPointerException e)
				{
				}
			}
			if (animal instanceof Sheeps)
			{
				try
				{
					if(animal.y %2 == 0)
						g2.drawImage(this.sheep[animal.orientation][animal.walk],
								animal.x * spriteWidth + abPoint,
								animal.y * spriteHeight/2 - decalAnimal + ordPoint,
								frame);
					else
						g2.drawImage(this.sheep[animal.orientation][animal.walk],
								animal.x * spriteWidth + spriteWidth/2 + abPoint,
								animal.y * spriteHeight/2 - decalAnimal + ordPoint,
								frame);
				} catch (NullPointerException e)
				{
				}
			}
	//	}
	}

	/** Paint water spares. */
	public void waterPaint(Graphics2D g2, int i, int j)
	{
		int east = 0, west = 0, north = 0, south = 0;

		if (altitude[i][j] < 0)
		{
			if(j%2 == 0){
				if (altitude[(i - 1 + dx) % dx][(j - 1 + dy) % dy] > -1) west = 1; 
				if (altitude[(i + dx) % dx ][(j + 1 + dy) % dy] > -1) east = 1; 
				if (altitude[(i - 1 + dx)%dx][(j + 1 + dy) % dy] > -1) south = 1;
				if (altitude[(i + dx % dx)][(j - 1 + dy) % dy] > -1) north = 1;

			}
			else{
				if (altitude[(i + dx) % dx][(j - 1 + dy) % dy] > -1) west = 1; 
				if (altitude[(i + 1 + dx) % dx ][(j + 1 + dy) % dy] > -1) east = 1; 
				if (altitude[i][(j + 1 + dy) % dy] > -1) south = 1;
				if (altitude[(i + 1 + dx) % dx][(j - 1 + dy) % dy] > -1) north = 1;  
			}
			if (altitude[i][j] < -1)
				if(j%2 == 0)
					g2.drawImage(seaSpriteRock,
							abPoint + i * spriteWidth,
							j * spriteHeight/2 + ordPoint,
							frame);
				else	
					g2.drawImage(seaSpriteRock,
							abPoint + i * spriteWidth + spriteWidth/2 ,
							j * spriteHeight/2 + ordPoint,
							frame);

			else
				if(j%2 == 0)
					g2.drawImage(seaSprites[north][east][south][west],
							abPoint + i * spriteWidth,
							j * spriteHeight/2 + ordPoint,
							frame);
				else
					g2.drawImage(seaSprites[north][east][south][west],
							abPoint + i * spriteWidth + spriteWidth/2,
							j * spriteHeight/2 + ordPoint,
							frame);
		}
	}

	/** Paint tree spares. */
	public void treesPaint(Graphics2D g2, int[][] trees, int i, int j)
	{

		if(j%2 == 0)
			g2.drawImage(treeSprites[(trees[i][j])],
					abPoint + i * spriteWidth,
					j * spriteHeight/2 - decalTree + ordPoint,
					frame);
		else
			g2.drawImage(treeSprites[(trees[i][j])],
					abPoint + i * spriteWidth + spriteWidth/2,
					j * spriteHeight/2 - decalTree + ordPoint,
					frame);
		// g2.drawImage(treeSprites[(trees[i][j])],
		// 	     abPoint + (j - i) * (spriteWidth / 2),
		// 	     ((i + j) * spriteHeight)/ 2 - decalTree + ordPoint,
		// 	     frame);


	}

	/** Paint Mountain spares. */
	public void mountainPaint(Graphics2D g2, ArrayList<MountainGestion> list)
	{	
		for (int m = 0; m < list.size(); m++){
			int dx = list.get(m).mountain.length;
			int dy = list.get(m).mountain[0].length;
			for(int i = 0 ; i != dx ; i++){
				for (int j = 0; j != dy; j++){
					int east = 0, west = 0, north = 0, south = 0;
					if ( (i + 1) < dx && list.get(m).mountain[(i + 1 + dx) % dx][j] > list.get(m).mountain[i][j] ) east = 1;
					if ( (i - 1) > 0 && list.get(m).mountain[(i - 1 + dx) % dx][j] > list.get(m).mountain[i][j] ) west = 1;
					if ( (j - 1) > 0 && list.get(m).mountain[i][j - 1] > list.get(m).mountain[i][j] ) north = 1;
					if ( (j + 1) < dy && list.get(m).mountain[i][j + 1] > list.get(m).mountain[i][j] ) south = 1;		
					g2.drawImage(mountainSprites[north][east][south][west],
							( abPoint + 60 + i - j + list.get(m).getX()) * spriteWidth/2 ,
							( i + j + list.get(m).getY()) * spriteHeight/2 - (list.get(m).mountain[i][j] + 1) * spriteHeight +ordPoint ,
							frame);
				}
			}
		}
	}

	/** Paint grass spares. */
	public void grassPaint(Graphics2D g2, int i, int j)
	{
		if(j%2 == 0)
			g2.drawImage(grassSprite,
					abPoint + i * spriteWidth,
					j * spriteHeight/2 + ordPoint,
					frame);
		else
			g2.drawImage(grassSprite,
					abPoint + i * spriteWidth + spriteWidth/2,
					j * spriteHeight/2 + ordPoint,
					frame);
		// g2.drawImage(grassSprite,
		// 	     abPoint + (j - i) * spriteWidth / 2,
		// 	     ((i + j) * spriteHeight) / 2 + ordPoint,
		// 	    frame);
	}

	/** Paint the whole world on screen. */
	public void paint(Graphics g)
	{
		Graphics2D g2 = (Graphics2D) g;

		g2.setColor(new Color(96,145,204));
		g2.fillRect(0, 0, getWidth(), getHeight());

		for (int i = 0 ; i < altitude.length ; i++)
			for (int j = 0 ; j < altitude[0].length ; j++)
			{
				grassPaint(g2, i, j);
				waterPaint(g2, i, j);  
			}
		mountainPaint(g2,this.mountainList);

		for(Animals animal : ListAnimals.bears)
			animalsPaint(g2, animal);
		for(int i=0; i < ListAnimals.wolfs.size(); i++)
			for(Animals animal : ListAnimals.wolfs.get(i))
				animalsPaint(g2,animal);
		for (Animals animal : ListAnimals.sheeps)
			animalsPaint(g2, animal);
		for (int i = 0 ; i < altitude.length ; i++)
			for (int j = 0 ; j < altitude[0].length ; j++){
				treesPaint(g2, trees, i, j);
			}
		
	//	for(Animals sheep : ListAnimals.sheeps)
			

	}
}
