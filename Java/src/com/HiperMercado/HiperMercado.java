package com.Hipermercado;


import java.io.Serializable;
import java.util.*;

/**
 * Hipermercado Class
 * Holds all relevant classes such as
 * ProductCatalog, ClientCatalog
 * Accounting, Sales
 * And their auxiliary classes.
 *
 * @author Pedro
 * @since 11/06/2015
 */
public class HiperMercado implements Serializable {
    private ProductCatalog productCatalog;
    private ClientCatalog clientCatalog;
    private Accounting acc;
    private Sales sales;


    /**
     * Hipermercado Constructor, inits empty Hipermercado
     */
    public HiperMercado() {
        productCatalog = new ProductCatalog();
        clientCatalog = new ClientCatalog();
        acc = new Accounting();
        sales = new Sales();
    }

    /**
     * Hipermercado Constructor, clones given Hipermercado
     *
     * @param h
     */
    public HiperMercado(HiperMercado h) {
        productCatalog = new ProductCatalog(h.getProductCatalog());
        clientCatalog = new ClientCatalog(h.getClientCatalog());
        /*
            missing Accounting init
            missing Sales init
         */
    }


    public ProductCatalog getProductCatalog() {
        return productCatalog;
    }

    public void setProductCatalog(ProductCatalog productCatalog) {
        this.productCatalog = productCatalog;
    }

    public ClientCatalog getClientCatalog() {
        return clientCatalog;
    }

    public void setClientCatalog(ClientCatalog clientCatalog) {
        this.clientCatalog = clientCatalog;
    }

    public Sales getSales() {
        return sales;
    }

    public void setSales(Sales sales) {
        this.sales = sales;
    }

    public Accounting getAcc() {
        return acc;
    }

    public void setAcc(Accounting acc) {
        this.acc = acc;
    }


    /**
     * Registers Given Product into ProductCatalog and Sales
     *
     * @param code
     * @throws ProductAlreadyExistsException
     */
    public void registerProduct(String code) throws ProductAlreadyExistsException {
        Product prod = new Product(code);

        productCatalog.insertProduct(prod);

        sales.registerProd(prod);
    }

    /**
     * Registers Given Client into ClientCatalog and Sales
     *
     * @param code
     * @throws ClientAlreadyExistsException
     */
    public void registerClient(String code) throws ClientAlreadyExistsException {
        Client cli = new Client(code);

        clientCatalog.insertClient(cli);

        sales.registerCli(cli);
    }

    /**
     * Query1
     * @return Unbought Products ordered alphabeticaly
     */
    public LinkedList<String> getUnboughtProducts()
    {
        return sales.getUnboughtProducts();
    }

    /**
     * Query2
     * @return Clients without purchases ordered alphabeticaly
     */
    public LinkedList<String> getClientsWithoutPurchases()
    {
        return sales.getClientsWithoutPurchases();
    }

    /**
     * Query4 - Gets statistics pertaining the clients purchases
     *
     * @param code Client's identifier
     * @param month Month
     * @throws ClientNotFoundException
     */
    public ClientStats getMonthlyClientStats(String code, int month) throws ClientNotFoundException, SalesNotFoundException {
        ClientStats clientStats = new ClientStats();
        Client cli = clientCatalog.getClient(code);
        if(cli == null)
            throw new ClientNotFoundException(code + " not found");

        clientStats.setYearlyBill(acc.getClientsYearlyBill(code));

        clientStats.setSalesCount(acc.getClientMonthlyCount(code));

        clientStats.setBill(acc.getClientMonthlyBill(code));

        try {
            clientStats.setUniqueCount(sales.getUniqueClientPurchases(cli));
        } catch (SalesNotFoundException e) {
            throw e;
        }


        return clientStats;
    }

    /**
     * Query4 - Gets statistics pertaining the clients purchases
     *
     * @param code Product's identifier
     * @param month Month
     * @throws ProductNotFoundException
     */
    public ClientStats getMonthlyProductStats(String code, int month) throws ProductNotFoundException, SalesNotFoundException {
        ClientStats clientStats = new ClientStats();
        Product pr = productCatalog.getProduct(code);
        if(pr == null)
            throw new ProductNotFoundException(code + " not found");

        clientStats.setYearlyBill(acc.getProductsYearlyBill(code));

        clientStats.setSalesCount(acc.getProductMonthlyCount(code));

        clientStats.setBill(acc.getProductMonthlyBill(code));

        try {
            clientStats.setUniqueCount(sales.getUniqueProductPurchases(pr));
        } catch (SalesNotFoundException e) {
            throw e;
        }


        return clientStats;
    }

    public TreeSet<String> getMostBoughtProductsForClient(String code) throws ClientNotFoundException {
        try {
            Client cli = clientCatalog.getClient(code);
            return sales.getMostBoughtProductsForClient(cli);
        } catch (ClientNotFoundException e) {
            throw e;
        }
    }

    public YearlySaleStats getYearlyProductStats(String code) throws ProductNotFoundException{
        if(!productCatalog.existsProduct(code))
            throw new ProductNotFoundException(code + "isn't registered");

        return acc.getYearlyProductStats(code);
    }

    public Set<Client> getClientsWithMostPurchases()
    {
        return sales.getSortedSalesCli().keySet();
    }

    /**
     * Registers Given Sale into Sales and Accounting
     *
     * @param s
     * @throws ProductNotFoundException
     * @throws ClientNotFoundException
     */
    public void registerSale(Sale s) throws ProductNotFoundException, ClientNotFoundException {
        acc.registerSale(s);

        sales.registerSale(s);
    }


    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        HiperMercado h = (HiperMercado) o;

        if (!(productCatalog.equals(h.getProductCatalog()))) return false;
        if (!(clientCatalog.equals(h.getClientCatalog()))) return false;
        if (!(sales.equals(h.getSales()))) return false;

        return acc.equals(h.getAcc());

    }

    @Override
    public int hashCode() {
        return (productCatalog.hashCode() + clientCatalog.hashCode() +
                sales.hashCode() + acc.hashCode());
    }

    @Override
    public HiperMercado clone() {
        return new HiperMercado(this);
    }


}
