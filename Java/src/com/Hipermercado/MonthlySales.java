package com.Hipermercado;

import java.util.ArrayList;

/**
 * MonthlySales Class, used by Sales Class
 *
 * @author Diogo
 * @since 09/06/2015
 */
public class MonthlySales implements Comparable<MonthlySales> {
    private ArrayList<SalesList> monthly;

    private String key;     // Parent key, used for alpha order
    private int totalP;        // sum of all months's MetaSales nTypeP
    private int totalN;        //	...
    private double total$P;    //	...
    private double total$N;    //	...
    private int totalAmount;    // sum of all months's MetaSales's amounts


    /**
     * MonthlySales Constructor, inits empty MonthlySales
     */
    public MonthlySales() {

        for (int i = 0; i < 12; i++)
            monthly.add(new SalesList());

        this.key = "";
        this.totalP = 0;
        this.totalN = 0;
        this.totalAmount = 0;
        this.total$P = 0.0;
        this.total$N = 0.0;
    }

    /**
     * MonthlySales Constructor, inits with given key
     *
     * @param key
     */
    public MonthlySales(String key) {

        for (int i = 0; i < 12; i++)
            monthly.add(new SalesList());

        this.key = key;
        this.totalP = 0;
        this.totalN = 0;
        this.totalAmount = 0;
        this.total$P = 0.0;
        this.total$N = 0.0;
    }

    /**
     * MonthlySales Constructor, clones given MonthlySales
     *
     * @param sales
     */
    public MonthlySales(MonthlySales sales) {
        this.monthly = sales.getMonthly();
        this.totalP = sales.getTotalP();
        this.totalN = sales.getTotalN();
        this.total$P = sales.getTotal$P();
        this.total$N = sales.getTotal$N();
        this.totalAmount = sales.getTotalAmount();
        this.key = sales.getKey();
    }


    /**
     * Registers Given Sale in MonthlySales
     *
     * @param sale  Given Sale
     * @param child Subject of Sale, not Recipient
     */
    public void registerSale(Sale sale, String child) {
        SalesList temp;

        temp = monthly.get(sale.getMonth() - 1);

        if (temp == null) {
            temp = new SalesList();
            monthly.set((sale.getMonth() - 1), temp);
        }

        temp.registerSale(sale, child);


        if (sale.getType().equals("P")) {
            this.totalP++;
            this.total$P += sale.getPrice() * sale.getAmount();
        } else {
            this.totalN++;
            this.total$N += sale.getPrice() * sale.getAmount();
        }

        this.totalAmount += sale.getAmount();
    }

    /**
     * Returns Year's Worth of SalesLists
     *
     * @return
     */
    public ArrayList<SalesList> getMonthly() {
        ArrayList<SalesList> toRet = new ArrayList<>();

        for (SalesList salesList : this.monthly) {
            toRet.add(salesList.clone());
        }

        return toRet;
    }

    public void setMonthly(ArrayList<SalesList> monthly) {
        this.monthly = monthly;
    }

    public String getKey() {
        return key;
    }

    public void setKey(String key) {
        this.key = key;
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

    @Override
    public MonthlySales clone() {
        return new MonthlySales(this);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        MonthlySales that = (MonthlySales) o;

        if (!getKey().equals(that.getKey())) return false;
        if (getTotalP() != that.getTotalP()) return false;
        if (getTotalN() != that.getTotalN()) return false;
        if (Double.compare(that.getTotal$P(), getTotal$P()) != 0) return false;
        if (Double.compare(that.getTotal$N(), getTotal$N()) != 0) return false;
        if (getTotalAmount() != that.getTotalAmount()) return false;
        return getMonthly().equals(that.getMonthly());

    }

    @Override
    public int hashCode() {
        int result;
        long temp;
        result = getMonthly().hashCode();
        result = 31 * result + getTotalP();
        result = 31 * result + getTotalN();
        result = 31 * result + getKey().length();
        temp = Double.doubleToLongBits(getTotal$P());
        result = 31 * result + (int) (temp ^ (temp >>> 32));
        temp = Double.doubleToLongBits(getTotal$N());
        result = 31 * result + (int) (temp ^ (temp >>> 32));
        result = 31 * result + getTotalAmount();
        return result;
    }

    @Override
    public String toString() {
        final StringBuilder sb = new StringBuilder("MonthlySales{");
        sb.append("key=").append(key);
        sb.append(", monthly=").append(monthly);
        sb.append(", totalP=").append(totalP);
        sb.append(", totalN=").append(totalN);
        sb.append(", total$P=").append(total$P);
        sb.append(", total$N=").append(total$N);
        sb.append(", totalAmount=").append(totalAmount);
        sb.append('}');
        return sb.toString();
    }

    @Override
    public int compareTo(MonthlySales o) {
        int res = (o.getTotalN() + o.getTotalP()) - (this.totalN + this.totalP);

        if (res == 0)
            res = key.compareTo(o.getKey());

        return res;
    }
}
