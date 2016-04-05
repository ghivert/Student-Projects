# Projet PC2R : Rapport
### Par Guillaume Hivert && Darius Mercadier

# Introduction
Comme demandé, le projet a été fait dans deux langages différents : le serveur en Go, et le client en Javascript à l'aide du framework Electron.
Le Go étant pensé pour faciliter la concurrence, il nous a paru comme un choix judicieux pour développer le serveur qui doit naturellement être non-bloquant. De plus, la gestion native des canaux, intimement liée à la concurrence, facilite grandement les opérations de communications du serveur vers les clients.
La majeur partie du travail autour du client étant liée à son interface graphique, Javascript et Electron sont apparus comme un outil pratique et puissant, dans la mesure où ils ont été concu pour accomplir ce genre de taches.


# Manuel Utilisateur
## Installation
Nous supposerons que vous disposez d'une machine unix. Si ce n'est pas le cas, vous pourrez probablement tester le programme, mais nous ne détaillerons pas les procédures d'installation.

### Serveur
Le serveur est écrit dans le langage Go. Pour le lancer, il vous faudra en premier lieu installer le langage Go.
Sur une distribution Linux, il est possible de passer par son gestionnaire de package (apt-get ou dnf par exemple) pour récupérer celui de `golang`. Sur Mac, il est possible de passer par Homebrew, à l'aide du package `go`.
Aucune compilation du serveur n'est nécessaire.

### Client
Trololol, démerdez vous



# Guide d'utilisation
### Lancement
Commencez par lancer le serveur depuis un terminal à l'aide de la commande :
`go run server.go`
Un certain nombre de messages de status et de progression s'afficheront sur la sortie d'erreur. Si vous souhaitez vous en passer, lancez plutot la commande :
`go run server.go 2>/dev/null`
<br>
Vous pouvez maintenant lancer le client comme suit :


### Déroulement de la partie
Une fois que deux clients auront été lancés, la partie démarera automatiquement.
Une partie comporte 10 tours.
Chaque tours se déroule en 3 phases :
- une phase de réflexion de 5 minutes pendant laquelle vous réfléchirez aux solutions du problème. Le premier client à annoncer qu'il a trouvé une solution met fin à la phase de reflexion.
- une phase d'enchères pendant laquelle vous pouvez annoncer un certain nombre de coups pour votre solution. Vous ne pouvez pas annoncer plus de coups qu'une de vos enchère précédente, ni annoncer le même nombre de coups qu'un autre joueur.
- une phase de résolution pendant laquelle les joueurs, un à un (dans l'ordre du moins offrant au plus offrant), détailleront leur solution jusqu'à ce qu'un solution soit valide. Le joueur qui a proposé la solution la moins offrante valide gagne 1 point.
Le joueur ayant le plus de points à la fin gagne la partie.


# Guide technique
Cette partie a pour but de vous présenter le fonctionnement interne du serveur et du client. Nous vous recommandons de la lire avant d'essayer de lire les codes sources.

### Serveur
Le serveur est séparé en deux parties : d'un coté la gestion du jeu (fonction `game`), et de l'autre, la gestion des connections et des messages des clients (boucle infinie acceptant les connections et lancant une fonction `client` pour chaque conneciton). Ces deux partie sont reliées par la fonction `run` et un objet (sous forme de structure) `hub`.
Chaque client est représenté par une structure `connection` qui contient la socket, le nom du client, le score du client, et un cannal sur lequel les messages seront envoyé depuis la fonction de jeu vers le client.
Le `hub` contient 5 champs : une table de hashage répertoriant les clients, un cannal `register` par lequel les clients s'ajoutent à la hashmap de clients, un cannal `unregister` par lequel ils s'en suppriment, un cannal `action` par lequel les clients interagissent avec le serveur, et pour finir un cannal`broadcast` sur lequel la fonction de jeu envoie les messages devant être relayés à tous les clients.
La fonction de jeu (`game`) gère le jeu, et écoute sur le cannal `action` du hub sur lequel les clients envoient des messages pour effectuer leurs actions. Le cannal `action` est géré de manière non-concurrente (un seul message à la fois sur le cannal), donc il ne peut pas y avoir d'incohérences dans l'état du jeu lié à des accès concurrents à des variables internes (par exemple si deux enchère de la même valeur arrivent en même temps, celle qui passera en premier sur le cannal `action` sera validée, et l'autre sera refusée.).
<br>
