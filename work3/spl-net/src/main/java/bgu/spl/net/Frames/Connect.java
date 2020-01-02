package bgu.spl.net.Frames;

import java.nio.charset.StandardCharsets;

public class Connect extends ServerToClientFrames {

    private String version;

    public Connect(String version){
        this.version = version;
    }

    @Override
    public byte[] encode() {
        String command = "CONNECTED\n";
        String tmp = "version: " + this.version;
        String end = "\n\n\0";
        return  (command + tmp + end).getBytes(StandardCharsets.UTF_8);    }
}
