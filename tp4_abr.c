#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp4_abr.h"

int verifier_intervalle(T_Inter intervalle){

    if(intervalle.max < 0 || intervalle.min < 0 ){
        printf("Erreur l'unde des borne de l'intervalle ne peut pas etre negative.\n");
        return 0;
    }

    if(intervalle.max < intervalle.min){
        printf("Erreur les bornes min et max de l'intervalle sont inversees.\n");
        return 0;
    }

    //verification sur intervalle.min
    int mois_min = intervalle.min / 100;
    int jours_min = intervalle.min % 100;

    if(mois_min < 1 || mois_min > 12){
        printf("Erreur sur l'intervalle minimum, le mois dois etre compris entre 1 et 12.\n");
        return 0;
    }

    if(jours_min == 0 || jours_min > 31){
        printf("Erreur sur l'intervalle minimum, le mois dois etre compris entre 1 et 31.\n");
        return 0;
    }

    if(mois_min == 2 && jours_min > 29){
        printf("Erreur sur l'intervalle minimum, le nombre de jours pour le mois de Fevrier ne peut pas depasser 29.\n");
        return 0;
    }

    if((mois_min == 4 || mois_min == 6 || mois_min == 9 || mois_min == 11) && jours_min > 30){
        printf("Erreur sur l'intervalle minimum, le nombre de jours pour les mois Avril, Juin, Septembre et Nombre ne peut pas depasser 30.\n");
        return 0;
    }



    //verification sur intervalle.max
    int mois_max = intervalle.max / 100;
    int jours_max = intervalle.max % 100;

    if(mois_max < 1 || mois_max > 12){
        printf("Erreur sur l'intervalle maximum, le mois dois etre compris entre 1 et 12.\n");
        return 0;
    }

    if(jours_max == 0 || jours_max > 31){
        printf("Erreur sur l'intervalle maximum, le mois dois etre compris entre 1 et 31.\n");
        return 0;
    }

    if(mois_max == 2 && jours_max > 29){
        printf("Erreur sur l'intervalle maximum, le nombre de jours pour le mois de Fevrier ne peut pas depasser 29.\n");
        return 0;
    }

    if((mois_max == 4 || mois_max == 6 || mois_max == 9 || mois_max == 11) && jours_max > 30){
        printf("Erreur sur l'intervalle maximum, le nombre de jours pour les mois Avril, Juin, Septembre et Nombre ne peut pas depasser 30.\n");
        return 0;
    }

    return 1;

}

int conflit_intervalles(T_Inter premier, T_Inter deuxieme){

    if(premier.min <= deuxieme.max && premier.min >= deuxieme.min){
        //Necessairement premier.min appartient à deuxieme
        return 0;
    }

    if(premier.max <= deuxieme.max && premier.max >= deuxieme.min){
        //Necessairement premier.max appartient à deuxieme
        return 0;
    }

    if(deuxieme.min <= premier.max && deuxieme.min >= premier.min){
        //Necessairement deuxieme.min appartient à premier
        return 0;
    }

    if(deuxieme.max <= premier.max && deuxieme.max >= premier.min){
        //Necessairement deuxieme.max appartient à premier
        return 0;
    }

    return 1;
}

T_Noeud* creer_noeud(int Id_entreprise, T_Inter intervalle){

    T_Noeud *noeud = malloc(sizeof(T_Noeud));


    if(Id_entreprise < 0){
        printf("Erreur l'identifiant de l'entreprise ne peut pas etre negatif");
        return NULL;
    }

    if(verifier_intervalle(intervalle) == 0){
        return NULL;
    }

    noeud->fils_droit = NULL;
    noeud->fils_gauche = NULL;
    noeud->id_entreprise = Id_entreprise;
    noeud->intervalle = intervalle;
    noeud->hauteur = 0;
    noeud->equilibre = 0;
    return noeud;
}

int max(int a,int b){
    if(a>=b){
        return a;
    }
    else{
        return b;
    }
}

int min(int a,int b){
    if(a<=b){
        return a;
    }
    else{
        return b;
    }
}

T_Arbre* rotDroite(T_Arbre* a, T_Noeud *x, int *delta){

    if(x->fils_gauche != NULL){

        x->hauteur = calculerHauteur(&x);

        T_Noeud *y = x->fils_gauche;
        T_Noeud *C = y->fils_droit;

        T_Noeud *pereX = pere(*a, x);
        if(pereX == x){
            pereX = NULL;
        }

        if(pereX != NULL){
            if(pereX->fils_gauche == x){
                pereX->fils_gauche = y;
            }
            else{
                pereX->fils_droit = y;
            }
        }
        else{
            *a = y;
        }

        y->fils_droit = x;
        x->fils_gauche = C;


        //Mise a jour de la hauteur dans l'arbre

        int h = x->hauteur;
        int hB; //hauteur de B
        int hC; //hauteur de C
        int hD; //hauteur de D

        T_Noeud *B = y->fils_gauche;
        if(B != NULL){
            hB = B->hauteur;
        }
        else{
            hB = -1;
        }

        if(C != NULL){
            hC = C->hauteur;
        }
        else{
            hC = -1;
        }

        T_Noeud *D = x->fils_droit;
        if(D != NULL){
            hD = D->hauteur;
        }
        else{
            hD = -1;
        }

        //x->hauteur = max(hC, hD) + 1;
        y->hauteur = (max(hB, calculerHauteur(&(y->fils_droit))) + 1);

        delta = y->hauteur - h;

        T_Noeud *i = y;
        T_Noeud *v = pere(*a, i);

        T_Noeud *j = NULL;
        int hJ; //hauteur de J

        while(v != NULL && delta != 0){

            if(v->fils_gauche == i){
                j = v->fils_droit;
            }
            else{
                j = v->fils_gauche;
            }

            if(j != NULL){
                hJ = j->hauteur;
            }
            else{
                hJ = -1;
            }

            if(hJ > i->hauteur || (hJ == i->hauteur && delta == 1)){
                v->hauteur = v->hauteur + *delta;
                i = v;
                v = pere(*a, v);
            }
            else{
                delta = 0;
            }

        }

        //maintenant les equilibres
        int eqX = x->equilibre;
        int eqY = y->equilibre;

        x->equilibre = eqX - 1 - max(0, eqY);

        if(x->equilibre >= 0){
            y->equilibre = eqY - 1;
        }
        else{
            y->equilibre = eqX -2 + min(0, eqY);
        }

        delta = 0;
        if(y->equilibre >= 0){
            delta = -1;
        }
        else if(eqX <= 0){
            delta = 1;
        }

        a = reequilibreArbre(a, pereX, delta);

        return y;
    }

    return x;
}

T_Arbre* rotGauche(T_Arbre* a, T_Noeud *y, int *delta){

    if(y->fils_droit != NULL){


        y->hauteur = calculerHauteur(&y);

        T_Noeud *x = y->fils_droit;
        T_Noeud *C = x->fils_gauche;


        T_Noeud *pereY = pere(*a, y);

        if(pereY != NULL){

            if(pereY->fils_gauche == y){
                pereY->fils_gauche = x;
            }
            else{
                pereY->fils_droit = x;
            }
        }
        else{
            *a = x;
        }

        y->fils_droit = C;
        x->fils_gauche = y;


        //mise à jour de la hauteur
        int h = y->hauteur;
        int hB; //hauteur de B
        int hC; //hauteur de C
        int hD; //hauteur de D

        T_Noeud *B = y->fils_gauche;
        if(B != NULL){
            hB = B->hauteur;
        }
        else{
            hB = -1;
        }

        if(C != NULL){
            hC = C->hauteur;
        }
        else{
            hC = -1;
        }

        T_Noeud *D = x->fils_droit;
        if(D != NULL){
            hD = D->hauteur;
        }
        else{
            hD = -1;
        }

        //y->hauteur = max(hB, hC) + 1;
        x->hauteur = max(calculerHauteur(&y), hD) + 1;

        delta = x->hauteur - h;

        T_Noeud *i = x;
        T_Noeud *v = pere(*a, i);
        T_Noeud *j = NULL;
        int hJ; //hauteur de J

        while(v != NULL && delta != 0){

            if(v->fils_gauche == i){
                j = v->fils_droit;
            }
            else{
                j = v->fils_gauche;
            }

            if(j != NULL){
                hJ = j->hauteur;
            }
            else{
                hJ = -1;
            }

            if(hJ > i->hauteur || (hJ == i->hauteur && delta == 1)){
                v->hauteur = v->hauteur + delta;
                i = v;
                v = pere(*a, v);
            }
            else{
                delta = 0;
            }

        }

        //maintenant les equilibres
        int eqX = x->equilibre;
        int eqY = y->equilibre;

        x->equilibre = eqX + 1 - min(0, eqY);

        if(x->equilibre <= 0){
            y->equilibre = eqY + 1;
        }
        else{
            y->equilibre = eqX + 2 + max(0, eqY);
        }

        delta = 0;
        if(y->equilibre <= 0){
            delta = -1;
        }
        else if(eqX >= 0){
            delta = 1;
        }

        a = reequilibreArbre(a, pereY, delta);


        return x;
    }
    return y;
}


T_Arbre* rotGaucheDroite(T_Arbre* abr, T_Noeud *x, int *delta){
    if(x->fils_gauche != NULL && x->fils_gauche->fils_droit != NULL){
        x->fils_gauche = rotGauche(abr, x->fils_gauche, *delta);
        x->equilibre = x->equilibre + *delta;
        T_Arbre *x2 = rotDroite(abr, x, *delta);
        return x2;
    }
}

T_Arbre* rotDroiteGauche(T_Arbre* abr, T_Noeud *x, int *delta){
    if(x->fils_droit != NULL && x->fils_droit->fils_gauche != NULL){
        x->fils_droit = rotDroite(abr, x->fils_droit, delta);
        x->equilibre = x->equilibre + delta;
        T_Arbre *x2 = rotGauche(abr, x, delta);
        return x2;
    }
}


T_Arbre* reequilibreArbre(T_Arbre* abr, T_Noeud *x, int *delta){

    if(x != NULL){
        //on recalcule l'equilibre ici
        x->equilibre = calculerHauteur(&x->fils_gauche) - calculerHauteur(&x->fils_droit);

        if(x->equilibre == 2){
            T_Noeud *y = x->fils_gauche;

            y->equilibre = calculerHauteur(&y->fils_gauche) - calculerHauteur(&y->fils_droit);

            if(y->equilibre == 1){
                //printf("rotDroite\n");
                return rotDroite(abr, x, delta);
            }
            else if(y->equilibre == -1){
                //printf("rotGaucheDroite\n");
                return rotGaucheDroite(abr, x, delta);
            }
        }
        else if(x->equilibre == -2){
            T_Noeud *y = x->fils_droit;

            y->equilibre = calculerHauteur(&y->fils_gauche) - calculerHauteur(&y->fils_droit);

            if(y->equilibre == -1){
                //printf("rotGauche\n");
                return rotGauche(abr, x, delta);
            }
            else if(y->equilibre == 1){
                //printf("rotDroiteGauche\n");
                return rotDroiteGauche(abr, x, delta);
            }
        }
    }
    return NULL;
}

int calculerHauteur(T_Noeud** noeud){
    if(*noeud == NULL){
        return -1;
    }
    else{
        return  1 + max( calculerHauteur(&(*noeud)->fils_gauche), calculerHauteur(&(*noeud)->fils_droit));
    }
}

void ajouter_noeud(T_Arbre* abr, T_Noeud* noeud){

    if(noeud != NULL){
        T_Noeud *y = NULL;
        T_Noeud *x = *abr;

        while(x != NULL){
            y = x;
                if(conflit_intervalles(y->intervalle, noeud->intervalle) == 0){
                    printf("Erreur impossible d'ajouter le noeud car conflit d'intervalle.\n");
                    return;  //C'est pourquoi notre programme a échoué en classe
                }
                else if(conflit_intervalles(y->intervalle, noeud->intervalle) == 1){
                    if(noeud->intervalle.max < x->intervalle.min){
                        x = x->fils_gauche;
                    }
                    else if(noeud->intervalle.max > x->intervalle.min){
                        x = x->fils_droit;
                    }
                }
        }

        if(y == NULL){
            *abr = noeud;
        }
        else{
             //Mise a jour de la hauteur
            int h; //avant modif
            h = calculerHauteur(&y);

            if(noeud->intervalle.max < y->intervalle.min){
                y->fils_gauche = noeud;
            }
            else if(noeud->intervalle.min > y->intervalle.max){
                y->fils_droit = noeud;
            }

            //mise a jour hauteur deuxime partie
            int hPrime;
            hPrime = calculerHauteur(&y);

            int delta = hPrime - h;
            int deltaCopie = delta;

            y->hauteur = hPrime;

            T_Noeud *i = y;
            T_Noeud *v = pere((*abr), i);

            T_Noeud *j = NULL;
            int hJ; //hauteur de J

            while(v != NULL && delta != 0){
                if(v->fils_gauche == i){
                    j = v->fils_droit;
                }
                else{
                    j = v->fils_gauche;
                }

                if(j != NULL){
                    hJ = j->hauteur;
                }
                else{
                    hJ = -1;
                }

                if(hJ > i->hauteur || (hJ == i->hauteur && delta == 1)){
                    v->hauteur = v->hauteur + delta;
                    i = v;
                    v = pere((*abr), v);
                }
                else{
                    delta = 0;
                }

            }

            T_Noeud *grandpere = pere(*abr, y);
            abr = reequilibreArbre(abr, grandpere, &deltaCopie);
        }
    }
    else{
        printf("Erreur le noeud a ajouter est NULL.\n");
    }
}


T_Noeud* recherche(T_Arbre abr, T_Inter intervalle, int Id_entreprise){

    if(Id_entreprise < 0){
        printf("Erreur l'identifiant d'une entreprise ne peut pas etre negatif.\n");
        return NULL;
    }

    if(verifier_intervalle(intervalle) == 0){
        printf("Erreur l'intervalle entre en parametre n'es pas valide.\n");
        return NULL;
    }

    if(abr==NULL){
        return NULL;
    }

    if(Id_entreprise == abr->id_entreprise && abr->intervalle.min==intervalle.min && abr->intervalle.max==intervalle.max){
        return abr;
    }

    if(intervalle.max < abr->intervalle.min){
        return recherche(abr->fils_gauche,intervalle,Id_entreprise);
    }

    if(intervalle.min > abr->intervalle.max){
        return recherche(abr->fils_droit,intervalle,Id_entreprise);
    }

    return NULL;    //on a rien trouve

}

T_Noeud* recherche_conflit(T_Arbre abr, T_Inter intervalle, int Id_entreprise){

    if(Id_entreprise < 0){
        printf("Erreur l'identifiant d'une entreprise ne peut pas etre negatif.\n");
        return NULL;
    }

    if(verifier_intervalle(intervalle) == 0){
        printf("Erreur l'intervalle entre en parametre n'es pas valide.\n");
        return NULL;
    }

    if(abr==NULL){
        return NULL;
    }


    if(conflit_intervalles(intervalle, abr->intervalle) == 0){
        return abr;
    }

    if(intervalle.max < abr->intervalle.min){
        return recherche_conflit(abr->fils_gauche,intervalle,Id_entreprise);
    }

    if(intervalle.min > abr->intervalle.max){
        return recherche_conflit(abr->fils_droit,intervalle,Id_entreprise);
    }

    return NULL;    //on a rien trouve

}

T_Noeud* maximum(T_Arbre *abr){

    if(*abr == NULL){
        return NULL;
    }

    T_Noeud *noeud = *abr;

    while(noeud->fils_droit != NULL){
        noeud = noeud->fils_droit;
    }

    return noeud;
}

T_Noeud* minimum(T_Arbre *abr){

    if(*abr == NULL){
        return NULL;
    }

    T_Noeud *noeud = *abr;

    while(noeud->fils_gauche != NULL){
        noeud = noeud->fils_gauche;
    }
    return noeud;
}

T_Noeud* pere(T_Arbre arb, T_Noeud* noeud){
    if(arb == NULL){
        printf("Erreur l'arbre passe en parametre est NULL.\n");
        return NULL;
    }

    T_Noeud* Pere = NULL;
    Pere = arb;

    while(arb != NULL){
        if((arb->intervalle.min == noeud->intervalle.min && arb->intervalle.max == noeud->intervalle.max) && noeud->id_entreprise == arb->id_entreprise){
            return Pere;
        }
        else if(noeud->intervalle.max < arb->intervalle.min){
            Pere=arb;
            arb = arb->fils_gauche;
        }
        else{
            Pere=arb;
            arb = arb->fils_droit;
        }
    }

    return NULL;
}


void Supp_noeud(T_Arbre *abr, T_Inter intervalle, int id_entreprise){


    if(id_entreprise < 0){
        printf("Erreur l'identifiant d'une entreprise ne peut pas etre negatif.\n");
        return;
    }

    if(verifier_intervalle(intervalle) == 0){
        printf("Erreur l'intervalle entre en parametre n'est pas valide.\n");
        return;
    }

    if(abr == NULL){
        printf("Erreur l'arbre passe en parametre est NULL.\n");
        return;
    }

    T_Arbre copie = *abr;

    T_Noeud* t=malloc(sizeof(T_Noeud));


    t->fils_droit=NULL;
    t->fils_gauche=NULL;
    t->id_entreprise=id_entreprise;
    t->intervalle=intervalle;

    T_Arbre pere_copie = pere(*abr,t);

    int n=0;    //booleen pour savoir si le noeud existe

        while(copie != NULL){

            if(id_entreprise == copie->id_entreprise && intervalle.min== copie->intervalle.min && intervalle.max==copie->intervalle.max){
                n=1;
                //il faut supprimer copie

                //Si le noeud à supprimer n'a pas de fils
                if(copie->fils_droit == NULL && copie->fils_gauche == NULL){

                    if(pere_copie->fils_droit == copie){
                        pere_copie->fils_droit = NULL;
                    }
                    else if(pere_copie->fils_gauche == copie){
                        pere_copie->fils_gauche = NULL;
                    }


                    free(copie);
                    copie=NULL;

                    printf("Noeud supprime avec succes.\n");
                }
                else if(copie->fils_droit == NULL && copie->fils_gauche != NULL){   //Si copie n'a qu'un seul fils

                    if(copie == *abr){
                        //*abr = copie->fils_gauche;
                        copie->hauteur = copie->fils_gauche->hauteur;
                        copie->equilibre = copie->fils_gauche->equilibre;
                        copie->intervalle = copie->fils_gauche->intervalle;
                        copie->id_entreprise = copie->fils_gauche->id_entreprise;

                        copie->fils_gauche = copie->fils_gauche->fils_gauche;
                        copie->fils_droit = copie->fils_gauche->fils_droit;

                        free(copie->fils_gauche);

                    }
                    else{
                        if(pere_copie->fils_droit == copie){
                                pere_copie->fils_droit = copie->fils_gauche;
                        }
                        else if(pere_copie->fils_gauche == copie){
                            pere_copie->fils_gauche = copie->fils_gauche;
                        }

                        free(copie);
                        copie=NULL;
                    }


                    printf("Noeud supprime avec succes.\n");
                }
                else if(copie->fils_gauche == NULL && copie->fils_droit != NULL){

                    if(copie == *abr){
                        //*abr = copie->fils_droit;

                        copie->hauteur = copie->fils_droit->hauteur;
                        copie->equilibre = copie->fils_droit->equilibre;
                        copie->intervalle = copie->fils_droit->intervalle;
                        copie->id_entreprise = copie->fils_droit->id_entreprise;

                        copie->fils_gauche = copie->fils_droit->fils_gauche;
                        copie->fils_droit = copie->fils_droit->fils_droit;

                        free(copie->fils_droit);
                    }
                    else{
                        if(pere_copie->fils_gauche == copie){
                            pere_copie->fils_gauche = copie->fils_droit;
                        }
                        else if(pere_copie->fils_droit == copie){
                            pere_copie->fils_droit = copie->fils_droit;
                        }

                        free(copie);
                        copie=NULL;
                    }

                    printf("Noeud supprime avec succes.\n");
                }
                else if(copie->fils_gauche != NULL && copie->fils_droit != NULL){  //On a deux fils

                    //on regarde le macimum du sous-arbre droit de copie
                    //on remplace copie par le maximum
                    //on supprime copie


                    T_Noeud *n = maximum(&(copie->fils_droit));
                    T_Noeud *pere_n = pere(*abr, n);

                    copie->intervalle = n->intervalle;
                    copie->id_entreprise = n->id_entreprise;

                    if(pere_n->fils_droit == n){
                        pere_n->fils_droit = NULL;
                    }
                    else{
                        pere_n->fils_gauche = NULL;
                    }


                    free(n);
                    copie=NULL;

                    printf("Noeud supprime avec succes.\n");

                    int delta = -1;
                    abr = reequilibreArbre(abr, pere_n, &delta);

                }
            }
            else if(conflit_intervalles(intervalle, copie->intervalle) == 0){
                printf("Impossible de supprimer ce noeud.\nUne partie de l'intervalle est utilise pour une reservation.\nVeulliez saisir un intervalle complet.\n");
                copie = NULL;
            }
            else if(intervalle.max < copie->intervalle.min){
                pere_copie = copie;
                copie = copie->fils_gauche;
            }
            else if(intervalle.min > copie->intervalle.max){
                pere_copie = copie;
                copie = copie->fils_droit;
            }
            else{
                copie = NULL;
            }
        }

    if(n==0){
        printf("Ce noeud n'existe pas.\n");
    }
}

void modif_noeud(T_Arbre abr, T_Inter intervalle, int Id_entreprise, T_Inter NouvelIntervalle){

    if(Id_entreprise < 0){
        printf("Erreur l'identifiant d'une entreprise ne peut pas etre negatif.\n");
        return;
    }

    if(verifier_intervalle(intervalle) == 0){
        printf("Erreur l'intervalle entre en parametre n'est pas valide.\n");
        return;
    }

    if(verifier_intervalle(NouvelIntervalle) == 0){
        printf("Erreur le nouvel intervalle entre en parametre n'est pas valide.\n");
        return;
    }

    if(abr == NULL){
        printf("Erreur l'arbre passe en parametre est NULL.\n");
        return;
    }

    //on regarde si le noeud existe
    //Si c'est le cas on le supprime et on en crée un nouveau
    //sinon on ne fait rien

    T_Noeud *noeud = recherche(abr, intervalle, Id_entreprise);
    if(noeud == NULL){
            printf("Impossible de modifier le noeud car il n'existe pas dans l'arbre.\n");
            return;
    }
    else if(recherche_conflit(abr,NouvelIntervalle,Id_entreprise) != NULL){

            ///TODO modifier un sous-intervalle

            if(recherche_conflit(abr,NouvelIntervalle,Id_entreprise) == noeud){
                //Le nouvelle intervalle contient un sous intervalle de l'intervalle à modifier

                if((NouvelIntervalle.min != abr->intervalle.min) && (NouvelIntervalle.max != abr->intervalle.max)){

                    //printf("Noeud est different d'abr.\n");
                    //on supprime le noeud

                    int copie_id_entreprise = Id_entreprise;
                    T_Inter copie_intervalle = intervalle;

                    Supp_noeud(&abr, intervalle, Id_entreprise);

                    //on reregarde s'il y a encore un conflit
                    T_Noeud *test = recherche_conflit(abr,NouvelIntervalle,Id_entreprise);

                    if(test == NULL){

                        printf("Pas de conflit wtf.");

                        T_Noeud *n = creer_noeud(Id_entreprise, NouvelIntervalle);

                        if(n == NULL){
                            printf("Echec de la modification du noeud.\n");
                            return;
                        }
                        else{
                            ajouter_noeud(&abr, n);
                            printf("Noeud modifie avec succes.\n");
                        }
                    }
                    else{
                        T_Noeud *n = creer_noeud(copie_id_entreprise, copie_intervalle);
                        printf("Erreur : on essaye de modifier l'intervalle sur des jours non disponibles.\n");

                        if(n == NULL){
                            printf("Erreur critique.\n");
                            return;
                        }
                        else{
                            ajouter_noeud(&abr, n);
                        }

                    }
                }
                else{

                    if(NouvelIntervalle.max > abr->intervalle.max && NouvelIntervalle.min < abr->intervalle.max){

                        //on regarde s'il n'y a pas de conflit pour les jours en plus

                        T_Inter ne;
                        ne.min = abr->intervalle.max +1;
                        ne.max = NouvelIntervalle.max;

                        if(recherche_conflit(abr,ne,Id_entreprise) != NULL){
                             printf("Erreur : on essaye de modifier l'intervalle sur des jours non disponibles.\n");
                             return;
                        }
                        else{
                            abr->intervalle.max = NouvelIntervalle.max;
                        }
                    }
                    else if(NouvelIntervalle.min < abr->intervalle.min && NouvelIntervalle.min > abr->intervalle.min){

                        //on verifie s'il n'y a pas de conflit avec les jpurs en plus

                        T_Inter ne;
                        ne.min = NouvelIntervalle.min;
                        ne.max = abr->intervalle.min -1;

                        if(recherche_conflit(abr,ne,Id_entreprise) != NULL){
                             printf("Erreur : on essaye de modifier l'intervalle sur des jours non disponibles.\n");
                             return;
                        }
                        else{
                            abr->intervalle.min = NouvelIntervalle.min;
                        }

                    }
                    else{
                        //printf("Erreur : Impossible de mofifier l'intervalle en racine (une borne de l'intervalle a la fois svp).\n");
                        return;
                    }

                }

            }
            else{
                printf("Erreur : la nouvelle réservation existe deja.\n");
            }
    }
    else if(recherche_conflit(abr,NouvelIntervalle,Id_entreprise) == NULL){

            Supp_noeud(&abr, intervalle, Id_entreprise);

            afficher_abr(abr);

            T_Noeud *n = creer_noeud(Id_entreprise, NouvelIntervalle);

            if(n == NULL){
                printf("Echec de la modification du noeud.\n");
                return;
            }

            ajouter_noeud(&abr, n);
            printf("Noeud modifie avec succes.\n");

    }
}

void afficher_abr(T_Arbre abr){
    if(abr == NULL){
        //printf("Erreur l'arbre passe en parametre est NULL.\n");
        return ;
    }

    afficher_abr(abr->fils_gauche);
    printf(" --> ID_Entr:%d -- [%d,%d]\n", (abr)->id_entreprise, (abr)->intervalle.min, (abr)->intervalle.max);
    afficher_abr(abr->fils_droit);
}


void afficher_entr(T_Arbre abr, int id_entreprise){

    if(id_entreprise < 0){
        printf("Erreur l'identifiant d'une entreprise ne peut pas etre negatif.\n");
        return;
    }
    if(abr == NULL){
       // printf("Erreur l'arbre passe en parametre est NULL.\n");
       //CONDITION d'arret
        return;
    }
    afficher_entr(abr->fils_gauche,id_entreprise);
    if(abr->id_entreprise==id_entreprise){
        printf(" --> ID_Entr:%d -- [%d,%d]\n", (abr)->id_entreprise, (abr)->intervalle.min, (abr)->intervalle.max);
    }
    afficher_entr(abr->fils_droit,id_entreprise);
}

void detruire_arbre(T_Arbre* abr){
    if(*abr == NULL){
        printf("Erreur l'arbre passe en parametre est NULL.\n");
        return;
    }
    else{
        if((*abr)->fils_gauche != NULL){
                detruire_arbre((*abr)->fils_gauche);
        }
        if((*abr)->fils_droit != NULL){
                detruire_arbre((*abr)->fils_droit);
        }
        free(*abr);
        *abr = NULL;
    }
}

