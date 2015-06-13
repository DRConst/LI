package com.Hipermercado;


import java.io.Serializable;

/**
 * HiperMercado Class
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
     * HiperMercado Constructor, inits empty HiperMercado
     */
    public HiperMercado() {
        productCatalog = new ProductCatalog();
        clientCatalog = new ClientCatalog();
        acc = new Accounting();
        sales = new Sales();
    }

    /**
     * HiperMercado Constructor, clones given HiperMercado
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
