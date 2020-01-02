package bgu.spl.net.impl.rci;

import bgu.spl.net.api.MessagingProtocol;
import bgu.spl.net.srv.ConnectionsImpl;

import java.io.IOException;
import java.io.Serializable;

public class RemoteCommandInvocationProtocol<T> implements MessagingProtocol<Serializable> {

    private T arg;

    public RemoteCommandInvocationProtocol(T arg) {
        this.arg = arg;
    }

    @Override
    public Serializable process(Serializable msg) throws IOException {
        return ((Command) msg).execute(arg , 1 , new ConnectionsImpl());
    }

    @Override
    public boolean shouldTerminate() {
        return false;
    }

}
