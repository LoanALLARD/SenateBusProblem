// #include <algorithm>
// #include <iostream>
// #include <thread>
// #include <semaphore>
// #include <mutex>
// #include <chrono>
// #include <vector>

// using namespace std;

// mutex mtx;

// const int TOTAL_RIDERS = 125;

// // Bus variables
// counting_semaphore<50> bus_semaphore(0);
// counting_semaphore<50> allAboard(0);


// // Riders variables
// counting_semaphore<50> nb_place (50);
// int count_riders = 0;
// int nb_riders_board = 0;

// void bus() {
//     while (true) {
//         this_thread::sleep_for(chrono::milliseconds(1000));
//         mtx.lock();

//         // Condition de sécurité
//         if (nb_riders_board >= TOTAL_RIDERS) {
//             mtx.unlock();
//             break;
//         }

//         if (count_riders > 0) {
//             cout << "Le bus laisse monté les premiers passagés. \n";

//             bus_semaphore.release();
//             allAboard.acquire();
//         } else {
//             cout << "Le bus est arrivé main il n'y a personne. Il repart direct.\n";
//         }

//         cout << "Le bus part. \n";

//         mtx.unlock();
//     }
// }


// void riders_func(int id) {
//     nb_place.acquire();

//     mtx.lock();
//     count_riders += 1;
//     cout << "Un passager arrive. (En attente " << count_riders << ")\n";
//     mtx.unlock();

//     bus_semaphore.acquire(); // Le bus attend que le passagé monte
//     nb_place.release(); // Libérer sa place dans l'air d'attente

//     cout << "Le passager numéro " << id << " monte dans le bus.\n";

//     count_riders -= 1;
//     nb_riders_board += 1;

//     if (count_riders == 0) {
//         allAboard.release(); // Réveille le bus pour partir
//     } else {
//         bus_semaphore.release(); // Révéille le passager suivant pour monter
//     }
// }


// int main()
// {
//     vector<thread> riders;
//     thread bus_senat (bus);

//     for (unsigned int i = 1; i <= TOTAL_RIDERS; ++i) {
//         riders.emplace_back(thread (riders_func, i));

//         this_thread::sleep_for(chrono::milliseconds(40));
//     }

//     for (auto& rider : riders) {
//         rider.join();
//     }

//     bus_senat.join();

//     cout << "Tout les passager on été transportés.\n";

//     return 0;
// }
