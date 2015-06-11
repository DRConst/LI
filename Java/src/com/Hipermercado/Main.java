package com.Hipermercado;


import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

/**
 * Main, Class interacting with user and holding primary instances
 * @author LI_Grupo 6
 */
public class Main {

    public static void main(String[] args) {
	    int userOpt;

        Hipermercado hiper = new Hipermercado();

        /*
        Sales testSales = new Sales();
        Sale s1,s2,s3,s4,s5,s6,s7,s8;
        Product prod1,prod2,prod3,prod4,prod5,prod6;
        Client cl1,cl2,cl3,cl4,cl5,cl6;

        prod1 = new Product( "AX5023" );
        prod2 = new Product( "TA9952" );
        prod3 = new Product( "AA6126" );
        prod4 = new Product( "YS2863" );
        prod5 = new Product( "BB6013" );
        prod6 = new Product( "OL2332" );

        cl1 = new Client("AD001");
        cl2 = new Client("AD002");
        cl3 = new Client("CK503");
        cl4 = new Client("QA832");
        cl5 = new Client("GO965");
        cl6 = new Client("LA615");

        s1 = new Sale( 5, 7, 3.21, prod1, cl2, "P");

        s2 = new Sale( 12, 5, 12.1, prod5, cl2, "N");

        s3 = new Sale( 1, 2, 0.62, prod1, cl6, "N");

        s4 = new Sale( 1, 5, 8.34, prod2, cl3, "P");
        s5 = new Sale( 1, 12, 73.25, prod6, cl1, "P");
        s6 = new Sale( 7, 1, 1.96, prod6, cl2, "P");
        s7 = new Sale( 5, 6, 6.16, prod1, cl4, "N");
        s8 = new Sale( 9, 2, 2.88, prod3, cl1, "P");
        */

        do {
            userOpt = menu();

            switch( userOpt ) {

                case 1:
                    /*
                    try {
                        testSales.registerProd( prod1 );
                        testSales.registerProd( prod2 );
                //      testSales.registerProd( prod3 );
                        testSales.registerProd( prod4 );
                        testSales.registerProd( prod5 );
                        testSales.registerProd( prod6 );

                    } catch (ProductAlreadyExistsException e) {
                        e.printStackTrace();
                    }

                    try {
                        testSales.registerCli( cl1 );
                        testSales.registerCli( cl2 );
                        testSales.registerCli( cl3 );
                        testSales.registerCli( cl4 );
                        testSales.registerCli( cl5 );
                        testSales.registerCli( cl6 );
                    } catch (ClientAlreadyExistsException e) {
                        e.printStackTrace();
                    }


                    try {
                        testSales.registerSale( s1 );
                        testSales.registerSale( s2 );
                        testSales.registerSale( s3 );
                        testSales.registerSale( s4 );
                        testSales.registerSale( s5 );
                        testSales.registerSale( s6 );
                        testSales.registerSale( s7 );
                        testSales.registerSale( s8 );
                    } catch (ProductNotFoundException | ClientNotFoundException e) {
                        e.printStackTrace();
                    }*/

                    parseClientCatalog(hiper);
                    parseProductCatalog(hiper);

                    break;


                case 2:
                    /*
                    TreeMap<Product, MonthlySales> treeProd = testSales.getSortedSalesProd();
                    TreeMap<Client, MonthlySales> treeCli = testSales.getSortedSalesCli();

                    MonthlySales monthly = testSales.getMonthlyProd( prod5 );
                    */
                    break;

                case 3:
                    break;

                case 4:
                    System.out.println("hai");
                    break;

                case 5:
                    break;

                case 6:
                    break;

                case 7:
                    break;

                case 8:
                    break;

                case 9:
                    break;

                case 10:
                    System.out.println("yep");
                    break;

                case 11:
                    break;

                case 12:
                    break;

                case 13:
                    break;

                case 14:
                    break;

                default:
                    // doSaveToFile
                    break;
            }

            pageClear();

        }while( userOpt != 0 );

    }


    /**
     * Main Menu listing user options
     *  also gets user selection and validates it
     * @return  user option
     */
    public static int menu()
    {
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

        return getIntOpt(0,14);
    }


    /**
     * Asks for number in interval [min, max]
     * @param min inferior limit
     * @param max superior limit
     * @return valid user number
     */
    public static int getIntOpt(int min, int max)
    {
        Scanner scanner = new Scanner(System.in);
        boolean done = false;
        int input = max;

        System.out.println("Insert a number between " + min + " and " + max + ".\n");

        do
        {
            if (!scanner.hasNextInt())
            {
                System.out.println("Please insert an integer value.");
                scanner.nextLine();
            }
            else
            {
                input = scanner.nextInt();
                if (input < min || input > max)
                    System.out.println("The value must be between " + min + " and " + max + ".");
                else
                    done = true;
            }
        }while(!done);
        scanner.nextLine();
        return input;
    }


    /**
     * 'Cleaning' terminal
     */
    public static void pageClear()
    {
        Scanner scanner = new Scanner( System.in );


        scanner.nextLine();
        for (int i=0;i<50;i++)
            System.out.println ("\n");


    }

    private static void parseSales(Hipermercado hipermercado, String filename)
    {
        try {
            BufferedReader br = new BufferedReader(new FileReader(filename));
            String line;
            String product, client, type;
            double price;
            int ammount, month;
            StringTokenizer tok;
            Sale s;
            while((line = br.readLine()) != null)
            {
                tok = new StringTokenizer(line, " ", false);
                product = tok.nextToken();
                price = new Double(tok.nextToken());
                ammount = new Integer(tok.nextToken());
                type = tok.nextToken();
                client = tok.nextToken();
                month = new Integer(tok.nextToken());
                s = new Sale(month, ammount, price,hipermercado.getProductCatalog().getProduct(product), hipermercado.getClientCatalog().getClient(client), type);
                hipermercado.registerSale(s);
            }
            br.close();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ClientNotFoundException e) {
            e.printStackTrace();
        } catch (ProductNotFoundException e) {
            e.printStackTrace();
        }
    }

    private static void parseClientCatalog(Hipermercado hipermercado)
    {
        try {
            BufferedReader br = new BufferedReader(new FileReader("CatalogoClientes.txt"));
            String line;
            Crono.start();
            while((line = br.readLine()) != null)
            {
                hipermercado.registerClient(line);
            }
            System.out.println(Crono.stop());
            br.close();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ClientAlreadyExistsException e)
        {

        }
    }

    private static void parseProductCatalog(Hipermercado hipermercado)
    {
        try {
            BufferedReader br = new BufferedReader(new FileReader("CatalogoProdutos.txt"));
            String line;
            Crono.start();
            while((line = br.readLine()) != null)
            {
                hipermercado.registerProduct(line);
            }
            System.out.println(Crono.stop());
            br.close();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ProductAlreadyExistsException e)
        {

        }
    }

    private static void scannerNoParse()
    {
        try {
            Scanner sc = new Scanner(new FileInputStream("Compras1.txt"));
            String line;
            Crono.start();
            while(sc.hasNextLine())
                line = sc.nextLine();
            System.out.println(Crono.stop());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static  void brNoParse()
    {
        try {
            BufferedReader br = new BufferedReader(new FileReader("Compras1.txt"));
            String line;
            Crono.start();
            while((line = br.readLine()) != null)
                ;
            System.out.println(Crono.stop());
            br.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void scannerParse()
    {
        try {
            Scanner sc = new Scanner(new FileInputStream("Compras1.txt")).useLocale(Locale.US);
            String product, client, type;
            double price;
            int ammount, month;


            Crono.start();
            while(sc.hasNextLine())
            {
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
        }   catch (NoSuchElementException e)
        {
            System.out.println(Crono.stop());
            System.out.println(e.getMessage());
        }
    }

    private static  void brParse()
    {
        try {
            BufferedReader br = new BufferedReader(new FileReader("Compras1.txt"));
            String line;
            String product, client, type;
            double price;
            int ammount, month;
            StringTokenizer tok;
            Sale s;
            Crono.start();
            while((line = br.readLine()) != null)
            {
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
