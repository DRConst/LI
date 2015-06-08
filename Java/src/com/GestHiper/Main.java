package com.GestHiper;


import java.util.Scanner;

/**
 * Main, Class interacting with user and holding primary instances
 * @author LI_Grupo 6
 */
public class Main {

    public static void main(String[] args) {
	    int userOpt;


        do {
            userOpt = menu();

            switch( userOpt ) {

                case 1:
                    break;

                case 2:
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
