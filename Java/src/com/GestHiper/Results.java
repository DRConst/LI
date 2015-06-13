package com.GestHiper;

import java.util.HashMap;

/**
 * Results Class, HashMap containing keys and incremental functions
 *
 * @author Pedro
 * @since 12/06/2015
 */
public class Results {
    private HashMap<String, Integer> res;

    public Results() {
        res = new HashMap<>();
    }

    public Results(String... keys) {
        res = new HashMap<>();

        for (String key : keys)
            res.put(key, 0);
    }

    public Results(Results r) {
        this.res = r.getResults();
    }

    public void inc(String key) {
        Integer val = res.get(key);

        if (val == null)
            res.put(key, 1);
        else
            res.put(key, val + 1);
    }

    public int get(String key) {
        return res.get(key);
    }

    public void set(String key, int val) {
        res.put(key, val);
    }

    public HashMap<String, Integer> getResults() {
        HashMap<String, Integer> newRes = new HashMap<>();

        return newRes;
    }

    @Override
    public Results clone() {
        return new Results(this);
    }
}
