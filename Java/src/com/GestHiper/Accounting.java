package com.GestHiper;

import java.util.HashMap;
import java.util.Map;

/**
 * Created by Diogo on 09/06/2015.
 */
public class Accounting {

    private HashMap<String, AccountingStats> stats;

    public Accounting()
    {
        this.stats = new HashMap<>();
    }

    public Accounting(Map<String, AccountingStats> map)
    {
        this.stats = new HashMap<>(map);
    }

    public HashMap<String, AccountingStats> getStats() {
        HashMap<String, AccountingStats> toRet = new HashMap<>();

        for(AccountingStats stats : this.stats.values())
        {
            toRet.put(stats.getName(), stats);
        }

        return toRet;
    }

    public void setStats(HashMap<String, AccountingStats> stats) {
        this.stats = stats;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Accounting that = (Accounting) o;

        return getStats().equals(that.getStats());

    }

    @Override
    public int hashCode() {
        return getStats().hashCode();
    }

    @Override
    public String toString() {
        final StringBuilder sb = new StringBuilder("Accounting{");
        sb.append("stats=").append(stats);
        sb.append('}');
        return sb.toString();
    }
}
