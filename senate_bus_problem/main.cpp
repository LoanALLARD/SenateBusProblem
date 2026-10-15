#include <algorithm>
#include <chrono>
#include <iostream>
#include <thread>
#include <semaphore>
#include <mutex>
#include <chrono>

using namespace std;

counting_semaphore<3> places_parking(3);
mutex mutex_borne;

int argent_caisse = 0;

void voiture(int id) {
    places_parking.acquire();
    cout << "Voiture " << id << " est garée. \n";
    this_thread::sleep_for(chrono::milliseconds(500));

    mutex_borne.lock();
    argent_caisse += 10;
    mutex_borne.unlock();

    cout << "Voiture " << id << " quitte le parking. \n";
    places_parking.release();
}

int main()
{
    vector<thread> trafic;

    for (int i = 1; i <= 5;  ++i) {
        trafic.emplace_back(thread(voiture, i));
    }

    for (auto& v : trafic) {
        v.join();
    }

    return 0;
}
