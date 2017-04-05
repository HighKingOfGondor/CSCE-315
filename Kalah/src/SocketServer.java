package sample;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;

/**
 * Created by jaredwheeler on 4/4/17.
 */
public class SocketServer {

    public void connect() {
        Socket s = null;
        BufferedReader input = null;
        try {
            s = new Socket("127.0.0.1", 5000);
            input = new BufferedReader(new InputStreamReader(s.getInputStream()));
        } catch (IOException e) {
            e.printStackTrace();
        }
        String answer = null;
        
        try {
            answer = input.readLine();
        } catch (IOException e) {
            e.printStackTrace();
        }
        System.out.println(answer);
    }
}
