package connection;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

/**
 * Clasa responsabila pentru crearea si inchiderea conexiunilor cu baza de date.
 */
public class ConnectionFactory {

    private static final String DRIVER = "com.mysql.cj.jdbc.Driver";
    private static final String DBURL = "jdbc:mysql://localhost:3306/warehouse";
    private static final String USER = "root";
    private static final String PASS = "02112003.";

    private static ConnectionFactory singleInstance = new ConnectionFactory();

    /**
     * Constructor privat pentru a implementa pattern-ul Singleton.
     */
    private ConnectionFactory() {
        try {
            Class.forName(DRIVER);
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    /**
     * Returneaza instanta unica a clasei ConnectionFactory.
     *
     * @return instanta ConnectionFactory
     */
    public static ConnectionFactory getInstance() {
        return singleInstance;
    }

    /**
     * Creeaza o noua conexiune cu baza de date.
     *
     * @return conexiunea creata
     */
    private Connection createConnection() {
        Connection connection = null;
        try {
            connection = DriverManager.getConnection(DBURL, USER, PASS);
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return connection;
    }

    /**
     * Returneaza o conexiune cu baza de date.
     *
     * @return conexiunea cu baza de date
     */
    public static Connection getConnection() {
        return getInstance().createConnection();
    }

}
