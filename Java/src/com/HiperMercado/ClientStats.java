package com.Hipermercado;

import java.util.ArrayList;

/**
 * Created by Diogo on 13/06/2015.
 */
public class ClientStats {

    double yearlyBill;
    ArrayList<Integer> salesCount;
    ArrayList<Integer> uniqueCount;
    ArrayList<Double> bill;

    public ClientStats(double yearlyBill, ArrayList<Integer> salesCount, ArrayList<Integer> uniqueCount, ArrayList<Double> bill) {
        this.yearlyBill = yearlyBill;
        this.salesCount = salesCount;
        this.uniqueCount = uniqueCount;
        this.bill = bill;
    }

    public ClientStats() {
        salesCount = new ArrayList<>();
        uniqueCount = new ArrayList<>();
        bill = new ArrayList<>();
    }

    public ArrayList<Double> getBill() {
        return bill;
    }

    public void setBill(ArrayList<Double> bill) {
        this.bill = bill;
    }

    public ArrayList<Integer> getSalesCount() {
        return salesCount;
    }

    public void setSalesCount(ArrayList<Integer> salesCount) {
        this.salesCount = salesCount;
    }

    public void setSalesCountMonth(int cnt, int month)
    {
        salesCount.add(month - 1, cnt);
    }

    public double getYearlyBill() {
        return yearlyBill;
    }

    public void setYearlyBill(double yearlyBill) {
        this.yearlyBill = yearlyBill;
    }

    public ArrayList<Integer> getUniqueCount() {
        return uniqueCount;
    }

    public void setUniqueCount(ArrayList<Integer> uniqueCount) {
        this.uniqueCount = uniqueCount;
    }
}
