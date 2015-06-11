package com.Hipermercado;

import java.io.Serializable;
import java.util.*;

/**
 *  Sales Class
 *  @author     Diogo
 *  @since      09/06/2015
 */
public class Sales implements Serializable {
    private HashMap<Product, MonthlySales >salesMetaProd;   // Ordered desc by nSales( totalP + totalN )
    private HashMap<Client, MonthlySales > salesMetaCli;   // Ordered desc by nSales( totalP + totalN )


    public Sales()
    {
        this.salesMetaProd  = new HashMap<>();
        this.salesMetaCli  = new HashMap<>();
    }

    public Sales(HashMap<Product, MonthlySales> prodMap, HashMap<Client, MonthlySales> cliMap )
    {
        this.salesMetaProd  = new HashMap<>(prodMap);
        this.salesMetaCli  = new HashMap<>(cliMap);
    }

    public TreeMap<Product, MonthlySales> getSortedSalesProd()
    {
        TreeMap<Product, MonthlySales> result = new TreeMap<>( new ValueComparator(salesMetaProd));

        result.putAll( salesMetaProd );

        return result;
    }

    public TreeMap<Client, MonthlySales> getSortedSalesCli()
    {
        TreeMap<Client, MonthlySales> result = new TreeMap<>( new ValueComparator(salesMetaCli));

        result.putAll( salesMetaCli );

        return result;
    }

    public MonthlySales getMonthlyProd( Product prod )
    {
        return salesMetaProd.get( prod );
    }

    public void registerProd( Product prod ) throws ProductAlreadyExistsException
    {
        MonthlySales productSales = salesMetaProd.get( prod );

        if( productSales != null )
            throw new ProductAlreadyExistsException("com.Hipermercado.Sales " + prod.getCode() + " Already Registered in Sales.");

        productSales = new MonthlySales( prod.getCode() );
        salesMetaProd.put( prod, productSales );
    }

    public void registerCli( Client cli) throws ClientAlreadyExistsException
    {
        MonthlySales clientSales = salesMetaCli.get( cli );

        if( clientSales != null )
            throw new ClientAlreadyExistsException("com.Hipermercado.Sales " + cli.getCode() + " Already Registered in Sales.");

        clientSales = new MonthlySales( cli.getCode() );
        salesMetaCli.put( cli, clientSales );
    }

    public void registerSale(Sale sale) throws ProductNotFoundException,ClientNotFoundException
    {
        Product prod = sale.getProduct();
        Client client = sale.getClient();
        MonthlySales productSales = salesMetaProd.get(prod);
        MonthlySales clientSales = salesMetaCli.get(client);

        if( productSales == null )
            throw new ProductNotFoundException("com.Hipermercado.Sales " + prod.getCode() + " Not Found in Sales.");

        if(clientSales == null)
            throw new ClientNotFoundException("com.Hipermercado.Sales " + client.getCode() + " Not Found in Sales.");

        productSales.registerSale(sale, client.getCode() );
        clientSales.registerSale(sale, prod.getCode() );
    }


    public TreeMap<Product, MonthlySales> getSalesMetaProd()
    {
        TreeMap<Product, MonthlySales> toRet = new TreeMap<>();

        for(Map.Entry<Product, MonthlySales> entry : this.salesMetaProd.entrySet())
        {
            toRet.put(entry.getKey(), entry.getValue().clone());
        }

        return toRet;
    }

    public TreeMap<Client, MonthlySales> getSalesMetaCli()
    {
        TreeMap<Client, MonthlySales> toRet = new TreeMap<>();

        for(Map.Entry<Client, MonthlySales> entry : this.salesMetaCli.entrySet())
        {
            toRet.put(entry.getKey(), entry.getValue().clone());
        }

        return toRet;
    }

    public void setSalesMetaProd(HashMap<Product, MonthlySales> salesMetaProd)
    {
        this.salesMetaProd = salesMetaProd;
    }

    public void setSalesMetaCli(HashMap<Client, MonthlySales> salesMetaCli)
    {
        this.salesMetaCli = salesMetaCli;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Sales sales = (Sales) o;

        if( !(salesMetaProd.equals( sales.getSalesMetaProd()  ) ) ) return false;

        return salesMetaCli.equals(sales.getSalesMetaCli());

    }

    @Override
    public int hashCode() {
        return ( salesMetaProd.hashCode() + salesMetaCli.hashCode() );
    }

    @Override
    public String toString() {
        final StringBuilder sb = new StringBuilder("Sales{");
        sb.append("salesMetaProd=").append(salesMetaProd);
        sb.append(", salesMetaCli=").append(salesMetaCli);
        sb.append('}');
        return sb.toString();
    }

    private class ValueComparator implements Comparator {

        Map map;

        public ValueComparator(Map map){
            this.map = map;
        }
        public int compare(Object keyA, Object keyB){

            Comparable valueA = (Comparable) map.get(keyA);
            Comparable valueB = (Comparable) map.get(keyB);


            return valueA.compareTo(valueB);

        }
    }
}

