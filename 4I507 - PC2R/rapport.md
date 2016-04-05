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
Le serveur est écrit en Javascript, à l'aide de Node.js, et du framework Electron. Sur une distribution Linux, il faut tout d'abord installer Node.js, puis, à l'aide du gestionnaire de package npm, il faut installer le package electron-prebuilt. Installé globalement, il permet d'accéder à l'éxecutable electron. Pour installer Node facilement, celui-ci est disponible sur les principaux gestionnaire de package (`apt-get install nodejs` ou `dnf install nodejs`), ou sur Mac, via Homebrew (brew install nodejs). Ensuite, pour installer Electron de manière globale, il lancer la commande `npm install -g electron-prebuilt`. Si jamais Electron n'est pas sur le path, utiliser la commande `npm install electron-prebuilt`, permet de l'installer en local, dans le dossier node_modules.

# Guide d'utilisation
### Lancement
Commencez par lancer le serveur depuis un terminal à l'aide de la commande :
`go run lib/server/server.go`
Un certain nombre de messages de status et de progression s'afficheront sur la sortie d'erreur. Si vous souhaitez vous en passer, lancez plutot la commande :
`go run server.go 2>/dev/null`
<br>
Vous pouvez maintenant lancer le client comme suit : `electron .` ou `./node_modules/electron-prebuilt/bin/electron .`


### Déroulement de la partie
Une fois que deux clients auront été lancés, la partie démarera automatiquement.
Une partie comporte 10 tours.
Chaque tours se déroule en 3 phases :
- une phase de réflexion de 5 minutes pendant laquelle vous réfléchirez aux solutions du problème. Le premier client à annoncer qu'il a trouvé une solution met fin à la phase de reflexion.
- une phase d'enchères pendant laquelle vous pouvez annoncer un certain nombre de coups pour votre solution. Vous ne pouvez pas annoncer plus de coups qu'une de vos enchère précédente, ni annoncer le même nombre de coups qu'un autre joueur.
- une phase de résolution pendant laquelle les joueurs, un à un (dans l'ordre du moins offrant au plus offrant), détailleront leur solution jusqu'à ce qu'un solution soit valide. Le joueur qui a proposé la solution la moins offrante valide gagne 1 point.
Le joueur ayant le plus de points à la fin gagne la partie.

#### Utilisation du client
Il faut tout d'abord s'identifier avec son nom d'utilisateur. Ensuite, au début d'un tour, il est possible de miser une première enchère, ce qui déclenchera le début des enchères. Durant les enchères, il est possible de miser de nouveau. Une fois les enchères passées, et si l'on a la main, il convient de rentrer avec les boutons et les flèches les différents mouvements des robots : on clique sur la couleur du robot, puis la direction choisie. On valide ensuite, ce qui envoie la réponse sur le serveur. Un nouveau tour débute une fois que l'énigme est résolue.  
Vous pouvez entrez des messages dans le chat : ceux-ci seront reliés à tous les autres clients connectés.

# Guide technique / architecture
Cette partie a pour but de vous présenter le fonctionnement interne du serveur et du client. Nous vous recommandons de la lire avant d'essayer de lire les codes sources.  
  
Le plateau de jeu est tout le temps le même, il est codé en dur dans le serveur. Les positions des objectifs sont choisies au hasard parmis une liste liée aux emplacement des murs. Les positions de départ des robots sont tirées au hasard sur le plateau. Celà peut sembler répétitif, mais en réalité, il y a plusieurs milliards de possibilités différentes.  
  

### Serveur

Le serveur est séparé en deux parties : d'un coté la gestion du jeu (fonction `game`), et de l'autre, la gestion des connexions et des messages des clients (boucle infinie acceptant les connexions et lançant une fonction `client` pour chaque connexion). Ces deux parties sont reliées par la fonction `run` et un objet (sous forme de structure) `hub`.  
Chaque client est représenté par une structure `connection` qui contient la socket, le nom du client, le score du client, et un canal sur lequel les messages seront envoyés depuis la fonction de jeu vers le client.
Le `hub` contient 5 champs : une table de hashage répertoriant les clients, un canal `register` par lequel les clients s'ajoutent à la hashmap de clients, un canal `unregister` par lequel ils s'en suppriment, un canal `action` par lequel les clients interagissent avec le serveur, et pour finir un canal `broadcast` sur lequel la fonction de jeu envoie les messages devant être relayés à tous les clients.  
La fonction de jeu (`game`) gère le jeu, et écoute sur le canal `action` du hub sur lequel les clients envoient des messages pour effectuer leurs actions. Le canal `action` est géré de manière non-concurrente (un seul message à la fois sur le cannal), donc il ne peut pas y avoir d'incohérences dans l'état du jeu lié à des accès concurrents à des variables internes (par exemple si deux enchères de la même valeur arrivent en même temps, celle qui passera en premier sur le canal `action` sera validée, et l'autre sera refusée.).  
  
Les durées de chaque phase de jeu sont définies par les variables `reflexion_time`, `bid_time` et `res_time`.  
  
###### Le fonctionnement en détail du serveur :
La fonction d'interface entre le client et le serveur est lancée dès le début en tant que goroutine (fonction concurrente) par l'instruction `go h.run()`. Celle-ci lance la fonction de jeu en tant que goroutine également : `go game(h, session_chan, start_game)`. 2 canaux lui sont passé en argument : l'un par lequel `run` notifie `game` des clients qui se connectent (car la partie ne commence qu'une fois que 2 joueurs sont connectés), et l'autre par lequel `game` envoie à `run` le plateau de jeu une fois que celui-ci a été généré (afin que cette dernière envoie le plateau aux clients qui se connectent après le début de la partie).  
La connection des clients est gérée par la fonction `main` : à chaque nouvelle connection, une goroutine est crée (`go client(conn, h)`) pour gérer le client. Après une petite vérification du message envoyé par le client (qui doit être CONNEXION/user/), le client est ajouté à la liste de clients du `hub`. Ensuite, une goroutine anonyme est lancée pour géré l'envoie des message au client (il s'agit donc de transmettre au client les messages arrivant sur le cannal `send` du client). Et la fonction `client` se charge alors de recevoir les messages du client : il s'agit dans la plupart des cas, il s'agit de relayer le message à la fonction `game` (via le cannal `action` du `hub`).
La fonction de jeu (`game`) attend d'avoir été notifié de la connection de deux clients via le cannal `start` puis met le jeu en route. Cette fonction ne s'arrête qu'une fois que moins de deux joueurs sont connectés. Une partie est composé de 10 manches. Le jeu est donc composé d'un ensemble de parties. Les scores sont remis à 0 après chaque partie.
<br>

### Client
Le client est construit autour du framework Electron. Une vue web `Renderer process` se charge d'afficher le fichier HTML correspondant à l'interface de jeu. Le client se connecte tout d'abord au serveur, s'authentifie avec le nom d'utilisateur, puis écoute sur le canal du serveur.
A chaque donnée reçue sur le canal, le signal est immédiatement traité en callback, puis l'information est transmise à la vue web à l'aide d'un signal `WebContents.send`, qui actualise alors la page en conséquence, affichant l'information envoyé par le serveur. La vue web, quant à elle, se charge de faire l'interface entre l'utilisateur et le processus principal `Main process`. A chaque donnée entrée par l'utilisateur, le `Renderer process` se charge, à l'aide d'un signal `ipcRenderer`, d'envoyer l'information correspondante au `Main process`, qui l'envoie alors au serveur.

L'information provenant des signaux du serveur est constamment traitée en priorité. Ainsi, lorsque le serveur annonce la fin des enchères, si un utilisateur veut transmettre une enchère, le programme ne l'y autorise pas, même si cela a été fait quasiment en même temps.
Le score des différents participant est actualisé dès que le serveur l'envoie, ainsi que le plateau et la position des pions. Le compte à rebours est interne au serveur, et n'est pas communiqué aux joueurs.
  
# Fonctionnalités
Les fonctionnalités implémentés sont celles demandées dans l'énoncée. La seule extension est un chat.  


  
# Conclusion
L'utilisation de langages de haut niveau nous a permis de ne pas réinventer la roue avec les différents sockets TCP. En effet, là où un langage de plus bas niveau comme C nous force à tout réécrire, un simple appel à une librairie du langage nous permet de nous connecter en TCP directement du client au serveur. De plus, la gestion du paralélisme est également facilité. Le langage Go permet ainsi de faciliter le modèle de concurrence, puisqu'un appel à l'appel principal `go func` permet de lancer un nouveau thread, qui ensuite est géré par l'ordonanceur de Go. Le développeur n'a pas à travailler sur les différents états des threads, qui sont gérés par Go. Enfin, l'utilisation d'un langage web permet de travailler avec les technologies du web (HTML/CSS), permettant la construction et la prototypage rapide d'interfaces utilisateurs.
