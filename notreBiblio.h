#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <conio.h>




#ifndef DEF_DICO
#define DEF_DICO






typedef struct listeMot
{
    int id_mot;
    char mot[10];
    struct listeMot *suivant;
}listeMot;




listeMot *creerListeMot(int id_mot,char *mot);

listeMot *insererNvMot(listeMot *liste, listeMot *m);


int nombreAleatoire(int nbreMots);// retourne  0 <= nombre aleatoire <= nbreMots


void choisirMot(char *motChoisi, int tailleMot); // choisi un mot dans le dico al�atoirement et le met dans motChoisi


void choisirMotOrdinateur(char *motOrdi,char *mot_h, listeMot *listeMotsDejaEntres, int tailleMot); //choisi un mot dans le dico al�atoirement et le met dans motOrdi


int motExiste(char *mot); //verifierLettresV l'existence d'un mot dans le dico


void colorer(int couleurDuTexte,int couleurDeFond); // fonction d'affichage de couleurs



void verifierLettresV(char *motChoisi,char *motEntre, int *trouve, int taille);




void dessinerGrille(char **tab, int **trouve, int ligne, int colonne, int ligne_h);



void affecternbLettresV(char *motChoisi, char *motDebut, int *trouve, int nbLettreV); //affecter nbLettreV au mot avant de commencer le jeu




void controlerMot(int contient_chiffre, int tailleMot, char *tab, listeMot *L);



int verifierContientChiffre(char *tab, int tailleMot);







void rendreMotMinuscule(char *mot); // convertir tous les lettres en minuscule


void rendreMotMajuscule(char *mot); // convertir tous les lettres en majuscule


void Menu();


void nouvellePartie(); //debut du jeu



void unJoueur();

void jouerAvecOrdinateur();

void deuxJoueurs();





















#endif
