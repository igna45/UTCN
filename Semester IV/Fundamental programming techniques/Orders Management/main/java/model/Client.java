package model;

/**
 * Clasa Client reprezinta un client cu proprietatile sale asociate.
 *
 */
public class Client {
    private int client_id;
    private String name;
    private String address;
    private String email;
    private int age;

    /**
     * Constructor care seteaza toate proprietatile unui client.
     *
     * @param client_id ID-ul clientului
     * @param name      Numele clientului
     * @param address   Adresa clientului
     * @param email     Adresa de e-mail a clientului
     * @param age       Varsta clientului
     */
    public Client(int client_id, String name, String address, String email, int age) {
        this.client_id = client_id;
        this.name = name;
        this.address = address;
        this.email = email;
        this.age = age;
    }

    /**
     * Constructor fara parametri.
     */
    public Client() {

    }

    /**
     * Constructor care seteaza proprietatile unui client, fara ID.
     *
     * @param name    Numele clientului
     * @param address Adresa clientului
     * @param email   Adresa de e-mail a clientului
     * @param age     Varsta clientului
     */
    public Client(String name, String address, String email, int age) {
        this.name = name;
        this.address = address;
        this.email = email;
        this.age = age;
    }

    /**
     * Returneaza ID-ul clientului.
     *
     * @return ID-ul clientului
     */
    public int getId() {
        return client_id;
    }

    /**
     * Seteaza un nou ID pentru client.
     *
     * @param client_id Noul ID al clientului
     */
    public void setId(int client_id) {
        this.client_id = client_id;
    }

    /**
     * Returneaza numele clientului.
     *
     * @return Numele clientului
     */
    public String getName() {
        return name;
    }

    /**
     * Seteaza un nou nume pentru client.
     *
     * @param name Noul nume al clientului
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     * Returneaza adresa clientului.
     *
     * @return Adresa clientului
     */
    public String getAddress() {
        return address;
    }

    /**
     * Seteaza o noua adresa pentru client.
     *
     * @param address Noua adresa a clientului
     */
    public void setAddress(String address) {
        this.address = address;
    }

    /**
     * Returneaza adresa de e-mail a clientului.
     *
     * @return Adresa de e-mail a clientului
     */
    public String getEmail() {
        return email;
    }

    /**
     * Seteaza o noua adresa de e-mail pentru client.
     *
     * @param email Noua adresa de e-mail a clientului
     */
    public void setEmail(String email) {
        this.email = email;
    }

    /**
     * Returneaza varsta clientului.
     *
     * @return Varsta clientului
     */
    public int getAge() {
        return age;
    }

    /**
     * Seteaza o noua varsta pentru client.
     *
     * @param age Noua varsta a clientului
     */


    public void setAge(int age) {
        this.age = age;
    }

    /**
     * Returneaza o reprezentare textuala a obiectului Client.
     *
     * @return Un sir de caractere ce descrie obiectul Client
     */
    @Override
    public String toString() {
        return "Client{" +
                "id=" + client_id +
                ", name='" + name + '\'' +
                ", address='" + address + '\'' +
                ", email='" + email + '\'' +
                ", age=" + age +
                '}';
    }
}
