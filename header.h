#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef struct {
    int nombre;
    const char* type;
    const char* couleur;
}Carte;

typedef struct Case {
    Carte* data ;
    struct Case* next ;
}Case ;

void push(Carte* carte  , Case** stack) ;
Carte* peek(Case* stack) ;
void pop(Case** stack) ;
void melangerCartes(Carte** cartes, int nombreDeCartes) ;
void initialiser();
int determinerTypeZone(Case** zone) ;
bool deplacerCartes(Case** source, Case** destination) ;
int est_SerieDeCartes_validee(Case** source, Case** destination, int until ) ;
bool deplacerSerieDeCartes(Case** source, Case** destination, int until);
void afficherPlateau() ;
bool partieGagnee(Case* T[8] , Case* Q[4]) ;

extern Case* zone_1[8];
extern Case* zone_2[4];
extern Case* zone_3[4];






