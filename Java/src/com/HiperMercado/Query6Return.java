package com.Hipermercado;

/**
 * Created by Diogo on 10/06/2015.
 */
public class Query6Return {
    int cntP, cntN;
    double profitP, profitN;

    public Query6Return(int cntP, int cntN, double profitP, double profitN) {
        this.cntP = cntP;
        this.cntN = cntN;
        this.profitP = profitP;
        this.profitN = profitN;
    }

    public int getCntP() {
        return cntP;
    }

    public void setCntP(int cntP) {
        this.cntP = cntP;
    }

    public int getCntN() {
        return cntN;
    }

    public void setCntN(int cntN) {
        this.cntN = cntN;
    }

    public double getProfitP() {
        return profitP;
    }

    public void setProfitP(double profitP) {
        this.profitP = profitP;
    }

    public double getProfitN() {
        return profitN;
    }

    public void setProfitN(double profitN) {
        this.profitN = profitN;
    }
}
