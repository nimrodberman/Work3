package bgu.spl.net.api;

import bgu.spl.net.actions.Disconnect;
import bgu.spl.net.actions.Login;
import bgu.spl.net.actions.Subscribe;
import bgu.spl.net.srv.Connections;
import bgu.spl.net.srv.ConnectionsImpl;

public class MessagingProtocolImpl implements StompMessagingProtocol {
    private Connections connections;
    private  int connectionID;
    private boolean shouldTerminate = false;

    @Override
    public void start(int connectionId, Connections<String> connectionss) {
        this.connections = connectionss;
        connectionId = connectionID;


    }

    @Override
    public void process(String message) {
        String[] arr = message.split("\n");
        String command = arr[0];

        if (command.equals("CONNECT")){
            String[] name = arr[3].split(":");
            String[] password = arr[4].split(":");
            new Login(name[1],password[1]).execute(message, connectionID, connections);
        }

        if (command.equals("SUBSCRIBE")){
            String[] des = arr[1].split(":");
            String[] id = arr[2].split(":");
            int ID = Integer.parseInt(id[1]);
            String[] rec = arr[3].split(":");
            int REC = Integer.parseInt(rec[1]);
            new Subscribe(ID,des[1],REC).execute(message, connectionID, connections);
        }

        if (command.equals("DISCONNECT")){
            String[] rec = arr[1].split(":");
            int REC = Integer.parseInt(rec[1]);
            new Disconnect(REC).execute(message,connectionID,connections);

        }
        if (command.equals("UNSUBSCRIBE")){ //TODO: what is the message protocol


        }

        //TODO:: how to unsubscribe?? ask the metargel





    }


    @Override
    public boolean shouldTerminate() {
        return shouldTerminate;
    }
}
