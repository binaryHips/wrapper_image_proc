

Wrapper C++ pour faciliter le traitement d'images.


Utilisation/

./process.sh <nom_du_script>

L'image d'entrée et de sortie sont définies dans le script.

Des exemples de script sont disponibles dans ./scripts, ainsi qu'une documentation sommaire à la fin de ce fichier.


Fonctionnement/

la fonction FRAGMENT est un bout de code C++ et contient la logique de notre traitement d'image.
(on peut argumenter que le nom FRAGMENT, inspiré des langages de shaders est moins adapté que PIXEL par exemple,
car on regarde des pixels directement et pas une projection de géométrie 3D sur un pixel d'une caméra virtuelle. )

Quand process.sh est appelé, il exécuter ./wrapper, qui est un parseur écrit en yacc/flex.

Le parseur va générer un fichier source C++. Il effectue ces transformations

- récupère les chemins d'accès IN et OUT afin de les importer (en utilisant les fonctions d'image_ppm.h)
- récupère le bloc de code dans FRAGMENT et le met dans une fonction C++ fragment()
- remplace les appels à IN(u, v) dans FRAGMENT par une fonction c++ get_pixel_safe(u, v) (définie dans image_ppm.h)
- ajoute en fin de fichier une fonction main similaire aux programmes qu'on utilise en cours, qui appelle la fonction fragment() pour chaque pixel.

Pour observer le fichier C++ généré, il suffit de commenter la ligne "rm temp.cpp"



Scripts/

Un script doit avoir une entrée IN et une sortie OUT, ainsi qu'une fonction FRAGMENT{}.

Les variables et fonctions suivantes sont utilisables dans le bloc de code FRAGMENT.

Structures:

    color{int .r, int .g, int .b}: structure de couleur. Utilisée aussi pour stocker les autres formats entiers (auquel cas les champs .r, .g et .b ne correspondent pas à leur contenu!)

    hsv{float .h, float .s, float .v}: structure de couleur. Utilisée pour stocker le hsv. format flottant. /!\ Pas du HSL https://en.wikipedia.org/wiki/HSL_and_HSV


Variables:

    int U, V: variables contenant les coordonnées du pixel actuellement traité. L'image ppm est manipulée comme une image pgm (taille "pas triplée", gestion des couleurs grâce au type color).

    color COLOR: variable d'écriture (typiquement) initialisée à noir. après la fin de l'exécution de la fonction, COLOR est assignée dans l'image de sortie au pixel traité.

Fonctions:

    color IN(int u, int v): récupère la couleur du pixel de l'entrée aux coordonnées u, v. En cas de dépassement de la taille de l'image, répète en miroir.

    int lum(color c): retourne la luminance de c.

    color c(int r, int g, int b): crée une nouvelle couleur avec les composantes données.

    color add(color a , color b): additionne deux couleurs par composante. Autorise les dépassements!

    color sub(color a , color b): soustrait deux couleurs par composante. Autorise les dépassements!

    color scale(color c , float s): multiplie les composantes de c par le flottant s. Autorise les dépassements!


    color to_YCrCb(color source): conversion RGB -> YCrCb. attention, le résultat est une couleur (donc on y accède toujours avec .r, .g, .b)

    color from_YCrCb(color source): conversion YCrCb -> RGB.

    hsv to_HSV(color source): conversion RGB -> HSV. Le résultat est de type hsv (les champs sont des flottants dans [0, 1])

    color from_HSV(hsv source): conversion HSV -> RGB


    


Les fonctions sont implémentées dans images_ppm.h (IN() est get_pixel_safe()).


Futur/

Quelques fonctionnalités que j'aimerais ajouter si j'en ai l'occasion:


- possibilité de déclarer d'autres images sans chemins dans le prélude, afin d'avoir des buffers en plus (utile pour itérer un flou par exemple.)

- possibilité d'ajouter en prélude des fonctions c++

- possibilité de faire plusieurs passes en définissant plusieurs fonctions fragment. (utile pour les flous)

- possibilité d'exporter en png

- possibilité de déclarer plusieurs entrées (et possiblement sorties). IN deviendrait un nom de variable et IN() son accesseur.

- ajout d'options de la commande process.sh pour pouvoir garder le c++ sans devoir modifier le script bash.