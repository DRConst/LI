import java.util.HashMap;
import java.util.Map;

/**
 * Created by Diogo on 03/06/2015.
 */
public class ProductCatalog
{



    private HashMap<String, Product> ProductCatalog;

    ProductCatalog()
    {
        this.ProductCatalog = new HashMap<>();
    }

    ProductCatalog(ProductCatalog cCat)
    {
        this.ProductCatalog = new HashMap<>(cCat.getProductCount());

        for(Product cli : cCat.getProductCatalog().values())
        {
            this.ProductCatalog.put(cli.getCode(), cli.clone());
        }
    }

    public Map<String, Product> getProductCatalog() {
        return ProductCatalog;
    }

    public int getProductCount()
    {
        return ProductCatalog.size();
    }

}
