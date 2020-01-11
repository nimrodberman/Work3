package bgu.spl.net.impl.newsfeed;

import bgu.spl.net.impl.rci.Command;
import bgu.spl.net.srv.Connections;

import java.io.IOException;
import java.io.Serializable;

public class FetchNewsCommand implements Command<NewsFeed> {

    private String channel;

    public FetchNewsCommand(String channel) {
        this.channel = channel;
    }


    @Override
    public Serializable execute(NewsFeed arg, Integer connectionId, Connections con) throws IOException {
        return null;
    }
}
