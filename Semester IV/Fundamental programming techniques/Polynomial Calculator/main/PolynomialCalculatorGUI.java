package org.example;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Map;
public class PolynomialCalculatorGUI extends JFrame implements ActionListener {

    private JTextField poly1Field;
    private JTextField poly2Field;
    private JTextField resultField;
    private JComboBox<String> operationComboBox;
    private JButton calculateButton;
    public PolynomialCalculatorGUI() {
        setTitle("Calculator de Polinoame");
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setLayout(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();


        gbc.insets = new Insets(5, 5, 5, 5);
        gbc.gridy = 0;
        gbc.gridx = 0;
        gbc.gridwidth = 1;
        JLabel poly1Label = new JLabel("Polinomul 1:");
        add(poly1Label, gbc);

        gbc.gridx = 1;
        gbc.gridwidth = 5;
        poly1Field = new JTextField("", 20);
        add(poly1Field, gbc);

        gbc.gridy = 1;
        gbc.gridx = 0;
        gbc.gridwidth = 1;
        JLabel poly2Label = new JLabel("Polinomul 2:");
        add(poly2Label, gbc);

        gbc.gridx = 1;
        gbc.gridwidth = 5;
        poly2Field = new JTextField("", 20);
        add(poly2Field, gbc);

        gbc.gridy = 2;
        gbc.gridx = 0;
        gbc.gridwidth = 1;
        JLabel operationLabel = new JLabel("Operatie:");
        add(operationLabel, gbc);

        gbc.gridx = 1;
        String[] operations = {"SUMA", "SCADERE", "INMULTIRE"};
        operationComboBox = new JComboBox<>(operations);
        add(operationComboBox, gbc);

        gbc.gridx = 5;
        gbc.gridy = 2;
        gbc.gridwidth = 1;
        calculateButton = new JButton("Calculeaza");
        calculateButton.addActionListener(this);
        add(calculateButton, gbc);

        gbc.gridy = 5;
        gbc.gridx = 0;
        gbc.gridwidth = 1;
        JLabel resultLabel = new JLabel("Rezultat:");
        add(resultLabel, gbc);

        gbc.gridx = 1;
        gbc.gridwidth = 5;
        resultField = new JTextField(20);
        resultField.setEditable(false);
        add(resultField, gbc);

        getContentPane().setPreferredSize(new Dimension(350, 200));
        pack();
        setLocationRelativeTo(null);
        setVisible(true);

    }
    public void actionPerformed(ActionEvent e) {
        String operation = (String) operationComboBox.getSelectedItem();

        Polinom p1 = Polinom.toPolynomial(poly1Field.getText());
        Polinom p2 = Polinom.toPolynomial(poly2Field.getText());

        Map<Integer, Integer> result;
        switch (operation) {
            case "SUMA":
                result = p1.addPolynomials(p1.getPolinom(), p2.getPolinom());
                break;
            case "SCADERE":
                result = p1.subtractPolynomials(p1.getPolinom(), p2.getPolinom());
                break;
            case "INMULTIRE":
                result = p1.multiplyPolynomials(p1.getPolinom(), p2.getPolinom());
                break;
            default:
                return;
        }
        resultField.setText(new Polinom(result).toString());

    }

    public static void main(String[] args) {
        new PolynomialCalculatorGUI();
    }

}
