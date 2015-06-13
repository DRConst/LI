package com.Hipermercado;

import java.io.Serializable;
import java.util.HashMap;
import java.util.Map;

/**
 * Product Catalog Class
 *
 * @author Diogo
 * @since 03/06/2015
 */
public class ProductCatalog implements Serializable {
    private HashMap<String, Product> productCatalog;


    /**
     * ProductCatalog Constructor, inits empty ProductCatalog
     */
    ProductCatalog() {
        this.productCatalog = new HashMap<>();
    }

    /**
     * ProductCatalog Constructor, clones given ProductCatalog
     *
     * @param pCat
     */
    ProductCatalog(ProductCatalog pCat) {
        this.productCatalog = new HashMap<>(pCat.getProductCount());

        for (Product cli : pCat.getProductCatalog().values()) {
            this.productCatalog.put(cli.getCode(), cli.clone());
        }
    }


    /**
     * Retrieves new Map instance with catalog data
     *
     * @return ProductCatalog primary structure
     */
    public Map<String, Product> getProductCatalog() {

        HashMap<String, Product> toRet = new HashMap<>();

        for (Product pr : this.productCatalog.values()) {
            this.productCatalog.put(pr.getCode(), pr.clone());
        }

        return toRet;

    }


    /**
     * Returns nº products in catalog
     *
     * @return Nº Products
     */
    public int getProductCount() {
        return productCatalog.size();
    }


    /**
     * Checks for existence of provided code in catalog
     *
     * @param code Product Code
     * @return True, False - Existence of code
     */
    public boolean existsProduct(String code) {
        return this.productCatalog.containsKey(code);
    }


    /**
     * Gets Product Instance associated with provided code
     *
     * @param code Product Code
     * @return New Product instance associated with provided code
     * @throws ProductNotFoundException On Invalid Code
     */
    public Product getProduct(String code) throws ProductNotFoundException {
        Product p = this.productCatalog.get(code);
        if (p != null)
            return p;
        else {
            throw new ProductNotFoundException("com.Hipermercado.Product " + p.getCode() + " Not Found.");
        }
    }


    /**
     * Inserts new Product into the Catalog
     *
     * @param p New Product to be inserted
     * @throws ProductAlreadyExistsException On Attempting to Insert an already existent Product
     */
    public void insertProduct(Product p) throws ProductAlreadyExistsException {
        if (this.productCatalog.put(p.getCode(), p) != null)
            throw new ProductAlreadyExistsException("com.Hipermercado.Product " + p.getCode() + " Already In Catalog.");
    }


    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();

        for (Product pr : productCatalog.values())
            sb.append(pr.toString() + "\n");

        return sb.toString();
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        ProductCatalog that = (ProductCatalog) o;

        return getProductCatalog().equals(that.getProductCatalog());

    }

    @Override
    public int hashCode() {
        return getProductCatalog().hashCode();
    }

    @Override
    public ProductCatalog clone() {
        return new ProductCatalog(this);
    }
}
