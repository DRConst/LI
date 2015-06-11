package com.Hipermercado;


import java.io.Serializable;

/**
 * Hipermercado Class
 *  Holds all relevant classes such as
 *      ProductCatalog, ClientCatalog
 *      Accounting, Sales
 *  And their auxiliary classes.
 *
 * @author Pedro
 * @since 11/06/2015
 */
public class Hipermercado implements Serializable {
    private ProductCatalog productCat;
    private ClientCatalog clientCatalog;
    private Accounting acc;
    private Sales sales;

    public Hipermercado()
    {
        productCat = new ProductCatalog();
        clientCatalog = new ClientCatalog();
        acc = new Accounting();
        sales = new Sales();
    }

    public Hipermercado( Hipermercado h )
    {
        productCat = new ProductCatalog( h.getProductCat() );
        clientCatalog = new ClientCatalog( h.getClientCatalog() );
        /*
            missing Accounting init
            missing Sales init
         */
    }

    public void registerProduct( String code ) throws ProductAlreadyExistsException
    {
        Product prod = new Product( code );

        productCat.insertProduct( prod );

    }

    public ProductCatalog getProductCat() {
        return productCat;
    }

    public void setProductCat(ProductCatalog productCat) {
        this.productCat = productCat;
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
}
