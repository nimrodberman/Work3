package bgu.spl.net.api;

import java.awt.print.Book;
import java.util.ArrayList;

public class Genre {
    //----------fields-----------

    private String topic;
    private ArrayList <User> users = new ArrayList<>();
    private ArrayList <Book> books = new ArrayList<Book>();

    //-------constuctor-------

    public Genre(String topic) {
        this.topic = topic;
    }

    //-----------methods-----------

    public synchronized void addUser (User user){
        this.users.add(user);
    }

    public synchronized void removeUser (User user){
        this.users.remove(user);
    }

    public synchronized void addBook (Book book){
        this.books.add(book);
    }

    public synchronized Book borrowBook (String name){
        for ( ) {

        }

    }
}
