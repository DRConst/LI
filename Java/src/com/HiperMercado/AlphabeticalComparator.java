package com.Hipermercado;

import java.util.Comparator;

/**
 * Created by Diogo on 13/06/2015.
 */
public class AlphabeticalComparator<T extends Identifiable> implements Comparator<T>{

    @Override
    public int compare(T o1, T o2) {
       return o1.getCode().compareToIgnoreCase(o2.getCode());
    }
}
