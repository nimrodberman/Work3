package bgu.spl.net.api;

import java.util.concurrent.ConcurrentHashMap;

public class DataStructure {

    //all users in the server
    public volatile static ConcurrentHashMap <String , User> usersArchiveByName = new ConcurrentHashMap<String, User>();

    //all genres
    public volatile static ConcurrentHashMap <String , Topic> topics = new ConcurrentHashMap<String, Topic>();

    // current active users
    public volatile static ConcurrentHashMap <Integer , User > userByConnectionID = new ConcurrentHashMap<Integer, User>();



}
