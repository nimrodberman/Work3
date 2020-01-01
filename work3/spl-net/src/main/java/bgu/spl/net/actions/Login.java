package bgu.spl.net.actions;

import bgu.spl.net.impl.rci.Command;

import java.io.Serializable;

public class Login implements Command {
    private String userName;
    private String passWord;

    public Login(String userName, String passWord) {
        this.userName = userName;
        this.passWord = passWord;
    }

    @Override
    public Serializable execute(Object arg) {

        // Socket error

        // if the user is not exist



        //if the user exist

        //if wrong password





        return null;
    }
}
