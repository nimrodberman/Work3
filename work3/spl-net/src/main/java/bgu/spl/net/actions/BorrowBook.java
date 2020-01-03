package bgu.spl.net.actions;

import bgu.spl.net.api.DataStructure;
import bgu.spl.net.impl.rci.Command;
import bgu.spl.net.srv.Connections;

import java.io.IOException;
import java.io.Serializable;

public class BorrowBook implements Command {

    private String des;
    private String name;
    private String book;

    public BorrowBook(String des, String body) {
        this.des = des;
        String[] arr = body.split(" ");
        this.book = arr[0];
        this.name = arr[arr.length-1];
    }

    @Override
    public Serializable execute(Object arg, Integer connectionId, Connections con) throws IOException {
        //DataStructure.genres.get(this.des).getUsers().get(DataStructure.);
        return null;
    }
}
