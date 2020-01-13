package bgu.spl.net.Frames;


import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

public class Receipt extends ServerToClientFrames{
    private String conID;

    public Receipt(String conID) {


        this.conID = conID;
    }

    public byte[] encode(){

        String command = "RECEIPT\n";
        String tmp = "receipt-id:" + conID;
        String end = "\n\n\0";
        return  (command + tmp + end).getBytes(StandardCharsets.US_ASCII);
    }
}
