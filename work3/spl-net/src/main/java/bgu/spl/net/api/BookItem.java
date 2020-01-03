package bgu.spl.net.api;

import java.util.concurrent.BlockingDeque;
import java.util.concurrent.LinkedBlockingDeque;

public class BookItem {
    private static int counter=1;
    private int bookID;
    private String name;
    private String genre;
    private User currentHolder = null;
    private BlockingDeque<User> holdersHistory ;

    public BookItem(String name, String genre) {
        this.bookID = counter;
        counter++;
        this.name = name;
        this.genre = genre;
        this.holdersHistory = new LinkedBlockingDeque<>();
    }

    public void setBookID(int bookID) {
        this.bookID = bookID;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setGenre(String genre) {
        this.genre = genre;
    }

    public void setCurrentHolder(User currentHolder) {
        this.currentHolder = currentHolder;
    }

    public void setHoldersHistory(BlockingDeque<User> holdersHistory) {
        this.holdersHistory = holdersHistory;
    }

    public int getBookID() {
        return bookID;
    }

    public String getName() {
        return name;
    }

    public String getGenre() {
        return genre;
    }

    public User getCurrentHolder() {
        return currentHolder;
    }

    public BlockingDeque<User> getHoldersHistory() {
        return holdersHistory;
    }
}
