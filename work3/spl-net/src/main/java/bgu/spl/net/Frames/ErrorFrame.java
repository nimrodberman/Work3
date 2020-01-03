package bgu.spl.net.Frames;

import java.nio.charset.StandardCharsets;

public class ErrorFrame extends ServerToClientFrames {

    private String error;
    private String body;
    private String mID;

    public ErrorFrame(String error, String body , String mID) {
        this.error = "message: " + error +"\n\n";
        this.body = body;
        this.mID = mID;
    }

    public byte[] encode(){

        String command = "ERROR\n";
        String tmp = "receipt-id:" + this.mID +"\n";
        String end = "\0";
        return  (command + tmp + error + "\n\n" + body + end).getBytes(StandardCharsets.UTF_8); //TODO: understand how to fucking do it
    }
}
