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
            this.clientCatalog.put(cli.getCode(), cli);
        }
    }

    public Map<String, Client> getClientCatalog() {

        HashMap<String, Client> toRet = new HashMap<>();

        for(Client cli : this.clientCatalog.values())
        {
            this.clientCatalog.put(cli.getCode(), cli.clone());
        }

        return toRet;
    }

    public int getClientCount()
    {
        return clientCatalog.size();
    }

    public boolean existsClient(String code)
    {
        return this.clientCatalog.containsKey(code);
    }

    public Client getClient(String code) throws ClientNotFoundException
    {
        Client p = this.clientCatalog.get(code);
        if(p != null)
            return p;
        else
        {
            throw new ClientNotFoundException("Client " + p.getCode() + " Not Found.");
        }
    }

    public void insertClient(Client p) throws ClientAlreadyExistsException
    {
        if(this.clientCatalog.put(p.getCode(), p) == null)
            throw new ClientAlreadyExistsException("Client " + p.getCode() + " Already In Catalog.");
    }
}
