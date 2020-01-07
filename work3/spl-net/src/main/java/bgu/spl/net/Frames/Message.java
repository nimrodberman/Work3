package bgu.spl.net.Frames;

import java.nio.charset.StandardCharsets;

public class Message extends ServerToClientFrames {

    private String subscriptionID;
    private static int counter = 1;
    private int msgID;
    private String topic;
    String body;


    public Message(String subscription, String des, String body) {
        this.subscriptionID = subscription;
        this.topic = des;
        this.body = body;
        this.msgID = counter;
        counter++;
    }

    @Override
    public byte[] encode() {
        String command = "MESSAGE\n";
        String id = "id:" + this.subscriptionID +"\n";
        String msg_id = "Message-id:" + msgID + "\n";
        String gap  = "\n\n";
        String end = "\0";
        return  (command + id + msg_id + this.topic + gap + end).getBytes(StandardCharsets.UTF_8);
    }
}
