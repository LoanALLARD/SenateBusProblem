#include <algorithm>
#include <iostream>
#include <thread>
#include <semaphore>
#include <mutex>
#include <chrono>
#include <vector>
#include <random>

using namespace std;

// RANDOM VALUE (bonus)
int rand_val(unsigned int start, unsigned int end) {
    random_device seed;
    mt19937 gen(seed());
    uniform_int_distribution<> distrib(start, end);
    int nb_rand = distrib(gen);

    return nb_rand;
}

mutex mtx;

const int TOTAL_PLAYER = rand_val(100, 300);

// serveur variables
counting_semaphore<50> serveur_semaphore(0);
counting_semaphore<50> allAboard(0);


// players variables
counting_semaphore<50> nb_place (50); // the max place in the waiting area
int count_player = 0; // number of player in the waiting area
int nb_player_playing = 0; // number of player in the server

void serveur_func() {
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(3000)); // waiting 3 seconds to let player join
        mtx.lock();

        // Security conditon to not blocked in the loop
        if (nb_player_playing >= TOTAL_PLAYER) {
            mtx.unlock();
            break;
        }

        // Check if there is a player in the waiting area, during the 3 second waiting
        if (count_player > 0) {
            cout << "Le serveur fait entré des joueurs. \n";

            serveur_semaphore.release();
            allAboard.acquire();

        } else {
            cout << "Le serveur est vide. La partie est lancé.\n";
        }

        cout << "Le serveur se lance. \n";

        mtx.unlock();
    }
}


void player_func(int id) {
    nb_place.acquire(); // the player arrived in the waiting area

    mtx.lock();
    count_player += 1; // the number of player increase
    cout << "Un joueur arrive. (En attente " << count_player << ")\n";
    mtx.unlock();

    serveur_semaphore.acquire(); // the server waits the player join the server
    nb_place.release(); // the player free the place

    cout << "Le joueur numéro " << id << " rentre dans le serveur.\n";

    count_player -= 1;
    nb_player_playing += 1;

    // check if there is a player in the waiting area
    if (count_player == 0) {
        allAboard.release(); // the server launch the game
    } else {
        serveur_semaphore.release(); // the server let the next player to join him
    }
}


int main()
{
    vector<thread> players; // vector of players
    thread serveur (serveur_func); // the server

    // add players (thread) in the vector
    for (unsigned int i = 1; i <= TOTAL_PLAYER; ++i) {
        players.emplace_back(thread (player_func, i));

        this_thread::sleep_for(chrono::milliseconds(rand_val(40, 100))); // for the effect in the terminal (not important)
    }

    for (auto& player : players) {
        player.join(); // execute the player threads
    }

    serveur.join(); // execute the server thread

    cout << "Les " << TOTAL_PLAYER << " joueurs ont rejoins une partie.\n";

    return 0;
}
