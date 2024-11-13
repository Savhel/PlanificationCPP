#ifndef SRTF_H
#define SRTF_H

#include <iostream>
#include <climits>
#include <vector>
#include "Processus.h"

class SRTF {
public:
    void findAvgTimeSRTF(std::vector<Processus>& proc) {
        int totalWaitingTime = 0, totalTurnAroundTime = 0;
        std::vector<int> rt(proc.size());
        for (size_t i = 0; i < proc.size(); i++) {
            rt[i] = proc[i].burstTime;
        }
        
        int complete = 0, t = 0, minm = INT_MAX;
        int shortest = 0, finish_time;
        bool check = false;
        std::vector<std::string> chart;

        while (complete != proc.size()) {
            for (size_t j = 0; j < proc.size(); j++) {
                if ((rt[j] < minm) && (rt[j] > 0) && (proc[j].arrivalTime <= t)) {
                    minm = rt[j];
                    shortest = j;
                    check = true;
                }
            }

            if (!check) {
                t++;
                chart.emplace_back("| free ");
                continue;
            }

            rt[shortest]--;
            chart.push_back("| P" + std::to_string(proc[shortest].pid) + " ");
            minm = rt[shortest] ? rt[shortest] : INT_MAX;

            if (rt[shortest] == 0) {
                complete++;
                check = false;
                finish_time = t + 1;
                proc[shortest].calculateWaitingTime(finish_time - proc[shortest].burstTime);
                proc[shortest].calculateTurnAroundTime(finish_time);
            }

            t++;
        }

        std::cout << "Processus\t\tBurst Time\t\tWaiting Time\t\tTurnaround Time\n";

        for (const auto& p : proc) {
            totalWaitingTime += p.waitingTime;
            totalTurnAroundTime += p.turnAroundTime;
            std::cout << "    " << p.pid << "   \t\t\t" << p.burstTime << "   \t\t\t" << p.waitingTime<< "   \t\t\t" << p.turnAroundTime << std::endl;
        }

        std::cout << "Average waiting time = " << static_cast<float>(totalWaitingTime) / proc.size() << std::endl;
        std::cout << "Average turnaround time = " << static_cast<float>(totalTurnAroundTime) / proc.size() << std::endl;

        // Gantt Chart
        std::cout << "\nGantt Chart:\n";
        for (const auto& p : chart) {
            std::cout << p;
        }
        std::cout << "|\n";

        std::cout << "0";
        for (size_t i = 1; i <= chart.size(); i++) {
            std::cout << "    " << i;
        }
        std::cout << "\n";
    }

    void runSRTF(std::vector<Processus>& proc) {
        std::sort(std::begin(proc), std::end(proc), [](const Processus& a, const Processus& b) {
            return a.arrivalTime < b.arrivalTime;
        });
        findAvgTimeSRTF(proc);
    }
};

int mainSRTF(std::vector<Processus> proc) {
    SRTF srtf;
    srtf.runSRTF(proc);
    return 0;
}

#endif // SRTF_H
