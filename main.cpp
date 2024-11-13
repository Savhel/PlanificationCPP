#include <iostream>
#include <cstdlib>
#include <ctime>
#include "FCFS.h"
#include "Processus.h"
#include "SJF.h"
#include "RR.h"
#include "SRTF.h"
#include "RRP.h"

int main() {
    srand(time(0));
    int NB_PROCESSUS = rand() % 20 + 1;
    std::vector<Processus> proc(NB_PROCESSUS);

    // Génération des processus aléatoirement
    for (int i = 0; i < NB_PROCESSUS; i++) {
        proc[i].pid = i + 1;
        proc[i].burstTime = rand() % 10 + 1; // temps de burst aléatoire entre 1 et 10
        proc[i].waitingTime = 0;
        proc[i].turnAroundTime = 0;
        proc[i].arrivalTime = rand() % 10 + 1; // temps de burst aléatoire entre 1 et 10
        proc[i].remainingTime = 0;
        proc[i].priority = rand() % 10 + 1;
    }

    // int n = sizeof(proc) / sizeof(proc[0]);
    int quantum = 4;
    int choice = 5;

    std::cout << "Bonjour à toi !" << std::endl;
    std::cout << "Testons les algorithmes FCFS, SJF et RR" << std::endl;
    std::cout << "Voici les processus " << std::endl;
    std::cout << "Processus    Burst Time     Arrival Time    Waiting Time    Turnaround Time    Priority" << std::endl;
    for (int i = 0; i < NB_PROCESSUS; i++) {
        std::cout << " " << proc[i].pid << "\t\t" << proc[i].burstTime << "\t\t" << proc[i].arrivalTime << "\t\t" << proc[i].waitingTime << "\t\t" << proc[i].turnAroundTime << "\t\t" << proc[i].priority << std::endl;
    }

    std::cout << "Quels algorithmes veux-tu appliquer aux processus ? " << std::endl;
    std::cout << "1. FCFS (First-Come-First-Served) : les processus sont traités dans l'ordre de leur arrivée" << std::endl;
    std::cout << "2. SJF (Shortest Job First) : les processus sont traités en fonction de leur temps de burst" << std::endl;
    std::cout << "3. RR (Round Robin) : les processus sont traités en fonction de leur temps de burst et de leur priorité" << std::endl;
    std::cout << "4. SRTF (Shortest Remaining Time First) : les processus sont traités en fonction de leur temps de burst restant" << std::endl;
    std::cout << "5. RRP (Round Robin avec priorité) : les processus sont traités en fonction de leur temps de burst et de leur priorité" << std::endl;
    std::cout << "0. pour sortir " << std::endl;

    std::cin >> choice;

    while (choice != 0) {
        switch (choice) {
            case 1:
                mainFCFS(proc);
                break;
            case 2:
                mainSJF(proc);
                break;
            case 3:
                mainRR(proc, quantum);
                break;
            case 4:
                mainSRTF(proc);
                break;
            case 5:
                mainRRP(proc, quantum);
                break;
            default:
                std::cout << "Erreur : choix invalide" << std::endl;
                break;
        }

        std::cout << "Quels algorithmes veux-tu appliquer à ces mêmes processus ? " << std::endl;
        std::cout << "1. FCFS (First-Come-First-Served) : les processus sont traités dans l'ordre de leur arrivée" << std::endl;
        std::cout << "2. SJF (Shortest Job First) : les processus sont traités en fonction de leur temps de burst" << std::endl;
        std::cout << "3. RR (Round Robin) : les processus sont traités en fonction de leur temps de burst et de leur priorité" << std::endl;
        std::cout << "4. SRTF (Shortest Remaining Time First) : les processus sont traités en fonction de leur temps de burst restant" << std::endl;
        std::cout << "5. RRP (Round Robin avec priorité) : les processus sont traités en fonction de leur temps de burst et de leur priorité" << std::endl;
        std::cout << "0. pour sortir " << std::endl;

        std::cin >> choice;
    }

    return 0;
}