package com.GestHiper;

/**
 * Created by Diogo on 03/06/2015.
 */
public class Client {

    String code;

    Client(){ }

    Client(String code)
    {
        this.code = code;
    }

    Client(Client c)
    {
        this.code = c.getCode();
    }

    public String getCode() {
        return code;
    }

    public Client clone()
    {
        return new Client(this);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Client client = (Client) o;

        return code.equals(client.code);

    }

    @Override
    public int hashCode() {
        return code.hashCode();
    }
}
