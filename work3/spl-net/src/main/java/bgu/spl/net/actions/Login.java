package bgu.spl.net.actions;

import bgu.spl.net.Frames.Connect;
import bgu.spl.net.Frames.ErrorFrame;
import bgu.spl.net.Frames.Receipt;
import bgu.spl.net.api.DataStructure;
import bgu.spl.net.api.User;
import bgu.spl.net.impl.rci.Command;
import bgu.spl.net.srv.Connections;
import bgu.spl.net.srv.ConnectionsImpl;

import java.io.IOException;
import java.io.Serializable;

public class Login implements Command {
    private String userName;
    private String passWord;
    private String mID;

    public Login(String userName, String passWord, int counter_message) {
        this.userName = userName;
        this.passWord = passWord;
        this.mID = Integer.toString(counter_message);
    }

    @Override
    public Serializable execute(Object arg, Integer connectionId , Connections con) throws IOException {//TODO: socket error?
        // check if user exist
        if(DataStructure.usersArchiveByName.containsKey(userName)){
            User u = DataStructure.usersArchiveByName.get(userName);

            // already logged in
            if(u.isConnected()){
                con.send(connectionId.intValue(),new ErrorFrame("User is already logged in","" , this.mID));
            }

            // Wrong password
            else if(!u.getPassword().equals(passWord)){
                con.send(connectionId.intValue(),new ErrorFrame("Wrong password" , "" , this.mID));
            }

            // successful connection
            else if(u.getPassword().equals(passWord)){
                u.setConnected(true);
                con.send(connectionId.intValue(),new Connect("")); // TODO: understand what String to sent
            }
        }
        // create new user
        else {
            User u = new User(this.userName , this.passWord , connectionId);
            u.setConnected(true);
            DataStructure.usersArchiveByName.put(this.userName , u);
            DataStructure.userByConnectionID.put(connectionId , u);

            con.send(connectionId, new Connect(""));
        }
        return null;
    }
}
