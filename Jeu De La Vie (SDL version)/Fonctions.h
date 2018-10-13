#define Longueur 10
#define Largeur 10

typedef enum Cell Cell;
enum Cell
{
    VIVANTE=1, MORTE=0
};

int** JeuDeLaVie();
int estVivante(int** tab,int x,int y);
int getNbrVoisinsVivants(int** tab,int m,int n);
int seraVivante(int** tab,int a,int b);
int** GenerationSuivante(int **tab);
void afficher(int** tab);

