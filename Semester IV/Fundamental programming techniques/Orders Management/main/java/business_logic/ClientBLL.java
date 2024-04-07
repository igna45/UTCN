package business_logic;

import data_access.ClientDAO;
import model.Client;

import java.util.List;

/**
 * Clasa ClientBLL gestioneaza operatiile pentru clienti.
 */
public class ClientBLL {
    private ClientDAO clientDAO;

    /**
     * Constructorul implicit al clasei ClientBLL.
     */
    public ClientBLL() {
        clientDAO = new ClientDAO();
    }

    /**
     * Adauga un client nou in baza de date.
     *
     * @param client Obiectul Client ce trebuie adaugat
     * @return true daca operatia a avut succes, false altfel
     */
    public boolean addClient(Client client) {
        return clientDAO.insert(client);
    }

    /**
     * Modifica datele unui client existent in baza de date.
     *
     * @param client Obiectul Client cu datele actualizate
     * @return true daca operatia a avut succes, false altfel
     */
    public boolean editClient(Client client) {
        return clientDAO.update(client);
    }

    /**
     * Sterge un client din baza de date dupa ID.
     *
     * @param clientId ID-ul clientului ce trebuie sters
     * @return true daca operatia a avut succes, false altfel
     */
    public boolean deleteClient(int clientId) {
        return clientDAO.delete(clientId);
    }

    /**
     * Returneaza o lista cu toti clientii din baza de date.
     *
     * @return Lista de clienti
     */
    public List<Client> getAllClients() {
        return clientDAO.findAll();
    }
}