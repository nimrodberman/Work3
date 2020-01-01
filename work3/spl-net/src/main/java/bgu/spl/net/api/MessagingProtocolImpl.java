package bgu.spl.net.api;

import bgu.spl.net.actions.Login;
import bgu.spl.net.srv.Connections;

public class MessagingProtocolImpl implements StompMessagingProtocol {
    @Override
    public void start(int connectionId, Connections<String> connections) {

    }

    @Override
    public void process(STOMP message) {
        String command = message.getCommand();
        switch (command){
            case "CONNECT":
                new Login(message.getHeaders().get(2).getV(),message.getHeaders().get(3).getV()).execute(null);

            case "SUBSCRIBE":



        }

    }

    @Override
    public boolean shouldTerminate() {
        return false;
    }
}
