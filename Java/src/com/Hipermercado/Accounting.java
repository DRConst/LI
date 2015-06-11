package com.Hipermercado;


import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.TreeMap;

/**
 * Created by Diogo on 09/06/2015.
 */
public class Accounting {

    private TreeMap<Client, AccountingStats> clientStats = null;
    private TreeMap<Product, AccountingStats> productStats;
    private AccountingStats global;

    public void registerSale(Sale sale){
        String clientCode = sale.getClient().getCode();
        String productCode = sale.getProduct().getCode();
        AccountingStats clientStat = this.clientStats.get(sale.getClient());
        AccountingStats productStat = this.productStats.get(sale.getProduct());

        if(clientStats == null)
        {
            this.clientStats.put(sale.getClient(), new AccountingStats(clientCode));
            clientStat = this.clientStats.get(sale.getClient());
        }

        if(productStats == null)
        {
            this.productStats.put(sale.getProduct(), new AccountingStats(productCode));
            productStat = this.productStats.get(sale.getProduct());
        }

        clientStat.registerSale(sale);

        productStat.registerSale(sale);

        global.registerSale(sale);
    }



    public ArrayList<Integer> getMonthlySales()
    {
        int[] cntSalesN = global.getCntSalesN();
        int[] cntSalesP = global.getCntSalesP();

        ArrayList<Integer> toRet = new ArrayList<>(12);

        for(int i = 0; i < 12; i++)
        {
            toRet.add(cntSalesN[i] + cntSalesP[i]);
        }

        return toRet;
    }

    public double getTotalProfit()
    {
        double toRet = 0;
        double[] profits = global.getProfitP();

        for(double d : profits)
            toRet += d;

        return toRet;
    }

    public int getTotalUnits()
    {
        int toRet = 0;
        int[] profits = global.getUnits();

        for(int i : profits)
            toRet += i;

        return toRet;
    }

    public int getTotalNSales()
    {
        ArrayList<Integer> monthly = getMonthlySales();
        int total = 0;

        for( Integer m : monthly )
            total += m;

        return total;
    }


    public Accounting()
    {
        this.clientStats = new TreeMap<>();
        this.productStats = new TreeMap<>();
    }

    public Accounting(Map<Client, AccountingStats> clientMap, Map<Product, AccountingStats> productMap)
    {
        this.clientStats = new TreeMap<>(clientMap);
        this.productStats = new TreeMap<>(productMap);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Accounting that = (Accounting) o;

        if (!clientStats.equals(that.clientStats)) return false;
        if (!productStats.equals(that.productStats)) return false;
        return global.equals(that.global);

    }

    @Override
    public int hashCode() {
        int result = clientStats.hashCode();
        result = 31 * result + productStats.hashCode();
        result = 31 * result + global.hashCode();
        return result;
    }
}
