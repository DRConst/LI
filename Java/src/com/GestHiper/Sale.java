package com.GestHiper;

/**
 *  Sale Class
 *  @author     Diogo
 *  @since      07/06/2015
 */
public class Sale {
    private int month, amount;
    private double price;
    private String type;
	private Product product;
	private Client client; 

    public Sale(int month, int amount, double price, Product product, Client client, String type) {
        this.month = month;
        this.amount = amount;
        this.price = price;
        this.product = product.clone();
        this.client = client.clone();
        this.type = type;
    }

    public Sale() {
    }

    public Sale(Sale s) {
        this.month = s.getMonth();
        this.amount = s.getAmount();
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

    public int getAmount() {
        return amount;
    }

    public void setAmount(int amount) {
        this.amount = amount;
    }

    public double getPrice() {
        return price;
    }

    public void setPrice(double price) {
        this.price = price;
    }

    public Product getProduct() {
        return product.clone();
    }

    public void setProduct(Product product) {
        this.product = product.clone();
    }

    public Client getClient() {
        return client.clone();
    }

    public void setClient(Client client) {
        this.client = client.clone();
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

        if (month != sale.getMonth() ) return false;
        if (amount != sale.getAmount() ) return false;
        if (Double.compare(sale.getPrice() , price) != 0) return false;
        if (!product.equals( sale.getProduct() ) ) return false;
        if (!client.equals( sale.getClient() ) ) return false;
        return type.equals( sale.getType() );

    }

    @Override
    public int hashCode() {
        int result;
        long temp;
        result = month;
        result = 31 * result + amount;
        temp = Double.doubleToLongBits(price);
        result = 31 * result + (int) (temp ^ (temp >>> 32));
        result = 31 * result + product.hashCode();
        result = 31 * result + client.hashCode();
        result = 31 * result + type.hashCode();
        return result;
    }


    @Override
    public String toString() {
        final StringBuilder sb = new StringBuilder("com.GestHiper.Sale{");
        sb.append("month=").append(month);
        sb.append(", amount=").append(amount);
        sb.append(", price=").append(price);
        sb.append(", product='").append(product).append('\'');
        sb.append(", client='").append(client).append('\'');
        sb.append(", type='").append(type).append('\'');
        sb.append('}');
        return sb.toString();
    }

    public Sale clone()
    {
        return new Sale(this);
    }


}
