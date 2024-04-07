package Model;

import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.concurrent.locks.ReentrantLock;

public class Server implements Runnable {
    private Queue<Task> tasks;
    private int waitingTime;
    private ReentrantLock lock;
    private volatile boolean running;

    public Server() {
        tasks = new LinkedList<>();
        waitingTime = 0;
        lock = new ReentrantLock();
        running = true;
    }

    @Override
    public void run() {
        processTask();
    }

    public void stopServer() {
        running = false;
    }

    public boolean isEmpty() {
        lock.lock();
        try {
            return tasks.isEmpty();
        } finally {
            lock.unlock();
        }
    }

    public int getQueueSize() {
        lock.lock();
        try {
            return tasks.size();
        } finally {
            lock.unlock();
        }
    }

    public void addTask(Task task) {
        lock.lock();
        try {
            waitingTime += task.getProcessingTime();
            tasks.add(task);
        } finally {
            lock.unlock();
        }
    }

    public void processTask() {
        lock.lock();
        try {
            if (!isEmpty()) {
                Task currentTask = tasks.peek();
                currentTask.setProcessingTime(currentTask.getProcessingTime() - 1);
                if (currentTask.getProcessingTime() == 0) {
                    tasks.poll();
                }
            }
        } finally {
            lock.unlock();
        }
    }

    public void processTasks() {
        lock.lock();
        try {
            if (!tasks.isEmpty()) {
                for (Task task : tasks) {
                    task.setProcessingTime(task.getProcessingTime() - 1);
                }
                tasks.removeIf(task -> task.getProcessingTime() <= 0);
            }
        } finally {
            lock.unlock();
        }
    }

    public int getWaitingTime() {
        lock.lock();
        try {
            return waitingTime;
        } finally {
            lock.unlock();
        }
    }

    @Override
    public String toString() {
        StringBuilder output = new StringBuilder();
        lock.lock();
        try {
            if (tasks.isEmpty()) {
                output.append("closed");
            } else {
                tasks.forEach(task -> output.append(task.toString()).append("; "));
            }
        } finally {
            lock.unlock();
        }
        return output.toString();
    }
}