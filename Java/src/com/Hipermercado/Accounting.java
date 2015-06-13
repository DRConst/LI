package com.Hipermercado;


import java.io.Serializable;
import java.util.ArrayList;

/**
 * Accounting Class
 *
 * @author Diogo
 * @since 09/06/2015
 */
public class Accounting implements Serializable {
    private ArrayList<SalesList> products, clients;


    /**
     * Accounting Constructor, used normally
     */
    public Accounting() {
        products = new ArrayList<>(12);
        clients = new ArrayList<>(12);

        for (int i = 0; i < 12; i++) {
            this.products.add(new SalesList());
            this.clients.add(new SalesList());
        }

    }

    /**
     * Accounting Constructor, used for clone
     *
     * @param acc to be cloned
     */
    public Accounting(Accounting acc) {
        products = new ArrayList<>(acc.getProducts());
        clients = new ArrayList<>(acc.getClients());
    }


    /**
     * registerSale Method, inserts sale in it's correct month SalesList
     *
     * @param sale to be inserted
     */
    public void registerSale(Sale sale) {
        int idx = sale.getMonth() - 1;


        products.get(idx).registerSale(sale, sale.getProduct().getCode());
        clients.get(idx).registerSale(sale, sale.getClient().getCode());

    }

    /**
     * Processes Accounting Strucuture and Sorts it, down to the MetaSales
     */
    public void sortAcc() {
        for (int i = 0; i < 12; i++) {

            products.get(i).sortSales();
            clients.get(i).sortSales();

        }

    }

    /**
     * Returns Nº Unique Clients in the Specified Month
     *
     * @param month
     * @return Nº Unique Clients
     */
    public int getNDiffClientsByMonth(int month) {
        return this.clients.get(month - 1).getNDiff();
    }

    /**
     * Returns Nº Unique Products in the Specified Month
     *
     * @param month
     * @return Nº Unique Products
     */
    public int getNDiffProductsByMonth(int month) {
        return this.products.get(month - 1).getNDiff();
    }

    /**
     * Returns Nº Sales in the Specified Month
     *
     * @param month
     * @return Nº Sales
     */
    public int getNSalesByMonth(int month) {
        int res = this.products.get(month - 1).getTotalN();

        res += this.clients.get(month - 1).getTotalN();

        return res;
    }

    /**
     * Returns SalesLists from the entire year, in relation to Products
     *
     * @return SalesLists for entire year
     */
    public ArrayList<SalesList> getProducts() {
        ArrayList<SalesList> prods = new ArrayList<>();

        for (int i = 0; i < 12; i++)
            prods.add(products.get(i).clone());

        return prods;
    }

    /**
     * Returns SalesLists from the entire Year, in relation to Clients
     *
     * @return SalesLists for the entire year
     */
    public ArrayList<SalesList> getClients() {
        ArrayList<SalesList> clis = new ArrayList<>();

        for (int i = 0; i < 12; i++)
            clis.add(clients.get(i).clone());

        return clis;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Accounting that = (Accounting) o;

        for (int i = 0; i < 12; i++)
            if (!products.get(i).equals(that.getProducts().get(i)) ||
                    !clients.get(i).equals(that.getClients().get(i)))
                return false;

        return true;

    }

    @Override
    public int hashCode() {
        int result = products.hashCode();
        result = 31 * result + clients.hashCode();
        return result;
    }

    @Override
    public Accounting clone() {
        return new Accounting(this);
    }
}
