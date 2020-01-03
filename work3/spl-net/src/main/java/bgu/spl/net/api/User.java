package bgu.spl.net.api;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class User {
    //-------------fields-------------
    private String name;
    private String password;
    private ArrayList <BookItem> books;
    private ConcurrentHashMap<Integer,Genre> genres;
    private Integer conID;
    private boolean connected = false;

    //---------constructors-----------


    public User(String name, String password, Integer conID) {
        this.name = name;
        this.password = password;
        this.conID = conID;
        this.books = new ArrayList<BookItem>();
        this.genres = new ConcurrentHashMap<Integer, Genre>();
    }

    public void addBook (BookItem book){
        this.books.add(book);
    }

    public void borrowBook (BookItem book){
            this.books.remove(book);
    }

    public boolean bookIsExist(BookItem book){
        return this.books.contains(book);
    }

    public void subscribeGenre (Integer in ,Genre genre){
        this.genres.put(in, genre);
    }

    public void unsubscribeGenre (Integer in){
        this.genres.remove(in);
    }

    public boolean isConnected() {
        return connected;
    }

    public void setConnected(boolean connected) {
        this.connected = connected;
    }

    public String getName() {
        return name;
    }

    public String getPassword() {
        return password;
    }

    public void clearAllGenres(){
        // Remove the user from all genre lists
        Iterator it = genres.entrySet().iterator();
        for (Map.Entry<Integer, Genre> entry : genres.entrySet()){
            Integer key = entry.getKey();
            genres.get(key).removeUser(this);
        }
        genres.clear();
    }

    public Integer getConID() {
        return conID;
    }
}
