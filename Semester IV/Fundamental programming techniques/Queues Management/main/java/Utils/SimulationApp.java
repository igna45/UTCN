package Utils;

import Business_Logic.SimulationManager;
import Utils.Log;

import java.io.FileNotFoundException;

public class SimulationApp {
    public static void main(String[] args) {

        int numberOfClients = 50;
        int numberOfQueues = 5;
        int timeLimit = 60;
        int minArrivalTime = 2;
        int maxArrivalTime = 40;
        int minProcessingTime = 1;
        int maxProcessingTime = 7;

        Log log = null;
        try {
            log = new Log("simulation_log.txt");
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }

        SimulationManager simulationManager = new SimulationManager(timeLimit, maxProcessingTime, maxArrivalTime,
                minArrivalTime, minProcessingTime, numberOfQueues, numberOfClients, log);

        simulationManager.run();

        if (log != null) {
            log.close();
        }
    }
}