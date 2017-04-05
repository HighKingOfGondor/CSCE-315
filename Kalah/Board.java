package sample;

import javafx.application.Application;
import javafx.event.EventHandler;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.paint.ImagePattern;
import javafx.scene.shape.Rectangle;
import javafx.scene.text.Text;
import javafx.stage.Stage;

import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Vector;

/**
 * Created by jaredwheeler on 3/21/17.
 * Wyatt Payne
 * 	- Changed Piece.java-> House.java for naming purposes
 * 	- change
 */
public class Board extends Application {
    //menu return instance
    Main main_menu = new Main();

    //Main Mancala game
    Mancala kalha;

    //Players of the game
    //Player player1 = new Player(true, 1);
    //Player player2 = new Player(false, 2); //this is AI

    //Components of the game
    Pane root;
    Stage theStage;


    //options from Main
    boolean random = false;
    int seedCount = 0;
    //boolean currentPlayer = true;
    int counter = 0;

    //scores
    int storeOneScore = 0;
    int storeTwoScore = 0;

    //items that need redrawn
    Label turnLabel = new Label("");
    //Vector<House> topVals = new Vector<House>(6);
    //Vector<House> bottomVals = new Vector<House>(6);
    Vector<Button> topHouses = new Vector<Button>();
    Vector<Button> bottomHouses = new Vector<Button>();
    Label sOne = new Label(Integer.toString(storeOneScore));
    Label sTwo = new Label(Integer.toString(storeTwoScore));

    public Board(Pane r, boolean passRand, int passSeedCount) {
        root = r;
        random = passRand;
        seedCount = passSeedCount;
    }

    @Override
    public void start(Stage primaryStage) throws Exception {
        Scene scene = new Scene(initBoard());
        theStage = primaryStage;
        theStage.setTitle("KALAH GAME");
        theStage.setScene(scene);
        theStage.show();
    }

    private Parent initBoard() {
        root = new Pane();
        root.setPrefSize(1080, 720);
        kalha = new Mancala(seedCount, random);

        //setting up the background
        setBackground();
        //setting up the board itself
        setBoard();
        //make the quit function
        setQuit();
        setHouses(); //
        setStores(); //home bins
        setPlayerTitle("Player 1");
        goGame();

        return root;
    }

    private void goGame() {
        kalha.player1.setTurn(true);
    }

    private void setPlayerTitle(String curPlayer) {
        turnLabel.setText(curPlayer);
        turnLabel.setTranslateY(25);
        turnLabel.setTranslateX(500);
        turnLabel.setStyle("-fx-font: 26 arial;");
        turnLabel.setTextFill(Color.WHITE);

        root.getChildren().add(turnLabel);
    }


    private void setStores() {
        Rectangle storeOne = new Rectangle(110, 400);
        Rectangle storeTwo = new Rectangle(110, 400);
        try(InputStream is = Files.newInputStream(Paths.get("/Users/jaredwheeler/Documents/CSCE 315 Homework/TeamProjectTwo/src/0010-dark-wood-texture-seamless.jpg"))){
            ImagePattern img = new ImagePattern(new Image(is));
            storeOne.setFill(img);
            storeTwo.setFill(img);
        }
        catch(IOException e) {
            System.out.println("Couldn't load image");
        }
        storeOne.setTranslateY(160);
        storeOne.setTranslateX(800);
        storeTwo.setTranslateY(160);
        storeTwo.setTranslateX(140);
        sTwo.setTranslateY(340);
        sTwo.setTranslateX(185);
        sOne.setTranslateY(340);
        sOne.setTranslateX(845);
        sTwo.setStyle("-fx-font: 22 arial;");
        sTwo.setTextFill(Color.WHITE);
        sOne.setStyle("-fx-font: 22 arial;");
        sOne.setTextFill(Color.WHITE);
        root.getChildren().addAll(storeOne, storeTwo, sOne, sTwo);
    }

    private void setHouses() {
        //bottomVals = setSeeds();
        //topVals = setSeeds();
        for(int k = 0; k < 6; ++k ){
            topHouses.add(new Button());
            bottomHouses.add(new Button());
        }

        int i = 0;
        for (Button button : topHouses) {
            button.setStyle("-fx-background-color: brown;");
            button.setPrefWidth(50);
            button.setPrefHeight(50);
            button.setTranslateX(780 - 80 * (i + 1));
            button.setTranslateY(150);
            button.setText(Integer.toString(kalha.getHouseVal(0,i).getInteger()));
            int finalI = i;
            button.addEventHandler(MouseEvent.MOUSE_CLICKED, new EventHandler<MouseEvent>() {
                @Override
                public void handle(MouseEvent event) {
                    try {
                        sowTop(finalI); //houses[0]
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
            });
            root.getChildren().add(topHouses.elementAt(i));
            i++;
        }
        int j = 0;
        for (Button button : bottomHouses) {
            button.setStyle("-fx-background-color: brown;");
            button.setPrefWidth(50);
            button.setPrefHeight(50);
            button.setTranslateX(220 + 80 * (j + 1));
            button.setTranslateY(520);
            button.setText(Integer.toString(kalha.getHouseVal(1,j).getInteger()));
            int finalI = j;
            button.addEventHandler(MouseEvent.MOUSE_CLICKED, new EventHandler<MouseEvent>() {
                @Override
                public void handle(MouseEvent event) {
                    try {
                        sowBottom(finalI); //houses[1]
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
            });
            root.getChildren().add(bottomHouses.elementAt(j));
            j++;
        }
    }

    private void setQuit() {
        Button quit = new Button("QUIT");
        quit.setTextFill(Color.web("#ffffff"));
        quit.setStyle("-fx-background-color: brown;");
        quit.setMaxWidth(200);
        quit.setMaxHeight(150);
        quit.setTranslateX(1000);
        quit.setTranslateY(680);
        quit.addEventHandler(MouseEvent.MOUSE_CLICKED, new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent event) {
                Main returnTo = new Main();
                try {
                    returnTo.start(theStage);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });
        root.getChildren().add(quit);
    }

    private void wrongText(boolean addOrRemove) {
        Text wrongness = new Text("Wrong Side!");
        wrongness.setTranslateX(500);
        wrongness.setTranslateY(690);
        wrongness.setStyle("-fx-font: 26 arial;");
        wrongness.setFill(Color.WHITE);
        if (addOrRemove == true && !root.getChildren().contains(wrongness)) {
            root.getChildren().add(wrongness);
        } else if (addOrRemove == false && !root.getChildren().contains(wrongness)) {
            root.getChildren().removeAll(wrongness);
        } else {
            return;
        }
    }

    private void setBoard() {
        Rectangle board = new Rectangle(900, 500);
        try(InputStream is = Files.newInputStream(Paths.get("/Users/jaredwheeler/Documents/CSCE 315 Homework/TeamProjectTwo/src/KalahBoardImg.jpg"))){
            ImagePattern img = new ImagePattern(new Image(is));
            board.setFill(img);
            board.setTranslateY(105);
            board.setTranslateX(80);
        }
        catch(IOException e) {
            System.out.println("Couldn't load image");
        }
        root.getChildren().add(board);
    }

    private void setBackground() {
        try(InputStream is = Files.newInputStream(Paths.get("/Users/jaredwheeler/Documents/CSCE 315 Homework/TeamProjectTwo/src/myKalahBackground.jpg"))){
            ImageView img = new ImageView(new Image(is));
            img.setFitWidth(1080);
            img.setFitHeight(720);
            root.getChildren().add(img);
        }
        catch(IOException e) {
            System.out.println("Couldn't load image");
        }
    }

    private void sowBottom(int position) {
        if (kalha.player2.getTurn() == true) {
            System.out.println("wrong side!");
            wrongText(true);
        } else if (kalha.player1.getTurn() == true) {
            kalha.takeTurn(position);
            redraw();
        } else {
            System.out.println("You stupid stupid idiot - Ben Shapiro");
        }
    }

    private void sowTop(int position) {
        if (kalha.player1.getTurn() == true) {
            System.out.println("wrong side!");
            wrongText(true);
        } else if (kalha.player2.getTurn() == true) {
            kalha.takeTurn(position);
            redraw();
        } else {
            System.out.println("You stupid stupid idiot - Ben Shapiro");
        }
    }

    private void redraw() {
        int i = 0;
        for (Button button : topHouses) {
            button.setText(Integer.toString(kalha.getHouseVal(0,i).getInteger()));
            i++;
        }
        int j = 0;
        for (Button button : bottomHouses) {
            button.setText(Integer.toString(kalha.getHouseVal(1,j).getInteger()));
            j++;
        }
        sOne.setText(Integer.toString(kalha.getHouseVal(1, 6).integer));
        sTwo.setText(Integer.toString(kalha.getHouseVal(0, 6).integer));

        if (kalha.getTurn() == 1) {
            turnLabel.setText("Player 1");
        } else {
            turnLabel.setText("Player 2");
        }

        if (0 > seedCount) {
            try {
                main_menu.start(theStage);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    public void getAllowedMoves (int player) {
/*        if(player != player1.getPlayerNumber() && player != player2.getPlayerNumber()) {
            throw new IllegalArgumentException("PlayerID is not valid: " + player);
        }
        int offset = (player - 1) * 7;
        int size = 0;
        //get the number of legal moves
        for (int i = offset; i < offset + 6; i++) {
            if (kalha.getHouseVal(0,i).getInteger() > 0) {
                size++;
            }
        }
        int[] moves = new int[size];
        int index = 0;
        //add the moves to the array
        for (int i = offset; i < offset + 6; i++) {
            if (kalha.getHouseVal(0,i).getInteger() > 0) {
                moves[index] = i;
                index++;
            }
        }
        return moves;*/
    }

}