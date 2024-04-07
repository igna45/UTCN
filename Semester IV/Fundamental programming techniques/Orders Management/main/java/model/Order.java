package model;

/**
 * Clasa Order reprezinta o comanda in sistem.
 */
public class Order {
    private int id;
    private int client_id;
    private int product_id;
    private int quantity;

    /**
     * Constructorul implicit al clasei Order.
     */
    public Order() {

    }

    /**
     * Constructorul clasei Order.
     *
     * @param client_id  ID-ul clientului care face comanda
     * @param product_id ID-ul produsului comandat
     * @param quantity   Cantitatea de produs comandata
     */
    public Order(int client_id, int product_id, int quantity) {
        this.client_id = client_id;
        this.product_id = product_id;
        this.quantity = quantity;
    }

    /**
     * Returneaza ID-ul comenzii.
     *
     * @return ID-ul comenzii
     */
    public int getId() {
        return id;
    }

    /**
     * Seteaza ID-ul comenzii.
     *
     * @param id ID-ul de setat
     */
    public void setId(int id) {
        this.id = id;
    }

    /**
     * Returneaza ID-ul clientului care a facut comanda.
     *
     * @return ID-ul clientului
     */
    public int getClient_id() {
        return client_id;
    }

    /**
     * Seteaza ID-ul clientului care a facut comanda.
     *
     * @param client_id ID-ul de setat
     */
    public void setClient_id(int client_id) {
        this.client_id = client_id;
    }

    /**
     * Returneaza ID-ul produsului comandat.
     *
     * @return ID-ul produsului
     */
    public int getProduct_id() {
        return product_id;
    }

    /**
     * Seteaza ID-ul produsului comandat.
     *
     * @param product_id ID-ul de setat
     */
    public void setProduct_id(int product_id) {
        this.product_id = product_id;
    }

    /**
     * Returneaza cantitatea de produs comandata.
     *
     * @return Cantitatea comandata
     */
    public int getQuantity() {
        return quantity;
    }

    /**
     * Seteaza cantitatea de produs comandata.
     *
     * @param quantity Cantitatea de setat
     */
    public void setQuantity(int quantity) {
        this.quantity = quantity;
    }

    /**
     * Returneaza o reprezentare textuala a obiectului Order.
     *
     * @return Un sir de caractere ce descrie obiectul Order
     */
    @Override
    public String toString() {
        return "Order{" +
                "id=" + id +
                ", client_id=" + client_id +
                ", product_id=" + product_id +
                ", quantity=" + quantity +
                '}';
    }
}
