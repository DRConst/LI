package com.Hipermercado;

import java.io.Serializable;

/**
 * MetaSale Class, used by SalesList
 * @author Pedro
 * @since 10/06/2015
 */
public class MetaSale implements Comparable<MetaSale>,Serializable {
    private String key;
    private int amount;
    private int totalN;
    private int totalP;
    private double total$P;
    private double total$N;

    public MetaSale(String key) {
        this.key = key;
        this.amount = 0;
        this.totalN = 0;
        this.totalP = 0;
        this.total$P = 0.0;
        this.total$N = 0.0;
    }

    private MetaSale( MetaSale m ) {
        this.key = m.getKey();
        this.amount = m.getAmount();
        this.totalN = m.getTotalN();
        this.totalP = m.getTotalP();
        this.total$N = m.getTotal$N();
        this.total$P = m.getTotal$P();
    }

    public String getKey() {
        return key;
    }

    public void setKey(String key) {
        this.key = key;
    }

    public int getTotalN() {
        return totalN;
    }

    public void setTotalN(int totalN) {
        this.totalN = totalN;
    }

    public int getAmount() {
        return amount;
    }

    public void setAmount(int amount) {
        this.amount = amount;
    }

    public double getTotal$P() {
        return total$P;
    }

    public void setTotal$P(double total$P) {
        this.total$P = total$P;
    }

    public int getTotalP() {
        return totalP;
    }

    public void setTotalP(int totalP) {
        this.totalP = totalP;
    }

    public double getTotal$N() {
        return total$N;
    }

    public void setTotal$N(double total$N) {
        this.total$N = total$N;
    }

    public void registerMetaSale( Sale s ) {

        this.amount += s.getAmount();

        if (s.getType().equals("N")) {
            this.total$N += s.getPrice() * s.getAmount();
            this.totalN++;
        }else {
            this.total$P += s.getPrice() * s.getAmount();
            this.totalP++;
        }

    }


    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        MetaSale metaSale = (MetaSale) o;

        return getKey().equals(metaSale.getKey());

    }

    @Override
    public int hashCode() {
        return getKey().hashCode();
    }

    @Override
    public int compareTo(MetaSale o) {
        int res = o.getAmount() - this.amount;

        if( res == 0 )
            res = o.getKey().compareTo( this.key );

        return res;
    }
}
