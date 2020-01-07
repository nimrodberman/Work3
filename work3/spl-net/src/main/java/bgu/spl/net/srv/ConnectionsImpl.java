package bgu.spl.net.srv;

import bgu.spl.net.api.DataStructure;
import bgu.spl.net.api.User;

import java.io.IOException;
import java.util.concurrent.ConcurrentHashMap;

public class ConnectionsImpl<T> implements Connections<T> {
    private ConcurrentHashMap<Integer,ConnectionHandler> connections = new ConcurrentHashMap<>();
    private Integer con_id = 0;


    @Override
    public boolean send(int connectionId, T msg) throws IOException {
        if (connections.containsKey(connectionId)){
            connections.get(connectionId).send(msg);
            return true;
        }
        else{
            return false;
        }
    }

    @Override
    public void send(String channel, T msg) throws IOException {
        for (User u: DataStructure.topics.get(channel).getUsers()) {
            send(u.getConID(), msg);
        }

    }

    public void addConnection(ConnectionHandler con){
        synchronized (connections){
            connections.put(con_id,con);
            con_id++;
        }
    }

    // TODO: think if we need to add remove connection

    @Override
    public void disconnect(int connectionId) {
        if(connections.containsKey(connectionId)){
            connections.remove(connectionId);
        }
    }
}
