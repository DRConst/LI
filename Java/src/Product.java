/**
 * Created by Diogo on 03/06/2015.
 */
public class Product {

    String code;

    Product()
    {

    }

    Product(String code)
    {
        this.code = code;
    }

    Product(Product c)
    {
        this.code = c.getCode();
    }

    public String getCode() {
        return code;
    }

    public Product clone()
    {
        return new Product(this);
    }
}
