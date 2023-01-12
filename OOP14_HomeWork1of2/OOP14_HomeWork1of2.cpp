
#include <Windows.h>
#include <iostream>

#include "Queue.h"

using namespace std;

const int N = 25;

struct Day {
    int aveTimeApp_Eve = NULL;
    int aveTimeApp_Mor = NULL;
    int aveTimeApp_Aft = NULL;
    int typeOfBusStop = NULL;
};

void EnterData(Day &passTime, Day &busTime) {
    cout << "Enter the average time of appearance of passengers at the\n\
        stop at different times of the day (evening, morning, afternoon)\n";
    cin >> passTime.aveTimeApp_Eve >> passTime.aveTimeApp_Mor >> passTime.aveTimeApp_Aft;

    cout << "Enter the average time of appearance of bus at the\n\
        stop at different times of the day (evening, morning, afternoon)\n";
    cin >> busTime.aveTimeApp_Eve >> busTime.aveTimeApp_Mor >> busTime.aveTimeApp_Aft;

    cout << "Enter a type of bus stop(1 - final, 0 - not final):\n";
    cin >> busTime.typeOfBusStop;
}

// average waiting time
int AverageTime(int passTimeAf, int bussTimeAf, int mode) {
    int maxSizeBus = 0; // max size of bus

    // mode = 0 - afternoon, mode = 1 = morning, mode = 2 - evening
    if (mode == 0) maxSizeBus = 6;
    else if (mode == 1) maxSizeBus = 4;
    else if (mode == 2) maxSizeBus = 5;

    int maxTimesRepeat = 1000; // number of count repeats   
    srand(time(NULL));
    Queue passengers(N); // queue of passengers on a bus stop
    int averageTimeStay = 0; // average time stay passenger on a bus stop
    int averageTimesSpent = 0; // number of times the middle passenger was picked up by the bus

    int middlePassenger = N; // middle passenger =  all passengers / 2
    int timeSpent = 0; // time which a middle passenger spent on a bus stop
    int countBusSpent = 0; // buses which was missed

    int a = 0;
    while (maxTimesRepeat != 0) {
        maxTimesRepeat--;
        // filling the bus stop by passengers
        for (int i = 0; i < bussTimeAf / passTimeAf; i++) {
            passengers.add(i + 1);
        }
        // if bus is full
        if (passengers.isFull())
            return -1;

        // If we don't have a middle passenger yet
        if (middlePassenger == N) 
            middlePassenger = passengers.getCount() / 2;

        if (countBusSpent == 0)
            timeSpent += bussTimeAf / 2; // he waited first bus       
        else // he waited not first bus
            timeSpent += bussTimeAf; // How long he waited a bus

        countBusSpent++; // Missed bus (It must be more than 1 in order not to divide by 0)

        // number of seats' bus
        int busSeats = rand() % maxSizeBus + 1;

        // passengers are getting on the bus
        for (int i = 0; i < busSeats; i++) {
            passengers.extract();
        }

        if (middlePassenger >= passengers.getCount()) {
            averageTimeStay += timeSpent / countBusSpent; //determine the average time spent by one middle passenger
            averageTimesSpent++; // How many middle passengers waited
            timeSpent = 0; // Zeroing
            countBusSpent = 0; // Zeroing
            middlePassenger = passengers.getCount() / 2; // determining the middle passenger
        }

    }
    // average waiting time
    return averageTimeStay / averageTimesSpent;
}

// optimal time of arrival bus
int OptimumTimeOfBusArriving(int passTime, int maxSizeBus) {
    // optimal time of arrival bus
    // M - max size of bus
    // n - ideal count of people
    // +1 - need
    // 0.8 - ideal chance
    // |n = M+1 - 0.8 * M  (from formula ((M - n + 1) * 1/5 = 0.8)
    // P - people time arriving
    // B - bus time arriving
    // |ideal time of bus arriving (IToBA) = P * n
    // |=> IToBA = P * (M + 1 - 0.8 * M)
    return passTime * (maxSizeBus + 1 - 0.8 * maxSizeBus);
}

int main()
{
    srand(time(NULL));  
    Day busTime;
    Day passTime;

    EnterData(passTime, busTime);
    system("cls");
    int avTimeAf = AverageTime(passTime.aveTimeApp_Aft, busTime.aveTimeApp_Aft,0);
    int avTimeEv = AverageTime(passTime.aveTimeApp_Eve, busTime.aveTimeApp_Eve,2);
    int avTimeMo = AverageTime(passTime.aveTimeApp_Mor, busTime.aveTimeApp_Mor,1);

    cout << "Afternoon\n\n";
    if (avTimeAf != -1)
        cout << "Average waiting time during the day - " << avTimeAf << endl;
    else 
        cout << "The bus stop was fulled, so people didn't wait for the bus.\n";
    cout << "Best bus arrival time - " << OptimumTimeOfBusArriving(passTime.aveTimeApp_Aft, 6) << endl;
    
    cout << "\nEvening\n\n";
    if (avTimeEv != -1)
        cout << "Average waiting time during the day - " << avTimeEv << endl;
    else 
        cout << "The bus stop was fulled, so people didn't wait for the bus.\n";
    cout << "Best bus arrival time - " << OptimumTimeOfBusArriving(passTime.aveTimeApp_Eve, 6) << endl;

    cout << "\nMorning\n\n";
    if (avTimeMo != -1)
        cout << "Average waiting time during the day - " << avTimeMo << endl;
    else
        cout << "The bus stop was fulled, so people didn't wait for the bus.\n";
    cout << "Best bus arrival time - " << OptimumTimeOfBusArriving(passTime.aveTimeApp_Mor, 4) << endl;


    
}

