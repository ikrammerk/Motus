
#include "notreBiblio.h"
#include "sauvgarde_charge.h"





listeMot *creerListeMot(int id_mot,char *mot)
{

    listeMot *m = malloc(sizeof(listeMot));
    m->id_mot=id_mot;
    strcpy(m->mot,mot);
    m->suivant=NULL;

    return m;
}




listeMot *insererNvMot(listeMot *liste, listeMot *m)
{
    if(liste==NULL)
        return m;

    listeMot *p = liste;
    while(p->suivant != NULL)
        p=p->suivant;
    p->suivant=m;

    return liste;
}







void choisirMotOrdinateur(char *motOrdi,char *mot_h,listeMot *mot_deja_entrer, int tailleMot)
{
    listeMot *liste=NULL;
    listeMot *L1=NULL;
    listeMot *L2=NULL;

    char file[10]=""; //pour y stocker le nom du fichier utilise.

    switch(tailleMot)
    {
    case 6 :
        strcpy(file,"dico6.txt");
        break;
    case 7 :
        strcpy(file,"dico7.txt");
        break;
    case 8 :
        strcpy(file,"dico8.txt");
        break;
    case 9 :
        strcpy(file,"dico9.txt");
        break;
    case 10 :
        strcpy(file,"dico10.txt");
        break;
    default :
        printf("erreurPc");
    }





    char mot[11]=""; // aide lors la lecture dans le fichier
    FILE *dico=NULL; // pointeur vers le dico
    int nbreMots=0;  // nombre de mots dans le dico
    int numMotChoisi=0; // numero de la ligne du mot choisi

    dico = fopen(file,"r"); //ouvrir le fichier en mode de lecture seule

    if(dico==NULL) // l'ouverture de fichier a echoue
    {
        printf("\tImpossible d'ouvrir le fichier");
        fclose(dico);
        return;
    }

    //pour controler la jouabilite de l'ordinateur
    /*---------------------------------------------------------------------*/
    int id=0;
    int cpt_h=0; //calcul le nombre des lettres visibles
    for(int i=0; i<tailleMot; i++)
        if(mot_h[i] != ' ')
            cpt_h++;

    while(fscanf(dico,"%s",mot) != EOF)
    {
        int cpt_temp=0;
        for(int i=0; i<tailleMot; i++)
            if(mot[i]==mot_h[i])
                cpt_temp++;

        if(cpt_temp==cpt_h)
        {
            listeMot *m=creerListeMot(id,mot);
            liste= insererNvMot(liste,m);
            id++;
            nbreMots++;
        }
    }

    /*---------------------------------------------------------------------*/

    do
    {
        numMotChoisi=nombreAleatoire(nbreMots);// 0 <= numMotChoisi <= nombre de mots de la liste

        L1=liste;
        while(L1 != NULL && L1->id_mot!=numMotChoisi)
            L1=L1->suivant;
        L1->mot[tailleMot]='\0';

        L2=mot_deja_entrer;
        while(L2 != NULL && strcmp(L2->mot,L1->mot)!=0)
            L2=L2->suivant;


    }
    while(L2 != NULL);

    L1->mot[tailleMot]='\0';
    strcpy(motOrdi,L1->mot);




    fclose(dico);
    return; // tout est bien passe
}




void affecternbLettresV(char *motChoisi, char *motDebut, int *trouve, int nbLettreV) //affecter nbLettreV au mot avant de commencer le jeu
{
    trouve[0]=1;
    motDebut[0]=motChoisi[0];
    for(int k=1; k<nbLettreV; k++)
    {
        int num=nombreAleatoire(strlen(motChoisi));
        while(trouve[num] == 1)
            num=nombreAleatoire(strlen(motChoisi));

        trouve[num]=1;

    }

    for(int j=1; j<strlen(motChoisi); j++)
        if(trouve[j] == 0)
            motDebut[j]=' ';
        else
            motDebut[j]=motChoisi[j];

}




void choisirMot(char *motChoisi, int tailleMot) //choisi le mot secret aleatoiremment dans le dico
{

    char file[10]=""; //pour y stocker le nom du fichier utilise




    switch(tailleMot)
    {
    case 6 :
        strcpy(file,"dico6.txt");
        break;
    case 7 :
        strcpy(file,"dico7.txt");
        break;
    case 8 :
        strcpy(file,"dico8.txt");
        break;
    case 9 :
        strcpy(file,"dico9.txt");
        break;
    case 10 :
        strcpy(file,"dico10.txt");
        break;
    default :
        printf("erreur_choisir_mot\n");
    }



    char mot[11]=""; // aide lors la lecture dans le fichier
    FILE *dico=NULL; // pointeur vers le dico
    int nbreMots=0;  // nombre de mots dans le dico
    int numMotChoisi=0; // numero de la ligne du mot choisi

    dico = fopen(file,"r"); //ouvrir le fichier en mode de lecture seule

    if(dico==NULL) // l'ouverture de fichier a echoue
    {
        printf("\tImpossible d'ouvrir le fichier");
        fclose(dico);
        return;
    }


    while(fscanf(dico,"%s",mot) != EOF)
        nbreMots++;//calcul le nombre de mots dans le dico

    numMotChoisi=nombreAleatoire(nbreMots);// 0 <= numMotChoisi <= nombre de mots du dico


    rewind(dico); // curseur a la position 0 du fichier

    while(numMotChoisi > 0) //pour stationner le curseur devant la ligne du mot secret
    {
        int c = fgetc(dico);
        if(c == '\n')
            numMotChoisi--;
    }

    fscanf(dico,"%s",motChoisi);
    motChoisi[tailleMot]='\0';
    //rendreMotMajuscule(motChoisi);

    fclose(dico);
    return; // tout est bien passe
}






int motExiste(char *mot)
{
    char file[10]=""; //pour y stocker le nom du fichier utilise

    // ouvrir le dico selon la taille du mot
    switch(strlen(mot))
    {
    case 6 :
        strcpy(file,"dico6.txt");
        break;
    case 7 :
        strcpy(file,"dico7.txt");
        break;
    case 8 :
        strcpy(file,"dico8.txt");
        break;
    case 9 :
        strcpy(file,"dico9.txt");
        break;
    case 10 :
        strcpy(file,"dico10.txt");
        break;
    default :
        return 0;//break;
    }



    char temp[10]="";
    FILE *dico=NULL; // pointeur vers le dico
    dico = fopen(file,"r"); //ouvrir le fichier en mode lecture seule


    while(fscanf(dico,"%s", temp) != EOF) //lire d'apres le fichier tant qu'on est pas arrive a sa fin
    {
        if(strcmp(mot,temp)==0) // si mot et temp sont identiques
        {
            fclose(dico);
            return 1; // le mot existe dans le dico
        }

    }

    fclose(dico);
    return 0; // le mot n'existe pas dans le dico
}












void verifierLettresV(char *motChoisi,char *motSaisi, int *trouve, int taille)
{
    int i,j;
    char *temp= malloc(taille*sizeof(char));
    motChoisi[taille]='\0';
    motSaisi[taille]='\0';
    strcpy(temp,motChoisi);

    /* Chercher Les Lettres Communes Bien  Placees */
    for(i=0; i<taille; i++)
    {
        if(motSaisi[i]== temp[i])
        {
            trouve[i]=1;
            temp[i]='#';
        }
    }

    /* Chercher Les Lettres Communes Mal  Placees */
    for(i=0; i<taille; i++)
    {
        for(j=0; j<taille; j++)
            if(motSaisi[i]==temp[j] && trouve[i]!=1)
            {
                trouve[i]=2;
                temp[j]='@';
                break;
            }
    }
    free(temp);
}






void dessinerGrille(char **tab, int **trouve, int ligne, int colonne, int ligne_h)
{
    system("cls");
    colorer(15,0);

    printf("\n\n\n");
    for(int i=0; i<colonne; i++)
        printf("+-----");

    printf("+\n");

    for(int i=0; i<ligne; i++) //affichage des lignes
    {
        if(i != ligne_h) // si le mot existe dans le dico
        {

            for(int j=0; j<colonne; j++)//affichage des colonnes
            {
                if(trouve[i][j]==1)
                {
                    colorer(15,0);
                    printf("|");
                    colorer(10,0);// on colorie la lettre par la couleur vert
                    printf("  %c  ",tab[i][j]);
                    colorer(15,0);
                }
                else
                {
                    if(trouve[i][j]==2)
                    {
                        colorer(15,0);
                        printf("|");
                        colorer(14,0);//on colorie la lettre par la couleur jaune
                        printf("  %c  ",tab[i][j]);
                        colorer(15,0);//revenir au couleur par defaut

                    }
                    else
                    {
                        colorer(15,0);
                        printf("|  %c  ",tab[i][j]);
                    }
                }


            }
        }
        else //le mot n'existe pas dans le dico
        {
            if(i == ligne_h)
            {
                colorer(3,0);
                for(int j=0; j<colonne; j++)//affichage des colonnes
                {
                    printf("|  %c  ",tab[i][j]);
                }
                colorer(7,0);
            }
            else
            {
                colorer(15,0);
                for(int j=0; j<colonne; j++)
                    printf("|  %c  ",tab[i][j]); //affichage normal sans couleur
            }

        }

        colorer(15,0);
        printf("|\n");
        for(int i=0; i<colonne; i++)
            printf("+-----");

        printf("+\n");
    }
    colorer(6,0);
    printf(" Pour quitter la partie appuyez sur '&', voir statistiques '@'.\n\n");
    colorer(7,0);
}








int nombreAleatoire(int nbreMots) // 0 <= genere un nombre aleatoires <= nbreMots
{
    srand(time(NULL)); // initialiser le generateur du temps a 0
    return (rand()%nbreMots);

}
















int verifierContientChiffre(char *tab, int tailleMot)
{
    int contient_chiffre=1; // 1: contient au moins un chiffre et 0: contient aucun chiffre

    int temp_cpt=0;
    for(int z=0; z<strlen(tab) && strlen(tab)<=tailleMot; z++)
        if(tab[z]>='A' && tab[z]<='Z')
            temp_cpt++;

    if(temp_cpt == strlen(tab))//strlen(tab) && strlen(tab)<=tailleMot) //ne contient que des lettres
        contient_chiffre=0;

    return contient_chiffre;
}








void controlerMot(int contient_chiffre, int tailleMot, char *tab, listeMot *L)
{
    if(strlen(tab) > tailleMot)
    {
        colorer(12,0);
        printf("\tMot invalide, il a depasse %d lettres.\n",tailleMot);
        colorer(7,0);
    }
    if(strlen(tab) < tailleMot && contient_chiffre == 0)
    {
        colorer(12,0);
        printf("\tMot invalide, la longueur est inferieur a %d lettres.\n",tailleMot);
        colorer(7,0);
    }

    if(L != NULL)
    {
        colorer(12,0);
        printf("\tMot invalide, deja existe.\n");
        colorer(7,0);
    }
    if(contient_chiffre == 1 && strlen(tab) <= tailleMot)
    {
        colorer(12,0);
        printf("\tMot invalide, il contient des chiffres ou des caracteres speciaux.\n");
        colorer(7,0);
    }
}









void nouvellePartie() //debut du jeu
{
    colorer(15,0);
    printf("\n\n +================< CHOIX DU MODE DU JEU >================+\n");
    printf(" |                                                        |\n");
    printf(" |            1) un seul joueur.                          |\n");
    printf(" |            2) un joueur contre l'ordinateur.           |\n");
    printf(" |            3) un joueur contre un autre joueur.        |\n");
    printf(" |            4) Retour vers le menu principal.           |\n");
    printf(" |                                                        |\n");
    printf(" +========================================================+\n");
    printf("\n   Entrer votre choix : ");
    int mode=0;
    fflush(stdin);
    scanf("%d",&mode);
    colorer(7,0);

    while(mode <=0 || mode >=5) // en cas de choix invalide
    {
        colorer(12,0);
        printf("      Choix invalide !\n");
        colorer(7,0);
        colorer(15,0);
        printf("\n   Entrer a nouveau votre choix : ");
        fflush(stdin);
        scanf("%d",&mode);
        colorer(7,0);
    }
    system("cls"); //vider l'ecran
    switch(mode)
    {
    case 1:
        unJoueur();
        break;

    case 2:
        jouerAvecOrdinateur();
        break;
    case 3:
        deuxJoueurs();
        break;
    case 4:
        Menu();
        break;

    default:
        nouvellePartie();
        break;
    }
}




void chargerPartie()
{
     char  PseudoCharge[30]=" ";
    couleur(14,0);
    printf("\n\n\n  ----> Vous avez choisi de charger une partie !\n\n");
    printf("\t----> Donnez votre Pseudo ou & pour quitter:  ");
        couleur(15,0);

    scanf("%s",PseudoCharge);
    couleur(15,0);
    if(PseudoCharge[0]=='&')
    {
        system("cls");
        Menu();
    }
    afficher_Partie_Sauv(PseudoCharge);
    lire_Partie_Existe(PseudoCharge);
}












void Aide()
{
    char file[10]="Aide.txt"; //pour y stocker le nom du fichier utilise

    char mot[100]=""; // aide lors la lecture dans le fichier
    FILE *help=NULL; // pointeur vers le dico

    help = fopen(file,"r"); //ouvrir le fichier en mode de lecture seule

    if(help==NULL) // l'ouverture de fichier a echoue
    {
        printf("\tImpossible d'ouvrir le fichier");
        fclose(help);
    }


    while(fgets(mot,sizeof(mot),help) != NULL)
    {
        colorer(15,0);
        printf(" %s",mot);
    }
    colorer(7,0);


    fclose(help);



    char retour=' ';
    colorer(6,0);
    printf("\n          Pour revenir au menu principal, appuyez sur '&'. ");
    colorer(7,0);
    fflush(stdin);
    colorer(15,0);
    scanf("%c",&retour);
    colorer(7,0);

    while(retour != '&') /*en cas d'erreur de frappe*/
    {
        colorer(12,0);
        printf("    Choix invalide !\n");
        colorer(7,0);

        colorer(15,0);
        printf("\n   Veuillez appuyez sur '&' : ");
        fflush(stdin);
        scanf("%c",&retour);
        colorer(7,0);
    }
    Menu();
}




void Menu()
{
    system("cls");
    int choix=0;
    colorer(15,0);
    printf("\n\n +=====================< MENU PRINCIPAL >=====================+\n");
    printf(" |                                                            |\n");
    printf(" |                         M O T U S                          |\n");
    printf(" |============================================================|\n");
    printf(" |                                                            |\n");
    printf(" |                     1) Nouvelle partie.                    |\n");
    printf(" |                     2) Charger partie.                     |\n");
    printf(" |                     3) Aide.                               |\n");
    printf(" |                     4) Quitter le jeu.                     |\n");
    printf(" |                                                            |\n");
    printf(" +============================================================+\n\n");

    printf("    Entrez votre choix : ");
    fflush(stdin);
    scanf("%d",&choix);
    colorer(7,0);


    while(choix <=0 || choix >=5)
    {
        colorer(12,0);
        printf("      Choix invalide !\n");
        colorer(7,0);
        colorer(15,0);
        printf("\n   Entrez a nouveau votre choix : ");
        fflush(stdin);
        scanf("%d",&choix);
        colorer(7,0);
    }

    system("cls"); //vider l'ecran

    switch(choix)//selon le choix de l'utilisateur
    {
    case 1:
        nouvellePartie();
        break;

    case 2:
        chargerPartie();
        break;

    case 3:
        Aide();
        break;

    case 4:
        exit(0);

    default:
        Menu(); //reafficher le menu
        break;
    }

}




















void rendreMotMinuscule(char *mot) // convertir tous les lettres en minuscule
{
    for(int z=0; z<strlen(mot); z++)
    {
        if(mot[z]>='A' && mot[z]<='Z')
            mot[z]=mot[z]-'A'+'a';
    }
}




void rendreMotMajuscule(char *mot) // convertir tous les lettres en majuscule
{
    for(int z=0; z<strlen(mot); z++)
    {
        if(mot[z]>='a' && mot[z]<='z')
            mot[z]=mot[z]-'a'+'A';
    }

}



void colorer(int couleurDuTexte,int couleurDeFond) // fonction d'affichage de couleurs
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}

float jouerTour(int mode,char **tab, int **trouve, int id,char *motChoisi,int tailleMot,int i,int nbtenta,Joueur * monjoueur, listeMot * listeMotsDejaEntres,int *numero_h, char *lettre_h, int *score, int *nbPartieG){
	listeMot *L=NULL;
	float time = 0;
    int cpt_tenta=(mode==0)?nbtenta:nbtenta/2;
	do
	{
	    /*reinitialisation de ligne de trouve*/
	    for(int x=0; x<tailleMot; x++)
	        trouve[i][x]=0;
	
	  	if(i%2!=0 && mode==1)
		{
			 printf("\n--> Le tour d'ordinateur.\n ");
            choisirMotOrdinateur(tab[i],lettre_h,listeMotsDejaEntres,tailleMot);
            colorer(15,0);
            printf("    Le mot propose est : '%s', appuyez sur entrer", tab[i]);
            colorer(7,0);
            getch();
		}
		else
		{
			colorer(15,0);
			printf("  Il vous reste %d tentatives, tapez votre mot : ",(cpt_tenta));
			
			fflush(stdin); // vider la memoire du clavier avant la saisie
			scanf("%s",tab[i]);
			colorer(7,0);
			
			if(tab[i][0]=='&')
			    break;
			if(tab[i][0]=='@')
			{
			    afficherStatistiques(monjoueur->pseudo);
			
			    printf("\n  Il vous reste %d tentatives, tapez votre mot : ",(cpt_tenta));
			    fflush(stdin); // vider la memoire du clavier avant la saisie
			    scanf("%s",tab[i]);
			}
			
			rendreMotMajuscule(tab[i]);
			
			L=listeMotsDejaEntres;
			while(L != NULL && strcmp(L->mot,tab[i])!=0)
			    L=L->suivant;
			
			// 1: contient au moins un chiffre et 0: contient aucun chiffre
			int contient_chiffre=verifierContientChiffre(tab[i],tailleMot);
			
			
			/*en cas d'erreur*/
			while((contient_chiffre == 1 && strlen(tab[i]) <= tailleMot) || strlen(tab[i]) > tailleMot || strlen(tab[i]) < tailleMot || L != NULL)
			{
			    controlerMot(contient_chiffre,tailleMot,tab[i],L);
			
			    colorer(15,0);
			    printf("  Veuillez retapez votre mot : ");
			    fflush(stdin); // vider la memoire du clavier avant la saisie
			    scanf("%s",tab[i]);
			    colorer(7,0);
			    if(tab[i][0]=='&')
			        break;
			
			
			    rendreMotMajuscule(tab[i]);
			
			    // 1: contient au moins un chiffre et 0: contient aucun chiffre
			    contient_chiffre=verifierContientChiffre(tab[i],tailleMot);
			
			    L=listeMotsDejaEntres;
			    while(L != NULL && strcmp(L->mot,tab[i])!=0)
			        L=L->suivant;
			   
			}// fin de la controle du mot entre par l'utilisateur
			cpt_tenta--;
			if(tab[i][0]=='&')
	        		break;
			
		}
	    /*----------------------------------------------------*/
	    //on remplit la liste par les mots qui existent dans la grille
	
	    listeMot *mot_grille=creerListeMot(id,tab[i]);
	    listeMotsDejaEntres= insererNvMot(listeMotsDejaEntres,mot_grille);
	    id++;
	    /*----------------------------------------------------*/
	    verifierLettresV(motChoisi,tab[i],trouve[i],tailleMot);
	
	
	
	
	
	    /*--------------------------------------------*/
	    if(i<nbtenta-1)
	    {
	        for(int x=0; x<tailleMot; x++)
	            if(trouve[i][x]==1)
	            {
	                numero_h[x]=1;
	                lettre_h[x]=tab[i][x];
	            }
	
	
	        for(int x=0; x<tailleMot; x++)
	        {
	            if(numero_h[x]==1)
	            {
	                trouve[i+1][x]=1;
	                tab[i+1][x]=lettre_h[x];
	            }
	            if(numero_h[x]==0)
	                tab[i+1][x]='.';
	        }
	
	    }
	    /*--------------------------------------------*/
	
	    //calcul du nombre de lettres bien placees
	    int cpt=0;
	    for(int z=0; z<tailleMot; z++)
	        if(trouve[i][z]==1)
	            cpt++;
	
	
	
	
	    if(cpt == tailleMot ) //s'il a trouve le mot
	    {
	        if(i<nbtenta-1)
	            for(int x=0; x<tailleMot; x++)
	                tab[i+1][x]=0;
	        dessinerGrille(tab, trouve,nbtenta,tailleMot,(i+1));
	        if(mode==1 & i%2!=0)
	        {
	        	printf("\n Perdu, l'ordinateur a pu deviner le mot secret.\n\n");
                time = clock()*0.001;
			}
			else
			{
				colorer(10,0);
		        printf("\n Bravo '%s', vous avez trouver le mot.\n",monjoueur->pseudo);
		        colorer(7,0);
		        /****************************/
		        time = clock()*0.001;
		        
		        *nbPartieG++;
		        *score+=5;
			}
			
	        /**************************/
	        break; // quitter la partie
	    }
	    else
	        dessinerGrille(tab, trouve,nbtenta,tailleMot,(i+1));
	
	
	    i++; // on incremente a l'essai suivant
	}
	while(i<nbtenta);
	return time;
}


void unJoueur()
{

    int Mode=1;
    listeMot *listeMotsDejaEntres=NULL;
    listeMot *L=NULL;
    int id=0; //id du mot_deja_enter

    int nbtenta=6;
    int tailleMot;
    int nbLettreV=1;
    int i=0; // pour les tentatives
    /**************************************/
    int numero,enregistrer;
    char niveau[MAXCHAINE]; /* le niveau  */
    strcpy(niveau,"niveau-");
    niveau[strlen(niveau)+1]='\0';
    char numPartie[3];
    char nomJ[30];
    int nbPartieG=0;
    float time;
    int score=0;
    /****************************************/
    colorer(15,0);
    printf("\n Entrez votre pseudo : ");
    scanf("%s",nomJ);
    Joueur*monjoueur;
    monjoueur=creerJoueur(nomJ);
    creerDossier(nomJ);
    afficher_niveau();
    printf("\n\t Donner votre choix : ");
    scanf("%d",&numero);
    switch(numero)
    {
    case 1 :
        tailleMot=6;
        break;

    case 2 :
        tailleMot=7;
        break;

    case 3 :
        tailleMot=8;
        break;

    case 4 :
        tailleMot=9;
        break;

    case 5 :
        tailleMot=10;
        break;

    default :
        tailleMot=6;
        break;

    }
    couleur(15,0);
    printf("\n");

    itoa(numero,numPartie,10);
    strcat(niveau,numPartie);
    strcat(niveau,".txt");
    niveau[strlen(niveau)+1]='\0';
    strcpy(monjoueur->niveau,niveau);
    system("cls");


    /*******************************************************/
    char motChoisi[10]=""; //pour y stocker le mot secret
    choisirMot(motChoisi,tailleMot);
    motChoisi[tailleMot]='\0';


    system("cls");

    /*printf("\nLe mot secret est : %s",motChoisi); // c'est a nous,pour afficher le motChoisi
    getch();*/


    char **tab=(char**) calloc(nbtenta,sizeof(char*));
    for(int x=0; x<nbtenta; x++)
        tab[x]=(char*) calloc(tailleMot,sizeof(char));

    //-->initialisation du grille
    for(int x=0; x<nbtenta; x++)
        for(int y=0; y<tailleMot; y++)
            tab[x][y]=' ';


    int **trouve=(int**) calloc(nbtenta,sizeof(int*));
    for(int x=0; x<nbtenta; x++)
        trouve[x]=(int*) calloc(tailleMot,sizeof(int));


    int *numero_h = calloc(tailleMot,sizeof(int));
    char *lettre_h = calloc(tailleMot,sizeof(char));

    tab[i][tailleMot]='\0';


    affecternbLettresV(motChoisi, tab[i],trouve[i], nbLettreV); //affecter nbLettreV au mot avant de commencer le jeu

    tab[i][tailleMot]='\0';

    strcpy(lettre_h,tab[i]);
    for(int x=0; x<tailleMot; x++)
        if(lettre_h[x] != ' ')
            numero_h[x]=1;
        else
            tab[i][x] = '.';

    //affichage de la grille initiale
    dessinerGrille(tab, trouve,nbtenta,tailleMot,i);

	time=jouerTour(0,tab, trouve, id, motChoisi, tailleMot, i, nbtenta, monjoueur, listeMotsDejaEntres, numero_h, lettre_h, &score, &nbPartieG);

     //compteur des tentatives du joueur
  // tant qu'on est pas depasser le nbtenta


    if(i== nbtenta) // si on a depasser le nbtenta
    {
        printf("\n Perdu, le mot cherche etait bien : %s.\n",motChoisi);
        time = clock()*0.001;
    }

    if(i< nbtenta && tab[i][0]=='&')
        printf("\n\n  vous avez quitter la partie.\n");

    /***********************************************************/

    monjoueur->duree=time;
    monjoueur->nbPartieG=nbPartieG;
    monjoueur->score=score;
    printf("|=>\t Vous souhaitez enregistrer votre partie\n");
    printf("|=>\t Tapez 1 si oui ou 0 si non\n");
    printf("|=>\t\t\t");
    scanf("%d",&enregistrer);
    monjoueur->enregistrer=enregistrer;

    sauvegarder_Partie(monjoueur,tab,nbtenta,tailleMot,motChoisi,i,Mode);


    /***************************************************************************/


    /* liberer les espaces memoires alloues*/
    for(int i=0; i<nbtenta; i++)
        free(trouve[i]);
    free(trouve);

    for(int i=0; i<nbtenta; i++)
        free(tab[i]);
    free(tab);


    free(numero_h);
    free(lettre_h);



    //------------> FIN DU JEU <-------------

    printf("    Que Voulez-vous faire ?\n");
    printf("   ---------------------------------------\n");
    printf("    1) Recommencer une nouvelle partie.\n");
    printf("    2) Changer le mode du jeu.\n");
    printf("    3) Retour vers le menu principal.\n");
    printf("    4) Quitter le jeu.\n");
    int decision=0; //pour y stocker la decision du joueur
    colorer(15,0);
    printf("      Entrer votre choix : ");
    fflush(stdin);
    scanf("%d",&decision);
    colorer(7,0);


    //Pour une autre partie

    while(decision<=0 || decision >=5) // en cas de choix invalide
    {
        colorer(12,0);
        printf("\tChoix invalide.\n");
        colorer(7,0);

        colorer(15,0);
        printf("      Entrez a nouveau votre choix : ");
        fflush(stdin);
        scanf("%d",&decision);
        colorer(7,0);
    }

    if(decision ==1)
    {
        system("cls"); // clean screen
        unJoueur(); // appel recursive de la fonction du debut du jeu
    }
    if(decision ==2)
    {
        system("cls"); // clean screen
        nouvellePartie(); // appel recursive de la fonction du debut du jeu
    }
    if(decision ==3)
    {
        system("cls"); // clean screen
        Menu(); //appel recursive de la fonction qui affiche le menu
    }
    if(decision ==4)
    {
        exit(0);
    }

}













///////////////////////////////////////////////////////////////////////////////////////////////
void jouerAvecOrdinateur()//l'utilisateur joue contre l'ordinateur
{
    int Mode=2;

    int nbtenta=6;
    int tailleMot;
    int nbLettreV=1;
    int i=0; // pour les tentatives

    /**********************************************/
    int numero,enregistrer;
    char niveau[MAXCHAINE]; /* le niveau  */
    strcpy(niveau,"niveau-");
    niveau[strlen(niveau)+1]='\0';
    char numPartie[3];
    char nomJ[30];
    int nbPartieG=0;
    float time;
    int score=0;

    /****************************************/


    /*********************************************************************/

    printf("\n Entrez votre pseudo : ");
    scanf("%s",nomJ);
    Joueur*monjoueur;
    monjoueur=creerJoueur(nomJ);
    creerDossier(nomJ);
    afficher_niveau();
    printf("\n\t Donner votre choix : ");
    scanf("%d",&numero);
    switch(numero)
    {
    case 1 :
        tailleMot=6;
        break;

    case 2 :
        tailleMot=7;
        break;

    case 3 :
        tailleMot=8;
        break;

    case 4 :
        tailleMot=9;
        break;

    case 5 :
        tailleMot=10;
        break;

    default :
        tailleMot=6;
        break;

    }
    couleur(15,0);
    printf("\n");

    itoa(numero,numPartie,10);
    strcat(niveau,numPartie);
    strcat(niveau,".txt");
    niveau[strlen(niveau)+1]='\0';
    strcpy(monjoueur->niveau,niveau);
    system("cls");
    /***********************************************************************/



    listeMot *listeMotsDejaEntres=NULL;
    listeMot *L=NULL;
    int id=0; //id du mot_deja_enter


    char motChoisi[10]=""; //pour y stocker le mot secret
    choisirMot(motChoisi,tailleMot);
    motChoisi[tailleMot]='\0';


    system("cls");

    /*printf("\nLe mot secret est : %s",motChoisi); // c'est a nous,pour afficher le motChoisi
    getch();*/



    //-->declaration de la grille
    char **tab=(char**) calloc(nbtenta,sizeof(char*));
    for(int x=0; x<nbtenta; x++)
        tab[x]=(char*) calloc(tailleMot,sizeof(char));

    //-->initialisation de la grille
    for(int x=0; x<nbtenta; x++)
        for(int y=0; y<tailleMot; y++)
            tab[x][y]=' ';

    /*-------------------------*/
    for(int x=0; x<nbtenta; x++)
        tab[x][tailleMot]='\0';
    /*-------------------------*/

    /*ici ou se trouve le probleme avec le dico 8*/
    printf("\nverif tailleMot : %d",tailleMot);// il ne s'affiche pas ce printf

    int **trouve=(int**) calloc(nbtenta,sizeof(int*));
    for(int x=0; x<nbtenta; x++)
        trouve[x]=(int*) calloc(tailleMot,sizeof(int));


    int *numero_h = calloc(tailleMot,sizeof(int));
    char *lettre_h = calloc(tailleMot,sizeof(char));

    tab[i][tailleMot]='\0';



    affecternbLettresV(motChoisi, tab[i],trouve[i], nbLettreV); //affecter nbLettreV au mot avant de commencer le jeu

    tab[i][tailleMot]='\0';

    strcpy(lettre_h,tab[i]);
    for(int x=0; x<tailleMot; x++)
        if(lettre_h[x] != ' ')
            numero_h[x]=1;
        else
            tab[i][x] = '.';

    //affichage de la grille initial
    dessinerGrille(tab, trouve,nbtenta,tailleMot,i);


    time = 0;
    int cpt_tenta=nbtenta/2; //compteur des tentatives du joueur
  	time=jouerTour(1,tab, trouve, id, motChoisi, tailleMot, i, nbtenta, monjoueur, listeMotsDejaEntres, numero_h, lettre_h, &score, &nbPartieG);

    if(i== nbtenta) // si on a depasser le nbtenta
   {
        printf("\n Perdu, le mot cherche etait bien : %s.\n\n",motChoisi);
        time = clock()*0.001;

    }


    if(i< nbtenta && tab[i][0]=='&')
        printf("\n\n  Vous avez quitter la partie.\n\n");

    /********************************************************************************/

    monjoueur->duree=time;
    monjoueur->nbPartieG=nbPartieG;
    monjoueur->score=score;
    printf("|=>\t Vous souhaitez enregistrer votre partie\n");
    printf("|=>\t Tapez 1 si oui ou 0 si non\n");
    printf("|=>\t\t\t");
    scanf("%d",&enregistrer);
    monjoueur->enregistrer=enregistrer;

    sauvegarder_Partie(monjoueur,tab,nbtenta,tailleMot,motChoisi,i,Mode);



    /*************************************************************************************/

    /* liberer les espaces memoires alloues*/
    for(int i=0; i<nbtenta; i++)
        free(trouve[i]);
    free(trouve);

    for(int i=0; i<nbtenta; i++)
        free(tab[i]);
    free(tab);


    free(numero_h);
    free(lettre_h);



    //------------> FIN DU JEU <-------------

    printf("    Que Voulez-vous faire ?\n");
    printf("    --------------------------------------\n");
    printf("    1) Recommencer une nouvelle partie.\n");
    printf("    2) Changer le mode du jeu.\n");
    printf("    3) Retour vers le menu principal.\n");
    printf("    4) Quitter le jeu.\n");
    int decision=0; //pour y stocker la decision du joueur
    colorer(15,0);
    printf("      Entrer votre choix : ");
    fflush(stdin);
    scanf("%d",&decision);
    colorer(7,0);


    //Pour une autre partie

    while(decision<=0 || decision >=5) // en cas de choix invalide
    {
        colorer(12,0);
        printf("\tChoix invalide.\n");
        colorer(7,0);

        colorer(15,0);
        printf("      Entrez a nouveau votre choix : ");
        fflush(stdin);
        scanf("%d",&decision);
        colorer(7,0);
    }

    if(decision ==1)
    {
        system("cls"); // clean screen
        jouerAvecOrdinateur(); // appel recursive de la fonction du debut du jeu
    }
    if(decision ==2)
    {
        system("cls"); // clean screen
        nouvellePartie(); // appel recursive de la fonction du debut du jeu
    }
    if(decision ==3)
    {
        system("cls"); // clean screen
        Menu(); //appel recursive de la fonction qui affiche le menu
    }
    if(decision ==4)
    {
        exit(0);
    }

}








void deuxJoueurs() //l'utilisateur joue contre un autre joueur
{
    int Mode=3;
    listeMot *listeMotsDejaEntres=NULL;
    listeMot *L=NULL;
    int id=0; //id du mot_deja_enter

    int nbtenta=6;
    int tailleMot=6;
    int nbLettreV=1;
    int i=0; // pour les tentatives

    /********************************************************************/
    int numero,enregistrer;
    char niveau[MAXCHAINE]; /* le niveau  */
    strcpy(niveau,"niveau-");
    niveau[strlen(niveau)+1]='\0';
    char numPartie[3];
    char nomJ1[30];
    int nbPartieGJ1=0;
    float time;
    int scoreJ1=0;

    /****************************************/
    int scoreJ2=0;
    char nomJ2[30];
    int nbPartieGJ2=0;

    /*********************************************************************/

    printf("\n Entrez le pseudo de premier joueur : ");
    scanf("%s",nomJ1);
    printf("\n Entrez le pseudo de deuxieme joueur : ");
    scanf("%s",nomJ2);
    Joueur*monjoueur1;
    monjoueur1=creerJoueur(nomJ1);
    Joueur*monjoueur2;
    monjoueur2=creerJoueur(nomJ2);
    creerDossier(nomJ1);
    creerDossier(nomJ2);
    afficher_niveau();
    printf("\t Donner votre choix : ");
    scanf("%d",&numero);
    switch(numero)
    {
    case 1 :
        tailleMot=6;
        break;

    case 2 :
        tailleMot=7;
        break;

    case 3 :
        tailleMot=8;
        break;

    case 4 :
        tailleMot=9;
        break;

    case 5 :
        tailleMot=10;
        break;

    default :
        tailleMot=6;
        break;

    }
    couleur(15,0);
    printf("\n");

    itoa(numero,numPartie,10);
    strcat(niveau,numPartie);
    strcat(niveau,".txt");
    niveau[strlen(niveau)+1]='\0';
    strcpy(monjoueur1->niveau,niveau);
    strcpy(monjoueur2->niveau,niveau);
    system("cls");
    /***********************************************************************/


    char motChoisi[10]=""; //pour y stocker le mot secret
    choisirMot(motChoisi,tailleMot);
    motChoisi[tailleMot]='\0';


    system("cls");

    /*printf("\n Le mot secret est : %s",motChoisi); // c'est a nous,pour afficher le motChoisi
    getch();*/


    char **tab=(char**) calloc(nbtenta,sizeof(char*));
    for(int x=0; x<nbtenta; x++)
        tab[x]=(char*) calloc(tailleMot,sizeof(char));

    //-->initialisation du grille
    for(int x=0; x<nbtenta; x++)
        for(int y=0; y<tailleMot; y++)
            tab[x][y]=' ';


    int **trouve=(int**) calloc(nbtenta,sizeof(int*));
    for(int x=0; x<nbtenta; x++)
        trouve[x]=(int*) calloc(tailleMot,sizeof(int));


    int *numero_h = calloc(tailleMot,sizeof(int));
    char *lettre_h = calloc(tailleMot,sizeof(char));

    tab[i][tailleMot]='\0';


    affecternbLettresV(motChoisi, tab[i],trouve[i], nbLettreV); //affecter nbLettreV au mot avant de commencer le jeu

    tab[i][tailleMot]='\0';

    strcpy(lettre_h,tab[i]);
    for(int x=0; x<tailleMot; x++)
        if(lettre_h[x] != ' ')
            numero_h[x]=1;
        else
            tab[i][x] = '.';

    //affichage de la grille initial
    dessinerGrille(tab, trouve,nbtenta,tailleMot,i);


    time=0;
    int cpt_tenta1=nbtenta/2; //compteur des tentatives du joueur
    int cpt_tenta2=nbtenta/2;
    do
    {

        if(i%2 == 0)//si le tour du joueur
        {
            /*reeinitialisation de ligne de trouve*/
            for(int x=0; x<tailleMot; x++)
                trouve[i][x]=0;

            printf("\n --> Le tour de %s.\n",monjoueur1->pseudo);

            colorer(15,0);
            printf("  Il vous reste %d tentatives, tapez votre mot : ",cpt_tenta1);

            fflush(stdin); // vider la memoire du clavier avant la saisie
            scanf("%s",tab[i]);
            colorer(7,0);

            if(tab[i][0]=='&')
                break;
            if(tab[i][0]=='@')
            {
                afficherStatistiques(monjoueur1->pseudo);

                printf("\n  Il vous reste %d tentatives, tapez votre mot : ",(cpt_tenta1));
                fflush(stdin); // vider la memoire du clavier avant la saisie
                scanf("%s",tab[i]);
            }

            rendreMotMajuscule(tab[i]);

            L=listeMotsDejaEntres;
            while(L != NULL && strcmp(L->mot,tab[i])!=0)
                L=L->suivant;

            // 1: contient au moins un chiffre et 0: contient aucun chiffre
            int contient_chiffre=verifierContientChiffre(tab[i],tailleMot);


            /*en cas d'erreur*/
            while((contient_chiffre == 1 && strlen(tab[i]) <= tailleMot) || strlen(tab[i]) > tailleMot || strlen(tab[i]) < tailleMot || L != NULL)
            {
                controlerMot(contient_chiffre,tailleMot,tab[i],L);

                colorer(15,0);
                printf("  Veuillez retapez votre mot : ");
                fflush(stdin); // vider la memoire du clavier avant la saisie
                scanf("%s",tab[i]);
                colorer(7,0);
                if(tab[i][0]=='&')
                    break;
                rendreMotMajuscule(tab[i]);

                // 1: contient au moins un chiffre et 0: contient aucun chiffre
                contient_chiffre=verifierContientChiffre(tab[i],tailleMot);

                L=listeMotsDejaEntres;
                while(L != NULL && strcmp(L->mot,tab[i])!=0)
                    L=L->suivant;

            } // fin de la controle du mot entre par l'utilisateur

            cpt_tenta1--;

            if(tab[i][0]=='&')
                break;

            /*----------------------------------------------------*/
            //on remplit la liste par les mots qui existent dans la grille

            listeMot *mot_grille=creerListeMot(id,tab[i]);
            listeMotsDejaEntres= insererNvMot(listeMotsDejaEntres,mot_grille);
            id++;
            /*----------------------------------------------------*/
            verifierLettresV(motChoisi,tab[i],trouve[i],tailleMot);





            /*--------------------------------------------*/
            if(i<nbtenta-1)
            {
                for(int x=0; x<tailleMot; x++)
                    if(trouve[i][x]==1)
                    {
                        numero_h[x]=1;
                        lettre_h[x]=tab[i][x];
                    }


                for(int x=0; x<tailleMot; x++)
                {
                    if(numero_h[x]==1)
                    {
                        trouve[i+1][x]=1;
                        tab[i+1][x]=lettre_h[x];
                    }
                    if(numero_h[x]==0)
                        tab[i+1][x]='.';
                }

            }
            /*--------------------------------------------*/

            //calcul du nombre de lettres bien placees
            int cpt=0;
            for(int z=0; z<tailleMot; z++)
                if(trouve[i][z]==1)
                    cpt++;




            if(cpt == tailleMot ) //s'il a trouve le mot
            {
                if(i<nbtenta-1)
                    for(int x=0; x<tailleMot; x++)
                        tab[i+1][x]=0;
                dessinerGrille(tab, trouve,nbtenta,tailleMot,(i+1));
                colorer(10,0);
                printf("\n Bravo '%s', vous avez trouver le mot.\n",monjoueur1->pseudo);
                colorer(7,0);
                /*--------------------------*/
                time = clock()*0.001;
                nbPartieGJ1++;
                scoreJ1+=5;
                /*----------------------*/

                break; // quitter la partie
            }
            else
                dessinerGrille(tab, trouve,nbtenta,tailleMot,(i+1));
        }



        if(i%2 != 0)//si le tour du joueur 2
        {
            /*reeinitialisation de ligne de trouve*/
            for(int x=0; x<tailleMot; x++)
                trouve[i][x]=0;

            printf("\n --> Le tour de %s.\n",monjoueur2->pseudo);

            colorer(15,0);
            printf("  Il vous reste %d tentatives, tapez votre mot : ",cpt_tenta2);

            fflush(stdin); // vider la memoire du clavier avant la saisie
            scanf("%s",tab[i]);
            colorer(7,0);

            if(tab[i][0]=='&')
                break;

            if(tab[i][0]=='@')
            {
                afficherStatistiques(monjoueur2->pseudo);

                printf("\n  Il vous reste %d tentatives, tapez votre mot : ",(cpt_tenta2));
                fflush(stdin); // vider la memoire du clavier avant la saisie
                scanf("%s",tab[i]);
            }

            rendreMotMajuscule(tab[i]);

            L=listeMotsDejaEntres;
            while(L != NULL && strcmp(L->mot,tab[i])!=0)
                L=L->suivant;

            // 1: contient au moins un chiffre et 0: contient aucun chiffre
            int contient_chiffre=verifierContientChiffre(tab[i],tailleMot);


            /*en cas d'erreur*/
            while((contient_chiffre == 1 && strlen(tab[i]) <= tailleMot) || strlen(tab[i]) > tailleMot || strlen(tab[i]) < tailleMot || L != NULL)
            {
                controlerMot(contient_chiffre,tailleMot,tab[i],L);

                colorer(15,0);
                printf("  Veuillez retapez votre mot : ");
                fflush(stdin); // vider la memoire du clavier avant la saisie
                scanf("%s",tab[i]);
                colorer(7,0);
                if(tab[i][0]=='&')
                    break;
                rendreMotMajuscule(tab[i]);

                // 1: contient au moins un chiffre et 0: contient aucun chiffre
                contient_chiffre=verifierContientChiffre(tab[i],tailleMot);

                L=listeMotsDejaEntres;
                while(L != NULL && strcmp(L->mot,tab[i])!=0)
                    L=L->suivant;

            } // fin de la controle du mot entre par l'utilisateur

            cpt_tenta2--;

            if(tab[i][0]=='&')
                break;

            /*----------------------------------------------------*/
            //on remplit la liste par les mots qui existent dans la grille

            listeMot *mot_grille=creerListeMot(id,tab[i]);
            listeMotsDejaEntres= insererNvMot(listeMotsDejaEntres,mot_grille);
            id++;
            /*----------------------------------------------------*/
            verifierLettresV(motChoisi,tab[i],trouve[i],tailleMot);





            /*--------------------------------------------*/
            if(i<nbtenta-1)
            {
                for(int x=0; x<tailleMot; x++)
                    if(trouve[i][x]==1)
                    {
                        numero_h[x]=1;
                        lettre_h[x]=tab[i][x];
                    }


                for(int x=0; x<tailleMot; x++)
                {
                    if(numero_h[x]==1)
                    {
                        trouve[i+1][x]=1;
                        tab[i+1][x]=lettre_h[x];
                    }
                    if(numero_h[x]==0)
                        tab[i+1][x]='.';
                }

            }
            /*--------------------------------------------*/

            //calcul du nombre de lettres bien placees
            int cpt=0;
            for(int z=0; z<tailleMot; z++)
                if(trouve[i][z]==1)
                    cpt++;




            if(cpt == tailleMot ) //s'il a trouve le mot
            {
                if(i<nbtenta-1)
                    for(int x=0; x<tailleMot; x++)
                        tab[i+1][x]=0;
                dessinerGrille(tab, trouve,nbtenta,tailleMot,(i+1));
                colorer(10,0);
                printf("\n Bravo '%s', vous avez trouver le mot.\n",monjoueur2->pseudo);
                colorer(7,0);
                /*--------------------------*/
                time = clock()*0.001;
                nbPartieGJ2++;
                scoreJ2+=5;
                /*----------------------*/

                break; // quitter la partie
            }
            else
                dessinerGrille(tab, trouve,nbtenta,tailleMot,(i+1));

        }


        i++; // on incremente a l'essaye suivant
    }
    while(i<nbtenta);  // tant qu'on est pas depasser le nbtenta


    if(i== nbtenta) // si on a depasser le nbtenta
    {
        printf("\n Perdu, le mot cherche etait bien : %s.\n",motChoisi);
        time = clock()*0.001;

    }


    if(i< nbtenta && tab[i][0]=='&')
        printf("\n\n  Vous avez quitter la partie.\n");

    /*************************************************************************/

    monjoueur1->duree=time;
    monjoueur1->nbPartieG=nbPartieGJ1;
    monjoueur1->score=scoreJ1;

    monjoueur2->duree=time;
    monjoueur2->nbPartieG=nbPartieGJ2;
    monjoueur2->score=scoreJ2;

    printf("|=>\t Vous souhaitez enregistrer votre partie\n");
    printf("|=>\t Tapez 1 si oui ou 0 si non\n");
    printf("|=>\t\t\t");
    scanf("%d",&enregistrer);
    monjoueur1->enregistrer=enregistrer;
    monjoueur2->enregistrer=enregistrer;


    sauvegarder_Partie(monjoueur1,tab,nbtenta,tailleMot,motChoisi,i,Mode);
    sauvegarder_Partie(monjoueur2,tab,nbtenta,tailleMot,motChoisi,i,Mode);




    /*******************************************************/

    /* liberer les espaces memoires alloues*/
    for(int i=0; i<nbtenta; i++)
        free(trouve[i]);
    free(trouve);

    for(int i=0; i<nbtenta; i++)
        free(tab[i]);
    free(tab);


    free(numero_h);
    free(lettre_h);



    //------------> FIN DU JEU <-------------

    printf("    Que Voulez-vous faire ?\n\n");
    printf("    -----------------------------------\n");
    printf("    1) Recommencer une nouvelle partie.\n");
    printf("    2) Changer le mode du jeu.\n");
    printf("    3) Retour vers le menu principal.\n");
    printf("    4) Quitter le jeu.\n");
    int decision=0; //pour y stocker la decision du joueur
    colorer(15,0);
    printf("      Entrer votre choix : ");
    fflush(stdin);
    scanf("%d",&decision);
    colorer(7,0);


    //Pour une autre partie

    while(decision<=0 || decision >=5) // en cas de choix invalide
    {
        colorer(12,0);
        printf("\tChoix invalide.\n");
        colorer(7,0);

        colorer(15,0);
        printf("      Entrez a nouveau votre choix : ");
        fflush(stdin);
        scanf("%d",&decision);
        colorer(7,0);
    }

    if(decision ==1)
    {
        system("cls"); // clean screen
        deuxJoueurs(); // appel recursive de la fonction du debut du jeu
    }
    if(decision ==2)
    {
        system("cls"); // clean screen
        nouvellePartie(); // appel recursive de la fonction du debut du jeu
    }
    if(decision ==3)
    {
        system("cls"); // clean screen
        Menu(); //appel recursive de la fonction qui affiche le menu
    }
    if(decision ==4)
    {
        exit(0);
    }

}

































