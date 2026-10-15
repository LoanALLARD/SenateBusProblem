# SenateBusProblem

- Un sémaphore est un compteur.
    - Si on occupe une place, on décrémente le compteur. S'il est à zéro, on ne peut rien faire et on attend.
- Un mutex, c'est comme une clé d'accès.
    - Il permet de gérer l'ordre de passage de chaque thread.
        - Exemple : Imaginons des toilettes. Une seule personne peut passer à la fois et cette personne détient une clé. Celui qui est dans les toilettes a la clé et les autres attendent de recevoir la clé pour pouvoir rentrer.

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
