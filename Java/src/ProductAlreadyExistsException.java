/**
 * Created by Diogo on 07/06/2015.
 */
public class ProductAlreadyExistsException extends Exception {

    public ProductAlreadyExistsException()
    {
        super();
    }

    public ProductAlreadyExistsException(String s){ super(s); }
}
