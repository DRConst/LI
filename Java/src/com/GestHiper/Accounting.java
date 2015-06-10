package com.GestHiper;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

/**
 * Created by Diogo on 09/06/2015.
 */
public class Accounting {

    private HashMap<String, AccountingStats> stats;
    private AccountingStats global;

    public void registerSale(Sale sale){
        String clientCode = sale.getClient().getCode();
        String productCode = sale.getProduct().getCode();
        AccountingStats clientStats = stats.get(clientCode);
        AccountingStats productStats = stats.get(productCode);

        if(clientStats == null)
        {
            clientStats = this.stats.put(clientCode, new AccountingStats(clientCode));
        }

        if(productStats == null)
        {
            productStats = this.stats.put(productCode, new AccountingStats(productCode));
        }

        clientStats.registerSale(sale);

        productStats.registerSale(sale);

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
        double[] profits = global.getProfit();

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


    public Accounting()
    {
        this.stats = new HashMap<>();
    }

    public Accounting(Map<String, AccountingStats> map)
    {
        this.stats = new HashMap<>(map);
    }

    public HashMap<String, AccountingStats> getStats() {
        HashMap<String, AccountingStats> toRet = new HashMap<>();

        for(AccountingStats stats : this.stats.values())
        {
            toRet.put(stats.getName(), stats);
        }

        return toRet;
    }

    public void setStats(HashMap<String, AccountingStats> stats) {
        this.stats = stats;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Accounting that = (Accounting) o;

        return getStats().equals(that.getStats());

    }

    @Override
    public int hashCode() {
        return getStats().hashCode();
    }

    @Override
    public String toString() {
        final StringBuilder sb = new StringBuilder("Accounting{");
        sb.append("stats=").append(stats);
        sb.append('}');
        return sb.toString();
    }
}
