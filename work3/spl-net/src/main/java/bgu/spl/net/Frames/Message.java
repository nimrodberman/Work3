package bgu.spl.net.Frames;

import java.nio.charset.StandardCharsets;

public class Message extends ServerToClientFrames {

    private int subscription;
    private static int counter = 1;
    private int msgID;
    String des;
    String body;


    public Message(int subscription, String des, String body) {
        this.subscription = subscription;
        this.des = des;
        this.body = body;
        this.msgID = counter;
        counter++;
    }

    @Override
    public byte[] encode() {
        String command = "MESSAGE\n";
        String id = "id:" + this.subscription +"\n";
        String msg_id = "Message-id:" + Integer.toString(msgID) + "\n";
        String gap  = "\n\n";
        String end = "\0";
        return  (command + id + msg_id + des + gap + end).getBytes(StandardCharsets.UTF_8);
    }
}
