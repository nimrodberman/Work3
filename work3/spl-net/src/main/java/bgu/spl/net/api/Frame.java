package bgu.spl.net.api;

import java.util.ArrayList;

public class Frame {
    private String command;
    private ArrayList <Pair> headers;
    private String body;

    public Frame(String command, ArrayList<Pair> headers, String body) {
        this.command = command;
        this.headers = headers;
        this.body = body;
    }

    public String getCommand() {
        return command;
    }

    public ArrayList<Pair> getHeaders() {
        return headers;
    }

    public String getBody() {
        return body;
    }

    public void setCommand(String command) {
        this.command = command;
    }

    public void addHeaders(Pair h) {
        this.headers.add(h);
    }

    public void setBody(String body) {
        this.body = body;
    }
}
