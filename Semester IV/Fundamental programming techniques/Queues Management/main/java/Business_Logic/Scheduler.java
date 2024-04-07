package Business_Logic;

import Model.Server;
import Model.Task;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.locks.ReentrantLock;

public class Scheduler {
    private List<Server> servers;
    private int numberOfServers;
    private ReentrantLock lock;

    public Scheduler(int numberOfServers) {
        this.numberOfServers = numberOfServers;
        servers = new ArrayList<>();
        lock = new ReentrantLock();
        for (int i = 0; i < numberOfServers; i++) {
            Server server = new Server();
            servers.add(server);
            new Thread(server).start();
        }
    }

    public void dispatchTask(Task task) {
        lock.lock();
        try {
            int minTasks = Integer.MAX_VALUE;
            int selectedServer = 0;
            for (int i = 0; i < numberOfServers; i++) {
                if (servers.get(i).getQueueSize() < minTasks) {
                    minTasks = servers.get(i).getQueueSize();
                    selectedServer = i;
                }
            }
            servers.get(selectedServer).addTask(task);
        } finally {
            lock.unlock();
        }
    }

    public void processFirstTasks() {
        for (Server server : servers) {
            server.processTask();
        }
    }

    public String getServersStatus() {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < numberOfServers; i++) {
            sb.append("Queue ").append(i + 1).append(": ");
            sb.append(servers.get(i).toString()).append("\n");
        }
        return sb.toString();
    }

    public boolean allServersEmpty() {
        return servers.stream().allMatch(Server::isEmpty);
    }

    public void stopServers() {
        for (Server server : servers) {
            server.stopServer();
        }
    }

    public List<Server> getServers() {
        return servers;
    }
}