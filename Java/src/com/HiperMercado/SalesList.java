package com.Hipermercado;

import java.io.Serializable;
import java.util.Comparator;
import java.util.HashMap;
import java.util.Map;
import java.util.TreeMap;

/**
 * SalesList Class, Used By MonthlySales
 *
 * @author Diogo
 * @since 10/06/2015
 */
public class SalesList implements Serializable {
    private int totalP;        // sum of this months's MetaSales nTypeP
    private int totalN;        //	...

    private double total$P;    //	...
    private double total$N;    //	...

    private int totalAmount;    // sum of this months's MetaSales's amounts

    private Map<String, MetaSale> sales; //SortedSet is abstract


    /**
     * SalesList Constructor, inits empty SalesList
     */
    public SalesList() {
        this.sales = new HashMap<>();
        this.totalP = 0;
        this.totalN = 0;
        this.total$P = 0.0;
        this.total$N = 0.0;
        this.totalAmount = 0;
    }

    /**
     * SalesList Constructor, inits SalesList with given values
     *
     * @param totalP
     * @param totalN
     * @param total$P
     * @param total$N
     * @param totalAmount
     * @param sales
     */
    public SalesList(int totalP, int totalN, double total$P, double total$N, int totalAmount, HashMap<String, MetaSale> sales) {
        this.totalP = totalP;
        this.totalN = totalN;
        this.total$P = total$P;
        this.total$N = total$N;
        this.totalAmount = totalAmount;
        this.sales = sales;
    }

    /**
     * SalesList Constructor, clones given SalesList
     *
     * @param salesList
     */
    public SalesList(SalesList salesList) {
        this.totalP = salesList.getTotalP();
        this.totalN = salesList.getTotalN();
        this.total$P = salesList.getTotal$P();
        this.total$N = salesList.getTotal$N();
        this.totalAmount = salesList.getTotalAmount();
        this.sales = salesList.getSales();
    }


    /**
     * Registers Sale into MetaSales, also tallies up the Sale's values
     *
     * @param sale
     * @param child
     */
    public void registerSale(Sale sale, String child) {
        MetaSale temp = sales.get(child);

        if (temp == null) {
            temp = new MetaSale(child);
            sales.put(child, temp);
        }

        temp.registerMetaSale(sale);


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
     * Sorts MetaSales
     */
    public void sortSales() {
        sales = getSortedSalesList();
    }

    /**
     * Returns Sorted MetaSales
     *
     * @return MetaSales
     */
    public TreeMap<String, MetaSale> getSortedSalesList() {
        TreeMap<String, MetaSale> result = new TreeMap<>(new ValueComparator(sales));

        result.putAll(sales);

        return result;
    }

    /**
     * Returns Nº Different Products/Clients Associated with Current Entry.
     *
     * @return N Diff Elements
     */
    public int getNDiff() {
        return this.sales.keySet().size();
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

    public HashMap<String, MetaSale> getSales() {
        HashMap<String, MetaSale> result = new HashMap<>(sales);

        return result;
    }


    public void setSales(HashMap<String, MetaSale> sales) {
        this.sales = sales;
    }


    public MetaSale getMetaSale(String code) throws SalesNotFoundException
    {
        MetaSale toRet = sales.get(code);

        if(toRet == null)
            throw new SalesNotFoundException();

        return toRet;
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

    @Override
    public SalesList clone() {
        return new SalesList(this);
    }


    /**
     * ValueComparator Class, used internally for Sorting Purposes
     */
    private class ValueComparator implements Comparator {
        Map map;


        public ValueComparator(Map map) {
            this.map = map;
        }


        public int compare(Object keyA, Object keyB) {

            Comparable valueA = (Comparable) map.get(keyA);
            Comparable valueB = (Comparable) map.get(keyB);


            return valueA.compareTo(valueB);

        }

    }


}
