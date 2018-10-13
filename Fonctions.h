
/*Programme fait par Bamouh Mohamed (G1) et Adam Saddiki (G8)*/

typedef enum Cell Cell;
enum Cell
{
    VIVANTE=1, MORTE=0
};

int** JeuDeLaVie(int l,int L);
int Modulol(int i,int l);
int ModuloL(int i,int L);
int getNbrVoisinsVivants(int** tab,int m,int n,int l,int L);
int seraVivante(int** tab,int a,int b,int l,int L);
int** GenerationSuivante(int **tab,int l,int L);
void afficher(int** tab,int l,int L);
int nbcolonnes(FILE* fichier);
int nblignes(FILE* fichier);
int** charger(FILE* fichier);
void sauvegarder(int** tab,int l, int L);

