package com.GestHiper;

/**
 *  Client Class
 *  @author     Diogo
 *  @since      03/06/2015
 */
public class Client {

    String code;

    Client(){ this.code = ""; }

    Client(String code)
    {
        this.code = code;
    }

    Client(Client c)
    {
        this.code = c.getCode();
    }


    /**
     * Retrieves Client Code
     * @return Client Code
     */
    public String getCode() {
        return code;
    }


    /**
     * Clones current Client instance, making use of Constructor
     * @return New Client Instance
     */
    public Client clone()
    {
        return new Client(this);
    }


    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Client client = (Client) o;

        return code.equals(client.getCode());

    }


    @Override
    public int hashCode() {
        return code.hashCode();
    }

    @Override
    public String toString() { return code; }
}
