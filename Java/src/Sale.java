/**
 * Created by Diogo on 07/06/2015.
 */
public class Sale {
    int month, ammount;
    double price;
    String product, client, type;

    public Sale(int month, int ammount, double price, String product, String client, String type) {
        this.month = month;
        this.ammount = ammount;
        this.price = price;
        this.product = product;
        this.client = client;
        this.type = type;
    }

    public Sale() {
    }

    public Sale(Sale s) {
        this.month = s.getMonth();
        this.ammount = s.getAmmount();
        this.price = s.getPrice();
        this.product = s.getProduct();
        this.client = s.getClient();
        this.type = s.getType();
    }

    //<editor-fold desc="Geters and Setters">
    public int getMonth() {
        return month;
    }

    public void setMonth(int month) {
        this.month = month;
    }

    public int getAmmount() {
        return ammount;
    }

    public void setAmmount(int ammount) {
        this.ammount = ammount;
    }

    public double getPrice() {
        return price;
    }

    public void setPrice(double price) {
        this.price = price;
    }

    public String getProduct() {
        return product;
    }

    public void setProduct(String product) {
        this.product = product;
    }

    public String getClient() {
        return client;
    }

    public void setClient(String client) {
        this.client = client;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }
    //</editor-fold>


    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Sale sale = (Sale) o;

        if (month != sale.month) return false;
        if (ammount != sale.ammount) return false;
        if (Double.compare(sale.price, price) != 0) return false;
        if (!product.equals(sale.product)) return false;
        if (!client.equals(sale.client)) return false;
        return type.equals(sale.type);

    }

    @Override
    public int hashCode() {
        int result;
        long temp;
        result = month;
        result = 31 * result + ammount;
        temp = Double.doubleToLongBits(price);
        result = 31 * result + (int) (temp ^ (temp >>> 32));
        result = 31 * result + product.hashCode();
        result = 31 * result + client.hashCode();
        result = 31 * result + type.hashCode();
        return result;
    }


    @Override
    public String toString() {
        final StringBuilder sb = new StringBuilder("Sale{");
        sb.append("month=").append(month);
        sb.append(", ammount=").append(ammount);
        sb.append(", price=").append(price);
        sb.append(", product='").append(product).append('\'');
        sb.append(", client='").append(client).append('\'');
        sb.append(", type='").append(type).append('\'');
        sb.append('}');
        return sb.toString();
    }


}
