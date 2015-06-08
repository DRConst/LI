package com.GestHiper;

/**
 * Created by Diogo on 03/06/2015.
 */
public class Product {

    String code;

    Product()
    {

    }

    Product(String code)
    {
        this.code = code;
    }

    Product(Product c)
    {
        this.code = c.getCode();
    }

    public String getCode() {
        return code;
    }

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
}
