package data_access;

import connection.ConnectionFactory;
import model.Order;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;


/**
 * Clasa pentru manipularea datelor comenzilor din baza de date.
 */
public class OrderDAO {
    private static final String INSERT_QUERY = "INSERT INTO `order` (client_id, product_id, quantity) VALUES (?, ?, ?)";
    private static final String FIND_ALL_QUERY = "SELECT * FROM `order`";

    /**
     * Insereaza o noua comanda in baza de date.
     *
     * @param order obiectul Order care contine datele noii comenzi
     * @return 'true' daca inserarea a avut succes, 'false' in caz contrar
     */
    public boolean insert(Order order) {
        try (Connection connection = ConnectionFactory.getConnection();
             PreparedStatement preparedStatement = connection.prepareStatement(INSERT_QUERY, Statement.RETURN_GENERATED_KEYS)) {

            preparedStatement.setInt(1, order.getClient_id());
            preparedStatement.setInt(2, order.getProduct_id());
            preparedStatement.setInt(3, order.getQuantity());

            int affectedRows = preparedStatement.executeUpdate();

            if (affectedRows == 0) {
                throw new SQLException("Creating order failed, no rows affected.");
            }

            try (ResultSet generatedKeys = preparedStatement.getGeneratedKeys()) {
                if (generatedKeys.next()) {
                    order.setId(generatedKeys.getInt(1));
                } else {
                    throw new SQLException("Creating order failed, no ID obtained.");
                }
            }
            return true;
        } catch (SQLException e) {
            System.out.println("Error while inserting order: " + order);
            e.printStackTrace();
            return false;
        }
    }

    /**
     * Returneaza o lista cu toate comenzile din baza de date.
     *
     * @return Lista de comenzi sau o lista goala daca nu exista comenzi in baza de date
     */
    public List<Order> findAll() {
        List<Order> orders = new ArrayList<>();

        try (Connection connection = ConnectionFactory.getConnection();
             PreparedStatement preparedStatement = connection.prepareStatement(FIND_ALL_QUERY);
             ResultSet resultSet = preparedStatement.executeQuery()) {

            while (resultSet.next()) {
                Order order = new Order();
                order.setId(resultSet.getInt("id"));
                order.setClient_id(resultSet.getInt("client_id"));
                order.setProduct_id(resultSet.getInt("product_id"));
                order.setQuantity(resultSet.getInt("quantity"));
                orders.add(order);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return orders;
    }
}

