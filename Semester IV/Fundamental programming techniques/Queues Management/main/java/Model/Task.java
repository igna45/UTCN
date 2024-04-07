package Model;

public class Task {
    private int id;
    private int arrivalTime;
    private int processingTime;

    public Task(int id, int arrivalTime, int processingTime) {
        this.id = id;
        this.arrivalTime = arrivalTime;
        this.processingTime = processingTime;
    }

    public int getArrivalTime() {
        return arrivalTime;
    }

    public int getProcessingTime() {
        return processingTime;
    }

    public void setProcessingTime(int processingTime) {
        this.processingTime = processingTime;
    }

    @Override
    public String toString() {
        return "(" + id + "," + arrivalTime + "," + processingTime + ")";
    }
}