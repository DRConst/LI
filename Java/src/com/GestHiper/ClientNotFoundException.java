package com.Hipermercado;

/**
 *  Exception for Client - Not Found
 *  @author     Diogo
 *  @since      07/06/2015
 */
public class ClientNotFoundException extends Exception {

    public ClientNotFoundException()
    {
        super();
    }

    public ClientNotFoundException(String s){ super(s); }
}
