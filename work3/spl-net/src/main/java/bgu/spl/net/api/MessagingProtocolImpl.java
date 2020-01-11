package bgu.spl.net.api;

import bgu.spl.net.actions.*;
import bgu.spl.net.srv.Connections;

import java.io.IOException;

public class MessagingProtocolImpl<T> implements MessagingProtocol<T> {
    private Connections connections;
    private  int connectionID;
    private boolean shouldTerminate = false;


    @Override
    public void start(int connectionId, Connections<String> connections) {
        this.connections = connections;
        this.connectionID = connectionId;
    }

    @Override
    public T process(T message) throws IOException {
        String[] arr = ((String)message).split("\n");
        String command = arr[0];

        if (command.equals("CONNECT")){
            System.out.println("Connected recived");
            String[] version = arr[1].split(":");
            String[] host = arr[2].split(":");
            String[] name = arr[3].split(":");
            String[] password = arr[4].split(":");
            new Connect(name[1],password[1],version[1]).execute(message, connectionID, connections);
        }

        if (command.equals("SUBSCRIBE")){
            String[] des = arr[1].split(":");
            String[] id = arr[2].split(":");
            String[] rec = arr[3].split(":");
            System.out.println("Subscribe recived " + id[1]);
            new Subscribe(id[1],des[1],rec[1]).execute(message, connectionID, connections);
        }

        if (command.equals("UNSUBSCRIBE")){
            String[] id = arr[1].split(":");
            String[] recId = arr[2].split(":");
            System.out.println("UnSubscribe recived " + id[1]);
            new Unsubscribe(id[1],recId[1]).execute(message, connectionID, connections);
        }

        if (command.equals("DISCONNECT")){
            String[] rec = arr[1].split(":");
            new Disconnect(rec[1]).execute(message,connectionID,connections);
            shouldTerminate = true;
        }

        if(command.equals("SEND")){
            for(String s: arr){
                System.out.println(s);
            }
            System.out.println("Send recived");
            String[] des = arr[1].split(":");
            String body = arr[3];
            new Send(des[1] , body).execute(message , connectionID , connections);
            }

        return null;
        }

    @Override
    public boolean shouldTerminate() {
        return shouldTerminate;
    }
}
