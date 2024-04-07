package presentation;

import model.Client;
import model.Order;
import model.Product;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.lang.reflect.Field;
import java.util.Arrays;
import java.util.List;
import javax.swing.border.EmptyBorder;

/**
 * Clasa View
 */
public class View extends JFrame {
    private Controller controller;

    private JButton addClientButton;
    private JButton updateClientButton;
    private JButton deleteClientButton;
    private JButton viewAllClientsButton;

    private JButton addProductButton;
    private JButton updateProductButton;
    private JButton deleteProductButton;
    private JButton viewAllProductsButton;

    private JButton createOrderButton;
    private JButton updateOrderButton;
    private JButton viewAllOrdersButton;

    private JComboBox<Client> clientComboBox;
    private JComboBox<Product> productComboBox;
    private JTextField quantityTextField;
    private JPanel clientPanel;
    private JPanel productPanel;
    private JPanel orderPanel;
    private JPanel mainPanel;

    /**
     * Constructorul clasei View
     * @param controller obiectul Controller folosit de clasa View pentru a interoga modelul si a actualiza datele afisate
     */
    public View(Controller controller) {
        this.controller = controller;

        // Initialize components
        initComponents();

        initClientComboBox();
        initProductComboBox();
        initQuantityTextField();


        // Set up the layout
        setUpLayout();

        // Set up frame properties
        setTitle("Orders Management");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(700, 450);
        setLocationRelativeTo(null);
    }

    /**
     * Metoda care genereaza un tabel cu datele primite ca parametru
     * @param dataList lista cu datele de afisat in tabel
     * @return un tabel cu datele primite ca parametru, reprezentat sub forma de obiect DefaultTableModel
     */
    private DefaultTableModel generateTableModelFromList(List<?> dataList) {
        if (dataList == null || dataList.isEmpty()) {
            return new DefaultTableModel();
        }

        Object firstObject = dataList.get(0);
        List<Field> fields = Arrays.asList(firstObject.getClass().getDeclaredFields());
        String[] columnNames = new String[fields.size()];

        for (int i = 0; i < fields.size(); i++) {
            columnNames[i] = fields.get(i).getName();
        }

        Object[][] data = new Object[dataList.size()][fields.size()];
        for (int i = 0; i < dataList.size(); i++) {
            Object dataObject = dataList.get(i);

            for (int j = 0; j < fields.size(); j++) {
                Field field = fields.get(j);
                field.setAccessible(true);

                try {
                    data[i][j] = field.get(dataObject);
                } catch (IllegalAccessException e) {
                    e.printStackTrace();
                }
            }
        }

        return new DefaultTableModel(data, columnNames);
    }

    /**
     * Metoda care initializeaza componenta grafica pentru introducerea cantitatii de produs necesara la crearea unei comenzi
     */
    private void initQuantityTextField() {
        quantityTextField = new JTextField(20);
    }

    /**
     * Metoda care initializeaza lista de clienti disponibili pentru a fi selectati in cadrul interfetei grafice
     */
    private void initClientComboBox() {
        List<Client> clients = controller.getAllClients();
        clientComboBox = new JComboBox<>(new DefaultComboBoxModel<>(clients.toArray(new Client[0])));
    }

    /**
     * Inițializează combobox-ul pentru produse.
     * Obține o listă de produse de la controler și o adaugă în combobox.
     */
    private void initProductComboBox() {
        List<Product> products = controller.getAllProducts();
        productComboBox = new JComboBox<>(new DefaultComboBoxModel<>(products.toArray(new Product[0])));
    }

    /**
     * Inițializează butoanele și le adaugă acțiunile.
     */
    private void initComponents() {
        addClientButton = new JButton("Add Client");
        updateClientButton = new JButton("Update Client");
        deleteClientButton = new JButton("Delete Client");
        viewAllClientsButton = new JButton("View All Clients");

        addProductButton = new JButton("Add Product");
        updateProductButton = new JButton("Update Product");
        deleteProductButton = new JButton("Delete Product");
        viewAllProductsButton = new JButton("View All Products");

        createOrderButton = new JButton("Create Order");
        viewAllOrdersButton = new JButton("View All Orders");

        // Add action listeners
        addClientButton.addActionListener(new AddClientButtonListener());
        deleteClientButton.addActionListener(new DeleteClientButtonListener());
        updateClientButton.addActionListener(new UpdateClientButtonListener());
        viewAllClientsButton.addActionListener(new ViewAllClientsButtonListener());

        addProductButton.addActionListener(new AddProductButtonListener());
        updateProductButton.addActionListener(new UpdateProductButtonListener());
        deleteProductButton.addActionListener(new DeleteProductButtonListener());
        viewAllProductsButton.addActionListener(new ViewAllProductsButtonListener());

        createOrderButton.addActionListener(new CreateOrderButtonListener());
        viewAllOrdersButton.addActionListener(new ViewAllOrdersButtonListener());
    }

    /**
     * Configurarea dimensiunii și a layout-ului butoanelor.
     */
    private void setUpLayout() {
        Dimension buttonSize = new Dimension(150, 50);

        addClientButton.setPreferredSize(buttonSize);
        updateClientButton.setPreferredSize(buttonSize);
        deleteClientButton.setPreferredSize(buttonSize);
        viewAllClientsButton.setPreferredSize(buttonSize);

        addProductButton.setPreferredSize(buttonSize);
        updateProductButton.setPreferredSize(buttonSize);
        deleteProductButton.setPreferredSize(buttonSize);
        viewAllProductsButton.setPreferredSize(buttonSize);

        createOrderButton.setPreferredSize(buttonSize);
        viewAllOrdersButton.setPreferredSize(buttonSize);

        // Set up panels
        clientPanel = new JPanel(new GridBagLayout());
        clientPanel.setBorder(BorderFactory.createTitledBorder("Clients"));

        GridBagConstraints gbc = new GridBagConstraints();
        gbc.fill = GridBagConstraints.BOTH;
        gbc.weightx = 1.0;
        gbc.weighty = 1.0;
        gbc.insets = new Insets(5, 5, 5, 5);

        gbc.gridx = 0;
        gbc.gridy = 0;
        clientPanel.add(addClientButton, gbc);

        gbc.gridx = 1;
        clientPanel.add(updateClientButton, gbc);

        gbc.gridx = 0;
        gbc.gridy = 1;
        clientPanel.add(deleteClientButton, gbc);

        gbc.gridx = 1;
        clientPanel.add(viewAllClientsButton, gbc);

        productPanel = new JPanel(new GridBagLayout());
        productPanel.setBorder(BorderFactory.createTitledBorder("Products"));

        // Reset gridx and gridy for productPanel
        gbc.gridx = 0;
        gbc.gridy = 0;
        productPanel.add(addProductButton, gbc);

        gbc.gridx = 1;
        productPanel.add(updateProductButton, gbc);

        gbc.gridx = 0;
        gbc.gridy = 1;
        productPanel.add(deleteProductButton, gbc);

        gbc.gridx = 1;
        productPanel.add(viewAllProductsButton, gbc);

        orderPanel = new JPanel(new GridBagLayout());
        orderPanel.setBorder(BorderFactory.createTitledBorder("Orders"));

        gbc.gridx = 0;
        gbc.gridy = 0;
        orderPanel.add(createOrderButton, gbc);

        gbc.gridx = 1;
        orderPanel.add(viewAllOrdersButton, gbc);

        mainPanel = new JPanel(new BorderLayout(10, 10));
        mainPanel.setBorder(new EmptyBorder(10, 10, 10, 10));
        mainPanel.add(clientPanel, BorderLayout.NORTH);
        mainPanel.add(productPanel, BorderLayout.CENTER);
        mainPanel.add(orderPanel, BorderLayout.SOUTH);

        // Set up the layout for main JFrame
        setLayout(new BorderLayout());
        add(mainPanel, BorderLayout.CENTER);
    }

    /**
     * Action Listener pentru butonul "Adauga Client".
     * Cand butonul este apasat, se deschide un dialog pentru introducerea informatiilor despre client.
     * Dupa ce informatiile sunt completate si se apasa OK, se creeaza un nou obiect Client si se adauga la lista de clienti.
     */
    private class AddClientButtonListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {

            JTextField nameField = new JTextField(20);
            JTextField addressField = new JTextField(20);
            JTextField emailField = new JTextField(20);
            JTextField ageField = new JTextField(5);

            JPanel inputPanel = new JPanel();
            inputPanel.setLayout(new GridLayout(4, 2));
            inputPanel.add(new JLabel("Name:"));
            inputPanel.add(nameField);
            inputPanel.add(new JLabel("Address:"));
            inputPanel.add(addressField);
            inputPanel.add(new JLabel("Email:"));
            inputPanel.add(emailField);
            inputPanel.add(new JLabel("Age:"));
            inputPanel.add(ageField);

            int result = JOptionPane.showConfirmDialog(null, inputPanel,
                    "Add Client", JOptionPane.OK_CANCEL_OPTION);
            if (result == JOptionPane.OK_OPTION) {
                String name = nameField.getText();
                String address = addressField.getText();
                String email = emailField.getText();
                int age = Integer.parseInt(ageField.getText());

                Client client = new Client(name, address, email, age);
                controller.addClient(client);
            }
        }
    }

    /**
     * Action Listener pentru butonul "Actualizeaza Client".
     * Cand butonul este apasat, se deschide un dialog pentru a introduce ID-ul clientului care trebuie actualizat.
     * Dupa ce ID-ul este introdus, se deschide un alt dialog pentru a introduce noile informatii despre client.
     * Dupa ce informatiile sunt completate si se apasa OK, se actualizeaza clientul in lista de clienti.
     */
    private class UpdateClientButtonListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {

            String clientIdStr = JOptionPane.showInputDialog("Enter the client ID to update:");
            if (clientIdStr != null) {
                int clientId = Integer.parseInt(clientIdStr);

                JTextField nameField = new JTextField(20);
                JTextField addressField = new JTextField(20);
                JTextField emailField = new JTextField(20);
                JTextField ageField = new JTextField(20);

                JPanel inputPanel = new JPanel();
                inputPanel.setLayout(new GridLayout(5, 2));
                inputPanel.add(new JLabel("Name:"));
                inputPanel.add(nameField);
                inputPanel.add(new JLabel("Address:"));
                inputPanel.add(addressField);
                inputPanel.add(new JLabel("Email:"));
                inputPanel.add(emailField);
                inputPanel.add(new JLabel("Age:"));
                inputPanel.add(ageField);

                int result = JOptionPane.showConfirmDialog(null, inputPanel,
                        "Update Client", JOptionPane.OK_CANCEL_OPTION);
                if (result == JOptionPane.OK_OPTION) {
                    String name = nameField.getText();
                    String address = addressField.getText();
                    String email = emailField.getText();
                    int age = Integer.parseInt(ageField.getText());

                    Client updatedClient = new Client(clientId, name, address, email, age);
                    controller.editClient(updatedClient);
                }
            }
        }
    }

    /**
     * Action Listener pentru butonul "Sterge Client".
     * Cand butonul este apasat, se deschide un dialog pentru a introduce ID-ul clientului care trebuie sters.
     * Dupa ce ID-ul este introdus si se apasa OK, se sterge clientul din lista de clienti.
     */
    private class DeleteClientButtonListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {

            String clientIdStr = JOptionPane.showInputDialog("Enter the client ID to delete:");
            if (clientIdStr != null) {
                int clientId = Integer.parseInt(clientIdStr);
                controller.deleteClient(clientId);
            }
        }
    }

    /**
     * Metoda pentru afisarea tuturor clientilor.
     * Este obtinuta lista de clienti prin apelul metodei getAllClients a controllerului.
     * Se creeaza un tabel cu lista de clienti obtinuta si se afiseaza intr-un dialog cu un scroll pane.
     */
    private class ViewAllClientsButtonListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            List<Client> clients = controller.getAllClients();
            DefaultTableModel model = generateTableModelFromList(clients);
            JTable table = new JTable(model);
            JScrollPane scrollPane = new JScrollPane(table);
            scrollPane.setPreferredSize(new Dimension(800, 600));
            JOptionPane.showMessageDialog(null, scrollPane, "All Clients", JOptionPane.INFORMATION_MESSAGE);
        }
    }

    /**
     * Metoda pentru adaugarea unui nou produs.
     * Se creeaza un dialog care va contine campurile de input pentru nume, pret si stocul produsului.
     * Dupa completarea campurilor si apasarea butonului OK, se creaza un nou produs si se adauga in baza de date.
     */
    private class AddProductButtonListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            // Show input dialog to collect client information
            JTextField nameField = new JTextField(20);
            JTextField priceField = new JTextField(20);
            JTextField stockField = new JTextField(20);

            JPanel inputPanel = new JPanel();
            inputPanel.setLayout(new GridLayout(4, 2));
            inputPanel.add(new JLabel("Name:"));
            inputPanel.add(nameField);
            inputPanel.add(new JLabel("Price:"));
            inputPanel.add(priceField);
            inputPanel.add(new JLabel("Stock:"));
            inputPanel.add(stockField);

            int result = JOptionPane.showConfirmDialog(null, inputPanel,
                    "Add Product", JOptionPane.OK_CANCEL_OPTION);
            if (result == JOptionPane.OK_OPTION) {
                String name = nameField.getText();
                int price = Integer.parseInt(priceField.getText());
                int current_stock = Integer.parseInt(stockField.getText());

                Product product = new Product(name, price, current_stock);
                controller.addProduct(product);
            }
        }
    }

    /**
     * Metoda pentru actualizarea unui produs.
     * Se afiseaza un dialog in care utilizatorul poate introduce ID-ul produsului pe care doreste sa il actualizeze.
     * Daca produsul exista, utilizatorul poate introduce noile date in campurile de input din dialog.
     * Dupa completarea campurilor si apasarea butonului OK, produsul este actualizat in baza de date.
     */
    private class UpdateProductButtonListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {

            String productIdStr = JOptionPane.showInputDialog("Enter the product ID to update:");
            if (productIdStr != null) {
                int productId = Integer.parseInt(productIdStr);

                JTextField nameField = new JTextField(20);
                JTextField priceField = new JTextField(20);
                JTextField stockField = new JTextField(20);

                JPanel inputPanel = new JPanel();
                inputPanel.setLayout(new GridLayout(4, 2));
                inputPanel.add(new JLabel("Name:"));
                inputPanel.add(nameField);
                inputPanel.add(new JLabel("Price:"));
                inputPanel.add(priceField);
                inputPanel.add(new JLabel("Stock:"));
                inputPanel.add(stockField);

                int result = JOptionPane.showConfirmDialog(null, inputPanel,
                        "Update Product", JOptionPane.OK_CANCEL_OPTION);
                if (result == JOptionPane.OK_OPTION) {
                    String name = nameField.getText();
                    double price = Double.parseDouble(priceField.getText());
                    int stock = Integer.parseInt(stockField.getText());

                    Product updatedProduct = new Product(productId, name, price, stock);
                    controller.editProduct(updatedProduct);
                }
            }
        }
    }

    /**
     * Această clasă reprezintă un Action Listener pentru butonul de ștergere produs.
     */
    private class DeleteProductButtonListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {

            String productIdStr = JOptionPane.showInputDialog("Enter the ID of the product you want to delete:");

            if (productIdStr != null) {
                int productId = Integer.parseInt(productIdStr);
                controller.deleteProduct(productId);
            }
        }
    }

    /**
     * Această clasă reprezintă un Action Listener pentru butonul de vizualizare a tuturor produselor.
     */
    private class ViewAllProductsButtonListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            List<Product> products = controller.getAllProducts();
            DefaultTableModel model = generateTableModelFromList(products);
            JTable table = new JTable(model);
            JScrollPane scrollPane = new JScrollPane(table);
            scrollPane.setPreferredSize(new Dimension(800, 600));
            JOptionPane.showMessageDialog(null, scrollPane, "All Products", JOptionPane.INFORMATION_MESSAGE);
        }
    }

    /**
     * Această clasă reprezintă un Action Listener pentru butonul de creare a comenzilor.
     */
    private class CreateOrderButtonListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            List<Client> clients = controller.getAllClients();
            JComboBox<Client> clientComboBox = new JComboBox<>(new DefaultComboBoxModel<>(clients.toArray(new Client[0])));

            List<Product> products = controller.getAllProducts();
            JComboBox<Product> productComboBox = new JComboBox<>(new DefaultComboBoxModel<>(products.toArray(new Product[0])));

            JTextField quantityField = new JTextField(5);

            JPanel inputPanel = new JPanel();
            inputPanel.setLayout(new GridLayout(3, 2));
            inputPanel.add(new JLabel("Client:"));
            inputPanel.add(clientComboBox);
            inputPanel.add(new JLabel("Product:"));
            inputPanel.add(productComboBox);
            inputPanel.add(new JLabel("Quantity:"));
            inputPanel.add(quantityField);

            int result = JOptionPane.showConfirmDialog(null, inputPanel,
                    "Create Order", JOptionPane.OK_CANCEL_OPTION);
            if (result == JOptionPane.OK_OPTION) {
                Client selectedClient = (Client) clientComboBox.getSelectedItem();
                Product selectedProduct = (Product) productComboBox.getSelectedItem();

                int desiredQuantity = Integer.parseInt(quantityField.getText());

                if (selectedProduct.getCurrent_stock() < desiredQuantity) {
                    JOptionPane.showMessageDialog(null, "Under-stock! Please reduce the order quantity.", "Error", JOptionPane.ERROR_MESSAGE);
                } else {
                    Order newOrder = new Order(selectedClient.getId(), selectedProduct.getId(), desiredQuantity);
                    controller.createOrder(newOrder);

                    int newStock = selectedProduct.getCurrent_stock() - desiredQuantity;
                    selectedProduct.setCurrent_stock(newStock);
                    controller.editProduct(selectedProduct);

                    JOptionPane.showMessageDialog(null, "Order created successfully!", "Success", JOptionPane.INFORMATION_MESSAGE);
                }
            }
        }
    }

    /**
     * Metoda pentru afisarea tuturor comenzilor.
     * Este obtinuta lista de comenzi prin apelul metodei getAllOrders a controllerului.
     * Se creeaza un tabel cu lista de comenzi obtinuta si se afiseaza intr-un dialog cu un scroll pane.
     */
    private class ViewAllOrdersButtonListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            List<Order> orders = controller.getAllOrders();
            DefaultTableModel model = generateTableModelFromList(orders);
            JTable table = new JTable(model);
            JScrollPane scrollPane = new JScrollPane(table);
            scrollPane.setPreferredSize(new Dimension(800, 600));
            JOptionPane.showMessageDialog(null, scrollPane, "All Orders", JOptionPane.INFORMATION_MESSAGE);
        }
    }

    /**
     * Functia main
     */
    public static void main(String[] args) {
        Controller controller = new Controller();
        View view = new View(controller);
        view.setVisible(true);
    }
}