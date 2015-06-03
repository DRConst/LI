import java.util.HashMap;
import java.util.Map;

/**
 * Created by Diogo on 03/06/2015.
 */
public class ClientCatalog
{



    private HashMap<String, Client> clientCatalog;

    ClientCatalog()
    {
        this.clientCatalog = new HashMap<>();
    }

    ClientCatalog(ClientCatalog cCat)
    {
        this.clientCatalog = new HashMap<>(cCat.getClientCount());

        for(Client cli : cCat.getClientCatalog().values())
        {
            this.clientCatalog.put(cli.getCode(), cli.clone());
        }
    }

    public Map<String, Client> getClientCatalog() {
        return clientCatalog;
    }

    public int getClientCount()
    {
        return clientCatalog.size();
    }

}
