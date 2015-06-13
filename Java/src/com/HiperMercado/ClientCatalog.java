package com.Hipermercado;

import java.io.Serializable;
import java.util.HashMap;
import java.util.Map;

/**
 * Client Catalog Class
 *
 * @author Diogo
 * @since 03/06/2015
 */
public class ClientCatalog implements Serializable {
    private HashMap<String, Client> clientCatalog;


    /**
     * ClientCatalog Constructor, inits empty catalog
     */
    ClientCatalog() {
        this.clientCatalog = new HashMap<>();
    }

    /**
     * ClientCatalog Constructor, clones given catalog
     *
     * @param cCat
     */
    ClientCatalog(ClientCatalog cCat) {
        this.clientCatalog = new HashMap<>(cCat.getClientCount());

        for (Client cli : cCat.getClientCatalog().values()) {
            this.clientCatalog.put(cli.getCode(), cli);
        }
    }


    /**
     * Retrieves new Map instance with catalog data
     *
     * @return ClientCatalog primary structure
     */
    public Map<String, Client> getClientCatalog() {

        HashMap<String, Client> toRet = new HashMap<>();

        for (Client cli : this.clientCatalog.values()) {
            this.clientCatalog.put(cli.getCode(), cli.clone());
        }

        return toRet;
    }


    /**
     * Returns nº clients in catalog
     *
     * @return Nº Clients
     */
    public int getClientCount() {
        return clientCatalog.size();
    }


    /**
     * Checks for existence of provided code in catalog
     *
     * @param code Client Code
     * @return True, False - Existence of code
     */
    public boolean existsClient(String code) {
        return this.clientCatalog.containsKey(code);
    }


    /**
     * Gets ClientInstance associated with provided code
     *
     * @param code Client Code
     * @return New Client instance associated with provided code
     * @throws ClientNotFoundException On Invalid code
     */
    public Client getClient(String code) throws ClientNotFoundException {
        Client p = this.clientCatalog.get(code);
        if (p != null)
            return p.clone();
        else {
            throw new ClientNotFoundException("com.HiperMercado.Client " + p.getCode() + " Not Found.");
        }
    }


    /**
     * Inserts new Client into Catalog
     *
     * @param p New Client to be inserted
     * @throws ClientAlreadyExistsException On Attempting to insert an already existent Client
     */
    public void insertClient(Client p) throws ClientAlreadyExistsException {
        if (this.clientCatalog.put(p.getCode(), p) != null)
            throw new ClientAlreadyExistsException("com.HiperMercado.Client " + p.getCode() + " Already In Catalog.");
    }


    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();

        for (Client cli : clientCatalog.values())
            sb.append(cli.toString() + "\n");

        return sb.toString();
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        ClientCatalog that = (ClientCatalog) o;

        return getClientCatalog().equals(that.getClientCatalog());

    }

    @Override
    public int hashCode() {
        return getClientCatalog().hashCode();
    }

    @Override
    public ClientCatalog clone() {
        return new ClientCatalog(this);
    }
}
