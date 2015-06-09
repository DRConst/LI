package com.GestHiper;

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

}
