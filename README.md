# Calculateur-voisinages

Cet utilitaire permet de calculer très simplement l'ordre de voisinage de tous les couples dans un semis de points.

"Calculateur de voisinage" est un utilitaire qui a été développé en 2011 au sein du laboratoire ESO-Rennes (UMR 6590 CNRS à l'Université Rennes 2) par Isabelle Brémond (Ingénieur d'étude en informatique) en réponse à un besoin exprimé dans le cadre d'un programme financé par l'ANR METAL (cf. supra). Il nécessite en entrée un tableau de contingence, préalablement formaté en colonnes (par exemple, à l'aide de l'utilitaire "Convertisseur de matrices", présenté ci-dessus).

Le tableau de contingence indique la liste des couples de points qui sont voisins d'ordre 1. Ce tableau doit être composé d'au moins deux colonnes (la troisième étant facultative). La première colonne contient l'identifiant de la première extrémité d'un couple de points voisins d'ordre 1, la deuxième colonne l'identifiant de l'autre extrémité. Le tableau de contingence peut être obtenu à partir d'un graphe de contiguïté. Les graphes de contiguïté relient deux à deux les points voisins d'ordre 1. Ce genre de graphe peut facilement être créé dans un SIG (Système d'Information Géographique).

"Calculateur de voisinage" est un logiciel gratuit fonctionnant sous Windows (Windows 7, 8 et 10). Vous pouvez le télécharger et l'utiliser librement. Nous vous demandons simplement de citer « Calculateur de voisinage - Laboratoire ESO-Rennes - UMR 6590 CNRS - Université Rennes 2 » si vous publiez des travaux dans lesquels vous l'utilisez. 

Le programme a été développé avec l'EDI Embarcadero C++ builder Community Edition, téléchargeable sur la page :
https://www.embarcadero.com/fr/products/cbuilder/starter<br>
L'installateur (voisinages_setup.exe) a été créé au moyen du logiciel libre Inno Setup http://www.jrsoftware.org/isinfo.php<br>
L'algorithme implémenté a été créé par Edsger Dijkstra https://fr.wikipedia.org/wiki/Algorithme_de_Dijkstra 

