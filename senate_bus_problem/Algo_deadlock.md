# Algorithme du <i>Senat Bus Problem</i> (Deadlock)

## serveur_func (DEADLOCK ICI)

```
WHILE LOOP:
    Attendre 3 secondes, pour laisser le temps au joueur d'arriver (ligne ajouté plus tard pour avoir un truc agréable dans le terminal)

    Il bloque le mutex

    SI le nombre de joueur dans la pool atteins son maximum ALORS (condition pour éviter un deadlock)
        Il debloque le mutex
        On sort de la boucle
    
    SI il y a des joueur en attente ALORS (PRÉCISEMENT ICI LE DEADLOCK, ON A INVERSÉ CES DEUX LIGNES)
        Le lancement se met en veille pour que tout les joueurs rentre
        Le serveur laisse monter le joueurs suivant
    SINON
        On affiche "Le serveur est vide. La partie est lancé."
    
    Il debloque le mutex
END WHILE LOOP
```

## player_func

```
(même code ...)
```

## main

```
(même code ...)
```

## Explication du dealock

1. Le serveur dit "je ne bouge pas tant que le dernier joueur n'aura pas rejoins"
2. Le problème, c'est que en inversant les deux ligne, le serveur s'est mis en veille AVANT d'avoir ouvert l'accés aux joueurs
3. Les joueurs dans la file d'attente ne peuvent pas rentrer tant que le serveur n'est pas ouvert
4. Et la partie ne peux jamais commencé tant que les joueurs ne sont pas tous rentrer et donner le signal

**DONC**

- Le serveur attend que les joueurs donne le signale
- Les joueur attendent que le serveur les laissent rentré
- Tout le monde attent tout le monde : c'est là le DEADLOCK
