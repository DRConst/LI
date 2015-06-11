package com.GestHiper;


import com.Hipermercado.*;

import java.util.Scanner;
import java.util.TreeMap;

/**
 * Main, Class interacting with user and holding primary instances
 * @author LI_Grupo 6
 */
public class Main {

    public static void main(String[] args) {
	    int userOpt;
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


        do {
            userOpt = menu();

            switch( userOpt ) {

                case 1:
                    testSales.registerSale( s1 );
                    testSales.registerSale( s2 );
                    testSales.registerSale( s3 );
                    testSales.registerSale( s4 );
                    testSales.registerSale( s5 );
                    testSales.registerSale( s6 );
                    testSales.registerSale( s7 );
                    testSales.registerSale( s8 );
                    break;

                case 2:
                    TreeMap<Product, MonthlySales> tree = testSales.getSortedSalesProd();
                    MonthlySales monthly = testSales.getMonthlyProd( prod5 );
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
                + "\t3\t- Nº Sales/Clients, given month;\n"
                + "\t4\t- Nº Sales/Products/$ for each month, given client;\n"
                + "\t5\t- Nº Sales/Clients/$ for each month, given product;\n"
                + "\t6\t- Nº N/P Sales and $ for each month, given product;\n"
                + "\t7\t- List Most Bought Products, desc:qtd,alph, given client;\n"
                + "\t8\t- List N Most Bought Products & their Nº Unique Clients;\n"
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

}
