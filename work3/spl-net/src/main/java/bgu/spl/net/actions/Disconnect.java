package bgu.spl.net.actions;

import bgu.spl.net.Frames.Receipt;
import bgu.spl.net.api.DataStructure;
import bgu.spl.net.impl.rci.Command;
import bgu.spl.net.srv.Connections;

import java.io.Serializable;

public class Disconnect implements Command {

    private int reciept_number;

    public Disconnect(int recnumber) {
        this.reciept_number = recnumber;
    }

    @Override
    public Serializable execute(Object arg, Integer connectionId, Connections con) {
        // TODO: understand if books are deleted as well?

        //assume that the user is active
        // delete from each Genre and delete user genre list
        DataStructure.userByConnectionID.get(connectionId).clearAllGenres();
        con.send(connectionId,new Receipt(reciept_number));

        return null;
    }
}
