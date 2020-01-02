package bgu.spl.net.api;

import bgu.spl.net.actions.Disconnect;
import bgu.spl.net.actions.Login;
import bgu.spl.net.actions.Subscribe;
import bgu.spl.net.actions.Unsubscribe;
import bgu.spl.net.srv.Connections;
import bgu.spl.net.srv.ConnectionsImpl;

import java.io.IOException;

public class MessagingProtocolImpl implements StompMessagingProtocol {
    private Connections connections;
    private  int connectionID;
    private boolean shouldTerminate = false;
    private int counter_message =0;


    @Override
    public void start(int connectionId, Connections<String> connectionss) {
        this.connections = connectionss;
        connectionID = connectionId;


    }

    @Override
    public void process(String message) throws IOException {
        String[] arr = message.split("\n");
        String command = arr[0];

        if (command.equals("CONNECT")){
            String[] name = arr[3].split(":");
            String[] password = arr[4].split(":");
            new Login(name[1],password[1],this.counter_message).execute(message, connectionID, connections);//TODO: version?
            this.counter_message++;
        }

        if (command.equals("SUBSCRIBE")){
            String[] des = arr[1].split(":");
            String[] id = arr[2].split(":");
            int ID = Integer.parseInt(id[1]);
            String[] rec = arr[3].split(":");
            int REC = Integer.parseInt(rec[1]);
            new Subscribe(ID,des[1],REC).execute(message, connectionID, connections);
            this.counter_message++;
        }

        if (command.equals("DISCONNECT")){ //TODO:: how to disconnect?
            String[] rec = arr[1].split(":");
            int REC = Integer.parseInt(rec[1]);
            new Disconnect(REC).execute(message,connectionID,connections);
            this.counter_message++;
            shouldTerminate = true;
        }
        if (command.equals("UNSUBSCRIBE")){
            String[] des = arr[1].split(":");
            String[] id = arr[2].split(":");
            int ID = Integer.parseInt(id[1]);
            String[] rec = arr[3].split(":");
            int REC = Integer.parseInt(rec[1]);
            new Unsubscribe(ID,des[1],REC).execute(message, connectionID, connections);
            this.counter_message++;
        }







    }


    @Override
    public boolean shouldTerminate() {
        return shouldTerminate;
    }
}
