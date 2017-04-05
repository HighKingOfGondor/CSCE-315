package sample;

/**
 * Created by jaredwheeler on 3/29/17.
 */
public abstract class AI {
    protected Board game;
    private int playerID;

    public AI(Board game, int playerID) {
        this.game = game;
        this.playerID = playerID;

    }

    public AI(){

    }

    abstract int makeMove();
    abstract void miniMax();
    /**
     Gets the legal moves a player can take
     @return The legal moves for that player
     */
    public void getAllowedMoves()
    {
        //return game.getAllowedMoves(playerID);
    }

    public int getPlayerID()
    {
        return playerID;
    }

    public void setPlayerID(int id)
    {
        playerID = id;
    }

}