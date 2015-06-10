package com.GestHiper;

import sun.reflect.generics.tree.Tree;

import java.util.ArrayList;
import java.util.SortedSet;
import java.util.TreeSet;

/**
 * Created by Diogo on 10/06/2015.
 */
public class SalesList {

    private int totalP;		// sum of all months's MetaSales nTypeP
    private int totalN;		//	...

    private double total$P;	//	...
    private double total$N;	//	...

    private int totalAmount;	// sum of all months's MetaSales's amounts

    private TreeSet<Sale> sales; //SortedSet is abstact

    public SalesList()
    {
        this.sales = new TreeSet<>();
    }

    public SalesList(int totalP, int totalN, double total$P, double total$N, int totalAmount, TreeSet<Sale> sales) {
        this.totalP = totalP;
        this.totalN = totalN;
        this.total$P = total$P;
        this.total$N = total$N;
        this.totalAmount = totalAmount;
        this.sales = sales;
    }

    public SalesList(SalesList salesList)
    {
        this.totalP = salesList.getTotalP();
        this.totalN = salesList.getTotalN();
        this.total$P = salesList.getTotal$P();
        this.total$N = salesList.getTotal$N();
        this.totalAmount = salesList.getTotalAmount();
        this.sales = salesList.getSales();
    }

    public int getTotalP() {
        return totalP;
    }

    public void setTotalP(int totalP) {
        this.totalP = totalP;
    }

    public int getTotalN() {
        return totalN;
    }

    public void setTotalN(int totalN) {
        this.totalN = totalN;
    }

    public double getTotal$P() {
        return total$P;
    }

    public void setTotal$P(double total$P) {
        this.total$P = total$P;
    }

    public double getTotal$N() {
        return total$N;
    }

    public void setTotal$N(double total$N) {
        this.total$N = total$N;
    }

    public int getTotalAmount() {
        return totalAmount;
    }

    public void setTotalAmount(int totalAmount) {
        this.totalAmount = totalAmount;
    }

    public TreeSet<Sale> getSales() {
        TreeSet<Sale> toRet = new TreeSet<>();

        for(Sale s : this.sales)
        {
            toRet.add(s.clone());
        }

        return toRet;
    }

    public void setSales(TreeSet<Sale> sales) {
        this.sales = sales;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        SalesList salesList = (SalesList) o;

        if (totalP != salesList.totalP) return false;
        if (totalN != salesList.totalN) return false;
        if (Double.compare(salesList.total$P, total$P) != 0) return false;
        if (Double.compare(salesList.total$N, total$N) != 0) return false;
        if (totalAmount != salesList.totalAmount) return false;
        return sales.equals(salesList.sales);

    }

    @Override
    public int hashCode() {
        int result;
        long temp;
        result = totalP;
        result = 31 * result + totalN;
        temp = Double.doubleToLongBits(total$P);
        result = 31 * result + (int) (temp ^ (temp >>> 32));
        temp = Double.doubleToLongBits(total$N);
        result = 31 * result + (int) (temp ^ (temp >>> 32));
        result = 31 * result + totalAmount;
        result = 31 * result + sales.hashCode();
        return result;
    }

    public SalesList clone()
    {
        return new SalesList(this);
    }
}
