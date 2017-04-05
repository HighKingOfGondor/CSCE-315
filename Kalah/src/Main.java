package sample;
import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.Paths;

import javafx.application.*;
import javafx.event.EventHandler;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.input.MouseEvent;
import javafx.scene.paint.*;
import javafx.stage.*;
import javafx.geometry.*;
import javafx.scene.*;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.Pane;
import javafx.scene.layout.StackPane;
import javafx.scene.layout.VBox;
import javafx.scene.shape.Line;
import javafx.scene.shape.Rectangle;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.scene.text.*;

public class Main extends Application {

    Pane root;
    Stage theStage;

    private boolean isRandom = false;
    private int seedCount = 50;

    public Parent createMainMenu() {

        root = new Pane();
        root.setPrefSize(1080, 720);

        try(InputStream is = Files.newInputStream(Paths.get("/Users/jaredwheeler/Documents/CSCE 315 Homework/TeamProjectTwo/src/myKalahBackground.jpg"))){
            ImageView img = new ImageView(new Image(is));
            img.setFitWidth(1080);
            img.setFitHeight(720);
            root.getChildren().add(img);
        }
        catch(IOException e) {
            System.out.println("Couldn't load image");
        }

        Title title = new Title ("K A L A H");
        title.setTranslateX(50);
        title.setTranslateY(200);

        MenuBox vbox = new MenuBox(
                new MenuItem("NEW GAME"),
                new MenuItem("OPTIONS"),
                new MenuItem("HELP"),
                new MenuItem("EXIT"));
        vbox.setTranslateX(100);
        vbox.setTranslateY(300);

        root.getChildren().addAll(title, vbox);

        return root;

    }

    private Parent createOptions() {
        root = new Pane();
        root.setPrefSize(1080, 720);

        try(InputStream is = Files.newInputStream(Paths.get("/Users/jaredwheeler/Documents/CSCE 315 Homework/TeamProjectTwo/src/myKalahBackground.jpg"))){
            ImageView img = new ImageView(new Image(is));
            img.setFitWidth(1080);
            img.setFitHeight(720);
            root.getChildren().add(img);
        }
        catch(IOException e) {
            System.out.println("Couldn't load image");
        }
        Title title = new Title ("K A L A H");
        title.setTranslateX(50);
        title.setTranslateY(200);

        Text defaultSeed = new Text("Default Seed Count is 50");
        defaultSeed.setFill(Color.WHITE);
        defaultSeed.setFont(Font.font("Times New Roman", FontWeight.SEMI_BOLD, 25));
        defaultSeed.setX(200);
        defaultSeed.setY(500);
        MenuBox numberOption = new MenuBox(
                new MenuItem("Set Seed Number To 40"),
                new MenuItem("Set Seed Number To 50"),
                new MenuItem("Set Seed Number To 60")
        );
        numberOption.setTranslateX(200);
        numberOption.setTranslateY(520);
        Text random = new Text("Random seeds in each house?");
        random.setFill(Color.WHITE);
        random.setFont(Font.font("Times New Roman", FontWeight.SEMI_BOLD, 25));
        random.setX(500);
        random.setY(500);
        Button yesRandom = new Button("Yes!");
        yesRandom.setStyle("-fx-background-color: brown; -fx-font: 22 arial;");
        yesRandom.setTextFill(Color.WHITE);
        yesRandom.setPrefHeight(50);
        yesRandom.setPrefWidth(100);
        yesRandom.setTranslateY(520);
        yesRandom.setTranslateX(500);
        yesRandom.addEventHandler(MouseEvent.MOUSE_CLICKED, new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent event) {
                isRandom = true;
            }
        });
        Button noRandom = new Button("No!");
        noRandom.setStyle("-fx-background-color: brown; -fx-font: 22 arial;");
        noRandom.setTextFill(Color.WHITE);
        noRandom.setPrefHeight(50);
        noRandom.setPrefWidth(100);
        noRandom.setTranslateY(520);
        noRandom.setTranslateX(620);
        noRandom.addEventHandler(MouseEvent.MOUSE_CLICKED, new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent event) {
                isRandom = false;
            }
        });
        Button back = new Button("BACK");
        back.setTextFill(Color.web("#ffffff"));
        back.setStyle("-fx-background-color: brown;");
        back.setMaxWidth(200);
        back.setTranslateX(40);
        back.setTranslateY(680);
        back.addEventHandler(MouseEvent.MOUSE_CLICKED, new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent event) {
                Scene helpScreen = new Scene(createMainMenu());
                theStage.setScene(helpScreen);
                theStage.show();               }
        });
        root.getChildren().addAll(title, defaultSeed, random, yesRandom, noRandom, numberOption, back);
        return root;
    }

    private Parent createInstructions() {
        root = new Pane();
        root.setPrefSize(1080, 720);

        try(InputStream is = Files.newInputStream(Paths.get("/Users/jaredwheeler/Documents/CSCE 315 Homework/TeamProjectTwo/src/myKalahBackground.jpg"))){
            ImageView img = new ImageView(new Image(is));
            img.setFitWidth(1080);
            img.setFitHeight(720);
            root.getChildren().add(img);
        }
        catch(IOException e) {
            System.out.println("Couldn't load image");
        }

        Title title = new Title ("K A L A H");
        title.setTranslateX(50);
        title.setTranslateY(200);

        Label instructionSet = new Label("1. At the beginning of the game, four seeds are placed in each house. This is the traditional method.\n" +
                "2. Each player controls the six houses and their seeds on the player's side of the board. The player's score is the number of seeds in the store to their right.\n" +
                "3. Players take turns sowing their seeds. On a turn, the player removes all seeds from one of the houses under their control. Moving counter-clockwise, the player drops one seed in each house in turn, including the player's own store but not their opponent's.\n" +
                "4. If the last sown seed lands in an empty house owned by the player, and the opposite house contains seeds, both the last seed and the opposite seeds are captured and placed into the player's store.\n" +
                "5. If the last sown seed lands in the player's store, the player gets an additional move. There is no limit on the number of moves a player can make in their turn.\n" +
                "6. When one player no longer has any seeds in any of their houses, the game ends. The other player moves all remaining seeds to their store, and the player with the most seeds in their store wins.");
        instructionSet.setFont(Font.font("Times New Roman", FontWeight.SEMI_BOLD,22));
        instructionSet.setStyle("-fx-border-color: white;");
        instructionSet.setWrapText(true);
        instructionSet.setMaxWidth(1000);
        instructionSet.setTextAlignment(TextAlignment.JUSTIFY);
        instructionSet.setTextFill(Color.web("#ffffff"));
        instructionSet.setTranslateX(40);
        instructionSet.setTranslateY(340);

        Button back = new Button("BACK");
        back.setTextFill(Color.web("#ffffff"));
        back.setStyle("-fx-background-color: brown;");
        back.setMaxWidth(200);
        back.setTranslateX(40);
        back.setTranslateY(680);
        back.addEventHandler(MouseEvent.MOUSE_CLICKED, new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent event) {
                Scene helpScreen = new Scene(createMainMenu());
                theStage.setScene(helpScreen);
                theStage.show();               }
        });

        root.getChildren().addAll(title, instructionSet, back);

        return root;
    }

    @Override
    public void start(Stage primaryStage) throws Exception{
        Scene scene = new Scene(createMainMenu());
        theStage = primaryStage;
        theStage.setTitle("KALAH GAME");
        theStage.setScene(scene);
        theStage.show();
    }

    public boolean getRandom() {
        return isRandom;
    }

    static class Title extends StackPane{
        public Title(String name) {

            Rectangle bg = new Rectangle(375, 60);
            bg.setStroke(Color.WHITE);
            bg.setStrokeWidth(2);
            try(InputStream is = Files.newInputStream(Paths.get("/Users/jaredwheeler/Documents/CSCE 315 Homework/TeamProjectTwo/src/kalahBackgroundTite.jpg"))){
                ImagePattern img = new ImagePattern(new Image(is));
                bg.setFill(img);
            }
            catch(IOException e) {
                System.out.println("Couldn't load image");
            }

            Text text = new Text(name);
            text.setFill(Color.WHITE);
            text.setFont(Font.font("Times New Roman", FontWeight.SEMI_BOLD, 50));

            setAlignment(Pos.CENTER);
            getChildren().addAll(bg,text);
        }
    }

    private static class MenuBox extends VBox{
        public MenuBox(MenuItem...items) {
            getChildren().add(createSeperator());

            for(MenuItem item : items) {
                getChildren().addAll(item, createSeperator());
            }
        }

        private Line createSeperator() {
            Line sep = new Line();
            sep.setEndX(210);
            sep.setStroke(Color.DARKGREY);
            return sep;
        }

    }


    private class MenuItem extends StackPane {
        public MenuItem(String name) {
            LinearGradient gradient = new LinearGradient(0, 0, 1, 0, true, CycleMethod.NO_CYCLE, new Stop[]{
                    new Stop(0, Color.BROWN),
                    new Stop(0.1, Color.BLACK),
                    new Stop(0.9, Color.BLACK),
                    new Stop(1, Color.BROWN)
            });

            Button option = new Button();
            option.setShape(new Rectangle(200, 30));
            option.setStyle("-fx-background-color: transparent;");
            option.setMaxWidth(200);

            Rectangle bg = new Rectangle(200, 30);
            bg.setOpacity(0.4);

            Text text = new Text(name);
            text.setFill(Color.DARKKHAKI);
            text.setFont(Font.font("Times New Roman", FontWeight.SEMI_BOLD, 20));

            setAlignment(Pos.CENTER);
            getChildren().addAll(bg, text, option);

            option.addEventHandler(MouseEvent.MOUSE_ENTERED, new EventHandler<MouseEvent>() {
                @Override
                public void handle(MouseEvent event) {
                    bg.setFill(gradient);
                    text.setFill(Color.WHITE);
                }
            });
            option.addEventHandler(MouseEvent.MOUSE_EXITED, new EventHandler<MouseEvent>() {
                @Override
                public void handle(MouseEvent event) {
                    bg.setFill(Color.BLACK);
                    text.setFill(Color.DARKKHAKI);
                }
            });
            option.addEventHandler(MouseEvent.MOUSE_CLICKED, new EventHandler<MouseEvent>() {
                @Override
                public void handle(MouseEvent event) {
                    bg.setFill(Color.FIREBRICK);
                    try {
                        menuFunctions(name);
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
            });
            option.addEventHandler(MouseEvent.MOUSE_RELEASED, new EventHandler<MouseEvent>() {
                @Override
                public void handle(MouseEvent event) {
                    bg.setFill(gradient);
                }
            });
        }

        private void menuFunctions(String which) throws Exception {

            if (which == "NEW GAME") {
                Board newGame = new Board(root, isRandom, seedCount);
                try {
                    newGame.start(theStage);

                } catch (Exception e) {
                    e.printStackTrace();
                }
            } else if (which == "OPTIONS") {
                //add in pebble adjustment options
                Scene optionsScreen = new Scene(createOptions());
                theStage.setScene(optionsScreen);
                theStage.show();
                //adjust difficulty
                //other possibilities
                //temporary close
            } else if (which == "HELP") {
                Scene helpScreen = new Scene(createInstructions());
                theStage.setScene(helpScreen);
                theStage.show();
            } else if (which == "EXIT") {
                theStage.close();
            } else if (which == "Set Seed Number To 40") {
                seedCount = 40;
                System.out.println(seedCount);
            } else if (which == "Set Seed Number To 50") {
                seedCount = 50;
                System.out.println(seedCount);
            } else if (which == "Set Seed Number To 60") {
                seedCount = 60;
                System.out.println(seedCount);
            }
        }

        private void setRandom(boolean random) {
            isRandom = random;
        }
        private void setSeedCount (int ss) {
            seedCount = ss;
        }
    }

    public static void main(String[] args) {
        SocketServer ss = new SocketServer();
        ss.connect();
        //launch(args);
    }
}
