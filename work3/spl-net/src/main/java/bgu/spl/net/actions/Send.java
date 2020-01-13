package bgu.spl.net.actions;

import bgu.spl.net.Frames.Message;
import bgu.spl.net.api.DataStructure;
import bgu.spl.net.api.MessagingProtocolImpl;
import bgu.spl.net.impl.rci.Command;
import bgu.spl.net.srv.Connections;

import java.io.IOException;
import java.io.Serializable;

public class Send implements Command {
    private String topic;
    private String body;

    public Send(String topic, String body) {
        this.topic = topic;
        this.body = body;
    }

    @Override
    public Serializable execute(Object arg, Integer connectionId, Connections con) throws IOException {

        con.send(this.topic , new Message(DataStructure.userByConnectionID.get(connectionId).getSubscription(topic),topic,body));
        return null;
    }
}
