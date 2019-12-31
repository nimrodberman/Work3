package bgu.spl.net.api;

import java.util.concurrent.ConcurrentHashMap;

public class DataStructure {

    //all users in the server
    public volatile static ConcurrentHashMap <String , User> usersArchive = new ConcurrentHashMap<String, User>();

    //all genres
    public volatile static ConcurrentHashMap <String , Genre > genres = new ConcurrentHashMap<String, Genre>();


}
