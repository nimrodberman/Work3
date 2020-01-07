package bgu.spl.net.api;

import java.awt.print.Book;
import java.util.ArrayList;

public class Topic {
    //----------fields-----------

    private String topic;
    private int id;
    private static int counter = 1;
    private ArrayList <User> users = new ArrayList<>();

    //-------constuctor-------

    public Topic(String s) {
        this.topic = s;
        this.id = counter;
        this.counter++;
    }

    //-----------methods-----------

    public synchronized void addUser (User user){
        this.users.add(user);
    }

    public synchronized void removeUser (User user){
        this.users.remove(user);
    }

    public ArrayList<User> getUsers() {
        return users;
    }

    public String getTopic() {
        return topic;
    }
}
