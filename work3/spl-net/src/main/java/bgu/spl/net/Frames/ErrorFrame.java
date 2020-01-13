package bgu.spl.net.Frames;

import java.nio.charset.StandardCharsets;

public class ErrorFrame extends ServerToClientFrames {

    private String error;
    private String body;
    private String reciptID;

    public ErrorFrame(String error, String body , String mID) {
        this.error = "message: " + error +"\n\n";
        this.body = body;
        this.reciptID = mID;
    }

    public byte[] encode(){

        String command = "ERROR\n";
        String tmp = "receipt-id:" + this.reciptID +"\n";
        String end = "\0";
        return  (command + tmp + error  + body + end).getBytes(StandardCharsets.US_ASCII);
    }
}
