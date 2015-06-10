package com.GestHiper;

import java.util.ArrayList;
import java.util.Set;
import java.util.SortedSet;

/**
 * Created by Diogo on 09/06/2015.
 */
public class MonthlySales {

    private ArrayList<SalesList > monthly;

    private int totalP;		// sum of all months's MetaSales nTypeP
    private int totalN;		//	...

    private double total$P;	//	...
    private double total$N;	//	...

    private int totalAmount;	// sum of all months's MetaSales's amounts

    public void registerSale(Sale sale)
    {
        monthly.get(sale.getMonth() - 1).registerSale(sale);

        if(sale.getType().equals("P"))
        {
            this.totalP++;
            this.total$P += sale.getPrice() * sale.getAmount();
        }else
        {
            this.totalN++;
            this.total$N += sale.getPrice() * sale.getAmount();
        }

        this.totalAmount += sale.getAmount();
    }



    public MonthlySales()
    {
        this.monthly = new ArrayList<  >( 12 );
    }

    public MonthlySales(ArrayList<SalesList> monthly, int totalP, int totalN, double total$P, double total$N, int totalAmount) {
        this.monthly = monthly;
        this.totalP = totalP;
        this.totalN = totalN;
        this.total$P = total$P;
        this.total$N = total$N;
        this.totalAmount = totalAmount;
    }

    public MonthlySales(MonthlySales sales)
    {
        this.monthly = sales.getMonthly();
        this.totalP = sales.getTotalP();
        this.totalN = sales.getTotalN();
        this.total$P = sales.getTotal$P();
        this.total$N = sales.getTotal$N();
        this.totalAmount = sales.getTotalAmount();
    }

    public ArrayList<SalesList> getMonthly() {
        ArrayList<SalesList> toRet = new ArrayList<>();

        for(SalesList salesList : this.monthly)
        {
            toRet.add(salesList.clone());
        }

        return toRet;
    }

    public void setMonthly(ArrayList<SalesList> monthly) {
        this.monthly = monthly;
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

    public MonthlySales clone()
    {
        return new MonthlySales(this);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        MonthlySales that = (MonthlySales) o;

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
        sb.append("monthly=").append(monthly);
        sb.append(", totalP=").append(totalP);
        sb.append(", totalN=").append(totalN);
        sb.append(", total$P=").append(total$P);
        sb.append(", total$N=").append(total$N);
        sb.append(", totalAmount=").append(totalAmount);
        sb.append('}');
        return sb.toString();
    }
}
