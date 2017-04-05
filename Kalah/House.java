package sample;

/**
 * Created by jaredwheeler on 3/28/17.
 */
public class House {
    Player player; //Who this piece belongs to
    Integer integer; //Number of seeds in house
    House (Player player, int integer) {
        this.integer = new Integer(integer);
        this.player = player;
    }

    public Player getPlayer() {
        return player;
    }
    public Integer getInteger() {
        return integer;
    }
}