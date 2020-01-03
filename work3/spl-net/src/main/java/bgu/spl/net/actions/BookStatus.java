package bgu.spl.net.actions;

import bgu.spl.net.Frames.Message;
import bgu.spl.net.impl.rci.Command;
import bgu.spl.net.srv.Connections;

import java.io.IOException;
import java.io.Serializable;

public class BookStatus implements Command {

    private String des;
    private String body;

    public BookStatus(String des, String body) {
        this.des = des;
        this.body = body;
    }


    @Override
    public Serializable execute(Object arg, Integer connectionId, Connections con) throws IOException {

        // send a message to all clients in the genre to give their book report
        con.send(des,new Message(0,des,"Book status"));
        return null;
    }

}
