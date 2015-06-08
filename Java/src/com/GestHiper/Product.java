package com.GestHiper;

/**
 *  Product Class
 *  @author     Diogo
 *  @since      03/06/2015
 */
public class Product {

    String code;

    Product() { this.code = ""; }

    Product(String code)
    {
        this.code = code;
    }

    Product(Product c)
    {
        this.code = c.getCode();
    }


    /**
     * Retrieves Product Code
     * @return Product Code
     */
    public String getCode() {
        return code;
    }


    /**
     * Clones current Product instance, making use of Constructor
     * @return New Product Instance
     */
    public Product clone()
    {
        return new Product(this);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Product product = (Product) o;

        return code.equals(product.code);

    }

    @Override
    public int hashCode() {
        return code.hashCode();
    }


    @Override
    public String toString() { return code; }
}
