package bgu.spl.net.actions;

import bgu.spl.net.Frames.Receipt;
import bgu.spl.net.api.DataStructure;
import bgu.spl.net.impl.rci.Command;
import bgu.spl.net.srv.Connections;

import java.io.IOException;
import java.io.Serializable;

public class Unsubscribe implements Command {

    private int ID;
    private String topic;
    private int receipt;

    public Unsubscribe(int ID , String topic , int receipt) {
        this.ID=ID;
        this.topic = topic;
        this.receipt = receipt;
    }

    @Override
    public Serializable execute(Object arg, Integer connectionId, Connections con) throws IOException {
        DataStructure.genres.get(this.topic).removeUser(DataStructure.userByConnectionID.get(this.ID));
        DataStructure.userByConnectionID.get(this.ID).unsubscribeGenre( DataStructure.genres.get(this.topic));
        con.send(connectionId,new Receipt(receipt));
        return null;

    }
}
