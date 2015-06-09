// Sales

public class Sales {
	private salesMeta = new TreeMap< Product, SalesMetaMonthly >();		// Ordered desc by nSales( totalP + totalN )
}

public class SalesMetaMonthly {
	private monthly = new ArrayList< ListMetaSales >( 12 );
	
	private int totalP;		// sum of all months's MetaSales nTypeP
	private int totalN;		//	...
	
	private double total$P;	//	...
	private double total$N;	//	...
	
	private int totalAmount;	// sum of all months's MetaSales's amounts
}

public class ListMetaSales {
	private listMeta = new OrderedSet<MetaSale>();	// Ordered by amount,alpha | no repetitions
	// Each MetaSale Holds Product/Client SaleMeta for an entire month
}

public class MetaSale {
	private String key;					// AX702
	private	int nTypeN, nTypeP, amount;	// amount: 12 | nTypeP: 2 | nTypeN: 1
	private double $TypeN, $TypeP;		// $TypeP: 8.25 | $TypeN: 2.51
}


			1 ...		
			2	-> { AX702, BA051, ... }
EE6660 -> 	3 ...		|
			4 ...		->[ key: AX702 | amount: 12 | nTypeP: 2 | nTypeN: 1 | $TypeP: 8.25 | $TypeN: 2.51 ]
		   ...
			12

		   