package data_access;

import connection.ConnectionFactory;
import model.Product;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

/**
 * Clasa pentru manipularea datelor produselor din baza de date.
 */
public class ProductDAO {
    private static final String INSERT_QUERY = "INSERT INTO product (name, price, current_stock) VALUES (?, ?, ?)";
    private static final String UPDATE_QUERY = "UPDATE product SET name = ?, price = ?, current_stock = ? WHERE product_id = ?";
    private static final String DELETE_QUERY = "DELETE FROM product WHERE product_id = ?";
    private static final String FIND_ALL_QUERY = "SELECT * FROM product";
    private static final String FIND_BY_ID_QUERY = "SELECT * FROM `product` WHERE id = ?";

    /**
     * Gaseste un produs dupa ID in baza de date.
     *
     * @param productId ID-ul produsului cautat
     * @return Un obiect Product daca produsul a fost gasit, altfel 'null'
     */
    public Product findProductById(int productId) {
        Product product = null;

        try (Connection connection = ConnectionFactory.getConnection();
             PreparedStatement preparedStatement = connection.prepareStatement(FIND_BY_ID_QUERY)) {

            preparedStatement.setInt(1, productId);
            ResultSet resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                product = new Product();
                product.setId(resultSet.getInt("id"));
                product.setName(resultSet.getString("name"));
                product.setCurrent_stock(resultSet.getInt("stock"));
                product.setPrice(resultSet.getDouble("price"));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return product;
    }

    /**
     * Insereaza un nou produs in baza de date.
     *
     * @param product obiectul Product care contine datele noului produs
     * @return 'true' daca inserarea a avut succes, 'false' in caz contrar
     */
    public boolean insert(Product product) {
        try (Connection connection = ConnectionFactory.getConnection();
             PreparedStatement preparedStatement = connection.prepareStatement(INSERT_QUERY, Statement.RETURN_GENERATED_KEYS)) {

            preparedStatement.setString(1, product.getName());
            preparedStatement.setDouble(2, product.getPrice());
            preparedStatement.setInt(3, product.getCurrent_stock());

            int affectedRows = preparedStatement.executeUpdate();

            if (affectedRows == 0) {
                throw new SQLException("Creating product failed, no rows affected.");
            }

            try (ResultSet generatedKeys = preparedStatement.getGeneratedKeys()) {
                if (generatedKeys.next()) {
                    product.setId(generatedKeys.getInt(1));
                } else {
                    throw new SQLException("Creating product failed, no ID obtained.");
                }
            }
            return true;
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }

    /**
     * Actualizeaza un produs existent in baza de date.
     *
     * @param product obiectul Product care contine datele actualizate ale produsului
     * @return 'true' daca actualizarea a avut succes, 'false' in caz contrar
     */
    public boolean update(Product product) {
        try (Connection connection = ConnectionFactory.getConnection();
             PreparedStatement preparedStatement = connection.prepareStatement(UPDATE_QUERY)) {

            preparedStatement.setString(1, product.getName());
            preparedStatement.setDouble(2, product.getPrice());
            preparedStatement.setInt(3, product.getCurrent_stock());
            preparedStatement.setInt(4, product.getId());

            preparedStatement.executeUpdate();
            return true;
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }

    /**
     * Sterge un produs din baza de date.
     *
     * @param productId ID-ul produsului care trebuie sters
     * @return 'true' daca stergerea a avut succes, 'false' in caz contrar
     */
    public boolean delete(int productId) {
        try (Connection connection = ConnectionFactory.getConnection();
             PreparedStatement preparedStatement = connection.prepareStatement(DELETE_QUERY)) {

            preparedStatement.setInt(1, productId);
            preparedStatement.executeUpdate();
            return true;
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }

    /**
     * Returneaza o lista cu toate produsele din baza de date.
     *
     * @return Lista de produse sau o lista goala daca nu exista produse in baza de date
     */
    public List<Product> findAll() {
        List<Product> products = new ArrayList<>();

        try (Connection connection = ConnectionFactory.getConnection();
             PreparedStatement preparedStatement = connection.prepareStatement(FIND_ALL_QUERY);
             ResultSet resultSet = preparedStatement.executeQuery()) {

            while (resultSet.next()) {
                Product product = new Product();
                product.setId(resultSet.getInt("product_id"));
                product.setName(resultSet.getString("name"));
                product.setPrice(resultSet.getDouble("price"));
                product.setCurrent_stock(resultSet.getInt("current_stock"));
                products.add(product);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return products;
    }
}
