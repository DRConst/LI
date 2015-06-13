package com.Hipermercado;

/**
 * Created by Diogo on 13/06/2015.
 */
public class MonthSaleStats {

    private int cntN, cntP;
    private double profitN, profitP;

    public MonthSaleStats(int cntN, int cntP, double profitN, double profitP) {
        this.cntN = cntN;
        this.cntP = cntP;
        this.profitN = profitN;
        this.profitP = profitP;
    }

    public MonthSaleStats() {
    }

    public int getCntN() {
        return cntN;
    }

    public void setCntN(int cntN) {
        this.cntN = cntN;
    }

    public int getCntP() {
        return cntP;
    }

    public void setCntP(int cntP) {
        this.cntP = cntP;
    }

    public double getProfitN() {
        return profitN;
    }

    public void setProfitN(double profitN) {
        this.profitN = profitN;
    }

    public double getProfitP() {
        return profitP;
    }

    public void setProfitP(double profitP) {
        this.profitP = profitP;
    }
}
