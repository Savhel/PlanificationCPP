#include <iostream>
#include <vector>
#include <algorithm>
#include "Processus.h"

class FCFS {
public:
    void findWaitingTimeFCFS(std::vector<Processus>& proc) {
        proc[0].waitingTime = 0; // Premier Processus n'a pas de temps d'attente

        for (size_t i = 1; i < proc.size(); i++) {
            proc[i].waitingTime = proc[i - 1].burstTime + proc[i - 1].waitingTime - proc[i].arrivalTime + proc[i-1].arrivalTime;
        }

    }

    void findTurnAroundTimeFCFS(std::vector<Processus>& proc) {
        for (auto& p : proc) {
            p.turnAroundTime = p.burstTime + p.waitingTime;
        }
    }

    void findAverageTimeFCFS(std::vector<Processus>& proc) {
        int totalWaitingTime = 0, totalTurnAroundTime = 0;
        findWaitingTimeFCFS(proc);
        findTurnAroundTimeFCFS(proc);

        std::cout << "Processus\t\tBurst Time\t\tWaiting Time\t\tTurnaround Time\n";
        for (const auto& p : proc) {
            totalWaitingTime += p.waitingTime;
            totalTurnAroundTime += p.turnAroundTime;
            std::cout << "    " << p.pid << "   \t\t\t" << p.burstTime << "   \t\t\t" << p.waitingTime<< "   \t\t\t" << p.turnAroundTime << std::endl;
        }

        std::cout << "\nAverage waiting time = " << (float)totalWaitingTime / proc.size();
        std::cout << "\nAverage turnaround time = " << (float)totalTurnAroundTime / proc.size() << std::endl;
    }

    void runFCFS(std::vector<Processus>& proc) {
        std::sort(std::begin(proc), std::end(proc), [](const Processus& a, const Processus& b) {
            return a.arrivalTime < b.arrivalTime;
        });
        findAverageTimeFCFS(proc);
    }

    void printGanttChartFCFS(const std::vector<Processus>& proc) {
        std::cout << "\nGantt Chart:\n";
        std::cout << "|";
        for (const auto& p : proc) {
            for (int j = 0; j < p.burstTime; j++) {
                std::cout << "--";
            }
            std::cout << "|";
        }
        std::cout << "\n";

        for (const auto& p : proc) {
            std::cout << "| P" << p.pid << " ";
        }
        std::cout << "|\n";

        std::cout << "0";
        int currentTime = 0;
        for (const auto& p : proc) {
            currentTime += p.burstTime;
            std::cout << "  ";
            if (currentTime < 10) std::cout << " ";
            std::cout << currentTime;
        }
        std::cout << "\n";
    }
};

int mainFCFS(std::vector<Processus> proc) {
    int currentTime = 0; // Valeur initiale du currentTime
    FCFS fcfs;
    fcfs.runFCFS(proc);
    fcfs.printGanttChartFCFS(proc);
    return 0;
}
