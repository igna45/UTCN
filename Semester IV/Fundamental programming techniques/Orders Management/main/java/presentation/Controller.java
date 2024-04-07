package presentation;

import business_logic.ClientBLL;
import business_logic.OrderBLL;
import business_logic.ProductBLL;
import model.Client;
import model.Order;
import model.Product;

import java.util.List;

/**
 * Clasa Controller pentru gestionarea operatiunilor de baza ale aplicatiei.
 */
public class Controller {
    private ClientBLL clientBLL;
    private ProductBLL productBLL;
    private OrderBLL orderBLL;

    /**
     * Constructorul clasei Controller.
     */
    public Controller() {
        clientBLL = new ClientBLL();
        productBLL = new ProductBLL();
        orderBLL = new OrderBLL();
    }

    /**
     * Adauga un client nou in baza de date.
     *
     * @param client obiectul Client ce va fi adaugat
     */
    public void addClient(Client client) {
        clientBLL.addClient(client);
    }

    /**
     * Modifica un client existent in baza de date.
     *
     * @param client obiectul Client ce va fi modificat
     */
    public void editClient(Client client) {
        clientBLL.editClient(client);
    }


    /**
     * Sterge un client din baza de date folosind ID-ul acestuia.
     *
     * @param clientId ID-ul clientului care va fi sters
     */
    public void deleteClient(int clientId) {
        clientBLL.deleteClient(clientId);
    }

    /**
     * Returneaza o lista cu toti clientii din baza de date.
     *
     * @return lista cu toti clientii
     */
    public List<Client> getAllClients() {
        return clientBLL.getAllClients();
    }

    /**
     * Adauga un produs nou in baza de date.
     *
     * @param product obiectul Product ce va fi adaugat
     */
    public void addProduct(Product product) {
        productBLL.addProduct(product);
    }

    /**
     * Modifica un produs existent in baza de date.
     *
     * @param product obiectul Product ce va fi modificat
     */
    public void editProduct(Product product) {
        productBLL.editProduct(product);
    }

    /**
     * Sterge un produs din baza de date folosind ID-ul acestuia.
     *
     * @param productId ID-ul produsului care va fi sters
     */
    public void deleteProduct(int productId) {
        productBLL.deleteProduct(productId);
    }

    /**
     * Returneaza o lista cu toate produsele din baza de date.
     *
     * @return lista cu toate produsele
     */
    public List<Product> getAllProducts() {
        return productBLL.getAllProducts();
    }

    /**
     * Creeaza o comanda noua.
     *
     * @param order obiectul Order ce va fi creat
     * @return true daca comanda a fost creata cu succes, altfel false
     */
    public boolean createOrder(Order order) {
        orderBLL.createOrder(order);
        return false;
    }

    /**
     * Returneaza o lista cu toate comenzile din baza de date.
     *
     * @return lista cu toate comenzile
     */
    public List<Order> getAllOrders() {
        return orderBLL.getAllOrders();
    }

}
