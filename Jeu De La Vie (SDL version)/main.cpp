#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>

#define Longueur 12
#define Largeur 12


enum Cell
{ VIVANTE=1, MORTE=0 };

int** JeuDeLaVie()
    {int i,j,k;int** tab=(int**)malloc(Longueur*sizeof(int*));
        for (i=0;i<Longueur;i++)
            {
                tab[i]=(int*)malloc(Largeur*sizeof(int));
            }
        for (j=0;j<Longueur;j++)
            {
            for (k=0;k<Largeur;k++)
                {
                tab[j][k]=MORTE;
                }
            }

        return tab;
    }


int estVivante(int** tab,int x,int y)
    {
            if (tab[x][y]==VIVANTE)
                return VIVANTE;
            else
                return MORTE;
    }



int Modulo(int i)
{
    return ((Longueur + (i)) % Longueur);
}
int getNbrVoisinsVivants(int** tab,int i,int j)
    {
        return tab[Modulo(i-1)][Modulo(j-1)] + (tab)[Modulo(i-1)][Modulo(j)]
           + (tab)[Modulo(i-1)][Modulo(j+1)] + (tab)[Modulo(i)][Modulo(j-1)]
           + (tab)[Modulo(i)][Modulo(j+1)] + (tab)[Modulo(i+1)][Modulo(j-1)]
           + (tab)[Modulo(i+1)][Modulo(j)] + (tab)[Modulo(i+1)][Modulo(j+1)];
    }

int seraVivante(int** tab,int a,int b)//Retourne l'état futur de la cellule.
    {
        if (tab[a][b]==MORTE)
        {
            if (getNbrVoisinsVivants(tab,a,b) == 3)
                {return VIVANTE;}
            else
                {return MORTE;}
        }
        else
        {
            if (getNbrVoisinsVivants(tab,a,b) == 2)
                {return VIVANTE;}
            else if (getNbrVoisinsVivants(tab,a,b) == 3)
                {return VIVANTE;}
            else
                {return MORTE;}
        }
    }

int** GenerationSuivante(int **tab)//Remplace les cellules dont l'état va changer a la génération suivante.
{int a,b;int** tab2=JeuDeLaVie();/*Matrice vide qui va recevoir les valeurs de la génération suivante.
On déclare une nouvelle matrice pour éviter le conflit des cellules vivantes de l'ancien tableau avec les autres*/
    for (a=0;a<Longueur;a++)
    {
        for (b=0;b<Largeur;b++)
            {
                (tab2[a][b])=(seraVivante(tab,a,b));
            }
    }
    return tab2;
}


int main(int argc, char *argv[])
{
    int continuer=1;int i,j,a,b;int** tab=JeuDeLaVie();
    SDL_Surface *ecran = NULL, *imageDeFond = NULL, *CaseVivant = NULL, *CaseMort = NULL;
    SDL_Rect positionFond, positionCase;

    SDL_Event event;

    positionFond.x = 0;
    positionFond.y = 0;


    SDL_Init(SDL_INIT_VIDEO);

    ecran = SDL_SetVideoMode(600, 600, 32, SDL_HWSURFACE); //Initialiser la fenêtre avec une taille de 600x600
    SDL_WM_SetCaption("Jeu De La Vie", NULL);

    imageDeFond = SDL_LoadBMP("Grille.bmp"); //Dans ce programme on a travailler avec l'image d'une grille
    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);

    CaseVivant = SDL_LoadBMP("Case.bmp");
    CaseMort = SDL_LoadBMP("CaseVivante.bmp");


while(continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT://Quitter le programme
                continuer=0;
                break;
            case SDL_MOUSEBUTTONUP:
            {
                switch (event.button.button)
                {
                case SDL_BUTTON_LEFT://Cliquer avec le bouton droit de la souris sur les cases mortes pour les ranimer
                {
                    positionCase.x = event.button.x;
                    positionCase.y = event.button.y;
                    // Ces conditions sert à determiner l'emplacement exact de la cellule à animer on etudiant l'emplacement du clic du curseur
                   if (positionCase.x<50)
                    {
                        if (positionCase.y<50)
                        {

                            positionCase.x = 0;
                            positionCase.y = 0;
                            i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
                        }
                        else if (positionCase.y<100)

                        {
                        positionCase.x = 0;
                        positionCase.y = 50;
                        i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
                        }

                        else if (positionCase.y<150)

                        {
                            positionCase.x = 0;
                            positionCase.y = 100;
                            i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
                        }

                        else if (positionCase.y<200)

                        {
                            positionCase.x = 0;
                            positionCase.y = 150;
                            i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
                        }

                        else if (positionCase.y<250)

                        {
                            positionCase.x = 0;
                            positionCase.y = 200;
                            i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
                        }
                        else if (positionCase.y<300)

                        {
                            positionCase.x = 0;
                            positionCase.y = 250;
                            i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
                        }
                        else if (positionCase.y<350)

                        {
                            positionCase.x = 0;
                            positionCase.y = 300;
                            i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
                        }
                        else if (positionCase.y<400)

                        {
                        positionCase.x = 0;
                        positionCase.y = 350;
                        i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<450)

	{
    		positionCase.x = 0;
    		positionCase.y = 400;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<500)

	{
    		positionCase.x = 0;
    		positionCase.y = 450;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<550)

	{
    		positionCase.x = 0;
    		positionCase.y = 500;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<600)

	{
    		positionCase.x = 0;
    		positionCase.y = 550;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}

}

else if (positionCase.x<100)
{
	if (positionCase.y<50)
	{
    	positionCase.x = 50;
    	positionCase.y = 0;

	i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<100)

	{
    		positionCase.x = 50;
    		positionCase.y = 50;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}

	else if (positionCase.y<150)

	{
    		positionCase.x = 50;
    		positionCase.y = 100;
		    i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}

	else if (positionCase.y<200)

	{
    		positionCase.x = 50;
    		positionCase.y = 150;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}

	else if (positionCase.y<250)

	{
    		positionCase.x = 50;
    		positionCase.y = 200;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<300)

	{
    		positionCase.x = 50;
    		positionCase.y = 250;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<350)

	{
    		positionCase.x = 50;
    		positionCase.y = 300;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<400)

	{
    		positionCase.x = 50;
    		positionCase.y = 350;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<450)

	{
    		positionCase.x = 50;
    		positionCase.y = 400;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<500)

	{
    		positionCase.x = 50;
    		positionCase.y = 450;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<550)

	{
    		positionCase.x = 50;
    		positionCase.y = 500;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<600)

	{
    		positionCase.x = 50;
    		positionCase.y = 550;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}

}



else if (positionCase.x<150)
{
	if (positionCase.y<50)
	{
    	positionCase.x = 100;
    	positionCase.y = 0;

	i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<100)

	{
    		positionCase.x = 100;
    		positionCase.y = 50;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}

	else if (positionCase.y<150)

	{
    		positionCase.x = 100;
    		positionCase.y = 100;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}

	else if (positionCase.y<200)

	{
    		positionCase.x = 100;
    		positionCase.y = 150;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}

	else if (positionCase.y<250)

	{
    		positionCase.x = 100;
    		positionCase.y = 200;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<300)

	{
    		positionCase.x = 100;
    		positionCase.y = 250;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<350)

	{
    		positionCase.x = 100;
    		positionCase.y = 300;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<400)

	{
    		positionCase.x = 100;
    		positionCase.y = 350;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<450)

	{
    		positionCase.x = 100;
    		positionCase.y = 400;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<500)

	{
    		positionCase.x = 100;
    		positionCase.y = 450;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<550)

	{
    		positionCase.x = 100;
    		positionCase.y = 500;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<600)

	{
    		positionCase.x = 100;
    		positionCase.y = 550;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}

}


else if (positionCase.x<200)
{
	if (positionCase.y<50)
	{
    	positionCase.x = 150;
    	positionCase.y = 0;

	i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<100)

	{
    		positionCase.x = 150;
    		positionCase.y = 50;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}

	else if (positionCase.y<150)

	{
    		positionCase.x = 150;
    		positionCase.y = 100;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}

	else if (positionCase.y<200)

	{
    		positionCase.x = 150;
    		positionCase.y = 150;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}

	else if (positionCase.y<250)

	{
    		positionCase.x = 150;
    		positionCase.y = 200;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<300)

	{
    		positionCase.x = 150;
    		positionCase.y = 250;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<350)

	{
    		positionCase.x = 150;
    		positionCase.y = 300;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<400)

	{
    		positionCase.x = 150;
    		positionCase.y = 350;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<450)

	{
    		positionCase.x = 150;
    		positionCase.y = 400;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<500)

	{
    		positionCase.x = 150;
    		positionCase.y = 450;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<550)

	{
    		positionCase.x = 150;
    		positionCase.y = 500;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<600)

	{
    		positionCase.x = 150;
    		positionCase.y = 550;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}

}


else if (positionCase.x<250)
{
	if (positionCase.y<50)
	{
    	positionCase.x = 200;
    	positionCase.y = 0;

	i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<100)

	{
    		positionCase.x = 200;
    		positionCase.y = 50;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}

	else if (positionCase.y<150)

	{
    		positionCase.x = 200;
    		positionCase.y = 100;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}

	else if (positionCase.y<200)

	{
    		positionCase.x = 200;
    		positionCase.y = 150;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}

	else if (positionCase.y<250)

	{
    		positionCase.x = 200;
    		positionCase.y = 200;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<300)

	{
    		positionCase.x = 200;
    		positionCase.y = 250;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<350)

	{
    		positionCase.x = 200;
    		positionCase.y = 300;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<400)

	{
    		positionCase.x = 200;
    		positionCase.y = 350;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<450)

	{
    		positionCase.x = 200;
    		positionCase.y = 400;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<500)

	{
    		positionCase.x = 200;
    		positionCase.y = 450;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<550)

	{
    		positionCase.x = 200;
    		positionCase.y = 500;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<600)

	{
    		positionCase.x = 200;
    		positionCase.y = 550;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}

}


else if (positionCase.x<300)
{
	if (positionCase.y<50)
	{
    	positionCase.x = 250;
    	positionCase.y = 0;

	i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<100)

	{
    		positionCase.x = 250;
    		positionCase.y = 50;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}

	else if (positionCase.y<150)

	{
    		positionCase.x = 250;
    		positionCase.y = 100;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}

	else if (positionCase.y<200)

	{
    		positionCase.x = 250;
    		positionCase.y = 150;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}

	else if (positionCase.y<250)

	{
    		positionCase.x = 250;
    		positionCase.y = 200;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<300)

	{
    		positionCase.x = 250;
    		positionCase.y = 250;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<350)

	{
    		positionCase.x = 250;
    		positionCase.y = 300;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<400)

	{
    		positionCase.x = 250;
    		positionCase.y = 350;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<450)

	{
    		positionCase.x = 250;
    		positionCase.y = 400;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<500)

	{
    		positionCase.x = 250;
    		positionCase.y = 450;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<550)

	{
    		positionCase.x = 250;
    		positionCase.y = 500;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<600)

	{
    		positionCase.x = 250;
    		positionCase.y = 550;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}

}


else if (positionCase.x<350)
{
	if (positionCase.y<50)
	{
    	positionCase.x = 300;
    	positionCase.y = 0;

	i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<100)

	{
    		positionCase.x = 300;
    		positionCase.y = 50;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}

	else if (positionCase.y<150)

	{
    		positionCase.x = 300;
    		positionCase.y = 100;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}

	else if (positionCase.y<200)

	{
    		positionCase.x = 300;
    		positionCase.y = 150;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}

	else if (positionCase.y<250)

	{
    		positionCase.x = 300;
    		positionCase.y = 200;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<300)

	{
    		positionCase.x = 300;
    		positionCase.y = 250;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<350)

	{
    		positionCase.x = 300;
    		positionCase.y = 300;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<400)

	{
    		positionCase.x = 300;
    		positionCase.y = 350;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<450)

	{
    		positionCase.x = 300;
    		positionCase.y = 400;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<500)

	{
    		positionCase.x = 300;
    		positionCase.y = 450;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<550)

	{
    		positionCase.x = 300;
    		positionCase.y = 500;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<600)

	{
    		positionCase.x = 300;
    		positionCase.y = 550;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}

}


else if (positionCase.x<400)
{
	if (positionCase.y<50)
	{
    	positionCase.x = 350;
    	positionCase.y = 0;

	i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<100)

	{
    		positionCase.x = 350;
    		positionCase.y = 50;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}

	else if (positionCase.y<150)

	{
    		positionCase.x = 350;
    		positionCase.y = 100;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}

	else if (positionCase.y<200)

	{
    		positionCase.x = 350;
    		positionCase.y = 150;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}

	else if (positionCase.y<250)

	{
    		positionCase.x = 350;
    		positionCase.y = 200;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<300)

	{
    		positionCase.x = 350;
    		positionCase.y = 250;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<350)

	{
    		positionCase.x = 350;
    		positionCase.y = 300;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<400)

	{
    		positionCase.x = 350;
    		positionCase.y = 350;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<450)

	{
    		positionCase.x = 350;
    		positionCase.y = 400;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<500)

	{
    		positionCase.x = 350;
    		positionCase.y = 450;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<550)

	{
    		positionCase.x = 350;
    		positionCase.y = 500;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<600)

	{
    		positionCase.x = 350;
    		positionCase.y = 550;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}

}




else if (positionCase.x<450)
{
	if (positionCase.y<50)
	{
    	positionCase.x = 0;
    	positionCase.y = 0;

	i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<100)

	{
    		positionCase.x = 400;
    		positionCase.y = 50;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}

	else if (positionCase.y<150)

	{
    		positionCase.x = 400;
    		positionCase.y = 100;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}

	else if (positionCase.y<200)

	{
    		positionCase.x = 400;
    		positionCase.y = 150;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}

	else if (positionCase.y<250)

	{
    		positionCase.x = 400;
    		positionCase.y = 200;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<300)

	{
    		positionCase.x = 400;
    		positionCase.y = 250;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<350)

	{
    		positionCase.x = 400;
    		positionCase.y = 300;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<400)

	{
    		positionCase.x = 400;
    		positionCase.y = 350;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<450)

	{
    		positionCase.x = 400;
    		positionCase.y = 400;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<500)

	{
    		positionCase.x = 400;
    		positionCase.y = 450;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<550)

	{
    		positionCase.x = 400;
    		positionCase.y = 500;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<600)

	{
    		positionCase.x = 400;
    		positionCase.y = 550;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}

}


else if (positionCase.x<500)
{
	if (positionCase.y<50)
	{
    	positionCase.x = 450;
    	positionCase.y = 0;

	i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<100)

	{
    		positionCase.x = 450;
    		positionCase.y = 50;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}

	else if (positionCase.y<150)

	{
    		positionCase.x = 450;
    		positionCase.y = 100;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}

	else if (positionCase.y<200)

	{
    		positionCase.x = 450;
    		positionCase.y = 150;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}

	else if (positionCase.y<250)

	{
    		positionCase.x = 450;
    		positionCase.y = 200;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<300)

	{
    		positionCase.x = 450;
    		positionCase.y = 250;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<350)

	{
    		positionCase.x = 450;
    		positionCase.y = 300;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<400)

	{
    		positionCase.x = 450;
    		positionCase.y = 350;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<450)

	{
    		positionCase.x = 450;
    		positionCase.y = 400;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<500)

	{
    		positionCase.x = 450;
    		positionCase.y = 450;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<550)

	{
    		positionCase.x = 450;
    		positionCase.y = 500;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<600)

	{
    		positionCase.x = 450;
    		positionCase.y = 550;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}

}


else if (positionCase.x<550)
{
	if (positionCase.y<50)
	{
    	positionCase.x = 500;
    	positionCase.y = 0;

	i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<100)

	{
    		positionCase.x = 500;
    		positionCase.y = 50;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}

	else if (positionCase.y<150)

	{
    		positionCase.x = 500;
    		positionCase.y = 100;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}

	else if (positionCase.y<200)

	{
    		positionCase.x = 500;
    		positionCase.y = 150;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}

	else if (positionCase.y<250)

	{
    		positionCase.x = 500;
    		positionCase.y = 200;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<300)

	{
    		positionCase.x = 500;
    		positionCase.y = 250;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<350)

	{
    		positionCase.x = 500;
    		positionCase.y = 300;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<400)

	{
    		positionCase.x = 500;
    		positionCase.y = 350;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<450)

	{
    		positionCase.x = 500;
    		positionCase.y = 400;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<500)

	{
    		positionCase.x = 500;
    		positionCase.y = 450;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<550)

	{
    		positionCase.x = 500;
    		positionCase.y = 500;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<600)

	{
    		positionCase.x = 500;
    		positionCase.y = 550;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}

}


else if (positionCase.x<600)
{
	if (positionCase.y<50)
	{
    	positionCase.x = 550;
    	positionCase.y = 0;

	i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<100)

	{
    		positionCase.x = 550;
    		positionCase.y = 50;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}

	else if (positionCase.y<150)

	{
    		positionCase.x = 550;
    		positionCase.y = 100;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}

	else if (positionCase.y<200)

	{
    		positionCase.x = 550;
    		positionCase.y = 150;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}

	else if (positionCase.y<250)

	{
    		positionCase.x = 550;
    		positionCase.y = 200;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<300)

	{
    		positionCase.x = 550;
    		positionCase.y = 250;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<350)

	{
    		positionCase.x = 550;
    		positionCase.y = 300;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<400)

	{
    		positionCase.x = 550;
    		positionCase.y = 350;
            i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<450)

	{
    		positionCase.x = 550;
    		positionCase.y = 400;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<500)

	{
    		positionCase.x = 550;
    		positionCase.y = 450;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<550)

	{
    		positionCase.x = 550;
    		positionCase.y = 500;
		i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }
	}
	else if (positionCase.y<600)

	{
    		positionCase.x = 550;
    		positionCase.y = 550;
            i=(positionCase.x)/50;
                            j=(positionCase.y)/50;
                            if (tab[i][j]==0)
                            {
                                SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=1;
                            }
                            else
                            {
                                SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                SDL_Flip(ecran);
                                tab[i][j]=0;
                            }

	}

}

                }
                break;
                // Dans ce cas et pour arrêter le remplissage de la grille l'utilisateur clic sur le boutton droit de la souris pour passer à la generation suivante
                case SDL_BUTTON_RIGHT:
                    {
                        tab=GenerationSuivante(tab);
                        for(a=0;a<Longueur;a++)
                        {
                            for (b=0;b<Largeur;b++)
                            {
                                switch(tab[a][b])
                                {
                                    case 1:
                                        {
                                            positionCase.x = a*50;
                                            positionCase.y = b*50;
                                            SDL_BlitSurface(CaseVivant, NULL,ecran,&positionCase);
                                            SDL_Flip(ecran);
                                        }
                                        break;
                                    case 0:
                                        {
                                            positionCase.x = a*50;
                                            positionCase.y = b*50;
                                            SDL_BlitSurface(CaseMort, NULL,ecran,&positionCase);
                                            SDL_Flip(ecran);
                                        }
                                        break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }



                SDL_Flip(ecran);
                SDL_FreeSurface(imageDeFond);
                SDL_FreeSurface(CaseVivant);
                SDL_FreeSurface(CaseMort);
                SDL_Quit();

                return EXIT_SUCCESS;

}

// La fonction pause a pour but de laisser la fenêtre ouverte tant que l'utilisateur ne clic pas sur le boutton "Fermer" "X"
void pause()
    {
        int continuer = 1;
        SDL_Event event;

        while (continuer)
        {
            SDL_WaitEvent(&event);
            switch(event.type)
            {
                case SDL_QUIT:
                    continuer = 0;
            }
        }
    }
