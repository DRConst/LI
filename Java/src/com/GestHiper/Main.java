package com.GestHiper;


import com.Hipermercado.*;

import java.io.*;
import java.text.DecimalFormat;
import java.util.*;

/**
 * Main, Class interacting with user and holding primary instances
 *
 * @author LI_Grupo 6
 */
public class Main {

    public static void main(String[] args) throws IOException, ProductNotFoundException, ClientNotFoundException {
        int userOpt;

        HiperMercado hiper = new HiperMercado();
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        do {
            userOpt = menu();

            switch (userOpt) {

                case 1:

                    Query1( hiper );

                    break;


                case 2:


                    Query2( hiper );

                    break;

                case 3:

                    Query3( hiper );

                    break;

                case 4:

                    Query4( hiper );

                    break;

                case 5:

                    Query5( hiper );

                    break;

                case 6:

                    Query6( hiper );

                    break;

                case 7:
                    System.out.println(hiper.getMostBoughtProductsForClient("FO767"));
                    break;

                case 8:

                    break;

                case 9:
                    System.out.println(hiper.getClientsWithMostPurchases());
                    break;

                case 10:
                    System.out.println("yep");
                    break;

                case 11:
                    break;

                case 12:

                    try {
                        hiper = Query12();
                    } catch (FileNotFoundException e) {
                        System.out.println("Erro " + e.getMessage());
                    }

                    break;

                case 13:

                    try {
                        hiper = new HiperMercado( (HiperMercado)Serializer.readObject(hiper.getClass().getName() ) );
                    }catch( ClassNotFoundException e) {}

                    break;

                case 14:
                    break;

                default:
                    try {
                        Serializer.writeObject(hiper);
                    } catch (IOException e) {
                        System.out.println("Error Saving Status.");
                    }
                    break;
            }

            pageClear();

        } while (userOpt != 0);

    }


    /**
     * Main Menu listing user options
     * also gets user selection and validates it
     *
     * @return user option
     */
    public static int menu() {
        System.out.println("GestHiper");
        System.out.println("--------------------------------------\n"
                + "\t1\t- Products Never Bought;\n"
                + "\t2\t- Clients Without Purchases;\n"
                + "\t3\t- N� Sales/Clients, given month;\n"
                + "\t4\t- N� Sales/Products/$ for each month, given client;\n"
                + "\t5\t- N� Sales/Clients/$ for each month, given product;\n"
                + "\t6\t- N� N/P Sales and $ for each month, given product;\n"
                + "\t7\t- List Most Bought Products, desc:qtd,alph, given client;\n"
                + "\t8\t- List N Most Bought Products & their N� Unique Clients;\n"
                + "\t9\t- List N Clients with Most Unique Purchases;\n"
                + "\t10\t- List N Clients Most Bought a Given product;\n"
                + "\t11\t- Display File Statistics;\n"
                + "\t12\t- Load Data from Files;\n"
                + "\t13\t- Load from File;\n"
                + "\t14\t- Save to File;\n"
                + "\t0\t- Exit;\n");

        return getIntOpt(0, 14);
    }


    /**
     * Asks for number in interval [min, max]
     *
     * @param min inferior limit
     * @param max superior limit
     * @return valid user number
     */
    public static int getIntOpt(int min, int max) {
        Scanner scanner = new Scanner(System.in);
        boolean done = false;
        int input = max;

        System.out.println("Insert a number between " + min + " and " + max + ".\n");

        do {
            if (!scanner.hasNextInt()) {
                System.out.println("Please insert an integer value.");
                scanner.nextLine();
            } else {
                input = scanner.nextInt();
                if (input < min || input > max)
                    System.out.println("The value must be between " + min + " and " + max + ".");
                else
                    done = true;
            }
        } while (!done);
        scanner.nextLine();
        return input;
    }

    /**
     * Checks if given String is an Integer
     * @param s
     * @return Boolean
     */
    public static boolean isNumeric(String s )
    {

        try {
            Integer.parseInt(s);
        }
        catch(NumberFormatException e) { return false; }

        return true;
    }

    /**
     * 'Cleaning' terminal
     */
    public static void pageClear() {
        Scanner scanner = new Scanner(System.in);


        scanner.nextLine();
        for (int i = 0; i < 50; i++)
            System.out.println("\n");


    }

    public static void Query1( HiperMercado hiper )
    {
        Results res = new Results();
        LinkedList<String> prods = hiper.getUnboughtProducts();
        res.add("Products", prods);
        res.add( "*Total", prods.size() );
        paginate(res);
    }

    public static void Query2( HiperMercado hiper )
    {
        Results res = new Results();
        LinkedList<String> clis = hiper.getClientsWithoutPurchases();
        res.add( "Products", clis );
        res.add( "*Total", clis.size() );
        paginate( res );
    }

    public static void Query3( HiperMercado hiper )
    {
        int month;


        System.out.println("Insert Month: ");
        month = getIntOpt(1, 12);

        System.out.println("Nº Sales: "+ hiper.getNSalesPerMonth( month ) +", Nº Unique Clients: "+ hiper.getNDiffClientsPerMonth( month ) );
    }

    public static void Query4( HiperMercado hiper )
    {
        String code;
        Scanner scanner = new Scanner(System.in);
        int month;
        ArrayList<Integer> nSales, nUnique;
        ArrayList<Double> expenses;
        Results res = new Results();
        int nTotalSales, nTotalUnique;
        double totalExpenses;
        LinkedList<String> tempSales, tempUnique, tempExpenses;
        DecimalFormat formatExpenses = new DecimalFormat("0.00");


        System.out.println("Insert Client Code: ");
        code = scanner.nextLine();

        try {
            nSales = hiper.getClientNSalesYearly( code );
            nUnique = hiper.getClientNUniqueProducts( code );
            expenses = hiper.getClientExpenses( code );

        }catch( ClientNotFoundException e) {
            System.out.println("No Client Found");
            return;
        }catch( SalesNotFoundException e ) {
            System.out.println("No Sales Found for specified Client");
            return;
        }

        nTotalSales = nTotalUnique = 0;
        totalExpenses = 0.0;
        tempExpenses = new LinkedList<>();
        tempSales = new LinkedList<>();
        tempUnique = new LinkedList<>();
        for(int i=0;i<12; i++) {

            tempSales.add( nSales.get(i)+"" );
            tempUnique.add( nUnique.get(i)+"" );
            tempExpenses.add( formatExpenses.format( expenses.get(i) ) );

            nTotalSales += nSales.get( i );
            nTotalUnique += nUnique.get( i );
            totalExpenses += expenses.get( i );
        }

        res.add( "# Sales", tempSales );
        res.add( "# Products", tempUnique );
        res.add( "$ Spent", tempExpenses );
        res.add( "*TotalSales: ", nTotalSales );
        res.add( "*TotalProducts: ", nTotalUnique );
        res.add( "*TotalExpense: ", formatExpenses.format( totalExpenses ) );

        paginate(res);
    }

    public static void Query5( HiperMercado hiper ) {
        String code;
        Scanner scanner = new Scanner(System.in);
        int month;
        ArrayList<Integer> nSales, nUnique;
        ArrayList<Double> expenses;
        Results res = new Results();
        int nTotalSales, nTotalUnique;
        double totalExpenses;
        LinkedList<String> tempSales, tempUnique, tempExpenses;
        DecimalFormat formatExpenses = new DecimalFormat("0.00");


        System.out.println("Insert Product Code: ");
        code = scanner.nextLine();

        try {
            nSales = hiper.getProductNSalesYearly(code);
            nUnique = hiper.getProductNUniqueProducts(code);
            expenses = hiper.getProductExpenses(code);

        }catch( ProductNotFoundException e) {
            System.out.println("No Product Found");
            return;
        }catch( SalesNotFoundException e ) {
            System.out.println("No Sales Found for specified Product");
            return;
        }

        nTotalSales = nTotalUnique = 0;
        totalExpenses = 0.0;
        tempExpenses = new LinkedList<>();
        tempSales = new LinkedList<>();
        tempUnique = new LinkedList<>();
        for(int i=0;i<12; i++) {

            tempSales.add( nSales.get(i)+"" );
            tempUnique.add( nUnique.get(i)+"" );
            tempExpenses.add( formatExpenses.format( expenses.get(i) ) );

            nTotalSales += nSales.get( i );
            nTotalUnique += nUnique.get( i );
            totalExpenses += expenses.get( i );
        }

        res.add( "# Sales", tempSales );
        res.add( "# Clients", tempUnique );
        res.add( "$ Spent", tempExpenses );
        res.add( "*TotalSales: ", nTotalSales );
        res.add( "*TotalClients: ", nTotalUnique );
        res.add( "*TotalExpense: ", formatExpenses.format( totalExpenses ) );

        paginate(res);
    }

    public static void Query6( HiperMercado hiper ) {
        Results res = new Results();
        ArrayList<SalesList> monthly;
        String code;
        Scanner scanner = new Scanner( System.in );
        LinkedList<String> countP, countN, expenseP, expenseN;
        DecimalFormat formatExpenses = new DecimalFormat("0.00");
        int nTotalP, nTotalN;
        double expensePTotal, expenseNTotal;

        System.out.println("Insert Product Code: ");
        code = scanner.nextLine();

        try {
            monthly = hiper.getProductMonthlyStats(code);

        }catch( ProductNotFoundException e) {
            System.out.println("No Product Found");
            return;
        }

        countP = new LinkedList<>();
        countN = new LinkedList<>();
        expenseP = new LinkedList<>();
        expenseN = new LinkedList<>();
        nTotalN = nTotalP = 0;
        expenseNTotal = expensePTotal = 0.0;
        for( SalesList s : monthly ) {

            countP.add( s.getTotalP()+"" );
            countN.add( s.getTotalN()+"" );
            expenseP.add( formatExpenses.format(s.getTotal$P()) );
            expenseN.add( formatExpenses.format( s.getTotal$N() ) );

            nTotalP += s.getTotalP();
            nTotalN += s.getTotalN();
            expensePTotal += s.getTotal$P();
            expenseNTotal += s.getTotal$N();
        }

        res.add( "*TotalP: ", nTotalP );
        res.add( "*TotalN: ", nTotalN );
        res.add( "*Expense P: ", expensePTotal );
        res.add( "*Expense N: ", expenseNTotal );

        res.add( "# Type P", countP );
        res.add( "# Type N", countN );
        res.add( "$ Type P", expenseP );
        res.add( "$ Type N", expenseN );

        paginate( res );
    }
/*
    public static void Query7( HiperMercado hiper ) {
        Results res = new Results();
        String client;
        Scanner scanner = new Scanner( System.in );
        LinkedList<String> prods;

        System.out.println("Insert Client: ");
        client = scanner.nextLine();


        try {
            prods = hiper.getMostBoughtProductsForClient( client );
        }catch( ClientNotFoundException e) {
            System.out.println("Client Not Found");
            return;
        }

        paginate(res);
    }
*/
    public static HiperMercado Query12() throws FileNotFoundException {
        Scanner scanner = new Scanner(System.in);
        HiperMercado hiper = new HiperMercado();
        String salesFile;
        Results res;

        System.out.println("Input Sales File: ");
        salesFile = scanner.nextLine();

        if (salesFile.length() == 0)
            salesFile = "Compras.txt";

        System.out.print("Reading ClientCatalog...");
        res = parseClientCatalog(hiper);

        System.out.println(res.get("nValid") + " Read, " + res.get("nInvalid") + " Invalid.");


        System.out.print("Reading ProductCatalog...");
        res = parseProductCatalog(hiper);
        System.out.println(res.get("nValid") + " Read, " + res.get("nInvalid") + " Invalid.");


        System.out.print("Reading " + salesFile + "...");
        res = parseSales(hiper, salesFile);
        System.out.println(res.get("nValid") + " Read, " + res.get("nInvalid") + " Invalid, " + res.get("null") + " Null.");
        System.out.print("Sorting Accounting...");
        hiper.getAcc().sortAcc();
        System.out.println("Done.");
        System.out.print("Sorting Sales...");
        hiper.getSales().sortSales();
        System.out.println("Done.");


        return hiper;
    }


    /**
     * Paginates Results
     * @param res
     */
    public static void paginate(Results res)
    {
        int nLists, maxEntries;
        TreeSet<String> columnNames = new TreeSet<>( res.getKeys() );
        String op = "";
        Scanner scanner = new Scanner( System.in );
        int nPage, maxPage;
        StringBuilder header = new StringBuilder();
        StringBuilder footer = new StringBuilder();
        StringBuilder footerBase = new StringBuilder();
        StringBuilder line = new StringBuilder();
        StringBuilder block = new StringBuilder();
        Boolean isEmpty = false;


        nLists = res.size();

        maxEntries = 0;
        nPage = 0;

        header.append( "| Idx" );
        for (int i = 0; i < 7; i++)
            header.append(" ");
        header.append("|");



        for( String key : columnNames ) {

            if( key.startsWith("*") )
                footerBase.append( key.substring(1) + res.get(key) + " | " );

            else {
                LinkedList<String> temp = (LinkedList) res.get(key);

                isEmpty = isEmpty | (temp.size() == 0);
                if (temp.size() > maxEntries)
                    maxEntries = temp.size();

                header.append(key);
                for (int i = 0; i < (10 - key.length()); i++)
                    header.append(" ");
                header.append("|");
            }
        }

        if( isEmpty ) {
            System.out.println("No Results");
            return;
        }

        maxPage = (int)Math.ceil( maxEntries / 10 );

        while( nPage != -1 ) {

            for(int i = 0; i < 20; i++)
                System.out.println("");

            System.out.println( header.toString() );

            block = new StringBuilder();
            for( int i = nPage * 10;
                 ( ( i < maxEntries ) &&  i < ( (nPage+1) * 10 ) );
                 i++){
                line = new StringBuilder();

                line. append( "| "+ (i+1) );
                for (int j = 0; j < (10 - ((i+1)+"").length()); j++)
                    line.append(" ");
                line.append("|");

                for( String key : columnNames ) {
                    if (key.startsWith("*"))
                        continue;
                    LinkedList<String> vals = (LinkedList)res.get( key );
                    String val = vals.get( i );

                    line.append("| "+ val );
                    for (int j = 0; j < (10 - val.length()); j++)
                        line.append(" ");
                    line.append("|");

                }

                block.append( line+ "\n");

            }
            System.out.println( block.toString() );
            footer = new StringBuilder ( footerBase.toString() + "Page: "+ (nPage+1)+ " / "+ (maxPage+1) );
            System.out.println( footer.toString() );


            if( scanner.hasNextLine() )
                op = scanner.nextLine();

            if( isNumeric( op ) )
                nPage = Integer.parseInt( op ) - 1;
            else {

                if( op.equals("n") )
                    nPage++;
                else {
                    if (op.equals("p"))
                        nPage--;
                    else {
                        if (op.equals("q"))
                            nPage = -1;
                    }
                }
            }


            if( nPage > maxPage )
                nPage = maxPage;

            if( ( nPage < 0 ) && (nPage != -1) )
                nPage = 0;
        }

    }


    /**
     * Parses Sales File and Registers each Sale into Hipermercado
     * also counts invalid Sales.
     *
     * @param hiperMercado
     * @param filename
     */
    private static Results parseSales(HiperMercado hiperMercado, String filename) throws FileNotFoundException {
        int nInvalidSales = 0;
        int nullSales = 0;
        Results res = new Results("null", "nValid", "nInvalid");


        try {
            BufferedReader br = new BufferedReader(new FileReader(filename));
            String line;
            String product, client, type;
            double price;
            int ammount, month;
            StringTokenizer tok;
            Sale s;


            while ((line = br.readLine()) != null) {
                tok = new StringTokenizer(line, " ", false);
                product = tok.nextToken();
                price = new Double(tok.nextToken());
                ammount = new Integer(tok.nextToken());
                type = tok.nextToken();
                client = tok.nextToken();
                month = new Integer(tok.nextToken());

                if (ammount == 0)
                    res.inc("null");

                try {

                    s = new Sale(month, ammount, price, new Product(product), new Client(client), type);
                    hiperMercado.registerSale(s);
                    res.inc("nValid");

                } catch (ClientNotFoundException | ProductNotFoundException p) {
                    res.inc("nInvalid");
                }

            }
            br.close();
        } catch (FileNotFoundException e) {
            throw e;

        } catch (IOException e) {
            e.printStackTrace();
        }

        return res;
    }

    /**
     * Parses default ClientCatalog's File
     * also outputs executionTime in seconds
     *
     * @param hiperMercado
     * @return Nº Invalid Clients
     */
    private static Results parseClientCatalog(HiperMercado hiperMercado) throws FileNotFoundException {
        int nInvalid = 0;
        Results res = new Results("nValid", "nInvalid");


        try {
            BufferedReader br = new BufferedReader(new FileReader("CatalogoClientes.txt"));
            String line;
            Crono.start();
            while ((line = br.readLine()) != null) {

                try {

                    hiperMercado.registerClient(line);
                    res.inc("nValid");

                } catch (ClientAlreadyExistsException e) {
                    res.inc("nInvalid");
                }

            }
            System.out.println(Crono.stop());
            br.close();
        } catch (FileNotFoundException e) {
            throw e;
        } catch (IOException e) {
            e.printStackTrace();
        }

        return res;
    }

    /**
     * Parses Default ProductCatalog's File
     * outputs executionTime in seconds
     *
     * @param hiperMercado
     * @return Nº Invalid Products
     */
    private static Results parseProductCatalog(HiperMercado hiperMercado) throws FileNotFoundException {
        Results res = new Results("nValid", "nInvalid");


        try {
            BufferedReader br = new BufferedReader(new FileReader("CatalogoProdutos.txt"));
            String line;
            Crono.start();
            while ((line = br.readLine()) != null) {
                try {

                    hiperMercado.registerProduct(line);
                    res.inc("nValid");

                } catch (ProductAlreadyExistsException e) {
                    res.inc("nInvalid");
                }

            }
            System.out.println(Crono.stop());
            br.close();
        } catch (FileNotFoundException e) {
            throw e;
        } catch (IOException e) {
            e.printStackTrace();
        }

        return res;
    }

    private static void scannerNoParse() {
        try {
            Scanner sc = new Scanner(new FileInputStream("Compras1.txt"));
            String line;
            Crono.start();
            while (sc.hasNextLine())
                line = sc.nextLine();
            System.out.println(Crono.stop());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void brNoParse() {
        try {
            BufferedReader br = new BufferedReader(new FileReader("Compras1.txt"));
            String line;
            Crono.start();
            while ((line = br.readLine()) != null)
                ;
            System.out.println(Crono.stop());
            br.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void scannerParse() {
        try {
            Scanner sc = new Scanner(new FileInputStream("Compras1.txt")).useLocale(Locale.US);
            String product, client, type;
            double price;
            int ammount, month;


            Crono.start();
            while (sc.hasNextLine()) {
                product = sc.next();
                price = sc.nextDouble();
                ammount = sc.nextInt();
                type = sc.next();
                client = sc.next();
                month = sc.nextInt();
            }
            System.out.println(Crono.stop());
            sc.close();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (NoSuchElementException e) {
            System.out.println(Crono.stop());
            System.out.println(e.getMessage());
        }
    }

    private static void brParse() {
        try {
            BufferedReader br = new BufferedReader(new FileReader("Compras1.txt"));
            String line;
            String product, client, type;
            double price;
            int ammount, month;
            StringTokenizer tok;
            Sale s;
            Crono.start();
            while ((line = br.readLine()) != null) {
                tok = new StringTokenizer(line, " ", false);
                product = tok.nextToken();
                price = new Double(tok.nextToken());
                ammount = new Integer(tok.nextToken());
                type = tok.nextToken();
                client = tok.nextToken();
                month = new Integer(tok.nextToken());

            }
            System.out.println(Crono.stop());
            br.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }


}