package business_logic;

import data_access.ProductDAO;
import model.Product;

import java.util.List;

/**
 * Clasa ProductBLL gestioneaza operatiile pentru produse.
 */
public class ProductBLL {
    private ProductDAO productDAO;

    /**
     * Constructorul implicit al clasei ProductBLL.
     */
    public ProductBLL() {
        productDAO = new ProductDAO();
    }

    /**
     * Adauga un produs nou in baza de date.
     *
     * @param product Obiectul Product ce trebuie adaugat
     * @return true daca operatia a avut succes, false altfel
     */
    public boolean addProduct(Product product) {
        return productDAO.insert(product);
    }

    /**
     * Modifica datele unuiprodus existent in baza de date.
     *
     * @param product Obiectul Product cu datele actualizate
     * @return true daca operatia a avut succes, false altfel
     */
    public boolean editProduct(Product product) {
        return productDAO.update(product);
    }

    /**
     * Sterge un produs din baza de date dupa ID.
     *
     * @param productId ID-ul produsului ce trebuie sters
     * @return true daca operatia a avut succes, false altfel
     */
    public boolean deleteProduct(int productId) {
        return productDAO.delete(productId);
    }

    /**
     * Returneaza o lista cu toate produsele din baza de date.
     *
     * @return Lista de produse
     */
    public List<Product> getAllProducts() {
        return productDAO.findAll();
    }

    /**
     * Cauta un produs dupa ID in baza de date.
     *
     * @param productId ID-ul produsului ce trebuie gasit
     * @return Obiectul Product daca a fost gasit, null altfel
     */
    public Product getProductById(int productId) {
        return productDAO.findProductById(productId);
    }
}