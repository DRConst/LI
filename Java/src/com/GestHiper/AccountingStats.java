package com.GestHiper;

import java.util.Arrays;

/**
 * Created by Diogo on 09/06/2015.
 */
public class AccountingStats {

    private int[] cntSalesP; /* Month Array, idx0 is total */
    private int[] cntSalesN;
    private int[] units;
    private double[] profit;
    private String name;

    public AccountingStats()
    {
        cntSalesP = new int[13];
        cntSalesN = new int[13];
        units = new int[13];
        profit = new double[13];
    }

    public int[] getCntSalesP() {
        return cntSalesP;
    }

    public void setCntSalesP(int[] cntSalesP) {
        this.cntSalesP = cntSalesP;
    }

    public int[] getCntSalesN() {
        return cntSalesN;
    }

    public void setCntSalesN(int[] cntSalesN) {
        this.cntSalesN = cntSalesN;
    }

    public int[] getUnits() {
        return units;
    }

    public void setUnits(int[] units) {
        this.units = units;
    }

    public double[] getProfit() {
        return profit;
    }

    public void setProfit(double[] profit) {
        this.profit = profit;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        AccountingStats stats = (AccountingStats) o;

        if (!Arrays.equals(getCntSalesP(), stats.getCntSalesP())) return false;
        if (!Arrays.equals(getCntSalesN(), stats.getCntSalesN())) return false;
        if (!Arrays.equals(getUnits(), stats.getUnits())) return false;
        if (!Arrays.equals(getProfit(), stats.getProfit())) return false;
        return getName().equals(stats.getName());

    }

    @Override
    public int hashCode() {
        int result = Arrays.hashCode(getCntSalesP());
        result = 31 * result + Arrays.hashCode(getCntSalesN());
        result = 31 * result + Arrays.hashCode(getUnits());
        result = 31 * result + Arrays.hashCode(getProfit());
        result = 31 * result + getName().hashCode();
        return result;
    }

    @Override
    public String toString() {
        final StringBuilder sb = new StringBuilder("AccountingStats{");
        sb.append("cntSalesP=").append(Arrays.toString(cntSalesP));
        sb.append(", cntSalesN=").append(Arrays.toString(cntSalesN));
        sb.append(", units=").append(Arrays.toString(units));
        sb.append(", profit=").append(Arrays.toString(profit));
        sb.append(", name='").append(name).append('\'');
        sb.append('}');
        return sb.toString();
    }
}
