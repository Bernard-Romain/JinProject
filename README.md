# Contexte
Ce jeu a été réalisé par Romain BERNARD et Pablo BROCHARD dans le cadre du cours de Développement C++ proposé par Télécom SudParis et encadré par Michel SIMATIC et Loïc JOLLY. L'objectif était de rassembler dans un projet les apprentissages du cours.

# Présentation du jeu
Le jeu s'inspire du titre The Binding of Isaac. Il reprend globalement le système de déplacement, de combat et d'exploration. Le but du jeu est de parcourir toutes les salles et d'éliminer tout les ennemis. Lorsque tout les ennemis d'une salle sont éliminés, l'accès aux autres salles est débloqué.

# Contrôles
Aller en haut :     Z
Aller à gauche :    Q
Aller en bas :      S
Aller à droite :    D

Cliquer pour tirer un projectile vers l'emplacement du curseur.

# Combat
Si vous touchez un ennemi avec un projectile, il meurt. Si vous vous faites toucher par un ennemi, vous mourez et la partie est perdue.

# Ennemis
Il existe plusieurs types d'ennemis qui ont des comportements différents :
- FatEnemy :    Il ne se déplace pas
- AngryEnemy :  Il suit le joueur
- DumbEnemy :   Il suit un parcours prédéfini
- CrazyEnemy :  Il se déplace de manière pseudo aléatoire, en allant globalement vers le joueur