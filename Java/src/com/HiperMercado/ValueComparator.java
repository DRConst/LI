package com.Hipermercado;

/**
 * Created by Diogo on 13/06/2015.
 */


import java.util.Comparator;
import java.util.Map;

/**
 * ValueComparator Class, used internally for Sorting Purposes
 */
public class ValueComparator implements Comparator {
    Map map;


    public ValueComparator(Map map) {
        this.map = map;
    }


    public int compare(Object keyA, Object keyB) {

        Comparable valueA = (Comparable) map.get(keyA);
        Comparable valueB = (Comparable) map.get(keyB);


        return valueA.compareTo(valueB);

    }

}