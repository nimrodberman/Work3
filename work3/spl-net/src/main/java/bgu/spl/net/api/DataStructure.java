package bgu.spl.net.api;

import java.util.concurrent.ConcurrentHashMap;

public class DataStructure {

    public volatile static ConcurrentHashMap <String , User> usersArchiveByName = new ConcurrentHashMap<String, User>();

    //all genres
    public volatile static ConcurrentHashMap <String , Topic> topics = new ConcurrentHashMap<String, Topic>();


    public volatile static ConcurrentHashMap <Integer , User > userByConnectionID = new ConcurrentHashMap<Integer, User>();



}
