struct Personne
{
    char nom[30];
    char prenom[30];
    char tel[20];
};

void Ajouter(struct Personne utilisateur[]);
void Lire(struct Personne utilisateur[]);
void Modifier(struct Personne utilisateur[]);
void Supprimer(struct Personne utilisateur[]);
void AfficherMenu();
