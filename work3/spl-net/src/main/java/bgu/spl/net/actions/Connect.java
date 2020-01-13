package bgu.spl.net.actions;

import bgu.spl.net.Frames.Connected;
import bgu.spl.net.Frames.ErrorFrame;
import bgu.spl.net.api.DataStructure;
import bgu.spl.net.api.User;
import bgu.spl.net.impl.rci.Command;
import bgu.spl.net.srv.Connections;

import java.io.IOException;
import java.io.Serializable;

public class Connect implements Command {
    private String userName;
    private String passWord;
    private String version;
    private String reciptID;

    public Connect(String userName, String passWord, String version) {
        this.userName = userName;
        this.passWord = passWord;
        this.version = version;
    }

    @Override
    public Serializable execute(Object arg, Integer connectionId , Connections con) throws IOException {
        // check if user exist
        if(DataStructure.usersArchiveByName.containsKey(userName)){
            User u = DataStructure.usersArchiveByName.get(userName);

            // already logged in
            if(u.isConnected()){
                con.send(connectionId,new ErrorFrame("User is already logged in","" , this.reciptID));
            }

            // Wrong password
            else if(!u.getPassword().equals(passWord)){
                con.send(connectionId.intValue(),new ErrorFrame("Wrong password" , "" , this.reciptID));
            }

            // successful connection
            else if(u.getPassword().equals(passWord)){
                int old = connectionId;
                u.setConnected(true);
                u.setConID(connectionId);
                DataStructure.userByConnectionID.put(connectionId, u);
                con.send(connectionId.intValue(),new Connected(this.version));
            }
        }
        // create new user
        else {
            User u = new User(this.userName , this.passWord , connectionId);
            u.setConnected(true);
            DataStructure.usersArchiveByName.put(this.userName , u);
            DataStructure.userByConnectionID.put(connectionId , u);
            con.send(connectionId, new Connected(this.version));
        }
        return null;
    }
}
