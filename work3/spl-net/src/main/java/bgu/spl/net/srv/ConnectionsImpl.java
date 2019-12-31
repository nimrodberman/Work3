package bgu.spl.net.srv;

import java.util.concurrent.ConcurrentHashMap;

public class ConnectionsImpl implements Connections {
    private ConcurrentHashMap<Integer,ConnectionHandler> connections = new ConcurrentHashMap<>();
    private Integer con_id = 0;


    @Override
    public boolean send(int connectionId, Object msg) {
        if (connections.containsKey(connectionId)){
            connections.get(connectionId).send(msg);
            return true;
        }
        else{
            return false;
        }

    }

    @Override
    public void send(String channel, Object msg) {

    }

    @Override
    public void disconnect(int connectionId) {
        if(connections.containsKey(connectionId)){
            connections.remove(connectionId);
        }
    }
}
