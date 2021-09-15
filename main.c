/// Michel FLORANTIN & Quentin FRANCOIS
/// EFREI Paris : LSI 1 2021/2022
/// Programmation en C et C++
/// Projet : Jeu des allumettes

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NB_ALLUMETTES 30;

#define NAME_SIZE 50

void menu();

void showMenu();
void showRules();
void showPlayMenu();

void showWinner(char *string);

void play();

void jeuIA(char **joueurs, int mode);
void jeuHumain(char **joueurs);
void affichageAllumettes(int i);
int pick(int nb_restantes, int mode);

char** choosePlayer(int i);

int main() {
    // Affichage du menu principal
    menu();
    return 0;
}

void menu(){    // Menu principal
    int choice, repeat = 1;

    while(repeat) {
        showMenu(); // Labels du menu
        fflush(stdin);
        scanf("%d", &choice);
        switch (choice) {
            case 1: {   // Affichage du menu de jeu
                play();
                break;
            }
            case 2: {
                showRules();    // Affichage des regles du jeu
                break;
            }
            case 3: {
                repeat = 0; //  Sortie du programme
                break;
            }
            default:    // Recommence la boucle
                printf("Inconnu...\n");
        }
    }
    exit(0);
}

void play() {   // Menu du jeu
    int mode;
    int repeat = 1;
    while(repeat==1) {
        showPlayMenu(); // Labels du menu
        scanf("%d", &mode);
        switch (mode) {
            case 1: {   // Joueur contre joueur
                char **joueurs = choosePlayer(2);   // Choix de deux noms
                jeuHumain(joueurs); // Demarrage du jeu JcJ
                break;
            }
            case 2 :case 3: {   // Joueur contre IA
                char **joueurs = choosePlayer(1);   // Choix d'un nom
                jeuIA(joueurs, mode);   // Demarrage du jeu JcIA
                break;
            }
            default: {  // Retour au menu principal
                printf("\n\n************************\n\n");
                printf("Sortie du mode Jeu\n");
                printf("\n************************\n\n");
                repeat = 0;
            }
        }
    }
}

void showRules() {  // Regles du jeu
    printf("\n\n************************\n\n");
    printf("Ce jeu se joue a deux. Les joueurs sont devant 30 allumettes.\nA chaque tour, il faut en enlever 1, 2 ou 3.\nCelui qui prend la derniere allumette perd.\n");
    printf("\nJeu code par Michel FLORANTIN & Quentin FRANCOIS\n");
    printf("\n************************\n\n");
}
void showMenu() {   // Labels du menu
    printf("\t\t**********************\t\n");
    printf("\t\t* Jeu des allumettes *\t\n");
    printf("\t\t**********************\t\n\n");
    printf("\tBonjour et bienvenue dans le jeu des allumettes !\n");
    printf("\n");
    printf("Que voulez vous faire ?\n");
    printf("1 - Jouer !\n");
    printf("2 - Lire les regles...\n");
    printf("3 - Quitter :(\n> ");
}
void showPlayMenu() {   // Labels du menu de jeu
    printf("\n\n************************\n\n");
    printf("\n(re) Bienvenue dans le mode \"Jeu\"\n");
    printf("A quel mode voulez-vous jouer ?\n");
    printf("1 - Jouer contre un Humain !\n");
    printf("2 - Jouer contre un robot nul... \n");
    printf("3 - Jouer contre un robot un peu intelligent\n");
    printf("4 - Retour au menu\n> ");
}

void showWinner(char *string) { // Affichage du gagnant avec recuperation de son nom
    printf("Le gagnant est %s, bien joue !\nA bientot !\n\n", string);
}

char** choosePlayer(int nb) {   // Choix des noms des joueurs
    char **joueurs;
    joueurs = calloc(nb, sizeof(char));
    printf("\n\n************************\n\n");
    printf("\nSaisissez le nom des joueurs :\n");
    for(int i = 0; i <nb; i++) {
        joueurs[i] = calloc(NAME_SIZE, sizeof(char));   // Remplissage du tableau de noms avec des noms
        printf("> Joueur %d: ", i+1);
        fflush(stdin);
        scanf("%s", joueurs[i]);    // Entree de l'utilisateur
    }
    printf("\n\n************************\n\n");
    return joueurs;
}

void jeuHumain(char **joueurs) {    // JcJ
    int nb_restantes = NB_ALLUMETTES;
    const int MAX_ALLUMETTES = NB_ALLUMETTES;
    int nb_choisi = 0;
    int current = 0;
    int true = 1;
    while (true) { // Boucle qui s'arrete a l'instruction break / Tour d'un joueur
        affichageAllumettes(nb_restantes);  // Affichage special des allumettes
        printf("\tIl reste %d allumette(s).\n", nb_restantes);
        printf("Au tour de : %s\n", joueurs[current]);
        printf("Combien prenez vous d'allumettes ?\n> ");

        fflush(stdin);
        scanf("%d", &nb_choisi); // Saisie du nombre d'allumette a prendre
        if (!(nb_choisi >= 1 && nb_choisi <= 3)) {  // Si le nombre d'allumette n'est pas compris entre 1 et 3, on recommence
            printf("Erreur, vous devez choisir un nombre entre 1 et 3.\n\n");
        } else if (nb_choisi > nb_restantes) {  // Si le nombre d'allumette est superieur au nombre d'allumette restante, on recommence
            printf("Erreur, vous ne pouvez pas choisir au dessus du nombre restant.\n\n");
        } else {
            nb_restantes = nb_restantes - nb_choisi;    // On retire le nombre d'allumette desire

            printf("%s prend %d allumette(s)\n\n", joueurs[current], nb_choisi);
            current = (current + 1) % 2; // Changement du tour
            if (nb_restantes <= 0) {
                break; // On sort de la boucle qu'il y a plus d'allumette
            }
        }
    }
    showWinner(joueurs[current]); // On affiche le gagnant par rapport a la fin du tour du joueur actuel
}

void jeuIA(char **joueurs, int mode) {
    int nb_restantes = NB_ALLUMETTES;
    int nb_choisi = 0;
    int true = 1;
    int end = 0;
    int gagnant = -1;

    while(nb_restantes > 0) {   // Boucle qui s'arrete des qu'il n'y a plus d'allumette
        while(true) {   // Boucle infini qui s'arrete a l'instruction break / Tour du joueur
            affichageAllumettes(nb_restantes);  // Affichage des allumettes
            printf("\tIl reste %d allumette(s).\n", nb_restantes);
            printf("Au tour de : %s\n", joueurs[0]);
            printf("Combien prenez vous d'allumettes ?\n> ");

            fflush(stdin);
            scanf("%d", &nb_choisi);    // Saisie d'un nombre d'allumette a retirer

            if (!(nb_choisi >= 1 && nb_choisi <= 3)) {  // On recommence si c'est pas le bon nombre
                printf("Erreur, vous devez choisir un nombre entre 1 et 3.\n");
            }
            else if (nb_choisi > nb_restantes) {
                printf("Erreur, vous ne pouvez pas choisir au dessus du nombre restant.\n");
            }
            else {  // Sinon on retire le nombre d'allumete
                nb_restantes = nb_restantes - nb_choisi;
                printf("%s prend %d allumette(s).\n\n", joueurs[0], nb_choisi);
                break;
            }
        }

        if(nb_restantes <= 0) { // On teste s'il n'y a plus d'allumete, et si c'est le cas, le joueur gagne
            gagnant = 0;
            break;
        }

        // Tour de l'ordinateur
        affichageAllumettes(nb_restantes);
        printf("\tIl reste %d allumette(s).\n", nb_restantes);
        printf("Au tour de : l'Ordinateur\n");
        srand(time(NULL));  // Randomiseur
        nb_choisi = pick(nb_restantes, mode);   // Choix du nombre d'allumete par rapport a la difficulte de l'ordinateur
        nb_restantes = nb_restantes - nb_choisi;
        printf("L'Ordinateur prend %d allumette(s).\n\n", nb_choisi);

        if(nb_restantes <= 0) { // S'il n'y a plus d'allumette a la fin de son tour, l'ordinateur gagne
            gagnant = 1;
            break;
        }
    }

    char *ptr_gagnant;
    ptr_gagnant = (!gagnant) ? "Ordinateur" : joueurs[0];
    showWinner(ptr_gagnant);    // Affichage du gagnant
}

void affichageAllumettes(nb_restantes) {    // Affichage special des allumettes
    int nb = NB_ALLUMETTES;
    for (int i = 0; i < nb; i++) {
        if (i < nb_restantes)
            printf(" | ");
        else
            printf("   ");
    }
}

int pick(int nb_restantes, int mode) {  // Fonction pour calculer le nombre d'allumette a prendre pour l'ordinateur
    const int COUP_MAX = 3;
    if(mode == 3) { // Pour l'ordinateur difficile, ...
        for(int i = 1; i <= COUP_MAX; i++) {
            if((nb_restantes-i)%4 == 1) // ... on regarde s'il peut retirer un nombre d'allumette qui donne un nombre resultat qui est modulo 4
                return i;   // On retire le bon nombre par rapport a la condition d'au dessus
        }

    }
    // Sinon (ou pour l'ordinateur facile), on retire un nombre aléatoire entre 1 ou 3 sauf s'il reste 2 ou 1 allumette(s), dans ce cas il prend le bon nombre
    return rand()%((nb_restantes < COUP_MAX) ? nb_restantes : COUP_MAX) + 1;
}
