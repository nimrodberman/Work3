package bgu.spl.net.api;

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
        return new byte[0];
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
}
