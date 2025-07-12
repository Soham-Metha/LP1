#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

class Job
{
  public:
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
    Job() : id(0), arrivalTime(0), burstTime(0), priority(0) {};
    Job(int ID, int arrivalTime, int burstTime)
        : id(ID), arrivalTime(arrivalTime), burstTime(burstTime), priority(0) {};
    Job(int ID, int arrivalTime, int burstTime, int priority)
        : id(ID), arrivalTime(arrivalTime), burstTime(burstTime), priority(priority) {};

    void process();
    bool cmpBT(const Job &other) const
    {
        return burstTime < other.burstTime;
    }
};

class TableElement
{
  public:
    int ID;
    int AT;
    int BT;
    int PRI;
    int CT;
    int TAT;
    int WT;
    TableElement() : ID(0), AT(0), BT(0), PRI(0), CT(0), TAT(0), WT(0) {};
    TableElement(int id, int at, int bt, int pri) : ID(id), AT(at), BT(bt), PRI(pri), CT(0), TAT(0), WT(0) {};
};

class Table
{
  public:
    TableElement op[100];

    void initTable(std::vector<Job> jobQueue, int len)
    {
        for (int i = 0; i < len; i++)
        {
            op[jobQueue[i].id] =
                TableElement(jobQueue[i].id, jobQueue[i].arrivalTime, jobQueue[i].burstTime, jobQueue[i].priority);
        }
    }

    void UpdateTableElementCT(int index, int ct)
    {
        op[index].CT = ct;
        op[index].TAT = ct - op[index].AT;
        op[index].WT = (ct - op[index].AT) - op[index].BT;
    }

    void printTable(int start, int end)
    {
        int avgTAT = 0, avgWT = 0;

        std::cout << "\n"
                  << "\n\t╭──────┬─────┬─────┬──────┬─────┬──────┬─────╮"
                  << "\n\t│ ID   │ AT  │ BT  │ PRI  │ CT  │ TAT  │ WT  │"
                  << "\n\t├──────┼─────┼─────┼──────┼─────┼──────┼─────┤";

        for (int i = start; i <= end; i++)
        {
            std::cout << "\n\t│ " << std::setw(4) << std::left << op[i].ID << " │ " << std::setw(3) << std::left
                      << op[i].AT << " │ " << std::setw(3) << std::left << op[i].BT << " │ " << std::setw(4)
                      << std::left << op[i].PRI << " │ " << std::setw(3) << std::left << op[i].CT << " │ "
                      << std::setw(4) << std::left << op[i].TAT << " │ " << std::setw(3) << std::left << op[i].WT
                      << " │";

            avgTAT += op[i].TAT;
            avgWT += op[i].WT;
        }

        std::cout << "\n\t╰──────┴─────┴─────┴──────┴─────┴──────┴─────╯";

        int count = end - start + 1;
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "\n\t Avg. TAT: " << static_cast<float>(avgTAT) / count
                  << "\t   Avg. WT : " << static_cast<float>(avgWT) / count << "\n";
    }
};

class JobQueue
{
  public:
    std::vector<Job> jobQueue;

    int getNextBatchArrivalTime(int timestamp)
    {
        int res;
        for (res = 0; res < jobQueue.size() && jobQueue[res].arrivalTime <= timestamp; res++)
            ;

        return (res >= jobQueue.size()) ? -1 : jobQueue[res].arrivalTime;
    }

    Job *getNextShortestJobInQueue(int timestamp)
    {
        int shortest = 0;
        for (int i = 0; i < jobQueue.size() && jobQueue[i].arrivalTime <= timestamp; i++)
        {
            if (jobQueue[shortest].burstTime <= 0)
                shortest = i;
            else if (jobQueue[i].burstTime > 0 && jobQueue[i].cmpBT(jobQueue[shortest]))
                shortest = i;
        }

        return (jobQueue[shortest].burstTime <= 0) ? NULL : &jobQueue[shortest];
    }
};

class AlgoRunner : public JobQueue
{
    Table op;

  public:
    AlgoRunner() : JobQueue() {};

    static void printTimestamp()
    {
        std::cout << "\033[42m  " << __timestamp << "  \033[44m";
    }
    void B2_RunAlgos(int i)
    {
        op.initTable(jobQueue, 3);
        ClearTimer();
        std::sort(jobQueue.begin(), jobQueue.end(), [](Job &a, Job &b) { return a.arrivalTime < b.arrivalTime; });
        std::cout << "\n\033[0m";
        switch (i)
        {
        case 1:
            std::cout << "FCFS:\t";
            B2_FCFS();
            break;
        case 2:
            std::cout << "PRI:\t";
            B2_PRI();
            break;
        case 3:
            std::cout << "SJF:\t";
            B2_SRTN();
            break;
        case 4:
            std::cout << "RR_25:\t";
            B2_RR(25);
            break;
        default:
            break;
        }
        printTimestamp();
        op.printTable((i - 1) * jobQueue.size() + 1, (i * jobQueue.size()));
        std::cout << "\n\n\033[0m";
    }

  private:
    static int __timestamp;

    void ClearTimer()
    {
        __timestamp = 0;
    }

    void B2_FCFS()
    {
        for (int i = 0; i < jobQueue.size(); i++)
        {
            if (__timestamp < jobQueue[i].arrivalTime)
            {
                Job().process();
                __timestamp = jobQueue[i].arrivalTime;
            }
            jobQueue[i].process();
            __timestamp += jobQueue[i].burstTime;

            op.UpdateTableElementCT(jobQueue[i].id, __timestamp);
        }
    }
    void B2_PRI()
    {
        std::sort(jobQueue.begin(), jobQueue.end(),
                  [](Job &a, Job &b) { return (a.arrivalTime <= b.arrivalTime) && (a.priority > b.priority); });
        for (int i = 0; i < jobQueue.size(); i++)
        {
            if (__timestamp < jobQueue[i].arrivalTime)
            {
                Job().process();
                __timestamp = jobQueue[i].arrivalTime;
            }
            jobQueue[i].process();
            __timestamp += jobQueue[i].burstTime;
            op.UpdateTableElementCT(jobQueue[i].id, __timestamp);
        }
    }
    void B2_SRTN()
    {
        while (1)
        {
            Job *job = getNextShortestJobInQueue(__timestamp);
            if (!job) // All jobs are completed
                break;

            // Job has arrived, process it
            int gap = getNextBatchArrivalTime(__timestamp) - __timestamp;
            gap = (gap < 0) || (gap > job->burstTime) ? job->burstTime : gap;
            job->burstTime -= gap;
            job->process();
            __timestamp += gap;
            if (job->burstTime <= 0)
                op.UpdateTableElementCT(job->id, __timestamp);
        }
    }
    void B2_RR(int timeSlice)
    {
        int i = 0, flag = 0;
        while (flag || i < jobQueue.size())
        {
            // If we have reached the end of the queue AND atleast 1 job is remaining,
            // or if the next job has not arrived yet, reset i to 0
            // reset i to 0
            if ((i >= jobQueue.size() && flag) || jobQueue[i].arrivalTime > __timestamp)
            {
                i = 0;
                flag = 0;
            }

            // If job is already completed, skip it
            if (jobQueue[i].burstTime <= 0)
            {
                i++;
                continue;
            }

            // Job has arrived, process it
            int gap = (jobQueue[i].burstTime < timeSlice) ? jobQueue[i].burstTime : timeSlice;
            jobQueue[i].burstTime -= gap;
            jobQueue[i].process();
            __timestamp += gap;
            if (jobQueue[i].burstTime <= 0)
            {
                op.UpdateTableElementCT(jobQueue[i].id, __timestamp);
            }
            flag = 1;
            i++;
        }
    }
};

void Job::process()
{
    AlgoRunner::printTimestamp();
    std::cout << "\033[41m P" << id << " ";
}

int AlgoRunner::__timestamp = 0;

int main()
{
    AlgoRunner arFCFS = AlgoRunner();
    AlgoRunner arPRI = AlgoRunner();
    AlgoRunner arSRTN = AlgoRunner();
    AlgoRunner arRR = AlgoRunner();

    arFCFS.jobQueue.push_back(Job(1, 0, 100, 4));
    arFCFS.jobQueue.push_back(Job(2, 0, 90, 6));
    arFCFS.jobQueue.push_back(Job(3, 2, 5, 1));
    arPRI.jobQueue.push_back(Job(4, 0, 100, 4));
    arPRI.jobQueue.push_back(Job(5, 0, 90, 6));
    arPRI.jobQueue.push_back(Job(6, 2, 5, 1));
    arSRTN.jobQueue.push_back(Job(7, 0, 100, 4));
    arSRTN.jobQueue.push_back(Job(8, 0, 90, 6));
    arSRTN.jobQueue.push_back(Job(9, 2, 5, 1));
    arRR.jobQueue.push_back(Job(10, 0, 100, 4));
    arRR.jobQueue.push_back(Job(11, 0, 90, 6));
    arRR.jobQueue.push_back(Job(12, 2, 5, 1));

    arFCFS.B2_RunAlgos(1);
    arPRI.B2_RunAlgos(2);
    arSRTN.B2_RunAlgos(3);
    arRR.B2_RunAlgos(4);

    return 0;
}