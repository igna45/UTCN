package Business_Logic;

import Model.Server;
import Model.Task;
import Utils.Log;

import java.util.ArrayList;
import java.util.List;

public class SimulationManager implements Runnable{
    private int timeLimit;
    private int maxProcessingTime;
    private int maxArrivalTime;
    private int minArrivalTime;
    private int minProcessingTime;
    private int numberOfServers;
    private int numberOfTasks;
    private int peakHour;
    private int totalServiceTime;
    private int numberOfServices;

    private List<Task> waitingTasks;
    private Scheduler scheduler;
    private Log log;

    public SimulationManager(int timeLimit, int maxProcessingTime, int maxArrivalTime,
                             int minArrivalTime, int minProcessingTime, int numberOfServers, int numberOfTasks, Log log) {
        this.timeLimit = timeLimit;
        this.maxProcessingTime = maxProcessingTime;
        this.maxArrivalTime = maxArrivalTime;
        this.minArrivalTime = minArrivalTime;
        this.minProcessingTime = minProcessingTime;
        this.numberOfServers = numberOfServers;
        this.numberOfTasks = numberOfTasks;
        this.log = log;

        waitingTasks = generateTasks();
        scheduler = new Scheduler(numberOfServers);
    }

    private List<Task> generateTasks() {
        List<Task> generatedTasks = new ArrayList<>();
        for (int i = 1; i <= numberOfTasks; i++) {
            int arrivalTime = (int) (Math.random() * (maxArrivalTime - minArrivalTime + 1)) + minArrivalTime;
            int processingTime = (int) (Math.random() * (maxProcessingTime - minProcessingTime + 1)) + minProcessingTime;
            generatedTasks.add(new Task(i, arrivalTime, processingTime));
        }
        return generatedTasks;
    }

    public void run() {
        int currentTime = 0;
        int totalWaitingTime = 0;
        int completedTasks = 0;

        while (currentTime < timeLimit || !waitingTasks.isEmpty() || !scheduler.allServersEmpty()) {

            List<Task> arrivedTasks = new ArrayList<>();
            for (Task task : waitingTasks) {
                if (task.getArrivalTime() <= currentTime) {
                    arrivedTasks.add(task);
                }
            }

            for (Task task : arrivedTasks) {
                scheduler.dispatchTask(task);
                waitingTasks.remove(task);

                // Calculate waiting time and service time for the task right after it is dispatched
                totalWaitingTime += task.getArrivalTime();
                totalServiceTime += task.getProcessingTime();
                completedTasks++;
                numberOfServices++;
            }

            System.out.println("Time " + currentTime);
            System.out.print("Waiting clients: ");
            waitingTasks.forEach(task -> System.out.print(task.toString() + "; "));
            System.out.println();

            log.log("Time " + currentTime);
            log.log("Waiting clients: ");
            waitingTasks.forEach(task -> log.log(task.toString() + "; "));
            log.log("");

            System.out.println(scheduler.getServersStatus());
            log.log(scheduler.getServersStatus());

            for (Server server : scheduler.getServers()) {
                new Thread(server).start();
            }

            try {
                Thread.sleep(10); // 1-second
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            for (Server server : scheduler.getServers()) {
                if (!server.isEmpty()) {
                    completedTasks++;
                }
            }

            currentTime++;
        }

        for (Server server : scheduler.getServers()) {
            try {
                new Thread(server).join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        scheduler.stopServers();

        double averageWaitingTime = (double) totalWaitingTime / numberOfTasks;
        double averageServiceTime = (double) totalServiceTime / numberOfTasks;

        log.log("Average waiting time: " + averageWaitingTime);
        System.out.println("Average waiting time: " + averageWaitingTime);
        log.log("Average service time: " + averageServiceTime);
        System.out.println("Average service time: " + averageServiceTime);
    }

}