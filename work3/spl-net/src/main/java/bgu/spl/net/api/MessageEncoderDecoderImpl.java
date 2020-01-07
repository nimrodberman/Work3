package bgu.spl.net.api;

import bgu.spl.net.Frames.Connected;
import bgu.spl.net.Frames.ErrorFrame;
import bgu.spl.net.Frames.Message;
import bgu.spl.net.Frames.Receipt;

import java.nio.charset.StandardCharsets;
import java.util.Arrays;

public class MessageEncoderDecoderImpl implements MessageEncoderDecoder {
    private byte[] bytes = new byte[1 << 10]; //start with 1k
    private int len = 0;


    @Override
    public Object decodeNextByte(byte nextByte){


        if(nextByte == '\0'){
            return popString();
        }
        pushByte(nextByte);


        return null;
    }

    @Override
    public byte[] encode(Object message) {
        return encodeByInstance(message);
    }

    private void pushByte(byte nextByte) {
        if (len >= bytes.length) {
            bytes = Arrays.copyOf(bytes, len * 2);
        }

        bytes[len++] = nextByte;
    }

    private String popString() {
        //notice that we explicitly requesting that the string will be decoded from UTF-8
        //this is not actually required as it is the default encoding in java.
        String result = new String(bytes, 0, len, StandardCharsets.UTF_8);
        len = 0;
        bytes = new byte[1 << 10];
        return result;
    }

    private byte[] encodeByInstance(Object m){

        if(m instanceof Receipt){
            return ((Receipt) m).encode();
        }
        if(m instanceof Message){
            return ((Message) m).encode();
        }
        if(m instanceof ErrorFrame){
            return ((ErrorFrame) m).encode();
        }
        if(m instanceof Connected){
            return ((Connected) m).encode();
        }
        return new byte[0];
    }
}
