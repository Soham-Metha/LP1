import java.util.*;

class Job {
    int id;
    int arrivalTime;
    int burstTime;
    int priority;

    Job(int id, int arrivalTime, int burstTime) {
        this(id, arrivalTime, burstTime, 0);
    }

    Job(int id, int arrivalTime, int burstTime, int priority) {
        this.id = id;
        this.arrivalTime = arrivalTime;
        this.burstTime = burstTime;
        this.priority = priority;
    }

    void process() {
        AlgoRunner.printTimestamp();
        System.out.printf("\033[41m P%d ", id);
    }

    boolean cmpBT(Job other) {
        return this.burstTime < other.burstTime;
    }
}

class TableElement {
    int ID, AT, BT, PRI, CT, TAT, WT;

    TableElement() {
    }

    TableElement(int id, int at, int bt, int pri) {
        this.ID = id;
        this.AT = at;
        this.BT = bt;
        this.PRI = pri;
    }
}

class Table {
    TableElement[] op = new TableElement[10];

    Table() {
        for (int i = 0; i < 10; i++) {
            op[i] = new TableElement();
        }
    }

    void initTable(List<Job> jobQueue) {
        for (Job job : jobQueue) {
            op[job.id] = new TableElement(job.id, job.arrivalTime, job.burstTime, job.priority);
        }
    }

    void updateCT(int index, int ct) {
        TableElement e = op[index];
        e.CT = ct;
        e.TAT = ct - e.AT;
        e.WT = e.TAT - e.BT;
    }

    void printTable(int start, int end) {
        int avgTAT = 0, avgWT = 0;

        System.out.println("\n\n\t╭──────┬─────┬─────┬──────┬─────┬──────┬─────╮");
        System.out.println("\t│ ID   │ AT  │ BT  │ PRI  │ CT  │ TAT  │ WT  │");
        System.out.println("\t├──────┼─────┼─────┼──────┼─────┼──────┼─────┤");

        for (int i = start; i <= end; i++) {
            TableElement t = op[i];
            System.out.printf("\t│ %-4d │ %-3d │ %-3d │ %-4d │ %-3d │ %-4d │ %-3d │\n",
                    t.ID, t.AT, t.BT, t.PRI, t.CT, t.TAT, t.WT);
            avgTAT += t.TAT;
            avgWT += t.WT;
        }

        System.out.println("\t╰──────┴─────┴─────┴──────┴─────┴──────┴─────╯");
        int count = end - start + 1;
        System.out.printf("\n\t Avg. TAT: %.2f\t   Avg. WT : %.2f\n", (float) avgTAT / count, (float) avgWT / count);
    }
}

class JobQueue {
    List<Job> jobQueue = new ArrayList<>();

    int getNextBatchArrivalTime(int timestamp) {
        for (Job job : jobQueue) {
            if (job.arrivalTime > timestamp)
                return job.arrivalTime;
        }
        return -1;
    }

    Job getNextShortestJobInQueue(int timestamp) {
        Job shortest = null;
        for (Job job : jobQueue) {
            if (job.arrivalTime <= timestamp && job.burstTime > 0) {
                if (shortest == null || job.cmpBT(shortest)) {
                    shortest = job;
                }
            }
        }
        return shortest;
    }
}

class AlgoRunner extends JobQueue {
    private static int __timestamp = 0;
    Table op = new Table();

    public static void printTimestamp() {
        System.out.printf("\033[42m  %d  \033[44m", __timestamp);
    }

    public void B2_RunAlgos(int i) {
        op.initTable(jobQueue);
        __timestamp = 0;
        jobQueue.sort(Comparator.comparingInt(j -> j.arrivalTime));
        System.out.println("\n\033[0m");
        switch (i) {
            case 1:
                System.out.print("FCFS:\t");
                B2_FCFS();
                break;
            case 2:
                System.out.print("PRI:\t");
                B2_PRI();
                break;
            case 3:
                System.out.print("SJF:\t");
                B2_SRTN();
                break;
            case 4:
                System.out.print("RR_25:\t");
                B2_RR(25);
                break;
        }
        printTimestamp();
        op.printTable((i - 1) * jobQueue.size() + 1, i * jobQueue.size());
        System.out.println("\n\n\033[0m");
    }

    private void B2_FCFS() {
        for (Job job : jobQueue) {
            if (__timestamp < job.arrivalTime) {
                new Job(-1, 0, 0).process();
                __timestamp = job.arrivalTime;
            }
            job.process();
            __timestamp += job.burstTime;
            op.updateCT(job.id, __timestamp);
        }
    }

    private void B2_PRI() {
        jobQueue.sort((a, b) -> {
            if (a.arrivalTime != b.arrivalTime)
                return Integer.compare(a.arrivalTime, b.arrivalTime);
            return Integer.compare(b.priority, a.priority);
        });

        for (Job job : jobQueue) {
            if (__timestamp < job.arrivalTime) {
                new Job(-1, 0, 0).process();
                __timestamp = job.arrivalTime;
            }
            job.process();
            __timestamp += job.burstTime;
            op.updateCT(job.id, __timestamp);
        }
    }

    private void B2_SRTN() {
        while (true) {
            Job job = getNextShortestJobInQueue(__timestamp);
            if (job == null)
                break;

            int gap = getNextBatchArrivalTime(__timestamp) - __timestamp;
            if (gap < 0 || gap > job.burstTime)
                gap = job.burstTime;

            job.burstTime -= gap;
            job.process();
            __timestamp += gap;

            if (job.burstTime <= 0)
                op.updateCT(job.id, __timestamp);
        }
    }

    private void B2_RR(int timeSlice) {
        int i = 0;
        boolean flag = false;

        while (flag || i < jobQueue.size()) {
            if ((i >= jobQueue.size() && flag) || jobQueue.get(i).arrivalTime > __timestamp) {
                i = 0;
                flag = false;
            }

            Job job = jobQueue.get(i);
            if (job.burstTime <= 0) {
                i++;
                continue;
            }

            int gap = Math.min(job.burstTime, timeSlice);
            job.burstTime -= gap;
            job.process();
            __timestamp += gap;

            if (job.burstTime <= 0)
                op.updateCT(job.id, __timestamp);

            flag = true;
            i++;
        }
    }
}

public class B2_main {
    public static void main(String[] args) {
        AlgoRunner arFCFS = new AlgoRunner();
        arFCFS.jobQueue.add(new Job(1, 0, 100, 4));
        arFCFS.jobQueue.add(new Job(2, 0, 90, 6));
        arFCFS.jobQueue.add(new Job(3, 2, 5, 1));

        AlgoRunner arPRI = new AlgoRunner();
        arPRI.jobQueue.add(new Job(4, 0, 100, 4));
        arPRI.jobQueue.add(new Job(5, 0, 90, 6));
        arPRI.jobQueue.add(new Job(6, 2, 5, 1));

        AlgoRunner arSRTN = new AlgoRunner();
        arSRTN.jobQueue.add(new Job(7, 0, 100, 4));
        arSRTN.jobQueue.add(new Job(8, 0, 90, 6));
        arSRTN.jobQueue.add(new Job(9, 2, 5, 1));

        AlgoRunner arRR = new AlgoRunner();
        arRR.jobQueue.add(new Job(10, 0, 100, 4));
        arRR.jobQueue.add(new Job(11, 0, 90, 6));
        arRR.jobQueue.add(new Job(12, 2, 5, 1));

        arFCFS.B2_RunAlgos(1);
        arPRI.B2_RunAlgos(2);
        arSRTN.B2_RunAlgos(3);
        arRR.B2_RunAlgos(4);
    }
}
