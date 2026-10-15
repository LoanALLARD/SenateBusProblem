# SenateBusProblem

## CPP REFERENCE

### counting_semaphore

```c++
#include <semaphore>
#include <thread>

std::counting_semaphore<3> count = 3
// Par exemple on a trois place au maximum dans un parking

int main() {
    count.acquire(); // Par exemple une voiture rentre dans un garage, donc elle occupe une place
    // count est décrémenté
    count.release(); // Ici une voiture sort du parking, donc count est incrémenté

    return 0;
}
```

### mutex

```c++
#include <thread>
#include <mutex>

std::mutex borne_paiement; // ici on représente une borne de paiement de sortie de parking, et ici impossible d'avoir deux voiture qui passent en même temps, chacun sont tour. Le mutex permet d'empêcher que de thread modifie une même valeur en même temps.

int main() {

    borne_paiement.lock() // Permet de dire que la borne est occupé attend ton tour.
    borne_paiement.unlock() // Permet de dire que la borne est libre, au suivant.

    return 0;
}

```

### thread

```c++
#include <thread>

void voiture(int id) {
    // code du comportement de la voiture
}

int main() {

    vector<thread> trafic;

    for (int i = 1; i <= 5; ++i) {
        trafic.emplace_back(thread(voiture, i))
    } // On ajoute dans le trafic une voiture qui va faire tout ses étapes

    for (auto& v : trafic) {
        v.join(); // La méthode join permet de dire attent l'execution jusqu'à la fin.
    }

    return 0;
}

```
