package com.GestHiper;

import java.util.Map;
import java.util.TreeMap;
import java.util.TreeSet;

/**
 * Created by Diogo on 09/06/2015.
 */
public class Sales {
    private TreeMap<String, MonthlySales > salesMeta;		// Ordered desc by nSales( totalP + totalN )
    private TreeSet<MonthlySales> orderedSet;


    public void registerSale(Sale sale)
    {
        String productCode = sale.getProduct().getCode();
        String clientCode = sale.getClient().getCode();
        MonthlySales productSales = salesMeta.get(productCode);
        MonthlySales clientSales = salesMeta.get(clientCode);

        if(productSales == null)
        {
            productSales = salesMeta.put(productCode, new MonthlySales());
        }

        if(clientSales == null)
        {
            clientSales = salesMeta.put(clientCode, new MonthlySales());
        }

        productSales.registerSale(sale);
        clientSales.registerSale(sale);
    }


    public void orderSales()
    {
        orderedSet = new TreeSet<>(/*Comparator*/);

        orderedSet.addAll(salesMeta.values());
    }





    public Sales()
    {
        this.salesMeta  = new TreeMap<>();
    }

    public Sales(Map<String, MonthlySales> map)
    {
        this.salesMeta = new TreeMap<>(map);
    }

    public TreeMap<String, MonthlySales> getSalesMeta() {
        TreeMap<String, MonthlySales> toRet = new TreeMap<>();

        for(Map.Entry<String, MonthlySales> entry : this.salesMeta.entrySet())
        {
            toRet.put(entry.getKey(), entry.getValue().clone());
        }

        return toRet;
    }

    public void setSalesMeta(TreeMap<String, MonthlySales> salesMeta) {
        this.salesMeta = salesMeta;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Sales sales = (Sales) o;

        return salesMeta.equals(sales.getSalesMeta());

    }

    @Override
    public int hashCode() {
        return salesMeta.hashCode();
    }

    @Override
    public String toString() {
        final StringBuilder sb = new StringBuilder("Sales{");
        sb.append("salesMeta=").append(salesMeta);
        sb.append('}');
        return sb.toString();
    }
}