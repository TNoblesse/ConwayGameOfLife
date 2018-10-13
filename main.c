#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "Fonctions.h"


int main()
{int a,b,c,d,i=1,k,e,l=0,L=0,m,n,nbiterations;int** tab=NULL;FILE* fichier=NULL;
    printf("********************Bienvenue au Jeu De La Vie********************\n\n ");
    printf("\nAppuyez sur 1 pour charger la configuration pr�c�dante, et 0 pour cr�er un nouveau tableau.\n");
    scanf("%d",&n);
    do{
        switch (n)
    {
    case 1:
        {
            tab=charger(fichier);
            l=nbcolonnes(fichier);
            L=nblignes(fichier);
        }
        break;
    case 0:
        {
            printf("Donner la longueur du tableau\n");
            scanf("%d",&l);
            printf("Donner sa largeur\n");
            scanf("%d",&L);
            tab=JeuDeLaVie(l,L);
        }
        break;
    default:
        {
                printf("Vous avez choisi une valeur diff�rente de 0 et 1, Ressayer !");
                scanf("%d",&n);
        }
        break;
    }
    }while(n!=0 && n!=1);

    printf("La longueur du tableau est actuellement �gale a %d et sa largeur a %d\n\n",l,L);
    do{//Boucle permettant de ranimer des cellules dans un tableau dans une it�ration durant le jeu de la vie
        c=1;d=1;
        while (c!=0) //Boucle permettant de ranimer des cellules de notre choix, c'est avec la matrice a la sortie de la boucle qu'on va lancer le jeu de la vie
        {
            printf("Donner une coordonn�e de cellule a ranimer ou tuer.\n");//Choisir les cellules a faire passer de l'�tat morte a vivante
            scanf("%d\n%d",&a,&b);
            while ((a<0) || (b<0) || (a>=l) || (b>=L))
            {
                printf("\nErreur (variable n�gative ou d�passant la taille du tableau)\n");
                scanf("%d\n%d",&a,&b);
            }
            if (tab[a][b]==VIVANTE) {tab[a][b]=MORTE;afficher(tab,l,L);}
            else {tab[a][b]=VIVANTE;afficher(tab,l,L);}
            printf("\nAppuyez sur 0 pour lancer le jeu de la vie, 1 pour continuer a ranimer des cellules \n");
            scanf("%d",&c);
            while (c!=0 && c!=1)
                {
                    printf("Vous avez choisi une valeur diff�rente de 0 et 1, Ressayer ! ");
                    printf("\nAppuyez sur 0 pour lancer le jeu de la vie, 1 pour continuer a ranimer ou tuer des cellules.\n");
                    scanf("%d",&c);
                }
        }
        printf("Appuyez sur 1 pour lancer le jeu it�ration par it�ration et 2 pour lancer n it�rations de votre choix d'un coup \n");
        scanf("%d",&m);
        do{
            switch (m)
        {
        case 1:
            {
                while (d!=0)//Jeu de la vie it�ration par it�ration
                    {
                        tab=GenerationSuivante(tab,l,L);
                        printf("\n\n************************** Generation %d **************************\n\n",i);
                        afficher(tab,l,L);
                        sauvegarder(tab,l,L);
                        i++;
                        printf("\nAppuyez sur 1 pour acc�der a l'it�ration suivante et 0 pour sortir du jeu. \n");
                        scanf("%d",&d);
                        while ((d!=0) && (d!=1))
                            {
                                printf("Vous avez choisi une valeur diff�rente de 0 et 1, Ressayer ! ");
                                printf("\n Appuyez sur 1 pour acc�der a l'it�ration suivante et 0 pour sortir du jeu. \n");
                                scanf("%d",&d);
                            }
                        system("cls");//Effacer la derni�re matrice de la console, facilitant la lisibilit� dans la console
                    }
            }
            break;
        case 2:
            {
                printf("\nDonnez le nombre d'it�rations voulu.\n");
                scanf("%d",&nbiterations);
                while (nbiterations<=0)
                {
                    printf("Vous avez choisi une valeur n�gative ou nulle, Ressayer ! ");
                    scanf("%d",&nbiterations);
                }
                for (k=1;k<=nbiterations;k++)
                {
                    printf("\n\n************************** Generation %d **************************\n\n",k);
                    tab=GenerationSuivante(tab,l,L);
                    afficher(tab,l,L);
                }
                sauvegarder(tab,l,L);
            }
            break;
        default:
            {
                printf("Vous avez choisi une valeur diff�rente de 1 et 2, Ressayer !");
                scanf("%d",&m);
            }
            break;
        }
        }while (m!=1 && m!=2);
        printf("\nVoulez-vous ranimer ou tuer d'autres cellules? (1: Oui, 0: Quitter le programme)\n");
        scanf("%d",&e);
        while (e!=0 && e!=1)
            {
                printf("Vous avez choisi une valeur diff�rente de 0 et 1, Ressayer ! ");
                printf("\nVoulez-vous ranimer ou tuer d'autres cellules? (1: Oui, 0: Quitter le programme) \n");
                scanf("%d",&e);
            }
        if (e==0) exit(1);
       }while(e==1);

    return 0;
    }
