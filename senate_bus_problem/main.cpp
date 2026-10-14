#include <algorithm>
#include <chrono>
#include <iostream>
#include <mutex>
#include <random>
#include <semaphore>
#include <thread>
#include <vector>

using namespace std;

constexpr int MAX_SLOTS = 50;

int waiting = 0;
mutex mtx;
counting_semaphore<> instanceReady(0);
counting_semaphore<> joined(0);

mutex io;
template <class... A> void log(A&&... a) {
    lock_guard<mutex> lk(io);
    (cout << ... << a) << '\n';
}

void joinMatch(int id)  { log("joueur ", id, " rejoint la partie"); }
void startMatch(int n)  { log("Partie lancée avec ", n, " joueurs \n"); }


void serverInstance() {
    int n;
    {
        lock_guard<mutex> lk(mtx);
        n = min(waiting, MAX_SLOTS);
        for (int i = 0; i < n; ++i) {
            instanceReady.release();
            joined.acquire();
        }
        waiting = max(waiting - MAX_SLOTS, 0);
    }
    startMatch(n);
}


void player(int id) {
    {
        lock_guard<mutex> lk(mtx);
        ++waiting;
    }
    instanceReady.acquire();
    joinMatch(id);
    joined.release();
}

int main() {
    mt19937 rng(42);
    uniform_int_distribution<int> delay(0, 600);

    vector<thread> threads;


    for (int id = 1; id <= 120; ++id) {
        threads.emplace_back([id, d = delay(rng)] {
            this_thread::sleep_for(chrono::milliseconds(d));
            player(id);
        });
    }

    thread server([] {
        for (int i = 0; i < 4; ++i) {
            this_thread::sleep_for(chrono::milliseconds(250));
            serverInstance();
        }
    });

    server.join();
    for (auto& t : threads) t.join();
}