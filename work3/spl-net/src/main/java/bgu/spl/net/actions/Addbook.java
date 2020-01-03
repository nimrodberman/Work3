package bgu.spl.net.actions;

import bgu.spl.net.Frames.Message;
import bgu.spl.net.api.BookItem;
import bgu.spl.net.api.DataStructure;
import bgu.spl.net.impl.rci.Command;
import bgu.spl.net.srv.Connections;

import java.io.IOException;
import java.io.Serializable;

public class Addbook implements Command {

    private String des;
    private String body;
    private BookItem book;

    public Addbook(String des, String body) {
        this.des = des;
        this.body = body;
    }

    @Override
    public Serializable execute(Object arg, Integer connectionId, Connections con) throws IOException {
        editBook(body);
        DataStructure.genres.get(des).addBook(book);
        DataStructure.userByConnectionID.get(connectionId).addBook(book);
        con.send(des,new Message(0,des,body)); // TODO: add a subscription number!
        return null;

    }

    private void editBook(String b){
        book.setCurrentHolder(DataStructure.usersArchiveByName.get(b.split(" ")[0]));
        book.setGenre(des);
        book.setName(b.split(" ")[5]);


    }
}
