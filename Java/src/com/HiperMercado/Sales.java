package com.Hipermercado;

import java.io.Serializable;
import java.lang.reflect.Array;
import java.util.*;

/**
 * Sales Class
 *
 * @author Diogo
 * @since 09/06/2015
 */
public class Sales implements Serializable {
    private Map<Product, MonthlySales> salesMetaProd;   // Ordered desc by nSales( totalP + totalN )
    private Map<Client, MonthlySales> salesMetaCli;   // Ordered desc by nSales( totalP + totalN )
    private boolean isSorted = false;

    public Sales() {
        this.salesMetaProd = new HashMap<>();
        this.salesMetaCli = new HashMap<>();
    }

    public Sales(HashMap<Product, MonthlySales> prodMap, HashMap<Client, MonthlySales> cliMap) {
        this.salesMetaProd = new HashMap<>(prodMap);
        this.salesMetaCli = new HashMap<>(cliMap);
    }

    public Sales(Sales s) {
        isSorted = true;
        salesMetaProd = new HashMap<>(s.getSalesMetaProd());
        salesMetaCli = new HashMap<>(s.getSalesMetaCli());
    }

    public void sortSales() {
        salesMetaProd = getSortedSalesProd();
        salesMetaCli = getSortedSalesCli();
        isSorted = true;
    }

    public TreeMap<Product, MonthlySales> getSortedSalesProd() {
        TreeMap<Product, MonthlySales> result = new TreeMap<>(new ValueComparator(salesMetaProd));

        result.putAll(salesMetaProd);

        return result;
    }

    public TreeMap<Client, MonthlySales> getSortedSalesCli() {
        TreeMap<Client, MonthlySales> result = new TreeMap<>(new ValueComparator(salesMetaCli));

        result.putAll(salesMetaCli);

        return result;
    }

    public MonthlySales getMonthlyProd(Product prod) {
        return salesMetaProd.get(prod);
    }

    public void registerProd(Product prod) throws ProductAlreadyExistsException {
        MonthlySales productSales = salesMetaProd.get(prod);

        if (productSales != null)
            throw new ProductAlreadyExistsException("com.Hipermercado.Sales " + prod.getCode() + " Already Registered in Sales.");

        productSales = new MonthlySales(prod.getCode());
        salesMetaProd.put(prod, productSales);
    }

    public void registerCli(Client cli) throws ClientAlreadyExistsException {
        MonthlySales clientSales = salesMetaCli.get(cli);

        if (clientSales != null)
            throw new ClientAlreadyExistsException("com.Hipermercado.Sales " + cli.getCode() + " Already Registered in Sales.");

        clientSales = new MonthlySales(cli.getCode());
        salesMetaCli.put(cli, clientSales);
    }

    public void registerSale(Sale sale) throws ProductNotFoundException, ClientNotFoundException {
        Product prod = sale.getProduct();
        Client client = sale.getClient();
        MonthlySales productSales = salesMetaProd.get(prod);
        MonthlySales clientSales = salesMetaCli.get(client);

        if (productSales == null)
            throw new ProductNotFoundException("com.Hipermercado.Sales " + prod.getCode() + " Not Found in Sales.");

        if (clientSales == null)
            throw new ClientNotFoundException("com.Hipermercado.Sales " + client.getCode() + " Not Found in Sales.");

        productSales.registerSale(sale, client.getCode());
        clientSales.registerSale(sale, prod.getCode());
    }


    public TreeMap<Product, MonthlySales> getSalesMetaProd() {
        TreeMap<Product, MonthlySales> toRet = new TreeMap<>();

        for (Map.Entry<Product, MonthlySales> entry : this.salesMetaProd.entrySet()) {
            toRet.put(entry.getKey(), entry.getValue().clone());
        }

        return toRet;
    }

    public void setSalesMetaProd(HashMap<Product, MonthlySales> salesMetaProd) {
        this.salesMetaProd = salesMetaProd;
    }

    public TreeMap<Client, MonthlySales> getSalesMetaCli() {
        TreeMap<Client, MonthlySales> toRet = new TreeMap<>();

        for (Map.Entry<Client, MonthlySales> entry : this.salesMetaCli.entrySet()) {
            toRet.put(entry.getKey(), entry.getValue().clone());
        }

        return toRet;
    }

    public void setSalesMetaCli(HashMap<Client, MonthlySales> salesMetaCli) {
        this.salesMetaCli = salesMetaCli;
    }

    public TreeSet<String> getMostBoughtProductsForClient(String code)
    {
        HashMap<String, MetaSale> temp = new HashMap<>();

        for(SalesList salesList : salesMetaCli.get(code).getMonthly())
        {
            for(MetaSale metaSale : salesList.getSales().values())
            {
                String key = metaSale.getKey();
                MetaSale tMetaSale;
                if(temp.containsKey(key))
                {
                    tMetaSale = temp.remove(key);
                    tMetaSale.setAmount(tMetaSale.getAmount() + metaSale.getAmount());
                    temp.put(key, tMetaSale);
                }else{
                    temp.put(key, metaSale);
                }
            }
        }
        return new TreeSet<>(new ValueComparator(temp));
    }

    public TreeSet<String> getClientsWithMostPurchases()
    {
        HashMap<String, Integer> temp = new HashMap<>();

        for(MonthlySales monthlySales : salesMetaCli.values())
        {
            Integer sum = 0;
            for(Integer i : monthlySales.getUniquePurchases())
                sum += i;
            temp.put(monthlySales.getKey(), sum);
        }
        return new TreeSet<>(new ValueComparator(temp));
    }

    

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Sales sales = (Sales) o;

        if (!(salesMetaProd.equals(sales.getSalesMetaProd()))) return false;

        return salesMetaCli.equals(sales.getSalesMetaCli());

    }

    /**
     * Query1
     * @return Unbought Products ordered alphabeticaly
     */
    public LinkedList<String> getUnboughtProducts()
    {
        LinkedList<String> toRet = new LinkedList<>();

        if(!isSorted)
            this.sortSales();

        TreeMap<Product, MonthlySales> temp = (TreeMap)salesMetaProd;
        NavigableSet<Product> test = temp.descendingKeySet();

        for( Product key : test )
        {
            MonthlySales p = salesMetaProd.get( key );
            if(p.getTotalAmount() != 0)
                break;

            toRet.add( key.getCode() );
        }


        Collections.sort( toRet, Collections.reverseOrder() );

        return toRet;
    }

    /**
     * Query2
     * @return Clients without purchases ordered alphabeticaly
     */
    public TreeSet<String> getClientsWithoutPurchases()
    {
        TreeSet<String> toRet = new TreeSet<>();

        if(!isSorted)
            this.sortSales();

        for(MonthlySales p : salesMetaCli.values())
        {
            if(p.getTotalAmount() != 0)
                break;

            toRet.add(p.getKey());
        }

        return toRet;
    }

    public ArrayList<Integer> getUniquePurchases(String code) throws SalesNotFoundException
    {
        MonthlySales monthlySales = salesMetaCli.get(code);

        if(monthlySales == null)
            throw new SalesNotFoundException("No sales for " + code);

        return  monthlySales.getUniquePurchases();

    }

    @Override
    public int hashCode() {
        return (salesMetaProd.hashCode() + salesMetaCli.hashCode());
    }

    @Override
    public Sales clone() {
        return new Sales(this);
    }

    @Override
    public String toString() {
        final StringBuilder sb = new StringBuilder("Sales{");
        sb.append("salesMetaProd=").append(salesMetaProd);
        sb.append(", salesMetaCli=").append(salesMetaCli);
        sb.append('}');
        return sb.toString();
    }


    /**
     * ValueComparator Class, used internally for Sorting Purposes
     */
    private class ValueComparator implements Comparator {
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


}

