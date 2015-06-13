package com.Hipermercado;


import java.io.Serializable;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.TreeMap;
import java.util.TreeSet;

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

    public double getClientsYearlyBill(String code)
    {
        double toRet = 0;

        for(SalesList salesList : clients)
        {
            try {
                MetaSale s = salesList.getMetaSale(code);
                toRet +=  s.getTotal$P() + s.getTotal$N();
            } catch (SalesNotFoundException e) {
                //Client has no purchases that month
            }
        }
        return toRet;
    }

    public double getProductsYearlyBill(String code)
    {
        double toRet = 0;

        for(SalesList salesList : products)
        {
            try {
                MetaSale s = salesList.getMetaSale(code);
                toRet +=  s.getTotal$P() + s.getTotal$N();
            } catch (SalesNotFoundException e) {
                //Product has no purchases that month
            }
        }
        return toRet;
    }

    public ArrayList<Integer> getClientMonthlyCount(String code)
    {
        ArrayList<Integer> toRet = new ArrayList<>();


        for( int i = 0; i < 12; i++)
        {
            try {
                SalesList salesList = clients.get(i);
                MetaSale s = salesList.getMetaSale(code);
                toRet.add(i, s.getTotalP() + s.getTotalN());
            } catch (SalesNotFoundException e) {
                //Client has no purchases that month
                toRet.add(i, 0);
            }
        }
        return toRet;
    }

    public ArrayList<Integer> getProductMonthlyCount(String code)
    {
        ArrayList<Integer> toRet = new ArrayList<>();


        for( int i = 0; i < 12; i++)
        {
            try {
                SalesList salesList = products.get(i);
                MetaSale s = salesList.getMetaSale(code);
                toRet.add(i, s.getTotalP() + s.getTotalN());
            } catch (SalesNotFoundException e) {
                //Product has no purchases that month
                toRet.add(i, 0);
            }
        }
        return toRet;
    }

    public ArrayList<Double> getClientMonthlyBill(String code)
    {
        ArrayList<Double> toRet = new ArrayList<>();


        for( int i = 0; i < 12; i++)
        {
            try {
                SalesList salesList = clients.get(i);
                MetaSale s = salesList.getMetaSale(code);
                toRet.add(i, s.getTotal$N() + s.getTotal$P());
            } catch (SalesNotFoundException e) {
                //Client has no purchases that month
                toRet.add(i, 0.0);
            }
        }
        return toRet;
    }

    public ArrayList<Double> getProductMonthlyBill(String code)
    {
        ArrayList<Double> toRet = new ArrayList<>();


        for( int i = 0; i < 12; i++)
        {
            try {
                SalesList salesList = products.get(i);
                MetaSale s = salesList.getMetaSale(code);
                toRet.add(i, s.getTotal$N() + s.getTotal$P());
            } catch (SalesNotFoundException e) {
                //Product has no purchases that month
                toRet.add(i, 0.0);
            }
        }
        return toRet;
    }

    public YearlySaleStats getYearlyProductStats(String code) {

        YearlySaleStats toRet = new YearlySaleStats();

        for(int i = 0; i < 12; i++)
        {
            MonthSaleStats monthSaleStats = new MonthSaleStats();
            SalesList salesList = products.get(i);
            try {
                MetaSale metaSale = salesList.getMetaSale(code);
                monthSaleStats.setCntN(metaSale.getTotalN());
                monthSaleStats.setCntP(metaSale.getTotalP());
                monthSaleStats.setProfitN(metaSale.getTotal$N());
                monthSaleStats.setProfitP(metaSale.getTotal$P());
                toRet.setMonthSaleStats(monthSaleStats, i + 1);
            } catch (SalesNotFoundException e) {
                toRet.setMonthSaleStats(new MonthSaleStats(0, 0, 0, 0), i + 1);
            }

        }
        return  toRet;
    }

    public TreeMap<String, MetaSale> getMostBoughtProducts()
    {

        HashMap<String, MetaSale> temp = new HashMap<>();

        for(SalesList salesList : products)
        {
            for(MetaSale metaSale : salesList.getSales().values())
            {
                String key = metaSale.getKey();
                MetaSale tMetaSale;
                if(temp.containsKey(key))
                {
                    tMetaSale = temp.remove(key);
                    tMetaSale.setAmount(tMetaSale.getAmount() + metaSale.getAmount());
                    temp.put(key, tMetaSale);
                }else{
                    temp.put(key, metaSale);
                }
            }
        }
        return new TreeMap<>(new ValueComparator(temp));
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
