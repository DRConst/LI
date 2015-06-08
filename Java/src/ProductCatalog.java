import java.util.HashMap;
import java.util.Map;

/**
 * Created by Diogo on 03/06/2015.
 */
public class ProductCatalog
{

    private HashMap<String, Product> productCatalog;

    ProductCatalog()
    {
        this.productCatalog = new HashMap<>();
    }

    ProductCatalog(ProductCatalog cCat)
    {
        this.productCatalog = new HashMap<>(cCat.getProductCount());

        for(Product cli : cCat.getProductCatalog().values())
        {
            this.productCatalog.put(cli.getCode(), cli.clone());
        }
    }

    public Map<String, Product> getProductCatalog(){

    HashMap<String, Product> toRet = new HashMap<>();

    for(Product pr : this.productCatalog.values())
    {
        this.productCatalog.put(pr.getCode(), pr.clone());
    }

    return toRet;

    }

    public int getProductCount()
    {
        return productCatalog.size();
    }

    public boolean existsProduct(String code)
    {
        return this.productCatalog.containsKey(code);
    }

    public Product getProduct(String code) throws ProductNotFoundException
    {
        Product p = this.productCatalog.get(code);
        if(p != null)
            return p;
        else
        {
            throw new ProductNotFoundException("Product " + p.getCode() + " Not Found.");
        }
    }

    public void insertProduct(Product p) throws ProductAlreadyExistsException
    {
        if(this.productCatalog.put(p.getCode(), p) == null)
            throw new ProductAlreadyExistsException("Product " + p.getCode() + " Already In Catalog.");
    }



}
