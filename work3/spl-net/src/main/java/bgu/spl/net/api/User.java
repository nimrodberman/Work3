package bgu.spl.net.api;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class User {
    //-------------fields-------------
    private String name;
    private String password;
    private ConcurrentHashMap<String, Topic> topicsOfUser;
    private Integer conID;
    private boolean connected = false;

    //---------constructors-----------


    public User(String name, String password, int conID) {
        this.name = name;
        this.password = password;
        this.conID = conID;
        this.topicsOfUser = new ConcurrentHashMap<String, Topic>();
    }

    public void subscribeGenre (String subscriptionID , Topic topic){
        this.topicsOfUser.put(subscriptionID, topic);
    }

    public void unsubscribeGenre (String subscriptionID){
        this.topicsOfUser.remove(subscriptionID);
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
        // Remove the user from all genre lists]
        for (Topic topic: this.topicsOfUser.values()) {
            DataStructure.topics.get(topic.getTopic()).removeUser(this);
        }
        topicsOfUser.clear();
    }

    public String getSubscription(String topic){
        Iterator it = this.topicsOfUser.entrySet().iterator();
        while (it.hasNext()) {
            Map.Entry pair = (Map.Entry)it.next();
            System.out.println(pair.getValue().toString());
            Topic t = (Topic)pair.getValue();
            if (t.getTopic().equals(topic))
                return (String) pair.getKey();
        }
        return null;
    }

    public Topic getTopicBySubscription(String subscriptionID){
        return this.topicsOfUser.get(subscriptionID);
    }

    public Integer getConID() {
        return conID;
    }

    public void setConID(Integer conID) {
        this.conID = conID;
    }
}
