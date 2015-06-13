package com.Hipermercado;

import java.util.ArrayList;

/**
 * Created by Diogo on 13/06/2015.
 */
public class YearlySaleStats {
    private ArrayList<MonthSaleStats> yearlySalesStats;

    public YearlySaleStats(ArrayList<MonthSaleStats> monthSaleStats) {
        this.yearlySalesStats = monthSaleStats;
    }

    public YearlySaleStats() {
        yearlySalesStats = new ArrayList<>(12);
    }

    public ArrayList<MonthSaleStats> getYearlySalesStats() {
        return yearlySalesStats;
    }

    public void setYearlySalesStats(ArrayList<MonthSaleStats> yearlySalesStats) {
        this.yearlySalesStats = yearlySalesStats;
    }

    public void setMonthSaleStats(MonthSaleStats monthSaleStats, int month)
    {
        this.yearlySalesStats.add(month - 1, monthSaleStats);
    }
}
