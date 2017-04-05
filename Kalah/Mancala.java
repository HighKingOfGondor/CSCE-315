package sample;

import java.util.Random;

public class Mancala {

    //Init Board Members
    private boolean AI;
    private boolean random;
    private int initSeedCount; //Seeds in each pocket at to start game

    //Board facilities
    private House[][] houses = new House[2][7]; //houses[0][i] == top && houses[1][i] == bottom
    public Player player1;	//client player
    public Player player2;  //AI == true -> p2.player == false


    public Mancala(int seed, boolean AI) {
        initSeedCount = seed;
        this.AI = AI;
        player1 = new Player(false, 1);
        player2 = new Player(AI, 2);

        initBoard();
        print();
    }

    /*		Example board setup		*/
	/*
	 *		6	6	6	6	6	6
	 *	0							0
	 *		6	6	6	6	6	6
	*/
    public void initBoard() {
        if(random){ //init seed count irrelevant
            for (int i = 0; i < 6; i++) {
                Random rand = new Random();
                int n = rand.nextInt(3) + 0;
                houses[0][i]= new House(player1, n);
                houses[1][i]= new House(player2, n);
            }
        }else{ //Revisit for seedsLeft
            int seedsLeft = initSeedCount;
            for (int i = 0; i < houses[0].length; ++i)
                if (i == houses[0].length - 1) {
                    houses[0][i] = new House(player1, 0);
                    houses[1][i] = new House(player2, 0);
                } else {
                    houses[0][i] = new House(player1, 6);
                    houses[1][i] = new House(player2, 6);
                }
        }
    }

    //TODO
    //check if last deposit was home pit
    //check if any seed steals are permmited
    //Dont deposit in enemy home bin
    public void takeTurn(int selector){
        if(selector == 7) //cannot move seeds from home pit
            return;

        int side = getTurn();
        int distribute = houses[getTurn()][selector].integer;
        int pit = selector + 1;
        houses[getTurn()][selector].integer = 0;

        //loop through to spread seeds
        //check final seed location to possibly collect opposite seeds
        //check final seed location if home pit, if so take turn again

        while(distribute > 0) { //loop until all seeds are spread
            while(pit < 7 && distribute > 0){ //loop through current side
                //if(side == getTurn()) { //depositing on our side
                ++houses[side][pit].integer;
                --distribute;
                ++pit;
				/*} else { //depositing on enemy side
					if (pit == 6) { //don't put seed in enemy home bin
						++pit;
					} else {
						++houses[side][pit].integer;
						--distribute;
						++pit;
					}
				}*/
            }

            //reset pit if not done distributing
            if(distribute > 0)
                pit = 0;

            side = 1 - side; //alternate 0,1
        }

        //steal opponents seeds?
		/*--pit; // last house placed in
		int steal_index = 5 - pit;
		if(houses[getTurn()][pit].integer == 1 && pit != 6) {
			houses[getTurn()][6].integer = houses[1-getTurn()][steal_index].integer + 1;
			houses[getTurn()][pit].integer = 0;
			houses[getTurn()][steal_index].integer = 0;
		}*/

        //Other players turn if pit != home pit
        //if (pit != 7) {
        player1.setTurn(player2.turn);
        player2.setTurn(!player1.getTurn());
        //}

        print();
    }

    public void AI() {
        // TODO Auto-generated method stub

    }

    //kinda gross but it works
    //prints houses to console
    public void print() {
        System.out.print("\t");
        for (int i = houses[0].length-2; i >= 0; i--)
            System.out.print(houses[0][i].integer + "\t");

        System.out.println("\n"+ houses[0][6].integer + "\t\t\t\t\t\t\t" + houses[1][6].integer);

        System.out.print("\t");
        for (int i = 0; i < houses[1].length-1; i++)
            System.out.print(houses[1][i].integer + "\t");

        System.out.print("\n------------------------------------------------------------\n");
    }

    private void pie(){
        //implement pie rule
    }

    public House getHouseVal (int i, int j) {
        return houses[i][j];
    }

    protected Player getP1() {
        return player1;
    }

    protected Player getP2() {
        return player2;
    }

    protected void setP1(Player p1) {
        this.player1 = p1;
    }

    protected void setP2(Player p2) {
        this.player2 = p2;
    }

    protected int getTurn() {
        return player1.turn ? 1 : 0;
        //int representation of who is going
        //useful for getting index for side of starting move
    }
}