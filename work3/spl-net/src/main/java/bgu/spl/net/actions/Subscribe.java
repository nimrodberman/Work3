package bgu.spl.net.actions;

import bgu.spl.net.Frames.ErrorFrame;
import bgu.spl.net.Frames.Receipt;
import bgu.spl.net.api.DataStructure;
import bgu.spl.net.impl.rci.Command;
import bgu.spl.net.srv.Connections;

import java.io.IOException;
import java.io.Serializable;

public class Subscribe implements Command {
    private String subscriptionID;
    private String topic;
    private String receiptID;

    public Subscribe(String ID, String topic, String rec) {
        this.subscriptionID =ID;
        this.topic = topic;
        this.receiptID = rec;
    }

    @Override
    public Serializable execute(Object arg, Integer connectionId, Connections con) throws IOException {
        if(!DataStructure.topics.containsKey(topic)){
            con.send(connectionId,new ErrorFrame("The genre does not exist" , "" , this.receiptID));
        }

        else{
            DataStructure.topics.get(topic).addUser(DataStructure.userByConnectionID.get(connectionId)); // add user to genre
            DataStructure.userByConnectionID.get(connectionId).subscribeGenre(this.subscriptionID,DataStructure.topics.get(topic)); //update user info
            // send a certification
            con.send(connectionId,new Receipt(this.receiptID));
        }
        return null;
    }
}
