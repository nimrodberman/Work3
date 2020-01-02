package bgu.spl.net.actions;

import bgu.spl.net.Frames.Receipt;
import bgu.spl.net.api.DataStructure;
import bgu.spl.net.impl.rci.Command;
import bgu.spl.net.srv.Connections;

import java.io.Serializable;

public class Subscribe implements Command {
    private int userID;
    private String club;
    private int receipt;

    public Subscribe(int userID, String club, int rec) {
        this.userID = userID;
        this.club = club;
        this.receipt = rec;
    }

    @Override
    public Serializable execute(Object arg, Integer connectionId, Connections con) {
        if(!DataStructure.genres.containsKey(club)){
            con.send(connectionId,new Error()); //TODO: error message
        }

        else{
            DataStructure.genres.get(club).addUser(DataStructure.userByConnectionID.get(connectionId));
            //update user info
            DataStructure.userByConnectionID.get(connectionId).subscribeGenre(DataStructure.genres.get(club));

            con.send(connectionId,new Receipt(receipt));// TODO: Add a message
        }
        return null;
    }
}
