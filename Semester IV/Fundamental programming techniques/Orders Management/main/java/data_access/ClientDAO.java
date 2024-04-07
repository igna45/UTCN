package data_access;

import connection.ConnectionFactory;
import model.Client;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

/**
 * Clasa pentru manipularea datelor clientilor din baza de date.
 */
public class ClientDAO {
    private static final String INSERT_QUERY = "INSERT INTO client (name, address, email, age) VALUES (?, ?, ?, ?)";
    private static final String UPDATE_QUERY = "UPDATE client SET name = ?, address = ?, email = ?, age = ? WHERE client_id = ?";
    private static final String DELETE_QUERY = "DELETE FROM client WHERE client_id = ?";
    private static final String FIND_ALL_QUERY = "SELECT * FROM client";

    /**
     * Insereaza un nou client in baza de date.
     *
     * @param client obiectul Client care contine datele noului client
     * @return 'true' daca inserarea a avut succes, 'false' in caz contrar
     */
    public boolean insert(Client client) {
        try (Connection connection = ConnectionFactory.getConnection();
             PreparedStatement preparedStatement = connection.prepareStatement(INSERT_QUERY, Statement.RETURN_GENERATED_KEYS)) {

            preparedStatement.setString(1, client.getName());
            preparedStatement.setString(2, client.getAddress());
            preparedStatement.setString(3, client.getEmail());
            preparedStatement.setInt(4, client.getAge());

            int affectedRows = preparedStatement.executeUpdate();

            if (affectedRows == 0) {
                throw new SQLException("Creating client failed, no rows affected.");
            }

            try (ResultSet generatedKeys = preparedStatement.getGeneratedKeys()) {
                if (generatedKeys.next()) {
                    client.setId(generatedKeys.getInt(1));
                } else {
                    throw new SQLException("Creating client failed, no ID obtained.");
                }
            }
            return true;
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }

    /**
     * Actualizeaza datele unui client existent in baza de date.
     *
     * @param client obiectul Client care contine datele actualizate ale clientului
     * @return 'true' daca actualizarea a avut succes, 'false' in caz contrar
     */
    public boolean update(Client client) {
        try (Connection connection = ConnectionFactory.getConnection();
             PreparedStatement preparedStatement = connection.prepareStatement(UPDATE_QUERY)) {

            preparedStatement.setString(1, client.getName());
            preparedStatement.setString(2, client.getAddress());
            preparedStatement.setString(3, client.getEmail());
            preparedStatement.setInt(4, client.getAge());
            preparedStatement.setInt(5, client.getId());

            preparedStatement.executeUpdate();
            return true;
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }

    /**
     * Sterge un client din baza de date dupa ID-ul acestuia.
     *
     * @param clientId ID-ul clientului care trebuie sters
     * @return 'true' daca stergerea a avut succes, 'false' in caz contrar
     */
    public boolean delete(int clientId) {
        try (Connection connection = ConnectionFactory.getConnection();
             PreparedStatement preparedStatement = connection.prepareStatement(DELETE_QUERY)) {

            preparedStatement.setInt(1, clientId);
            preparedStatement.executeUpdate();
            return true;
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }

    /**
     * Returneaza o lista cu toti clientii din baza de date.
     *
     * @return Lista de clienti sau o lista goala daca nu exista clienti in baza de date
     */
    public List<Client> findAll() {
        List<Client> clients = new ArrayList<>();

        try (Connection connection = ConnectionFactory.getConnection();
             PreparedStatement preparedStatement = connection.prepareStatement(FIND_ALL_QUERY);
             ResultSet resultSet = preparedStatement.executeQuery()) {

            while (resultSet.next()) {
                Client client = new Client();
                client.setId(resultSet.getInt("client_id"));
                client.setName(resultSet.getString("name"));
                client.setAddress(resultSet.getString("address"));
                client.setEmail(resultSet.getString("email"));
                client.setAge(resultSet.getInt("age"));
                clients.add(client);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return clients;
    }
}
