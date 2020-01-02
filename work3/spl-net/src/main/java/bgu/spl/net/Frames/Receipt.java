package bgu.spl.net.Frames;

import sun.nio.cs.UTF_8;

import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

public class Receipt extends ServerToClientFrames{
    private String conID;

    public Receipt(int conID) {

        // TODO: understand how to serialize the object and how to decode it
        this.conID = String.valueOf(conID);
    }

    public byte[] encode(){

        String command = "RECIEPT\n";
        String tmp = "receipt-id:" + conID;
        String end = "\n\n\0";
        return  (command + tmp + end).getBytes(StandardCharsets.UTF_8);
    }
}
