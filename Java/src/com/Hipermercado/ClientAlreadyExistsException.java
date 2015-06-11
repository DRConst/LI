package com.Hipermercado;

/**
 *  Exception for Client - Already Exists
 *  @author     Diogo
 *  @since      07/06/2015
 */
public class ClientAlreadyExistsException extends Exception {

    public ClientAlreadyExistsException()
    {
        super();
    }

    public ClientAlreadyExistsException(String s){ super(s); }
}
