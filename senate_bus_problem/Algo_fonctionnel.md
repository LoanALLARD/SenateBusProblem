# Algorithme du <i>Senat Bus Problem</i>

## serveur_func

```
WHILE LOOP:
    Attendre 3 secondes, pour laisser le temps au joueur d'arriver (ligne ajouté plus tard pour avoir un truc agréable dans le terminal)

    Il bloque le mutex

    SI le nombre de joueur dans la pool atteins son maximum ALORS (condition pour éviter un deadlock)
        Il debloque le mutex
        On sort de la boucle
    
    SI il y a des joueur en attente ALORS
        Le serveur laisse monter le joueurs suivant
        Le lancement se met en veille pour que tout les joueurs rentre
    SINON
        On affiche "Le serveur est vide. La partie est lancé."
    
    Il debloque le mutex
END WHILE LOOP
```

## player_func

```
Le joueur attend dans la file d'attente

Il bloque le mutex
Increment le nombre de joueur present dans le serveur
Il débloque le mutex

Le serveur attend que le joueur rentre dans le serveur
Le joueur qui est rentré libére la place

On décrémente le nombre de joueur en attente dans la file
On incrémente le nombre de joueur qui sont rentré dans le serveur (pour garder une trace du nombre de personne dans le serveur)

SI le joueur est le dernier en attente alors ALORS
    le serveur lance la partie
SINON :
    le serveur fait rentrer la personne suivante
```

## main

```
Initialisation d'un vector de thread (représente les joueurs)
Initialisation d'un thread nommé serveur

FOR LOOP:
    On ajoute le nombre total de joueur choisi aléatoirement
    On attend quelque millisecond pour avoir un effet de chargement dans le terminal (ligne complétement optionnel)
END FOR LOOP

FOR LOOP:
    On execute le code de chaque thread joueur
END FOR LOOP

On execute le thread serveur

On afficher total de joueur ayant participé à l'exécution dans le terminal
```

