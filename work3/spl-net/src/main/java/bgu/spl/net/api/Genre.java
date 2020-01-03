package bgu.spl.net.api;

import java.awt.print.Book;
import java.util.ArrayList;

public class Genre {
    //----------fields-----------

    private String topic;
    private int id;
    private static int counter = 1;
    private ArrayList <User> users = new ArrayList<>();
    private ArrayList <BookItem> books = new ArrayList<BookItem>();

    //-------constuctor-------

    public Genre(String s) {
        this.topic = s;
        id = counter;
        counter++;
    }

    //-----------methods-----------

    public synchronized void addUser (User user){
        this.users.add(user);
    }

    public synchronized void removeUser (User user){
        this.users.remove(user);
    }

    public synchronized void addBook (BookItem book){
        this.books.add(book);
    }

    public ArrayList<User> getUsers() {
        return users;
    }

    /*
    public synchronized Book borrowBook (String name){
        for ( ) {

        }

    }
    */

}
