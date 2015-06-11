package com.Hipermercado;

/**
 *  Exception for Product - Not Found
 *  @author     Diogo
 *  @since      07/06/2015
 */
public class ProductNotFoundException extends Exception{
    public ProductNotFoundException()
    {
        super();
    }

    public ProductNotFoundException(String s)
    {
        super(s);
    }

}
