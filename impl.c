#include "header.h"

// Ajouter une nouvelle carte au sommet de la pile ou la case (push)
void push(Carte* carte  , Case** stack){
    Case* pile ;
    pile = (Case*)malloc(sizeof(Case)) ;
    pile->data = carte ;
    pile->next = *stack ;
    *stack = pile ;
}

// retourner le sommet d'une case (peek)
Carte* peek(Case* stack){
    if (stack != NULL)
        return stack->data   ;
    return ;
}

// Supprimer le sommet d'une case (pop)
void pop(Case** stack){
    if (*stack == NULL)
        return ;
    Case* help ;
    help = *stack ;
    *stack = (*stack)->next ;
    free(help) ;
}

void melangerCartes(Carte** cartes, int nombreDeCartes) {
    for (int i = nombreDeCartes - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        // Échange les cartes[i] et cartes[j]
        Carte* temp = cartes[i];
        cartes[i] = cartes[j];
        cartes[j] = temp;
    }
}

void initialiser() {

    // Crée un tableau dynamique de 52 cartes
    Carte** jeuDeCartes = (Carte**)malloc(52 * sizeof(Carte*));

    // Initialise les cartes avec les types et couleurs spécifiés
    int index = 0;

    const char* types[] = {"Coeur", "Carreau", "Trefle", "Pique"};

    const char* couleurs[] = {"Rouge", "Noir"};

    for (int type = 0; type < 2; type++) {

        for (int nombre = 1; nombre <= 13; nombre++) {
            jeuDeCartes[index] = (Carte*)malloc(sizeof(Carte));
            jeuDeCartes[index]->nombre = nombre;
            jeuDeCartes[index]->type = types[type];
            jeuDeCartes[index]->couleur = couleurs[0];
            index++;
            }
    }

    for (int type = 2; type < 4; type++) {

        for (int nombre = 1; nombre <= 13; nombre++) {

            jeuDeCartes[index] = (Carte*)malloc(sizeof(Carte));
            jeuDeCartes[index]->nombre = nombre;
            jeuDeCartes[index]->type = types[type];
            jeuDeCartes[index]->couleur = couleurs[1];
            index++;
            }
    }

    // Mélange les cartes de manière aléatoire

    melangerCartes(jeuDeCartes,52);

    // Distribue les cartes dans la zone 1 selon la règle spécifiée

    index = 0;
    for (int i = 0; i < 8; i++) {
        zone_1[i] = NULL ;
        for (int j = 0; j < (i < 4 ? 7 : 6); j++) {
            Case* nouvellecarte ;
            nouvellecarte = (Case*)malloc(sizeof(Case));
            nouvellecarte->data = jeuDeCartes[index++];
            nouvellecarte->next = zone_1[i];
            zone_1[i] = nouvellecarte ;
        }
    }
    for (int i = 0; i < 4; i++) {
        zone_2[i] = NULL ;
        zone_3[i] = NULL ;
    }
}

int determinerTypeZone(Case** zone) {
    // Détermine le type de zone en fonction du tableau donné
    if (zone >= zone_1 && zone < zone_1 + 8) {
        return 1;  // Zone 1
    } else if (zone >= zone_2 && zone < zone_2 + 4) {
        return 2;  // Zone 2
    } else if (zone >= zone_3 && zone < zone_3 + 4) {
        return 3;  // Zone 3
    }
    return 0;  // Type de zone inconnu
}

bool deplacerCartes(Case** source, Case** destination){

    // Vérifie si la source est vide
    if (*source == NULL) {
        printf("La cellule de depart est vide.\n");
        return false;  // Échec du déplacement
    }

    // Détermine le type de la source et de la destination
    int typeSource = determinerTypeZone(source);
    int typeDestination = determinerTypeZone(destination);

    // Vérifie si le déplacement est autorisé
    switch (typeSource) {
        case 1: // Zone 1
            switch (typeDestination) {
                case 1: // Zone 1 vers Zone 1
                    if((*source != NULL && *destination == NULL) || (*source != NULL && (*source)->data->couleur != (*destination)->data->couleur && (*source)->data->nombre == (*destination)->data->nombre - 1 )){
                        Carte* karta ;
                        karta = (Carte*)malloc(sizeof(Carte));
                        karta = peek(*source) ;
                        push(karta,destination) ;
                        pop(source);
                        printf("Mouvement autorise.\n");
                        return true;  // Succès du déplacement
                    }
                    else{
                        printf("Mouvement non autorise.\n");
                        return false; // Échec du déplacement

                    }
                case 2: // Zone 1 vers Zone 2
                    if(*source != NULL && *destination == NULL){
                        Carte* karta ;
                        karta = (Carte*)malloc(sizeof(Carte));
                        karta = peek(*source) ;
                        push(karta,destination) ;
                        pop(source);
                        printf("Mouvement autorise.\n");
                        return true;  // Succès du déplacement
                    }
                    else{
                        printf("Mouvement non autorise.\n");
                        return false; // Échec du déplacement
                    }
                case 3: // Zone 1 vers Zone 3
                    if(((*source)->data->nombre == 1 && *destination == NULL) || (*source != NULL && (*destination) != NULL && (*source)->data->type == (*destination)->data->type && (*source)->data->nombre == (*destination)->data->nombre + 1 )){
                        Carte* karta ;
                        karta = (Carte*)malloc(sizeof(Carte));
                        karta = peek(*source) ;
                        push(karta,destination) ;
                        pop(source);
                        printf("Mouvement autorise.\n");
                        return true;  // Succès du déplacement
                    }
                    else{
                        printf("Mouvement non autorise.\n");
                        return false; // Échec du déplacement
                    }

                default:
                    printf("Mouvement non autorise.\n");
                    return false; // Échec du déplacement
            }
        case 2: // Zone 2
            switch (typeDestination) {
                case 1: // Zone 2 vers Zone 1
                    if((*source != NULL && *destination == NULL) || (*source != NULL && (*source)->data->couleur != (*destination)->data->couleur && (*source)->data->nombre == (*destination)->data->nombre - 1 )){
                        Carte* karta ;
                        karta = (Carte*)malloc(sizeof(Carte));
                        karta = peek(*source) ;
                        push(karta,destination) ;
                        *source = NULL ;
                        printf("Mouvement autorise.\n");
                        return true;  // Succès du déplacement
                    }
                    else{
                        printf("Mouvement non autorise.\n");
                        return false; // Échec du déplacement
                    }

                case 2: // Zone 2 vers Zone 2
                    if(*source != NULL && *destination == NULL){
                        Carte* karta ;
                        karta = (Carte*)malloc(sizeof(Carte));
                        karta = peek(*source) ;
                        push(karta,destination) ;
                        *source = NULL ;
                        printf("Mouvement autorise.\n");
                        return true;  // Succès du déplacement
                    }
                    else{
                        printf("Mouvement non autorise.\n");
                        return false; // Échec du déplacement
                    }

                case 3: // Zone 2 vers Zone 3
                    if(((*source)->data->nombre == 1 && *destination == NULL) || (*source != NULL && (*destination) != NULL && (*source)->data->type == (*destination)->data->type && (*source)->data->nombre == (*destination)->data->nombre + 1 )){
                        Carte* karta ;
                        karta = (Carte*)malloc(sizeof(Carte));
                        karta = peek(*source) ;
                        push(karta,destination) ;
                        *source = NULL ;
                        printf("Mouvement autorise.\n");
                        return true;  // Succès du déplacement
                    }
                    else{
                        printf("Mouvement non autorise.\n");
                        return false; // Échec du déplacement
                    }
                default:
                    printf("Mouvement non autorise.\n");
                    return false; // Échec du déplacement
            }
        case 3: // Zone 3 -> *
            printf("Mouvement non autorise.\n");
            return false; // Échec du déplacement

        default:
            printf("Type de zone inconnu.\n");
            return false; // Échec du déplacement
    }
}

int est_SerieDeCartes_validee(Case** source, Case** destination, int until ){
    Case* one ;
    one = (Case*)malloc(sizeof(Case));
    one = *source ;
    Case* two ;
    two = (Case*)malloc(sizeof(Case));
    two = (*source)->next ;
    for(int i = 1 ; i < until ; i++){
        if(one->data->couleur != two->data->couleur && one->data->nombre == two->data->nombre - 1){
            one = two ;
            two = two->next ;
        }
        else
            return 0 ;
    }
    if (one->data->couleur != (*destination)->data->couleur && one->data->nombre == (*destination)->data->nombre - 1)
        return 1 ;
    return 0 ;

}

bool deplacerSerieDeCartes(Case** source, Case** destination, int until){

    // Vérifie si la source est vide
    if (*source == NULL) {
        printf("La cellule de depart est vide.\n");
        return false;  // Échec du déplacement
    }

    // ce type de deplacement peut etre fait juste de la zone 1 vers la zone 1
    int typeSource = determinerTypeZone(source);
    int typeDestination = determinerTypeZone(destination);
    if (typeSource != 1 || typeDestination != 1){
        printf("Mouvement non autorise , ce type de deplacement peut etre fait juste de la zone 1 vers la zone 1 \n");
        return false;  // Échec du déplacement
    }

    // On recupere le nombre des cases disponibles dans la zone 2 dans la variable entiere dispo
    int dispo = 0 ;
    for (int i = 0 ; i < 4 ; i++){
        if (zone_2[i] == NULL)
            dispo++ ;
    }

    //condition sur la taille de la serie
    if(until > dispo + 1){
        printf("Mouvement non autorise.condition sur la taille de la serie\n");
        return false;  // Échec du déplacement
    }

    //tester si la forme est d'une série
    if (est_SerieDeCartes_validee(source,destination,until) == 1){
        // pour  empiler dans le bon sens on crée une nouvelle case fictive qui joue une étape intermediaire
        Case* fictivecase ;
        fictivecase = (Case*)malloc(sizeof(Case)) ;
        //on empile l'inverse de la série sur la case fictivecase
        for(int i = 0 ; i < until ; i++ ){
            push(peek(*source) , &fictivecase) ;
            pop(source);
        }
        //on empile la série sur la case destination
        for(int i = 0 ; i < until ; i++ ){
            push(peek(fictivecase) , destination) ;
            pop(&fictivecase);
        }
        free(fictivecase);
        printf("Mouvement autorise.\n");
        return true;  // Succès du déplacement
    }
    printf("Mouvement non autorise.\n");
    return false;  // Échec du déplacement
}

void afficherPlateau() {

    printf("---- Plateau de jeu ----\n");

    // Afficher Zone 1
    printf("--------Zone 1:--------\n");
    for (int i = 0; i < 8; i++) {

        Case* currentCase = zone_1[i];
        printf("Case %d (%p):",i+1,&zone_1[i]);
        while (currentCase != NULL) {
            printf(" [%d %s %s]", currentCase->data->nombre, currentCase->data->type, currentCase->data->couleur);
            currentCase = currentCase->next;
        }
        printf("\n");
    }

    // Afficher Zone 2
    printf("--------Zone 2:--------\n");
    for (int i = 0; i < 4; i++) {

        Case* currentCase = zone_2[i];
        printf("Case %d (%p):",i+1,&zone_2[i]);    //
        if (currentCase != NULL) {
            printf(" [%d %s %s]", currentCase->data->nombre, currentCase->data->type, currentCase->data->couleur);
        }
        printf("\n");
    }

    // Afficher Zone 3
    printf("--------Zone 3:--------\n");
    for (int i = 0; i < 4; i++) {

        Case* currentCase = zone_3[i];
        printf("Case %d (%p):",i+1,&zone_3[i]);
        while (currentCase != NULL) {
            printf(" [%d %s %s]", currentCase->data->nombre, currentCase->data->type, currentCase->data->couleur);
            currentCase = currentCase->next ;
        }
        printf("\n");
    }

    printf("---- Fin du plateau ----\n");
}

bool partieGagnee(Case* T[8] , Case* Q[4]){
    int k = 0 ;
    int i,j ;
    for (i = 0 , j = 4 ; i < 4 , j  < 8 ; i++ , j++){
        if(T[i] == NULL && Q[i] == NULL && T[j] == NULL)
            k++ ;
    }
    if (k == 4)
        return true ;
    return false ;
}

