/**
 * Created by Diogo on 03/06/2015.
 */
public class Client {

    String code;

    Client()
    {

    }

    Client(String code)
    {
        this.code = code;
    }

    Client(Client c)
    {
        this.code = c.getCode();
    }

    public String getCode() {
        return code;
    }

    public Client clone()
    {
        return new Client(this);
    }
}
