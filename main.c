#include "header.h"

Case* zone_1[8];
Case* zone_2[4];
Case* zone_3[4];

int main() {
    // Message de bienvenue
    printf("Bienvenue dans le jeu Freecell :\n");

    // Initialisation du générateur de nombres aléatoires
    srand((unsigned int)time(NULL));

    // Initialisation du jeu
    initialiser();

    // Affichage du plateau
    afficherPlateau();

    while (1) {
        int x;
        printf("Tapez 0 pour faire un deplacement unique ou 1 pour faire un deplacement par serie : ");
        scanf("%d", &x);

        if (x == 0) {
            Case** s;
            Case** d;
            printf("veuillez taper la zone de depart : ");
            scanf("%p", &s);
            printf("veuillez taper la zone de d'arrivee : ");
            scanf("%p", &d);
            deplacerCartes(s, d);
        }
        else if (x == 1) {
            Case** s;
            Case** d;
            int n;
            printf("veuillez taper la zone de depart : ");
            scanf("%p", &s);
            printf("veuillez taper la zone de d'arrivee : ");
            scanf("%p", &d);
            printf("veuillez taper la taille de la serie : ");
            scanf("%d", &n);
            deplacerSerieDeCartes(s,d,n);
        }

        afficherPlateau();

        if (partieGagnee(zone_1, zone_2)) {
            printf("Felicitations, vous avez gagne !\n");
            break;
        }
    }

    return 0;
}

