package model;

/**
 * Clasa Product reprezinta un produs in sistem.
 */
public class Product {
    private int product_id;
    private String name;
    private double price;
    private int current_stock;

    /**
     * Constructorul cu parametri al clasei Product.
     *
     * @param product_id    ID-ul produsului
     * @param name          Numele produsului
     * @param price         Pretul produsului
     * @param current_stock Stocul curent al produsului
     */
    public Product(int product_id, String name, double price, int current_stock) {
        this.product_id = product_id;
        this.name = name;
        this.price = price;
        this.current_stock = current_stock;
    }

    /**
     * Constructorul implicit al clasei Product.
     */
    public Product() {

    }

    /**
     * Constructorul cu parametri al clasei Product fara ID.
     *
     * @param name          Numele produsului
     * @param price         Pretul produsului
     * @param current_stock Stocul curent al produsului
     */
    public Product(String name, int price, int current_stock) {
        this.name = name;
        this.price = price;
        this.current_stock = current_stock;
    }

    /**
     * Returneaza ID-ul produsului.
     *
     * @return ID-ul produsului
     */
    public int getId() {
        return product_id;
    }

    /**
     * Seteaza ID-ul produsului.
     *
     * @param product_id ID-ul de setat
     */
    public void setId(int product_id) {
        this.product_id = product_id;
    }

    /**
     * Returneaza numele produsului.
     *
     * @return Numele produsului
     */
    public String getName() {
        return name;
    }

    /**
     * Seteaza numele produsului.
     *
     * @param name Numele de setat
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     * Returneaza pretul produsului.
     *
     * @return Pretul produsului
     */
    public double getPrice() {
        return price;
    }

    /**
     * Seteaza pretul produsului.
     *
     * @param price Pretul de setat
     */
    public void setPrice(double price) {
        this.price = price;
    }

    /**
     * Returneaza stocul curent al produsului.
     *
     * @return Stocul curent
     */
    public int getCurrent_stock() {
        return current_stock;
    }

    /**
     * Seteaza stocul curent al produsului.
     *
     * @param current_stock Stocul de setat
     */
    public void setCurrent_stock(int current_stock) {
        this.current_stock = current_stock;
    }

    /**
     * Returneaza o reprezentare textuala a obiectului Product.
     *
     * @return Un sir de caractere ce descrie obiectul Product
     */
    @Override
    public String toString() {
        return "Product{" +
                "id=" + product_id +
                ", name='" + name + '\'' +
                ", price=" + price +
                ", current_stock=" + current_stock +
                '}';
    }
}
