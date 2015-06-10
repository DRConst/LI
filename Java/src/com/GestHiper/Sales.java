package com.GestHiper;

import java.util.Map;
import java.util.TreeMap;

/**
 * Created by Diogo on 09/06/2015.
 */
public class Sales {
    private TreeMap<Product, MonthlySales > salesMeta;		// Ordered desc by nSales( totalP + totalN )

    public Sales()
    {
        this.salesMeta  = new TreeMap<>();
    }

    public Sales(Map<Product, MonthlySales> map)
    {
        this.salesMeta = new TreeMap<>(map);
    }

    public TreeMap<Product, MonthlySales> getSalesMeta() {
        TreeMap<Product, MonthlySales> toRet = new TreeMap<>();

        for(Map.Entry<Product, MonthlySales> entry : this.salesMeta.entrySet())
        {
            toRet.put(entry.getKey(), entry.getValue().clone());
        }

        return toRet;
    }

    public void setSalesMeta(TreeMap<Product, MonthlySales> salesMeta) {
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