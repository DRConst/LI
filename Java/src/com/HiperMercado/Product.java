package com.Hipermercado;

import java.io.Serializable;

/**
 * Product Class
 *
 * @author Diogo
 * @since 03/06/2015
 */
public class Product implements Serializable {
    String code;


    /**
     * Product Constructor, inits empty Product
     */
    Product() {
        this.code = "";
    }

    /**
     * Product Constructor, inits with given code
     *
     * @param code
     */
    public Product(String code) {
        this.code = code;
    }

    /**
     * Product Constructor, clones given Product
     *
     * @param p
     */
    Product(Product p) {
        this.code = p.getCode();
    }


    /**
     * Retrieves Product Code
     *
     * @return Product Code
     */
    public String getCode() {
        return code;
    }


    /**
     * Clones current Product instance, making use of Constructor
     *
     * @return New Product Instance
     */
    public Product clone() {
        return new Product(this);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Product product = (Product) o;

        return code.equals(product.getCode());

    }

    @Override
    public int hashCode() {
        return code.hashCode();
    }


    @Override
    public String toString() {
        return code;
    }
}
