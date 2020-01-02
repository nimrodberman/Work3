package bgu.spl.net.api;

import java.util.ArrayList;

public class User {
    //-------------fields-------------
    private String name;
    private String password;
    private ArrayList <Book> books;
    private ArrayList <Genre> genres;
    private Integer conID;
    private boolean connected = false;

    //---------constructors-----------


    public User(String name, String password, Integer conID) {
        this.name = name;
        this.password = password;
        this.conID = conID;
        this.books = new ArrayList<Book>();
        this.genres = new ArrayList<Genre>();
    }

    public void addBook (Book book){
        this.books.add(book);
    }

    public void borrowBook (Book book){
            this.books.remove(book);
    }

    public boolean bookIsExist(Book book){
        return this.books.contains(book);
    }

    public void subscribeGenre (Genre genre){
        this.genres.add(genre);
    }

    public void unsubscribeGenre (Genre genre){
        this.genres.remove(genre);
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
        for (Genre g : genres){
            g.removeUser(this);
        }
        genres.clear();
    }
}
