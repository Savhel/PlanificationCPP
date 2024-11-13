//
// Created by PFI BERTO COMPUTER on 26/10/2024.
//

#ifndef PROCESSUS_H
#define PROCESSUS_H



class Processus {
public:
    int pid;              // ID du processus
    int burstTime;        // Temps d'exécution
    int arrivalTime;      // Temps d'arrivée
    int waitingTime;      // Temps d'attente
    int turnAroundTime;   // Temps de rotation
    int remainingTime;
    int priority;

    Processus(int pid = -1, int burstTime = -1, int arrivalTime = -1, int priority = -1,
              int remainingTime = 0, int waitingTime = 0, int turnAroundTime = 0): pid(pid), burstTime(burstTime),
        arrivalTime(arrivalTime), waitingTime(0), turnAroundTime(0), remainingTime(0), priority(priority) {
    }

    void calculateWaitingTime(int currentTime) {
        waitingTime = currentTime - arrivalTime;
    }

    void calculateTurnAroundTime(int currentTime) {
        turnAroundTime = currentTime - arrivalTime + burstTime;
    }
};



#endif //PROCESSUS_H
