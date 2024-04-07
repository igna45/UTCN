package business_logic;

import data_access.OrderDAO;
import model.Order;

import java.util.List;

/**
 * Clasa OrderBLL gestioneaza operatiile pentru comenzi.
 */
public class OrderBLL {
    private OrderDAO orderDAO;

    /**
     * Constructorul implicit al clasei OrderBLL.
     */
    public OrderBLL() {
        orderDAO = new OrderDAO();
    }

    /**
     * Creeaza o comanda noua in baza de date.
     *
     * @param order Obiectul Order ce trebuie adaugat
     * @return true daca operatia a avut succes, false altfel
     */
    public boolean createOrder(Order order) {
        return orderDAO.insert(order);
    }

    /**
     * Returneaza o lista cu toate comenzile din baza de date.
     *
     * @return Lista de comenzi
     */
    public List<Order> getAllOrders() {
        return orderDAO.findAll();
    }

}