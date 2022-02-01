#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp4_abr.h"

int main()
{
    int choix = -1;
    T_Arbre arb = NULL;


/*    T_Inter inter;
    inter.min = 110;
    inter.max = 120;

    char str[50] = "x";

    T_Noeud *x = creer_noeud(1, inter, str);
    ajouter_noeud(&arb, x);     //x


    T_Inter inter2;
    inter2.min = 105;
    inter2.max = 106;

    char Y[50] = "y";

    T_Noeud *y = creer_noeud(1, inter2, Y);
    ajouter_noeud(&arb, y);    //y


    T_Inter inter3;
    inter3.min = 102;
    inter3.max = 103;

    char B[50] = "B";

    ajouter_noeud(&arb, creer_noeud(1, inter3, B));    //B


    T_Inter inter4;
    inter4.min = 108;
    inter4.max = 109;

    char C[50] = "C";
    T_Noeud *c = creer_noeud(1, inter4, C);

    ajouter_noeud(&arb, c);    //C


    T_Inter inter5;
    inter5.min = 125;
    inter5.max = 127;

    char D[50] = "D";

    ajouter_noeud(&arb, creer_noeud(1, inter5, D));    //D


    T_Inter inter6;
    inter6.min = 201;
    inter6.max = 202;

    char E[50] = "E";
    T_Noeud *e = creer_noeud(1, inter6, E);

    ajouter_noeud(&arb, e);    //D

    T_Inter inter7;
    inter7.min = 203;
    inter7.max = 204;

    char F[50] = "F";

    T_Noeud *f = creer_noeud(1, inter7, F);
    ajouter_noeud(&arb, f);    //D


    T_Inter inter8;
    inter8.min = 213;
    inter8.max = 214;

    char G[50] = "G";

    T_Noeud *g = creer_noeud(1, inter8, G);
    ajouter_noeud(&arb, g);    //D*/

    //afficher_abr(arb);

    printf("\n\n");


/*    if(recherche(arb, inter, 1) != NULL){
        printf("Trouve ! 1\n");
    }*/

    //Supp_noeud(&arb, inter, 1);

    //afficher_abr(arb);


    printf("Le debut et la fin des intervalles sont au format : MMJJ\n");

    do {
        printf("\n\nChoisir une action : \n");
        printf("1. Creer un ABR\n");
        printf("2. Afficher toutes les reservations\n");
        printf("3. Ajouter une reservation\n");
        printf("4. Modifier une reservation\n");
        printf("5. Supprimer une reservation\n");
        printf("6. Afficher les reservations d'une entreprise\n");
        printf("7. Supprimer l'arbre\n");
        printf("8. Quitter\n");
        scanf("%d", &choix);

        if(choix < 1 || choix > 9 ){
            printf("Merci de saisir un choix valide.\n");
        }
        else if(choix==1){

            if(arb == NULL){

                T_Arbre arb1=malloc(sizeof(T_Noeud));
                if(arb1 == NULL){
                    printf("Erreur d'allocation memoire.\n");
                    exit(0);
                }

                do{
                    printf("Entrez le debut et la fin de l'intervalle separes d'un espace.\n");
                    scanf("%d %d",&(arb1->intervalle.min),&(arb1->intervalle.max));

               }while(!verifier_intervalle(arb1->intervalle));

                do{
                    printf("Entrer l'identifiant de l'entreprise.\n");
                    scanf("%d",&arb1->id_entreprise);

                    if(arb1->id_entreprise<0){
                            printf("Erreur : l'identifiant doit etre positif.\n");
                    }
                }while(arb1->id_entreprise<0);

                arb1->fils_droit=NULL;
                arb1->fils_gauche=NULL;
                arb=arb1;
            }
            else{
                printf("Il existe deja un arbre.\n");
            }
        }
        else if(choix==2){
            if(arb == NULL){
                printf("L'arbre a afficher est vide.\n");
            }
            else{
                afficher_abr(arb);
            }
        }
        else if(choix==3){

            if(arb==NULL){
                    printf("L'arbre n'existe pas.\n");
            }
            else{

                int id_ent = -1;

                struct Intervalle inter;
                inter.min = -1;
                inter.max = -2;

                    do{
                        printf("Entrez le minimum : ");
                        scanf("%d",&inter.min);
                        printf("Entrez le maximum : ");
                        scanf("%d",&inter.max);
                    }while(!verifier_intervalle(inter));

                    do{
                        printf("Entrez l'identifiant de l'entreprise.\n");
                        scanf("%d",&id_ent);

                        if(id_ent<0){
                            printf("Erreur : l'identifiant doit etre positif.\n");
                        }
                    }while(id_ent<0);

                ajouter_noeud(&arb,creer_noeud(id_ent,inter));
            }
        }
        else if(choix==4){
            if(arb==NULL){
                    printf("L'arbre n'existe pas.\n");
            }
            else{
                T_Inter inter;      //ancien intervalle
                inter.min = -1;
                inter.max = -2;

                T_Inter nouinter;   //nouvel intervalle
                nouinter.min = -1;
                nouinter.max = -2;

                int id = -1;

                do{
                    printf("Entrez le debut et la fin de l'intervalle que vous souhaitez modifier separes d'un espace.\n");
                    scanf("%d %d",&inter.min,&inter.max);
                }while(!verifier_intervalle(inter));

                do{
                    printf("Entrez le debut et la fin de l'intervalle du nouvel interval separes d'un espace.\n");
                    scanf("%d %d",&nouinter.min,&nouinter.max);
                }while(!verifier_intervalle(nouinter));

                do{
                    printf("Entrez l'identifiant de l'entreprise que vous voulez modifier.\n");
                    scanf("%d",&id);

                    if(id<0){
                            printf("Erreur : l'identifiant doit etre positif.\n");
                    }
                }while(id<0);

                modif_noeud(arb,inter,id,nouinter); //probleme quand on modifie un sous-intervalle
            }
        }

        else if(choix==5){

            if(arb==NULL){
                    printf("L'arbre n'existe pas.\n");
            }
            else{
                T_Inter inter;
                inter.min = -1;
                inter.max = -2;
                int id = -1;

                do{
                    printf("Entrez le debut et la fin de l'intervalle que vous souhaitez supprimer separes d'un espace.\n");
                    scanf("%d %d",&inter.min,&inter.max);
                }while(!verifier_intervalle(inter));

                do{
                    printf("Entrez l'identifiant de l'entreprise que vous voulez supprimer.\n");
                    scanf("%d",&id);

                    if(id<0){
                         printf("Erreur : l'identifiant doit etre positif.\n");
                    }
                }while(id<0);

                Supp_noeud(&arb,inter,id);
            }
        }
        else if(choix==6){
            if(arb != NULL){

                int id = -1;

                do{
                    printf("Entrez l'identifiant de l'entreprise.\n");
                    scanf("%d",&id);

                    if(id<0){
                        printf("Erreur : l'identifiant doit etre positif.\n");
                    }
                }while(id<0);

                afficher_entr(arb,id);
            }
            else{
                printf("L'arbre a afficher est vide ou n'existe pas.\n");
            }
        }
        else if(choix==7){
            if(arb != NULL){    //on ne supprime pas s'il n'y a rien a supprimer
                detruire_arbre(&arb);
                arb = NULL;     //utile selon l'OS;
            }
            printf("Arbre detruit.\n");
        }
        else if(choix == 8){        //on vide quand même la mémoire avant de quitter
            if(arb != NULL){    //on ne supprime pas s'il n'y a rien a supprimer
                detruire_arbre(&arb);
                arb = NULL;     //utile selon l'OS;
            }
            printf("Au revoir.\n");
        }

    }while(choix!=8);

    return 0;
}
