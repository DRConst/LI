package com.Hipermercado;

import java.util.ArrayList;
import java.util.Arrays;

/**
 * Created by Diogo on 09/06/2015.
 */
public class AccountingStats implements Comparable<AccountingStats> {

    private int[] cntSalesP; /* Month Array, idx0 is total */
    private int[] cntSalesN;
    private int[] units;
    private double[] profitP;
    private double[] profitN;
    private String name;



    public void registerSale(Sale s)
    {
        int month = s.getMonth();

        if(s.getType().equals("N"))
        {
            cntSalesN[month]++;
            profitN[month] += s.getPrice() * s.getAmount();
        }
        else
        {
            cntSalesP[month]++;
            profitP[month] += s.getPrice() * s.getAmount();
        }

        units[month] += s.getAmount();


    }


    public ArrayList<Query6Return> getCountsProfitByType()
    {
        ArrayList<Query6Return> toRet = new ArrayList<>(12);

        for(int i = 1; i < 13; i++)
            toRet.add(new Query6Return(cntSalesP[i], cntSalesN[i], profitP[i], profitN[i]));

        return toRet;
    }


    public AccountingStats()
    {
        cntSalesP = new int[13];
        cntSalesN = new int[13];
        units = new int[13];
        profitP = new double[13];
    }

    public AccountingStats(String code)
    {
        cntSalesP = new int[13];
        cntSalesN = new int[13];
        units = new int[13];
        profitP = new double[13];
        this.name = code;
    }


    public double[] getProfitN() {
        return profitN;
    }

    public void setProfitN(double[] profitN) {
        this.profitN = profitN;
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

    public double[] getProfitP() {
        return profitP;
    }

    public void setProfitP(double[] profitP) {
        this.profitP = profitP;
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
        if (!Arrays.equals(getProfitP(), stats.getProfitP())) return false;
        return getName().equals(stats.getName());

    }

    @Override
    public int hashCode() {
        int result = Arrays.hashCode(getCntSalesP());
        result = 31 * result + Arrays.hashCode(getCntSalesN());
        result = 31 * result + Arrays.hashCode(getUnits());
        result = 31 * result + Arrays.hashCode(getProfitP());
        result = 31 * result + getName().hashCode();
        return result;
    }

    @Override
    public String toString() {
        final StringBuilder sb = new StringBuilder("AccountingStats{");
        sb.append("cntSalesP=").append(Arrays.toString(cntSalesP));
        sb.append(", cntSalesN=").append(Arrays.toString(cntSalesN));
        sb.append(", units=").append(Arrays.toString(units));
        sb.append(", profitP=").append(Arrays.toString(profitP));
        sb.append(", name='").append(name).append('\'');
        sb.append('}');
        return sb.toString();
    }

    @Override
    public int compareTo(AccountingStats o) {
        int res = o.get
    }
}
