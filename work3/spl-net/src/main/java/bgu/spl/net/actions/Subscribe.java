package bgu.spl.net.actions;

import bgu.spl.net.Frames.ErrorFrame;
import bgu.spl.net.Frames.Receipt;
import bgu.spl.net.api.DataStructure;
import bgu.spl.net.impl.rci.Command;
import bgu.spl.net.srv.Connections;

import java.io.IOException;
import java.io.Serializable;

public class Subscribe implements Command {
    private int ID;
    private String club;
    private int receipt;

    public Subscribe(int ID, String club, int rec) {
        this.ID=ID;
        this.club = club;
        this.receipt = rec;
    }

    @Override
    public Serializable execute(Object arg, Integer connectionId, Connections con) throws IOException {
        if(!DataStructure.genres.containsKey(club)){
            con.send(connectionId,new ErrorFrame("The genre dosent exist" , "" , String.valueOf(this.receipt)));
        }

        else{
            DataStructure.genres.get(club).addUser(DataStructure.userByConnectionID.get(this.ID));
            //update user info
            DataStructure.userByConnectionID.get(this.ID).subscribeGenre(DataStructure.genres.get(club));

            con.send(connectionId,new Receipt(receipt));
        }
        return null;
    }
}
