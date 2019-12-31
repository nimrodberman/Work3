package bgu.spl.net.api;

public class Book {
    int bookID;
    String name;
    String genre;
    User currentHolder = null;
    ConcurenentLinkdDeque<User> holdersHistory = new ConcurentLinkedDeque();

    public Book(int bookID, String name, String genre) {
        this.bookID = bookID;
        this.name = name;
        this.genre = genre;
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

    public void setHoldersHistory(ConcurenentLinkdDeque<User> holdersHistory) {
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

    public ConcurenentLinkdDeque<User> getHoldersHistory() {
        return holdersHistory;
    }
}
