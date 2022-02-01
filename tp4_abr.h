#ifndef TP4_ABR_H_INCLUDED
#define TP4_ABR_H_INCLUDED

struct Intervalle{
    int min;
    int max;
};

typedef struct Intervalle T_Inter;

struct Noeud{
    int id_entreprise;
    T_Inter intervalle;
    struct Noeud *fils_gauche;
    struct Noeud *fils_droit;
    int hauteur;
    int equilibre;
};

typedef struct Noeud T_Noeud;

typedef T_Noeud* T_Arbre;

/* fonction verifier_intervalle
 *          Permet de verifier si un intervalle est eu format MMJJ
 *          Retourne 0 si erreur, 1 sinon
 */
int verifier_intervalle(T_Inter intervalle);

/* fonction conflit_intervalle
 *          Permet de verifier si les intervalles sonts disjoints ou nons
 *          Retourne 0 si joints, 1 si disjoints
 */
int conflit_intervalles(T_Inter premier, T_Inter deuxieme);

/* fonction creer_noeud
 *          Permet de creer un noeud
 *          Renvoie NULL en cas d'écher, l'adresse du noeud en memoire sinon
 */
T_Noeud* creer_noeud(int Id_entreprise, T_Inter intervalle);

/* fonction ajouter_noeud
 *          Permet d'ajouter un noeud à un arbre
 *          Affiche une erreur en cas de probleme
 */
void ajouter_noeud(T_Arbre *abr, T_Noeud* noeud);

/* fonction recherche
 *          Recherche une reservation en fonction d'un intervalle et d'un identifiant d'entreprise
 *          Renvoie NULL en cas d'erreur ou si la réservation n'est pas trouvée, renvoie la réservation sinon
 */
T_Noeud* recherche(T_Arbre abr, T_Inter intervalle, int id_entreprise);

/* fonction recherche_conflit
 *          Recherche une reservation en fonction d'un intervalle et d'un identifiant d'entreprise
 *          Renvoie NULL en cas d'erreur ou si la réservation n'est pas trouvée, renvoie la réservation sinon
 */
T_Noeud* recherche_conflit(T_Arbre abr, T_Inter intervalle, int id_entreprise);

/* fonction maxiumum
 *          Renvoie le maximum de l'arbre
 *          Renvoie aussi le pere du noeud renvoyé
 */
T_Noeud* maximum(T_Arbre *abr);

/* fonction minimum
 *          Renvoie le minimum de l'arbre
 *          Renvoie aussi le pere du noeud renvoyé
 */
T_Noeud* minimum(T_Arbre *abr);

/* fonction Supp_noeud
 *          Supprime un noeud contenu dans l'abre
 *          Ne modifie rien si le noeud n'est pas trouvé dans l'abre
 */
void Supp_noeud(T_Arbre *abr, T_Inter intervalle, int Id_entreprise);


/* fonction modif_noeud
 *          Regarde si le noeud existe
 *          Si c'est le cas on supprime le noeud et on en crée un nouveau
 *          Sinon on ne fait rien et on avertit l'utilisateur
 */
void modif_noeud(T_Arbre abr, T_Inter intervalle, int Id_entreprise, T_Inter NouvelIntervalle);

/* fonction afficher_abr
 *          Affiche l'arbre dans un ordre croissant
 *          On creer une copie de l'abre, on affiche le muinimum, on retire le minimum de la copie de l'arbre et on recommence
 */
void afficher_abr(T_Arbre abr);

/* fonction afficher_entr
 *          Affiche l'arbre dans un ordre croissant si l'identifiant de l'entreprise correspond
 *          On creer une copie de l'abre, on affiche le muinimum, on retire le minimum de la copie de l'arbre et on recommence
 */
void afficher_entr(T_Arbre abr, int Id_entreprise);

/* fonction detruire_arbre
 *          Détruit tout les noeuds d'un arbre et libere la memoire
 */
void detruire_arbre(T_Arbre* abr);

/* fonction pere
 *          Renvoie le ^pere d'un noeud contenu dans un arbre
 */
T_Noeud* pere(T_Arbre arb,T_Noeud* noeud);

/* fonction max
 *          Retourne le maximum entre a et b
 */
int max(int a, int b);

/* fonction min
 *          Retourne le minimum entre a et b
 */
int max(int a, int b);



/* fonction rotDroite
 *          Permet d'effectuer une rotation a droite par rapport au noeud x dans l'arbre a
 *          Retourne le sous arbre nouvellement formé
 */
T_Arbre* rotDroite(T_Arbre* a, T_Noeud *x, int *delta);

/* fonction rotGauche
 *          Permet d'effectuer une rotation a gauche par rapport au noeud x dans l'arbre a
 *          Retourne le sous arbre nouvellement formé
 */
T_Arbre* rotGauche(T_Arbre* a, T_Noeud *x, int *delta);

/* fonction rotGaucheDroite
 *          Effectue une rotation a gauche puis une ratation a droite du noeud x de l'abre abr
 *          Retourne le sous-abre formé
 */
T_Arbre* rotGaucheDroite(T_Arbre* abr, T_Noeud *x, int *delta);
/* fonction rotDroiteGauche
 *          Effectue une rotation a droite puis une ratation a gauche du noeud x de l'abre abr
 *          Retourne le sous-abre formé
 */
T_Arbre* rotDroiteGauche(T_Arbre* abr, T_Noeud *x, int *delta);

/* fonction reequilibreAbre
 *          Permet de reequilibrer un noeud x dans l'abre a
 *          Appele rotDroite, rotGauche, rotDroiteGauche, rotGaucheDroite selon l'equilibre de x
 */
T_Arbre* reequilibreArbre(T_Arbre* abr, T_Noeud *x, int *delta);

/* fonction calculerHauteur
 *          Calcule la hauteur d'un noeud de manière récursive
 *          Retourne la hauteur du noeud
 */
int calculerHauteur(T_Noeud** noeud);

#endif // TP4_ABR_H_INCLUDED
