package com.GestHiper;

import java.util.HashMap;
import java.util.Set;

/**
 * Results Class, HashMap containing keys and incremental functions
 *
 * @author Pedro
 * @since 12/06/2015
 */
public class Results {
    private HashMap<String, Object> res;

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


    public void add( String key, Object o )
    {
        res.put( key, o );
    }
    public void inc(String key) {
        Integer val = (Integer)res.get(key);

        if (val == null)
            res.put(key, 1);
        else
            res.put(key, val + 1);
    }

    public Object get(String key) {
        return res.get(key);
    }

    public void set(String key, int val) {
        res.put(key, val);
    }

    public HashMap<String, Object> getResults() {
        HashMap<String, Object> newRes = new HashMap<>();

        return newRes;
    }

    public int size()
    {
        return res.size();
    }

    public Set<String> getKeys()
    {
        return res.keySet();
    }

    @Override
    public Results clone() {
        return new Results(this);
    }
}
