package com.Hipermercado;


import java.io.Serializable;
import java.util.*;

/**
 * Accounting Class
 * @author Diogo
 * @since 09/06/2015
 */
public class Accounting implements Serializable
{
    private ArrayList< SalesList > products, clients;


    public Accounting()
    {
        products = new ArrayList<>(12);
        clients = new ArrayList<>(12);

        for(int i=0; i < 12; i++) {
            this.products.add( new SalesList() );
            this.clients.add( new SalesList() );
        }

    }

    public Accounting( Accounting acc )
    {
        products = new ArrayList<>( acc.getProducts() );
        clients = new ArrayList<>( acc.getClients() );
    }


    public void registerSale( Sale sale )
    {
        int idx = sale.getMonth() - 1;


        products.get( idx ).registerSale( sale, sale.getProduct().getCode() );
        clients.get( idx ).registerSale( sale, sale.getClient().getCode() );

    }

    public void sortAcc()
    {
        for(int i=0;i<12;i++) {

            products.get(i).sortSales();
            clients.get(i).sortSales();

        }

    }

    public int getNDiffClientsByMonth( int month )
    {
        return this.clients.get( month - 1).getNDiff();
    }

    public int getNDiffProductsByMonth( int month )
    {
        return this.products.get( month - 1).getNDiff();
    }



    public int getNSalesByMonth( int month )
    {
        int res = this.products.get( month - 1 ).getTotalN();

        res += this.clients.get( month - 1).getTotalN();

        return res;
    }


    public ArrayList< SalesList > getProducts()
    {
        ArrayList<SalesList> prods = new ArrayList<>();

        for(int i=0;i<12;i++)
            prods.add( products.get(i).clone() );

        return prods;
    }

    public ArrayList< SalesList > getClients()
    {
        ArrayList<SalesList> clis = new ArrayList<>();

        for(int i=0;i<12;i++)
            clis.add( clients.get(i).clone() );

        return clis;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Accounting that = (Accounting) o;

        for(int i=0; i < 12; i++)
            if( !products.get(i).equals( that.getProducts().get(i) ) ||
                    !clients.get(i).equals( that.getClients().get(i) ) )
                return false;

        return true;

    }

    @Override
    public int hashCode() {
        int result = products.hashCode();
        result = 31 * result + clients.hashCode();
        return result;
    }

    public Accounting clone()
    {
        return new Accounting( this );
    }
}
