package bgu.spl.net.actions;

import bgu.spl.net.Frames.ErrorFrame;
import bgu.spl.net.Frames.Receipt;
import bgu.spl.net.api.DataStructure;
import bgu.spl.net.impl.rci.Command;
import bgu.spl.net.srv.Connections;

import java.io.IOException;
import java.io.Serializable;

public class Unsubscribe implements Command {
    private String subscriptionID;
    private String receiptID;

    public Unsubscribe(String ID ,String receiptID) {
        this.subscriptionID = ID;
        this.receiptID = receiptID;
    }

    @Override
    public Serializable execute(Object arg, Integer connectionId, Connections con) throws IOException {
        //if topic doesn't exist
        if(!DataStructure.topics.contains(DataStructure.userByConnectionID.get(connectionId).getTopicBySubscription(this.subscriptionID))){
            con.send(connectionId,new ErrorFrame("The genre does not exist" , "" , this.receiptID));
        }
        //the topic exist
        else {
            DataStructure.topics.get(DataStructure.userByConnectionID.get(connectionId).getTopicBySubscription(this.subscriptionID).getTopic()).removeUser(DataStructure.userByConnectionID.get(Integer.parseInt(this.subscriptionID)));
            DataStructure.userByConnectionID.get(connectionId).unsubscribeGenre(this.subscriptionID);
            con.send(connectionId, new Receipt(this.receiptID));
        }
        return null;

    }
}
