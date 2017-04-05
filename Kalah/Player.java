package sample;

import java.applet.Applet;
import sample.AI;

/**
 * Created by jaredwheeler on 3/28/17.
 */
public class Player {
    //used to check if a player two is going to play
    boolean isAI = false;
    boolean turn = false;
    int playerNumber;
    Player (boolean ai, int playerNumber) {
        //true if player, false if AI
        this.isAI = ai; //
        this.playerNumber = playerNumber;
        if(playerNumber == 1)
            turn = true;
        if (ai == false)
            setAI();
    }

    boolean getIsAI () { return isAI; }
    boolean getTurn () { return turn; }
    int getPlayerNumber () { return playerNumber; }

    public void setTurn (boolean t) { turn = t; }

    public void move () {
        if (turn == false) {
            System.out.println("Cannot move");

        } else {
            System.out.println("go ahead");
        }
    }

    private void setAI() {
        //AI ai = new AI();
    }
}