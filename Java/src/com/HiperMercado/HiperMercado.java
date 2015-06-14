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
     * Checks for existence of given code in ClientCatalog
     * @param code
     * @return true,false
     */
    public boolean existsClient(String code) {
        return clientCatalog.existsClient( code );
    }

    /**
     * Checks for existence of given code in ProductCatalog
     * @param code
     * @return
     */
    public boolean existsProduct( String code ) {
        return productCatalog.existsProduct( code );
    }

    /**
     * Returns ArrayList containing Unique Sales for specified code
     * @param code Client
     * @return # Sales per Month
     * @throws ClientNotFoundException
     */
    public ArrayList<Integer> getClientNSalesYearly( String code ) throws ClientNotFoundException {
        ArrayList<Integer> toRet;


        if( !clientCatalog.existsClient( code ) )
            throw new ClientNotFoundException();

        toRet = acc.getClientMonthlyCount( code );

        return toRet;
    }

    /**
     * Returns ArrayList containing Unique Sales for specified code
     * @param code Product
     * @return # Sales per Month
     * @throws ProductNotFoundException
     */
    public ArrayList<Integer> getProductNSalesYearly( String code ) throws ProductNotFoundException {
        ArrayList<Integer> toRet;


        if( !productCatalog.existsProduct(code) )
            throw new ProductNotFoundException();

        toRet = acc.getProductMonthlyCount(code);

        return toRet;
    }

    /**
     * Returns ArrayList containing Unique Products for specified code
     * @param code Client
     * @return # Unique Products bought by specified client, per month
     * @throws ClientNotFoundException
     * @throws SalesNotFoundException
     */
    public ArrayList<Integer> getClientNUniqueProducts( String code ) throws ClientNotFoundException,SalesNotFoundException {
        ArrayList<Integer> toRet;
        Client cli;


        try {
            cli = clientCatalog.getClient( code );
            toRet = sales.getUniqueClientPurchases( cli );

        }catch( ClientNotFoundException | SalesNotFoundException e ) {
            throw e;
        }


        return toRet;
    }

    /**
     * Returns ArrayList containing Unique Clients for specified code
     * @param code Product
     * @return # Unique Clients that bought the specified Product, per month
     * @throws ProductNotFoundException
     * @throws SalesNotFoundException
     */
    public ArrayList<Integer> getProductNUniqueProducts( String code ) throws ProductNotFoundException,SalesNotFoundException {
        ArrayList<Integer> toRet;
        Product prod;


        try {
            prod = productCatalog.getProduct(code);
            toRet = sales.getUniqueProductPurchases(prod);

        }catch( ProductNotFoundException | SalesNotFoundException e ) {
            throw e;
        }


        return toRet;
    }

    /**
     * Get Client Expenses Yearly
     * @param code code
     * @return Expenses per Month
     * @throws ClientNotFoundException
     */
    public ArrayList<Double> getClientExpenses( String code ) throws ClientNotFoundException {
        ArrayList<Double> toRet = new ArrayList<>(12);
        Client cli;
        MonthlySales m;

        cli = clientCatalog.getClient( code );

        if( cli == null )
            throw new ClientNotFoundException();

        m = sales.getMonthlyCli( cli );

        for(int i=0;i<12;i++) {
            SalesList temp = m.getMonthly().get(i);
            toRet.add( temp.getTotal$N() + temp.getTotal$P() );
        }


        return toRet;
    }

    /**
     * Get Product Expenses Yearly
     * @param code code
     * @return Expenses per Month
     * @throws ProductNotFoundException
     */
    public ArrayList<Double> getProductExpenses( String code ) throws ProductNotFoundException {
        ArrayList<Double> toRet = new ArrayList<>(12);
        Product prod;
        MonthlySales m;

        prod = productCatalog.getProduct(code);

        if( prod == null )
            throw new ProductNotFoundException();

        m = sales.getMonthlyProd(prod);

        for(int i=0;i<12;i++) {
            SalesList temp = m.getMonthly().get(i);
            toRet.add( temp.getTotal$N() + temp.getTotal$P() );
        }


        return toRet;
    }

    public ArrayList<SalesList> getProductMonthlyStats( String code) throws ProductNotFoundException {
        Product prod;

        prod = productCatalog.getProduct( code );

        if( prod == null )
            throw new ProductNotFoundException();

        return sales.getMonthlyProd( prod ).getMonthly();
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

    public int getNSalesPerMonth( int month ) {
        return acc.getNSalesByMonth( month );
    }

    public int getNDiffClientsPerMonth( int month ) {
        return acc.getNDiffClientsByMonth( month );
    }

    public int getNDiffProductsPerMonth( int month ) {
        return acc.getNDiffProductsByMonth( month );
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