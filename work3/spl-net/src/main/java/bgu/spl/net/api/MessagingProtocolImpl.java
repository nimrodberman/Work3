package bgu.spl.net.api;

import bgu.spl.net.actions.*;
import bgu.spl.net.srv.Connections;
import bgu.spl.net.srv.ConnectionsImpl;

import java.io.IOException;
import java.io.StringReader;

public class MessagingProtocolImpl implements StompMessagingProtocol {
    private Connections connections;
    private  int connectionID;
    private boolean shouldTerminate = false;


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
            new Login(name[1],password[1],0).execute(message, connectionID, connections);//TODO: version? TODO: counter message
        }

        if (command.equals("SUBSCRIBE")){
            String[] des = arr[1].split(":");
            String[] id = arr[2].split(":");
            int ID = Integer.parseInt(id[1]);
            String[] rec = arr[3].split(":");
            int REC = Integer.parseInt(rec[1]);
            new Subscribe(ID,des[1],REC).execute(message, connectionID, connections);
        }

        if (command.equals("DISCONNECT")){ //TODO:: how to disconnect?
            String[] rec = arr[1].split(":");
            int REC = Integer.parseInt(rec[1]);
            new Disconnect(REC).execute(message,connectionID,connections);
            shouldTerminate = true;
        }
        if (command.equals("UNSUBSCRIBE")){
            String[] des = arr[1].split(":");
            String[] id = arr[2].split(":");
            int ID = Integer.parseInt(id[1]);
            String[] rec = arr[3].split(":");
            int REC = Integer.parseInt(rec[1]);
            new Unsubscribe(ID,des[1],REC).execute(message, connectionID, connections);
        }

        if(command.equals("SEND")){
            // get the type of the message
            String type = arr[1].split(":")[1];
            String des = arr[2].split(":")[1]; // destination
            String body = arr[5].split(":")[1];
            switch (type){
                case("add"): new Addbook(des,body).execute(message,connectionID,connections);

                case("status"): new BookStatus(des,body).execute(message,connectionID,connections);

                case("status1"): new BookStatus(des,body).execute(message,connectionID,connections); // TODO: are we able to return the info from the client
            }

        }







    }


    @Override
    public boolean shouldTerminate() {
        return shouldTerminate;
    }
}
