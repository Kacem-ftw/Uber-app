#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include<string.h>
#include<math.h>
#include<windows.h>
#include<time.h>

// structures pour clients et chauffeurs
typedef struct Client {
    int id;
    char nom[30];
    char prenom[30];
    char num_tel[8];
    struct Client* suiv;
} Client;

typedef struct Chauffeur {
    int id;
    char nom[30];
    char prenom[30];
    char num_tel[8];
    char matricule[20];
    float x;
    float y;
    char etat[10];
    struct Chauffeur* suiv;
} Chauffeur;

Client* tete_clients = NULL;
Chauffeur* tete_chauffeurs = NULL;

// Chercher un client dans la liste chaînée
int chercher_client(Client* tete, int id) {
    Client* courant = tete;
    while (courant != NULL) {
        if (courant->id == id) {
            return 1;
        }
        courant = courant->suiv;
    }
    return 0;
}

// Chercher un chauffeur dans une liste chaînée
int chercher_chauffeur(Chauffeur* tete, int id) {
    Chauffeur* courant = tete;
    while (courant != NULL) {
        if (courant->id == id) {
            return 1;
        }
        courant = courant->suiv;
    }
    return 0;
}
// Vérifier que le numéro contient exactement 8 caractères et que ce sont tous des chiffres
int verifier_numero(const char* num_tel) {
    if (strlen(num_tel) !=8) {
        return 0;
    }
    for (int i = 0; i < 8; i++) {
        if (!isdigit(num_tel[i])) {
            return 0;
        }
    }
    return 1;
}
// ajout d'un client
void ajout_client() {
    FILE *in;
    char ch[512];
    char ch1[512];
    in = fopen("clients.txt", "a");
    if (in == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    Client* nouv_client = (Client*)malloc(sizeof(Client));
    if (nouv_client == NULL) {
        printf("Echec d'allocation memoire.\n");
        fclose(in);
        return;
    }

    do {
        printf("Votre id (8 chiffres) : ");
        scanf("%s",&ch1);
        if (!verifier_numero(ch1)) {
            printf("id invalide. Veuillez entrer exactement 8 chiffres.\n");
        }
    } while (!verifier_numero(ch1));
    nouv_client->id=atoi(ch1);
    if(chercher_chauffeur(tete_chauffeurs,nouv_client->id)==1 || chercher_client(tete_clients,nouv_client->id) == 1) {
        printf("Un compte existe deja avec cet id !");
        free(nouv_client);
        fclose(in);
        return;
    }
        printf("Votre nom: ");
        scanf("%s", nouv_client->nom);

        printf("Votre prenom: ");
        scanf("%s", nouv_client->prenom);

    do {
        printf("Votre numero de telephone (8 chiffres) : ");
        scanf("%s", nouv_client->num_tel);
        if (!verifier_numero(nouv_client->num_tel)) {
            printf("Numéro invalide. Veuillez entrer exactement 8 chiffres.\n");
        }
    } while (!verifier_numero(nouv_client->num_tel));

        sprintf(ch, "Client ID: %d, Nom: %s, Prenom: %s, Num Tel: %s\n",
                nouv_client->id, nouv_client->nom, nouv_client->prenom, nouv_client->num_tel);
        fputs(ch, in);
        nouv_client->suiv = tete_clients;
        tete_clients = nouv_client;
        printf("Client ajoute avec succes !\n");
        fclose(in);
    }


// ajout d'un chauffeur
void ajout_chauffeur() {
    FILE *in;
    char ch[512];
    char ch1[512];

    in = fopen("chauffeurs.txt", "a");
    if (in == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    Chauffeur* nouv_chauffeur = (Chauffeur*)malloc(sizeof(Chauffeur));
    if (nouv_chauffeur == NULL) {
        printf("Echec d'allocation memoire.\n");
        fclose(in);
        return;
    }
    do {
        printf("Votre id (8 chiffres) : ");
        scanf("%s",&ch1);
        if (!verifier_numero(ch1)) {
            printf("id invalide. Veuillez entrer exactement 8 chiffres.\n");
        }
    } while (!verifier_numero(ch1));
    nouv_chauffeur->id = atoi(ch1);
    if(chercher_chauffeur(tete_chauffeurs, nouv_chauffeur->id) == 1 || chercher_client(tete_clients, nouv_chauffeur->id) == 1) {
        printf("Un compte existe deja avec cet id !");
        free(nouv_chauffeur);
        fclose(in);
        return;
    }

    printf("Votre nom: ");
    scanf("%s", nouv_chauffeur->nom);

    printf("Votre prenom: ");
    scanf("%s", nouv_chauffeur->prenom);

    do {
        printf("Votre numero de telephone (8 chiffres) : ");
        scanf("%s", nouv_chauffeur->num_tel);
        if (!verifier_numero(nouv_chauffeur->num_tel)) {
            printf("Numéro invalide. Veuillez entrer exactement 8 chiffres.\n");
        }
    } while (!verifier_numero(nouv_chauffeur->num_tel));

    printf("Votre matricule: ");
    scanf("%s", nouv_chauffeur->matricule);

    printf("Votre coordonnee x: ");
    scanf("%f", &nouv_chauffeur->x);

    printf("Votre coordonnee y: ");
    scanf("%f", &nouv_chauffeur->y);
do {
    printf("Votre etat(oui/non): ");
    scanf("%s", nouv_chauffeur->etat);
}while (strcmp(nouv_chauffeur->etat, "oui") != 0 && strcmp(nouv_chauffeur->etat, "non") != 0);
    fprintf(in, "Chauffeur ID: %d, Nom: %s, Prenom: %s, Num Tel: %s, Matricule: %s, x: %.2f, y: %.2f\n, etat: %s\n",
            nouv_chauffeur->id, nouv_chauffeur->nom, nouv_chauffeur->prenom,
            nouv_chauffeur->num_tel, nouv_chauffeur->matricule,
            nouv_chauffeur->x, nouv_chauffeur->y, nouv_chauffeur->etat);

    nouv_chauffeur->suiv = tete_chauffeurs;
    tete_chauffeurs = nouv_chauffeur;

    printf("Chauffeur ajoute avec succes !\n");
    fclose(in);
}
// modifier un chauffeur
void modifier_chauffeur() {
    int id1, trouve = 0;
    FILE *fichier;
    char lignes[1000][512];
    int nombre_lignes = 0;

    fichier = fopen("chauffeurs.txt", "r");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    while (fgets(lignes[nombre_lignes], sizeof(lignes[nombre_lignes]), fichier) != NULL) {
        nombre_lignes++;
    }
    fclose(fichier);

    printf("Donner votre id à modifier (8 chiffres) : ");
    scanf("%d", &id1);

    fichier = fopen("chauffeurs.txt", "w");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    for (int i = 0; i < nombre_lignes; i++) {
        int id_fichier;
        if (sscanf(lignes[i], "Chauffeur ID: %d", &id_fichier) == 1) {
            if (id_fichier == id1) {
                Chauffeur* courant = tete_chauffeurs;
                while (courant != NULL) {
                    if (courant->id == id1) {
                        do {
                            printf("Votre numero de telephone (8 chiffres) : ");
                            scanf("%s", courant->num_tel);
                            if (!verifier_numero(courant->num_tel)) {
                                printf("Numéro invalide. Veuillez entrer exactement 8 chiffres.\n");
                            }
                        } while (!verifier_numero(courant->num_tel));

                        printf("Donner votre nouvelle matricule : ");
                        scanf("%19s", courant->matricule);

                        printf("Donner votre nouvelle coordonnee x : ");
                        scanf("%f", &courant->x);

                        printf("Votre nouvelle coordonnee y : ");
                        scanf("%f", &courant->y);
                        do {
                            printf("Votre etat(oui/non): ");
                            scanf("%s", courant->etat);
                        }while (strcmp(courant->etat, "oui") != 0 && strcmp(courant->etat, "non") != 0);

                        fprintf(fichier, "Chauffeur ID: %d, Nom: %s, Prenom: %s, Num Tel: %s, Matricule: %s, x: %.2f, y: %.2f, etat: %s\n",
                                courant->id, courant->nom, courant->prenom,
                                courant->num_tel, courant->matricule, courant->x, courant->y,courant->etat);

                        trouve = 1;
                        printf("Chauffeur modifie avec succes !\n");
                        break;
                    }
                    courant = courant->suiv;
                }
            } else {
                fputs(lignes[i], fichier);
            }
        }
    }

    fclose(fichier);

    if (!trouve) {
        printf("Aucun chauffeur trouvé avec cet ID.\n");
    }
}
// supprimer un chauffeur
void supprimer_chauffeur() {
    int id1, trouve = 0;
    FILE *fichier;
    char lignes[1000][512];
    int nombre_lignes = 0;

    fichier = fopen("chauffeurs.txt", "r");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }
    while (fgets(lignes[nombre_lignes], sizeof(lignes[nombre_lignes]), fichier) != NULL) {
        nombre_lignes++;
    }
    fclose(fichier);

    printf("Donner votre id à supprimer : ");
    scanf("%d", &id1);

    fichier = fopen("chauffeurs.txt", "w");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    for (int i = 0; i < nombre_lignes; i += 2) {
        int id_fichier;
        if (sscanf(lignes[i], "Chauffeur ID: %d", &id_fichier) == 1) {
            if (id_fichier != id1){
                fputs(lignes[i], fichier);
                if (i + 1 < nombre_lignes) {
                    fputs(lignes[i + 1], fichier);
                }
            } else {
                trouve = 1;
                i++;
            }
        }
    }

    fclose(fichier);

    Chauffeur *courant = tete_chauffeurs, *precedent = NULL;
    while (courant != NULL) {
        if (courant->id == id1) {
            if (precedent == NULL) {
                tete_chauffeurs = courant->suiv;
            } else {
                precedent->suiv = courant->suiv;
            }
            free(courant);
            break;
        }
        precedent = courant;
        courant = courant->suiv;
    }

    if (trouve) {
        printf("Chauffeur supprime avec succes !\n");
    } else {
        printf("Aucun chauffeur trouve avec cet ID.\n");
    }
}

// modifier un client
void modifier_client() {
    int id1, trouve = 0;
    FILE *fichier;
    char lignes[1000][512];
    int nombre_lignes = 0;

    fichier = fopen("clients.txt", "r");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }
    while (fgets(lignes[nombre_lignes], sizeof(lignes[nombre_lignes]), fichier) != NULL) {
        nombre_lignes++;
    }
    fclose(fichier);

    printf("Donner votre id à modifier : ");
    scanf("%d", &id1);


    fichier = fopen("clients.txt", "w");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }
    for (int i = 0; i < nombre_lignes; i++) {
        int id_fichier;
        if (sscanf(lignes[i], "Client ID: %d", &id_fichier) == 1) {
            if (id_fichier == id1) {
                Client* courant = tete_clients;
                while (courant != NULL) {
                    if (courant->id == id1) {
                        do {
                            printf("Votre numero de telephone (8 chiffres) : ");
                            scanf("%s", courant->num_tel);
                            if (!verifier_numero(courant->num_tel)) {
                                printf("Numéro invalide. Veuillez entrer exactement 8 chiffres.\n");
                            }
                        } while (!verifier_numero(courant->num_tel));

                        fprintf(fichier, "Client ID: %d, Nom: %s, Prenom: %s, Num Tel: %s\n",
                                courant->id, courant->nom, courant->prenom,
                                courant->num_tel);

                        trouve = 1;
                        printf("Client modifie avec succes !\n");
                        break;
                    }
                    courant = courant->suiv;
                }
            } else {
                fputs(lignes[i], fichier);
            }
        }
    }

    fclose(fichier);

    if (!trouve) {
        printf("Aucun client trouve avec cet ID.\n");
    }
}
// supprimer un client
void supprimer_client() {
    int id1, trouve = 0;
    FILE *fichier;
    char lignes[1000][512];
    int nombre_lignes = 0;
    fichier = fopen("clients.txt", "r");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }
    while (fgets(lignes[nombre_lignes], sizeof(lignes[nombre_lignes]), fichier) != NULL) {
        nombre_lignes++;
    }
    fclose(fichier);

    printf("Donner votre id à supprimer : ");
    scanf("%d", &id1);

    fichier = fopen("clients.txt", "w");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    for (int i = 0; i < nombre_lignes; i++) {
        int id_fichier;
        if (sscanf(lignes[i], "Client ID: %d", &id_fichier) == 1) {
            if (id_fichier != id1) {
                fputs(lignes[i], fichier);
            } else {
                trouve = 1;
            }
        }
    }

    fclose(fichier);

    Client *courant = tete_clients, *precedent = NULL;
    while (courant != NULL) {
        if (courant->id == id1) {
            if (precedent == NULL) {
                tete_clients = courant->suiv;
            } else {
                precedent->suiv = courant->suiv;
            }
            free(courant);
            break;
        }
        precedent = courant;
        courant = courant->suiv;
    }

    if (trouve) {
        printf("Client supprime avec succes !\n");
    } else {
        printf("Aucun client trouve avec cet ID.\n");
    }
}
// Calcul de la distance entre deux points
float calculer_distance(float x1, float y1, float x2, float y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

// Tri des distances avec leurs indices (Tri à bulles)
void trier_distances(float distances[], int indices[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (distances[j] > distances[j + 1]) {
                float temp_dist = distances[j];
                distances[j] = distances[j + 1];
                distances[j + 1] = temp_dist;

                int temp_index = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = temp_index;
            }
        }
    }
}



// Afficher le chauffeur le plus proche
Chauffeur* afficher_chauffeur_plus_proche(float client_x, float client_y) {
    int nombre_chauffeurs_disponibles = 0;
    Chauffeur* courant = tete_chauffeurs;

    if (courant == NULL) {
        printf("La liste des chauffeurs est vide.\n");
        return NULL;
    }

    printf("Verification des chauffeurs disponibles...\n");

    while (courant != NULL) {
        if (strcmp(courant->etat, "oui") == 0) {
            printf("Chauffeur disponible trouvee : ID %d\n", courant->id);
            nombre_chauffeurs_disponibles++;
        }
        courant = courant->suiv;
    }
    if (nombre_chauffeurs_disponibles == 0) {
        printf("----------------\n");
        printf("Desole, emchi 3la segik.\n");
        printf("----------------\n");
        return NULL;
    }
    float* distances = malloc(nombre_chauffeurs_disponibles * sizeof(float));
    Chauffeur** chauffeurs = malloc(nombre_chauffeurs_disponibles * sizeof(Chauffeur*));
    int* indices = malloc(nombre_chauffeurs_disponibles * sizeof(int));

    courant = tete_chauffeurs;
    int i = 0;
    while (courant != NULL) {
        if (strcmp(courant->etat, "oui") == 0) {
            distances[i] = calculer_distance(client_x, client_y, courant->x, courant->y);
            chauffeurs[i] = courant;
            indices[i] = i;
            i++;
        }
        courant = courant->suiv;
    }
    trier_distances(distances, indices, nombre_chauffeurs_disponibles);

    Chauffeur* chauffeur_proche = chauffeurs[indices[0]];
    printf("----------------\n");
    printf("Le chauffeur le plus proche est : %s %s, avec la matricule : %s\n",
           chauffeur_proche->nom, chauffeur_proche->prenom, chauffeur_proche->matricule);
    printf("----------------\n");

    free(distances);
    free(chauffeurs);
    free(indices);

    return chauffeur_proche;
}

// Calcul du prix de la course
float calculer_prix_course(float client_x, float client_y) {
    float destination_x, destination_y;
    printf("Entrez la coordonnee X de votre destination : ");
    scanf("%f", &destination_x);
    printf("Entrez la coordonnee Y de votre destination : ");
    scanf("%f", &destination_y);

    float distance_client_destination = calculer_distance(client_x, client_y, destination_x, destination_y);

    Chauffeur* chauffeur_proche = afficher_chauffeur_plus_proche(client_x, client_y);
    float distance_chauffeur_client = 0;

    if (chauffeur_proche != NULL) {
        distance_chauffeur_client = calculer_distance(client_x, client_y, chauffeur_proche->x, chauffeur_proche->y);
        float prix_total = ((distance_client_destination + distance_chauffeur_client) * 800) + 1000;
        return prix_total;
    }else {
        return -1;
    }

}
// affichier tous les clients
void afficher_clients() {
    char ch[512];
    FILE *out;
    out = fopen("clients.txt", "r");
    if (out == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }
    printf("---------------------------\n");
    printf("Liste des clients:\n");
    while(fgets(ch, sizeof(ch), out) != NULL) {
        printf("%s", ch);
    }
    printf("---------------------------\n");
    fclose(out);
}
// afficher tous les chauffeurs
void afficher_chauffeurs() {
    char ch[512];
    FILE *out;
    out = fopen("chauffeurs.txt", "r");
    if (out == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }
    printf("---------------------------\n");
    printf("Liste des chauffeurs:\n");
    while(fgets(ch, sizeof(ch), out) != NULL) {
        printf("%s", ch);
    }
    printf("---------------------------\n");
    fclose(out);
}
// récuperer les données après le redemarrage
void recup_donnees() {
    FILE *out1, *out2;
    char ligne[512];
    char id[8], nom[30], prenom[30], num_tel[8], matricule[20], etat[10];
    float x, y;

    out1 = fopen("clients.txt", "r");
    if (out1 != NULL) {
        while (fgets(ligne, sizeof(ligne), out1) != NULL) {
            if (sscanf(ligne, "Client ID: %s, Nom: %[^,], Prenom: %[^,], Num Tel: %s",
                       id, nom, prenom, num_tel) == 4) {
                if (chercher_client(tete_clients, id) == 0) {
                    Client* nouv_client = (Client*)malloc(sizeof(Client));
                    if (nouv_client != NULL) {
                        strcpy(nouv_client->id, id);
                        strcpy(nouv_client->nom, nom);
                        strcpy(nouv_client->prenom, prenom);
                        strcpy(nouv_client->num_tel, num_tel);
                        nouv_client->suiv = tete_clients;
                        tete_clients = nouv_client;
                    }
                }
                       }
        }
        fclose(out1);
    }

    out2 = fopen("chauffeurs.txt", "r");
    if (out2 != NULL) {
        while (fgets(ligne, sizeof(ligne), out2) != NULL) {
            if (sscanf(ligne, "Chauffeur ID: %d, Nom: %[^,], Prenom: %[^,], Num Tel: %[^,], Matricule: %[^,], x: %f, y: %f, etat: %[^,]",
                       id, nom, prenom, num_tel, matricule, &x, &y, etat) == 8) {
                if (chercher_chauffeur(tete_chauffeurs, id) == 0) {
                    Chauffeur* nouv_chauffeur = (Chauffeur*)malloc(sizeof(Chauffeur));
                    if (nouv_chauffeur != NULL) {
                        strcpy(nouv_chauffeur->id, id);
                        strcpy(nouv_chauffeur->nom, nom);
                        strcpy(nouv_chauffeur->prenom, prenom);
                        strcpy(nouv_chauffeur->num_tel, num_tel);
                        strcpy(nouv_chauffeur->matricule, matricule);
                        nouv_chauffeur->x = x;
                        nouv_chauffeur->y = y;
                        strcpy(nouv_chauffeur->etat, etat);
                        nouv_chauffeur->suiv = tete_chauffeurs;
                        tete_chauffeurs = nouv_chauffeur;
                    }
                }
            }
        }
        fclose(out2);
    }
}

// une page de bienvenue
void welcome_page(){
    time_t t;
    time(&t);
    printf("                                                                                                         \n");
    printf("---------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\t%s",ctime(&t));
    printf("---------------------------------------------------------------------------------------------------------\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t**********************************\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t|\t     WELCOME TO \t |\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t|\t       E-Uber\t         |\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t**********************************\t\t\t\t\t\t|\n");
    printf("|\t\t\t\    REALISED BY: JOUINI BECEM & KACEM WAEL   \t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t     ENSI\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t      \"TIME IS PRECIOUS.WE MAKE YOUR LIFE EASIER.\"\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|Press any key to continue.........\t\t\t\t\t\t\t\t\t\t|\n");

    printf("---------------------------------------------------------------------------------------------------------\n");
    getch();
    system("cls");
}
int main() {
    recup_donnees();
    welcome_page();
    int choix;
    int confirmation;
    do {
        printf("\n===== Menu principal =====\n");
        printf("1. Ajouter un client\n");
        printf("2. Modifier un client\n");
        printf("3. Supprimer un client\n");
        printf("4. Afficher les clients\n");
        printf("5. Ajouter un chauffeur\n");
        printf("6. Modifier un chauffeur\n");
        printf("7. Supprimer un chauffeur\n");
        printf("8. Afficher les chauffeurs\n");
        printf("9. Calculer le prix d'une course\n");
        printf("10. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:{
                system("cls");
                ajout_client();
                break;
            }
            case 2: {
                system("cls");
                modifier_client();
                break;
            }
            case 3: {
                system("cls");
                supprimer_client();
                break;
            }
            case 4: {
                afficher_clients();
                break;
            }
            case 5: {
                system("cls");
                ajout_chauffeur();
                break;
            }
            case 6: {
                system("cls");
                modifier_chauffeur();
                break;
            }
            case 7: {
                system("cls");
                supprimer_chauffeur();
                break;
            }
            case 8: {
                afficher_chauffeurs();
                break;
            }
            case 9: {
                system("cls");
                float client_x, client_y;
                printf("Entrez votre position x : ");
                scanf("%f", &client_x);
                printf("Entrez votre position y : ");
                scanf("%f", &client_y);
                if(afficher_chauffeur_plus_proche(client_x, client_y)!=NULL) {
                    float prix = calculer_prix_course(client_x, client_y);
                    printf("Le prix de la course est : %f Millimes\n", prix);
                    printf("1. pour confirmer\n");
                    printf("0. pour annuler\n");
                    printf("donner votre confirmation:");
                    scanf("%d", &confirmation);
                    if(confirmation == 1) {
                        printf("le chauffeur est en route!");
                    }else {
                        printf("transaction annulee");
                    }
                }
                break;
            }
            case 10: {
                printf("Au revoir !\n");
                break;
            }
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while (choix != 10);

    return 0;
}