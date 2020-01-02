package bgu.spl.net.srv;

import java.util.concurrent.ConcurrentHashMap;

public class ConnectionsImpl implements Connections<String> {
    private ConcurrentHashMap<Integer,ConnectionHandler> connections = new ConcurrentHashMap<>();
    private Integer con_id = 0;


    @Override
    public boolean send(int connectionId, String msg) {
        if (connections.containsKey(connectionId)){
            connections.get(connectionId).send(msg);
            return true;
        }
        else{
            return false;
        }
    }

    @Override
    public void send(String channel, String msg) {

    }

    public void addConnection(ConnectionHandler con){
        synchronized (connections){
            connections.put(con_id,con);
            con_id++;
        }
    }

    @Override
    public void disconnect(int connectionId) {
        if(connections.containsKey(connectionId)){
            connections.remove(connectionId);
        }
    }
}
