package com.GestHiper;

/**
 * Created by Diogo on 07/06/2015.
 */
public class ClientAlreadyExistsException extends Exception {

    public ClientAlreadyExistsException()
    {
        super();
    }

    public ClientAlreadyExistsException(String s){ super(s); }
}
