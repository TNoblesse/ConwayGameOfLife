#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef enum Cell Cell;// Enumération permettant de faciliter les futurs calculs, vu que les futurs valeurs des cases ne peuvent etre que 0 ou 1
enum Cell
{
    VIVANTE=1, MORTE=0
};

int** JeuDeLaVie(int l,int L)//Initialise une matrice de taille Longueur*Largeur, toutes ses cases seront initialisées a 0.
    {int i,j,k;int** tab=(int**)malloc(l*sizeof(int*));
        for (i=0;i<l;i++)
            {
            tab[i]=(int*)malloc(L*sizeof(int));
            }
        for (j=0;j<l;j++)
        {
            for (k=0;k<L;k++)
            {
                tab[j][k]=MORTE;
            }
        }

        return tab;
    }


int Modulol(int i,int l) /*Permet d'éviter d'avoir des coordonnées négatives et de donner les coordonnées des cases de l'autre coté du tableau
par exemple, une case située dans la première colonne a, en plus de ses voisins sur la meme colonne, une partie de ses voisins dans la 2eme colonne, et une autre dans la dernière colonne*/
{
    return ((l + (i)) % l);
}

int ModuloL(int i,int L)
{
    return ((L + (i)) % L);
}

int getNbrVoisinsVivants(int** tab,int i,int j,int l,int L)//Additionne les cases voisinantes de la case en entrée.
    {
        return tab[Modulol(i-1,l)][ModuloL(j-1,L)] + tab[Modulol(i-1,l)][ModuloL(j,L)]
           + tab[Modulol(i-1,l)][ModuloL(j+1,L)] + tab[Modulol(i,l)][ModuloL(j-1,L)]
           + tab[Modulol(i,l)][ModuloL(j+1,L)] + tab[Modulol(i+1,l)][ModuloL(j-1,L)]
           + tab[Modulol(i+1,l)][ModuloL(j,L)] + tab[Modulol(i+1,l)][ModuloL(j+1,L)];
    }

int seraVivante(int** tab,int a,int b,int l,int L)//Retourne l'état futur de la cellule.
    {
        if (tab[a][b]==MORTE)
        {
            if (getNbrVoisinsVivants(tab,a,b,l,L) == 3)
                {return VIVANTE;}
            else
                {return MORTE;}
        }
        else
        {
            if (getNbrVoisinsVivants(tab,a,b,l,L) == 2)
                {return VIVANTE;}
            else if (getNbrVoisinsVivants(tab,a,b,l,L) == 3)
                {return VIVANTE;}
            else
                {return MORTE;}
        }
    }

int** GenerationSuivante(int **tab,int l,int L)//Remplace les cellules dont l'état va changer a la génération suivante.
{int a,b;int** tab2=JeuDeLaVie(l,L);/*Matrice vide qui va recevoir les valeurs de la génération suivante.
On déclare une nouvelle matrice pour éviter le conflit des cellules vivantes de l'ancien tableau avec les autres*/
    for (a=0;a<l;a++)
    {
        for (b=0;b<L;b++)
            {
                (tab2[a][b])=(seraVivante(tab,a,b,l,L));
            }
    }
    return tab2;
}

void afficher(int** tab,int l,int L)//Affiche la matrice.
{int i,j,C;
    for (i=0;i<l;i++)
    {
        for(j=0;j<L;j++)
            {
                C=tab[i][j];
                printf("%d\t",C);
            }
        printf("\n");
    }
}

void sauvegarder(int** tab,int l,int L)
{FILE *fichier=NULL;int i,j;
    fichier=fopen("JeuDeLaVie.txt","w");
    if(fichier == NULL){
      printf("Impossible d'ouvrir le fichier");
      exit(1);
    }
    for(i=0;i<l;i++)
    {
        for(j=0;j<L;j++)
            {
                fprintf(fichier,"%d\t",tab[i][j]);
            }
        fputs("\n",fichier);
    }
    fclose(fichier);
}

int nbcolonnes(FILE* fichier)
{int nbcolonnes=0;char chaine[100] ={0};
    fichier=fopen("JeuDeLaVie.txt","r");
    if (fichier != NULL)//Calcul du nombre de colonnes de la matrice qui est initialement inconnu
    {
        while (fgets(chaine, 100, fichier) != NULL) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
        {
            nbcolonnes++;
        }
    }
    fclose(fichier);
    return nbcolonnes;
}

int nblignes(FILE* fichier)
{int nblignes=0;
    fichier=fopen("JeuDeLaVie.txt","r");
    if (fichier!=NULL)//Calcul du nombre de lignes de la matrice
    {
        while (fgetc(fichier)!='\n')
        {
            nblignes++;
        }
    }
    nblignes=nblignes/2;
    return nblignes;
    fclose(fichier);
}

int** charger(FILE* fichier)
{int i,j;int L=nblignes(fichier),l=nbcolonnes(fichier);int** tab=NULL;
    fichier=fopen("JeuDeLaVie.txt","r");
    rewind(fichier);
    tab=JeuDeLaVie(l,L);
    if (fichier != NULL)//Remplissage de la matrice avec les valeurs du fichier
    {
        for(i=0;i<l;i++)
        {
            for(j=0;j<L;j++)
            {
                fscanf(fichier,"%d",&(tab[i][j]));
                printf("%d\t",tab[i][j]);
            }
            printf("\n");
        }
    }
    fclose(fichier);
    return tab;
}
