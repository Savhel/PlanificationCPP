#ifndef SJF_H
#define SJF_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "Processus.h"

class SJF {
public:
    static void findWaitingTimeSJF(std::vector<Processus>& proc) {
        proc[0].waitingTime = 0; // Le premier processus n'a pas de temps d'attente

        for (size_t i = 1; i < proc.size(); i++) {
            proc[i].waitingTime = proc[i - 1].burstTime + proc[i - 1].waitingTime - proc[i].arrivalTime + proc[i - 1].arrivalTime;
            if (proc[i].waitingTime < 0) {
                proc[i].waitingTime = 0;
            }
        }
    }

    static void findTurnAroundTimeSJF(std::vector<Processus>& proc) {
        for (auto& p : proc) {
            p.turnAroundTime = p.burstTime + p.waitingTime;
        }
    }

    static void findAvgTimeSJF(std::vector<Processus>& proc) {
        int total_wt = 0, total_tat = 0;
        findWaitingTimeSJF(proc);
        findTurnAroundTimeSJF(proc);

        std::cout << "Processus\t\tBurst Time\t\tWaiting Time\t\tTurnaround Time\n";
        for (const auto& p : proc) {
            total_wt += p.waitingTime;
            total_tat += p.turnAroundTime;
            std::cout << "    " << p.pid << "   \t\t\t" << p.burstTime << "   \t\t\t" << p.waitingTime<< "   \t\t\t" << p.turnAroundTime << std::endl;

        }

        std::cout << "Average waiting time = " << static_cast<float>(total_wt) / proc.size() << std::endl;
        std::cout << "Average turnaround time = " << static_cast<float>(total_tat) / proc.size() << std::endl;
    }

    static void runSJF(std::vector<Processus>& proc) {
        std::sort(proc.begin(), proc.end(), [](const Processus& a, const Processus& b) {
            return a.burstTime < b.burstTime;
        });
        findAvgTimeSJF(proc);
    }

    static void printGanttChart(const std::vector<Processus>& proc) {
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

inline int mainSJF(std::vector<Processus> proc) {
    SJF::runSJF(proc);
    SJF::printGanttChart(proc);
    return 0;
}

#endif // SJF_H
