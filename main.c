#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

                         /***********************************************************/
                         /***********************************************************/
                         /***********************************************************/
                         /*                     hassan ettahiri                     */
                         /***********************************************************/
                         /***********************************************************/
                         /***********************************************************/


FILE *pvoi=NULL;
FILE *ptr=NULL;
FILE *p=NULL;
FILE *pcon=NULL;



typedef struct date{
    int jour;
    int mois;
    int annee;
}date;
typedef struct voiture{
    int idVoiture;
    char marque[15];
    char nomVoiture[15];
    char couleur[7];
    int nbplaces;
    int prixJour;
    char enLocation[4];
}voiture;
typedef struct contratLocation{
    float numContrat;
    int idVoiture;
    int idClient;
    date debut;
    date fin;
    int cout;
}contrat;
typedef struct client{
    int idClient;
    char nom[20];
    char prenom[20];
    int cin;
    char adress[15];
    int telephone;
}client;

int compnameclient(client *cl, char name[],char prename[]);
int compVoiture(voiture *ve, int id);
int enlocation_prixjour(voiture *ve,int id);
int idname(client *cl,char name[],char prename[]);
void enlocation(voiture *ve,int id);


void Location(){
    contrat *cn=NULL;
    client *cl=NULL;
    voiture *ve=NULL;
    int n;
    int id,det;
    while(1){
        do{
            printf("\n\t\tlocation d'une voiture\n\n");
            printf("\tVisualiser contrat....................1\n");
            printf("\tLouer voiture.........................2\n");
            printf("\tRetourner voiture.....................3\n");
            printf("\tModifier contrat......................4\n");
            printf("\tsupprimer contrat.....................5\n");
            printf("\tRetour................................6\n\n");
            printf("\t\tVotre choix   :   ");
            scanf("%d",&n);
            system("cls");
        }while(n<1 || n>6);
        switch(n){
            case 1:visualiserContrat(&cn);break;
            case 2:louerVoiture(&cn,&ve,&cl);break;
            case 3:retournerVoiture(&cn,&ve);break;
            case 4:modifierContrat(&cn,&ve);break;
            case 5:printf("\n\t-------------------- SUPPRIMER VOITURE: --------------------\n");
            printf("\n\tsaisir le numero de contrat a supprimer: ");
            scanf("%d",&id);
            supprimerContrat(&cn,&ve,id);
            system("cls");
            break;
            default:main();break;
        }
    }
}
void visualiserContrat(contrat *cn){
    int i=0;
    pcon=fopen("contrat.txt","rb");
    printf("\n\t-------------- LISTE DE CONTRAT: --------------\n");
    while(fread(cn,sizeof(contrat),1,pcon)==1){
        printf("\n\t ********* numero de contrat %.2f: *********\n",cn->numContrat);
        printf("\t - id de la voiture           : %d\n",cn->idVoiture);
        printf("\t - id de client               : %d\n",cn->idClient);
        printf("\t - la date de debut           : %d/%d/%d\n",cn->debut.jour,cn->debut.mois,cn->debut.annee);
        printf("\t - la date du fin             : %d/%d/%d\n",cn->fin.jour,cn->fin.mois,cn->fin.annee);
        printf("\t - le cout total              : %d DH\n",cn->cout);
        i++;
    }
    if(i==0){
        printf("\n\t ==> PAS DE contrat...");
        sleep(2);
        system("cls");
        Location(&cn);
    }
    system("pause");
    printf("\n");
    fclose(pcon);
    system("cls");
}
int jourcalc(int jourdeb,int moisdeb,int anneedeb,int jourend,int moisend,int anneeend){
    int result,debut,fin,somme=0,i,test=jourdeb;
    int mois[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    for(i=0;i<=moisdeb-2;i++){
        somme+=mois[i];
    }
    debut=somme+test;
    somme=0;
    for(i=0;i<=moisend-2;i++){
        somme+=mois[i];
    }
    fin=somme+jourend+((anneeend-anneedeb)*365.25);
    result=fin-debut;
    return result;
}
void louerVoiture(contrat *cn,voiture *ve,client *cl){
    system("cls");
    pcon=fopen ("contrat.txt", "ab");
    int conteur1=0,conteur2=0;
    char cnom[20],cpre[20];
    printf("\n\t-------------------- LOUER VOITURE: --------------------\n");
    p=fopen("client.txt","rb");
    printf("\n\t********* LISTE DE CLIENT: *********\n");
    while(fread(cl,sizeof(struct client),1,p)==1){
        printf("id: %d    nom: %s    prenom: %s    CIN: %d    adress: %s    tel: 0%d\n",cl->idClient,cl->nom,cl->prenom,cl->cin,cl->adress,cl->telephone);
    }
    fseek(pvoi,0,SEEK_SET);
    printf("\n\t ==>Saisir le nom: ");
    scanf("%s",cnom);
    printf("\t ==>Saisir le prenom :");
    scanf("%s",cpre);
    p=fopen("client.txt","rb");
    int idclient=0;
    fseek(p,0,SEEK_SET);
    while(fread(cl,sizeof(struct client),1,p)==1){
        if(strcmp(cl->nom,cnom)==0 && strcmp(cl->prenom,cpre)==0){
                conteur1=1;
        }
    }
    system("cls");
    printf("\n\t-------------------- LOUER VOITURE: --------------------\n");
    if(conteur1==1){
            int ID;
            printf("\n\tclient a ete detectee avec succes...");
            sleep(2);
            system("cls");
            int test;
            do{
            printf("\n\t-------------------- LOUER VOITURE: --------------------\n");
            printf("\n\t********* LISTE DE VOITURE: *********\n");
            pvoi=fopen("voiture.txt","rb");
            while(fread(ve,sizeof(struct voiture),1,pvoi)==1){
                printf("id: %d    marque: %s    nom: %s    couleur: %s    nbplaces: %d    prixjour: %ddh   location: %s\n",ve->idVoiture,ve->marque,ve->nomVoiture,ve->couleur,ve->nbplaces,ve->prixJour,ve->enLocation);
            }
            fseek(pvoi,0,SEEK_SET);
            printf("\n\tsaisir l'id de la voiture: ");
            scanf("%d",&ID);
            while(fread(ve,sizeof(voiture),1,pvoi)==1){
                if(ID==ve->idVoiture)
                {
                    conteur2=1;
                    break;
                }
            }
            system("cls");
            printf("\n\t-------------------- LOUER VOITURE: --------------------\n");
            if(conteur2==1){
                    printf("\n\t LA VOITURE A ETE DETECTE AVEC SUCCES...");
                    sleep(2);
                    system("cls");
                    test=0;
                    printf("\n\t-------------------- LOUER VOITURE: --------------------\n");
                    if(strcmp(ve->enLocation,"non") == 0){
                        float cnt;
                        printf("\n\tCETTE VOITURE EST DISPONIBLE .... Veuiller terminer les etapes suivant:");
                        sleep(4);
                        system("cls");
                        printf("\n\t-------------------- LOUER VOITURE: --------------------\n");
                        printf("\n\t entrer le numero de contrat : ");
                        scanf("%f",&cnt);
                        fseek(pvoi,0,SEEK_SET);
                        while(fread(cl,sizeof(client),1,p)==1){
                            if(strcmp(cl->nom,cnom)==0 && strcmp(cl->prenom,cpre)==0){
                                break;
                            }
                        }
                        cn->idClient=compnameclient(&cl,cnom,cpre) ;
                        int prix=ve->prixJour;
                        cn->idVoiture=ID ;
                        printf("\n\tsaisir la date de debut de location (jj/mm/aa): ");
                        printf("\n\tjj: ");scanf("%d",&cn->debut.jour);printf("\tmm: ");scanf("%d",&cn->debut.mois);printf("\taa: ");scanf("%d",&cn->debut.annee);
                        printf("\n\tsaisir la date de la fin de location (jj/mm/aa): ");
                        printf("\n\tjj: ");scanf("%d",&cn->fin.jour);fflush(stdin);
                        printf("\tmm: ");scanf("%d",&cn->fin.mois);fflush(stdin);
                        printf("\taa: ");scanf("%d",&cn->fin.annee);fflush(stdin);
                        cn->cout = jourcalc(cn->debut.jour,cn->debut.mois,cn->debut.annee,cn->fin.jour,cn->fin.mois,cn->fin.annee)*prix ;
                        cn->numContrat=cnt;
                        system("cls");
                        printf("\n\t-------------------- LOUER VOITURE: --------------------\n");
                        printf("\n\tCONTACT A ETE AJOUTER AVEC SUCCES...");
                        sleep(3);
                        system("cls");
                        fwrite (cn,sizeof(contrat),1,pcon);
                        fclose(pvoi);
                        enlocation(&ve,ID);
                    }else{
                        printf("\n\tCETTE VOITURE N'EST PAS DISPONIBLE  \n");
                        sleep(2);
                        system("cls");
                        printf("\n\t-------------------- LOUER VOITURE: --------------------\n");
                        printf("\n\tvouler vous choisir une autre voiture:");
                        printf("\n\t   1-oui       0-non(retour au menu)");
                        printf("\n\t        votre choix: ");
                        scanf("%d",&test);
                        system("cls");
                    }
                }else{
                printf("\tCETTE VOITURE N'EXISTE PAS  \n");
                sleep(3);
                system("cls");
                Location();
                }
            }while(test==1);
            }else{
                int choix;
                printf("\n\tCE NOM N'EXISTE PAS!!!!!\n");
                sleep(3);
                system("cls");
                printf("\n\t-------------------- LOUER VOITURE: --------------------\n");
                printf("\n\tvous voulez enregister ses information: \n");
                printf("\t  1-oui           0-non(retour au menu)\n");
                printf("\t           votre choix: ");
                scanf("%d",&choix);
                system("cls");
                if(choix==1){
                    fclose(p);fclose(pcon);
                    gestionClient();
                }
        }

    fclose(p);fclose(pcon);fclose(pvoi);
}
void retournerVoiture(contrat *cn,voiture *ve){
    int id,idvoiture=0;
    printf("\n\tsaisir le numero de contrat a retourner: ");
    scanf("%d",&id);
    pcon=fopen("contrat.txt","rb+");
    while(fread(cn,sizeof(contrat),1,pcon)==1){
        if(cn->numContrat==id){
            idvoiture=cn->idVoiture;
            break;
        }
    }
    fclose(pcon);
    if(idvoiture==0){
        printf("\n\tcette contrat n'exixte pas...");
        sleep(2);
    }else{
        printf("\n\t-------------------- SUPPRIMER VOITURE: --------------------\n");
        supprimerContrat(&cn,&ve,id);
        enlocation(&ve,idvoiture);
        printf("\n\tmerci de retourner la voiture!");
        sleep(2);
    }
    Location();
}
int poscontrat(contrat *cn,int id){
    pcon=fopen("contrat.txt","rb");
    int pos=0;
    while(fread(cn,sizeof(contrat),1,pcon)==1){
        if(id==cn->numContrat){
            fclose(pcon);
            return pos;
        }else pos++;
    }
    fclose(pcon);
    return -1;
}
void modifierContrat(contrat *cn,voiture *ve){
    int numcon,pos;
    int choix,c=0;
    printf("\n\t-------------- MODIFIER CONTRAT: --------------\n");
    printf("\n\tsaisir le numero de contrat a modifier: ");
    scanf("%d",&numcon);
    pcon=fopen("contrat.txt","rb+");
    pos=poscontrat(&cn,numcon);
    if(pos<0){
        printf("\n\t==>AUCUNE VOITURE AVEC CETTE ID...");
        sleep(2);
        system("cls");
        Location();
    }else{
        fseek(pcon,pos*sizeof(contrat),SEEK_SET);
        fread(cn,sizeof(contrat),1,pcon);
        system("cls");
        printf("\n\t-------------- MODIFIER CONTRAT: --------------\n");
        printf("\n\tsaisir la date de la fin de location (jj/mm/aa): ");
        printf("\n\t jj: ");
       // fflush(stdin);
        scanf("%d",&cn->fin.jour);
        printf("\t mm: ");
       // fflush(stdin);
        scanf("%d",&cn->fin.mois);
        printf("\t aa: ");
        fflush(stdin);
        scanf("%d",&cn->fin.annee);
        fflush(stdin);
        cn->cout=jourcalc(cn->debut.jour,cn->debut.mois,cn->debut.annee,cn->fin.jour,cn->fin.mois,cn->fin.annee)*enlocation_prixjour(&ve,cn->idVoiture);
        fseek(pcon, -sizeof(contrat), SEEK_CUR);
        fwrite(cn, sizeof(contrat), 1, pcon);
        system("cls");
        printf("\n\t-------------- MODIFIER CONTRAT: --------------\n");
        printf("\n\t ==> MODIFICATION AVEC SUCCES...");
        sleep(2);
        system("cls");
        fclose(pcon);
        Location();
    }
}
void supprimerContrat(contrat *cn,voiture *ve,int id){
    int detect=0;
    pcon=fopen("contrat.txt","rb");
    FILE *ptr1=NULL;
    ptr1=fopen("tempo.txt","wb");
    while(fread(cn,sizeof(contrat),1,pcon)==1){
        printf("1");
        if(cn->numContrat==id){
            detect=cn->idVoiture;
        }else{
            fwrite(cn,sizeof(contrat),1,ptr1);
        }
    }
    system("cls");
    if(detect>0){
        fclose(pcon);
        fclose(ptr1);
        remove("contrat.txt");
        rename("tempo.txt","contrat.txt");
        printf("\n\tSUPPRISSION AVEC SUCCES...");
        sleep(2);

    }else{
        fclose(pcon);
        fclose(ptr1);
        remove("tempo.txt");
        printf("\n\tPAS DE NUMERO DE CONTRAT AVEC CETTE ID %d...");
        sleep(2);
    }
    enlocation(&ve,detect);
}


void gestionVoiture(){
    voiture *ve=NULL;
    int n;
    while(1){
        do{printf("\n\t\tGestion des voitures\n\n");
            printf("\tListes des voitures............1\n");
            printf("\tAjouter voiture................2\n");
            printf("\tModifier voiture...............3\n");
            printf("\tSupprimer voiture..............4\n");
            printf("\tRetour.........................5\n\n");
            printf("\t\tVotre choix   :   ");
            scanf("%d",&n);
            system("cls");
        }while(n<1 || n>5);
        switch(n){
            case 1:listeVoiture(&ve);break;
            case 2:ajouterVoiture(&ve); break;
            case 3:modifierVoiture(&ve);break;
            case 4:suppVoiture(&ve);break;
            default:main();break;
        }

    }
}
void listeVoiture(voiture *ve){
    int i=0;
    pvoi=fopen("voiture.txt","rb");
    printf("\n\t-------------- LISTE DE VOITURE: --------------\n");
    while(fread(ve,sizeof(struct voiture),1,pvoi)==1){
        printf("\n\t ********* LA VOITURE %d: *********\n",ve->idVoiture);
        printf("\t - La marque           : %s\n",ve->marque);
        printf("\t - Le nom              : %s\n",ve->nomVoiture);
        printf("\t - La couleur          : %s\n",ve->couleur);
        printf("\t - Le nombre de place  : %d\n",ve->nbplaces);
        printf("\t - Le prix du jour     : %d DH\n",ve->prixJour);
        printf("\t - En location         : %s\n\n",ve->enLocation);
        i++;
    }
    if(i==0){
        printf("\n\t ==> PAS DE VOITURE... VEUILLER AJOIUTER DES VOITURE!!!");
        sleep(2);
        system("cls");
        gestionVoiture();
    }
    system("pause");
    printf("\n");
    fclose(pvoi);
    system("cls");
}
int compVoiture(voiture *ve, int id){
    while(fread(ve,sizeof(struct voiture),1,pvoi)==1){
                if(id==ve->idVoiture){
                    return 1;
                }
            }
            return 0;
}
void enlocation(voiture *ve,int id){
    int temp=0;
    int i=0;
    pvoi=fopen("voiture.txt","rb");
    FILE *ptr=NULL;
    ptr=fopen("temp.txt","wb");
    while(fread(ve,sizeof(struct voiture),1,pvoi)==1){
                if(id==ve->idVoiture){
                    if(strcmp(ve->enLocation,"non")==0){
                        i=1;
                        strcpy(ve->enLocation,"oui");
                        fwrite(ve,sizeof(struct voiture),1,ptr);
                    }else{
                        i=1;
                        strcpy(ve->enLocation,"non");
                        fwrite(ve,sizeof(struct voiture),1,ptr);
                    }
                }else{
                    fwrite(ve,sizeof(struct voiture),1,ptr);
                }
            }
            fclose(ptr);
            fclose(pvoi);
            if(i==1){
                remove("voiture.txt");
                rename("temp.txt","voiture.txt");
            }else remove("temp.txt");
}
int enlocation_prixjour(voiture *ve,int id){
    pvoi=fopen("voiture.txt","rb");
    while(fread(ve,sizeof(struct voiture),1,pvoi)==1){
            if(id==ve->idVoiture){
                fclose(pvoi);
                if(strcmp(ve->enLocation,"non")==0)return ve->prixJour;
            }
    }
    fclose(pvoi);
    return 0;
}
void ajouterVoiture(voiture *ve){
    int on;
    int newId;
    int n,i;
    int test;
    pvoi=fopen("voiture.txt","ab+");
            printf("\n\t-------------- AJOUTER VOITURE: --------------\n");
            printf("\n\tsaisir l'ID de la voiture: ");
            scanf("%d",&newId);
            if(compVoiture(ve,newId)==1){
                system("cls");
                printf("\n\t-------------- AJOUTER VOITURE: --------------\n");
                printf("\n\tL'ID %d DEJA EXISTE...VEUILLER SAISIR UN AUTRE ID.",newId);
                sleep(3);
                system("cls");
                ajouterVoiture(&ve);
                gestionVoiture();
            }else{
                ve->idVoiture=newId;
            }
            do{
                printf("\n\tsairir la marque de la voiture (max: 15 caractere): ");
                fflush(stdin);
                scanf("%s",ve->marque);
            }while(strlen(ve->marque)>15);
            do{
                printf("\n\tsaisir le nom de la voiture (max: 15 caractere): ");
                fflush(stdin);
                scanf("%s",ve->nomVoiture);
            }while(strlen(ve->nomVoiture)>15);
            do{
                printf("\n\tsaisir la couleur de voiture (max: 7 caractere): ");
                fflush(stdin);
                scanf("%s",ve->couleur);
            }while(strlen(ve->couleur)>7);
            printf("\n\t saisir nombres de places: ");
            scanf("%d",&ve->nbplaces);
            printf("\n\tsaisir le prix de jours: ");
            scanf("%d",&ve->prixJour);
            strcpy(ve->enLocation,"non");
            printf("\n\t_______________________________\n");
            fwrite(ve,sizeof(struct voiture),1,pvoi);
            system("cls");
            printf("\n\t-------------- AJOUTER VOITURE: --------------\n");
            printf("\n\t   ==>CREATION AVEC SUCCES...!\n");
            sleep(2);
            system("cls");
            printf("\n\t-------------- AJOUTER VOITURE: --------------\n");
            printf("\n\t==>vouler vous ajouter une autre voiture:  ");
            printf("\n\t 0-non                         1-oui");
            printf("\n\t             votre choix:");
            scanf("%d",&on);
            system("cls");
            if(on==1){
                fclose(pvoi);
                ajouterVoiture(&ve);
            }else{
                fclose(pvoi);
                system("cls");
                gestionVoiture();
            }

}
int rechercherVoiture(voiture *ve, int id){
    pvoi = fopen("voiture.txt","rb");
    int pos=0;
    while(fread(ve, sizeof(struct voiture), 1, pvoi)==1){
        if(ve->idVoiture==id){
            fclose(pvoi);
            return pos;
        }else pos++;
    }
    fclose(pvoi);
    return -1;
}
void modifierVoiture(voiture *ve){
    int pos;
    int id;
    int newId;
    printf("\n\t-------------- MODIFIER VOITURE: --------------\n");
    printf("\n\t ==> Veuiller entrer l'id de la voiture a modifier: ");
    scanf("%d",&id);
    system("cls");
    pos = rechercherVoiture(ve,id);
    pvoi = fopen("voiture.txt","rb+");
    if(pos < 0){
        printf("\n\t ==> AUCUNE VOITURE AVEC L'ID %d ...",id);
        sleep(3);
        fclose(pvoi);
        system("cls");
        gestionVoiture();
    }else{
        fseek(pvoi, pos*sizeof(struct voiture), SEEK_SET);
        fread(ve,sizeof(struct voiture),1,pvoi);
        int c=0;
        int choix,newId,n;
        while(1){
            do{
                printf("\n\t-------------- MODIFIER VOITURE: --------------\n");
                printf("\n\t 1- changer la marque.");
                printf("\n\t 2- changer le nom.");
                printf("\n\t 3- changer la couleur.");
                printf("\n\t 4- changer le nombre de place.");
                printf("\n\t 5- changer le prix du jour.");
                printf("\n\t 6- retour.");
                printf("\n\t       votre choix : ");
                scanf("%d",&choix);
                system("cls");
            }while(choix < 0 || choix > 6);
                if(choix==1){
                    do{
                        printf("\n\t-------------- MODIFIER VOITURE: --------------\n");
                        printf("\n\t => la nouvelle marque de la voiture: ");scanf("%s",ve->marque);c++;
                        system("cls");
                    }while(strlen(ve->marque)>15);
                }
                else if(choix==2){
                    do{
                        printf("\n\t-------------- MODIFIER VOITURE: --------------\n");
                        printf("\n\t => le nouveau nom de la voiture: ");scanf("%s",ve->nomVoiture);c++;
                        system("cls");
                    }while(strlen(ve->nomVoiture)>15);
                }
                else if(choix==3){
                    do{
                        printf("\n\t-------------- MODIFIER VOITURE: --------------\n");
                        printf("\n\t => la nouvelle couleur de la voiture: ");scanf("%s",ve->couleur);c++;
                        system("cls");
                    }while(strlen(ve->couleur)>7);
                }
                else if(choix==4){
                    printf("\n\t-------------- MODIFIER VOITURE: --------------\n");
                    printf("\n\t => le nouveaule nombre de place: ");scanf("%d",&ve->nbplaces);c++;
                }
                else if(choix==5){
                    printf("\n\t-------------- MODIFIER VOITURE: --------------\n");
                    printf("\n\t => le nouveau le prix du jour: ");scanf("%d",&ve->prixJour);c++;
                }
                else if(choix==6){
                    if(c!=0){
                        system("cls");
                        printf("\n\t-------------- MODIFIER VOITURE: --------------\n");
                        printf("\n\t ==> MODIFICATION AVEC SUCCES...");
                        sleep(2);
                        system("cls");
                        fseek(pvoi, -sizeof(struct voiture), SEEK_CUR);
                        fwrite(ve, sizeof(struct voiture), 1, pvoi);
                        fclose(pvoi);
                    }else{
                        system("cls");
                        printf("\n\t-------------- MODIFIER VOITURE: --------------\n");
                        printf("\n\t ==> PAS DE MODIFICATION...");
                        sleep(2);
                        system("cls");
                        fclose(pvoi);
                    }
                    return 0;
                }
        system("cls");

        }
    }
}
void suppVoiture(voiture *ve) {
    int id,choix;
    int detection=0;
    printf("\n\t-------------- SUPPRIMER VOITURE: --------------\n");
    do{
        printf("\n\t 1- supprimer tous les voiture.");
        printf("\n\t 2- supprimer une voiture par id.");
        printf("\n\t 3- retourner au menu.");
        printf("\n\t            votre choix: ");
        scanf("%d",&choix);
    }while(choix < 1 || choix > 3);
    system("cls");
    printf("\n\t-------------- SUPPRIMER VOITURE: --------------\n");
    if(choix == 2){
        printf("\n\t ==> saisir l'id de la voiture a supprimer :  ");
        scanf("%d",&id);
        system("cls");
        printf("\n\t-------------- SUPPRIMER VOITURE: --------------\n");
        pvoi = fopen("voiture.txt","rb");
            ptr = fopen("voiture1.txt","wb");
                while(fread(ve,sizeof(struct voiture),1,pvoi)==1){
                    if(ve->idVoiture==id){
                        printf("\n\t ==> LA VOITURE D'ID %d A ETE SUPPRIMEE AVEC SUCCES!!!",id);
                        sleep(3);
                        detection=1;
                    }else{
                        fwrite(ve,sizeof(struct voiture),1,ptr);
                    }
                }
            fclose(pvoi);
            fclose(ptr);
            if(detection=1){
                remove("voiture.txt");
                rename("voiture1.txt","voiture.txt");
            }else{
                remove("voiture1.txt");
            }
        system("cls");
        printf("\n\t-------------- SUPPRIMER VOITURE: --------------\n");
    }else if(choix==1){
        remove("voiture.txt");
        printf("\n\t ==> TOUS LES VOITURES SONT SUPPRIMER AVEC SUCCES...");
        sleep(3);
    }
    system("cls");
}


void gestionClient(){
    client *cl=NULL;
    int n;
    while(1){
        do{
            printf("\n\t\tgestion des client\n\n");
            printf("\tListe des clients..................1\n");
            printf("\tAjouter client.....................2\n");
            printf("\tModifier client....................3\n");
            printf("\tSupprimer client...................4\n");
            printf("\tRetour.............................5\n\n");
            printf("\t\tVotre choix   :   ");
            scanf("%d",&n);
            system("cls");
        }while(n<1 || n>5);
        switch(n){
            case 1:listeClient(&cl);break;
            case 2:ajouterClient(&cl);break;
            case 3:modifierClient(&cl);break;
            case 4:suppClient(&cl);break;
            default:main();break;
        }
    }
}
void listeClient(client *cl){
    int i=0;
    p=fopen("client.txt","rb");
    printf("\n\t-------------------- LISTE DE CLIENT: --------------------\n");
    while(fread(cl,sizeof(struct client),1,p)==1){
        printf("\n\t ************** Le client %d: **************\n",cl->idClient);
        printf("\t - Le nom                    : %s\n",cl->nom);
        printf("\t - Le prenom                 : %s\n",cl->prenom);
        printf("\t - Le CIN                    : %d\n",cl->cin);
        printf("\t - L'adress                  : ");puts(cl->adress);
        printf("\t - Le numero de telephone    : +212%d\n\n",cl->telephone);
        i++;
    }
    if(i==0){
        printf("\n\t ==> PAS DE CLIENT... VEUILLER AJOIUTER DES CLIENTS!!!");
        sleep(2);
        system("cls");
        gestionClient();
    }
    system("pause");
    printf("\n");
    fclose(p);
    system("cls");
}
int idname(client *cl,char name[],char prename[]){
    p=fopen("client.txt","rb");
    while(fread(cl,sizeof(struct client),1,p)==1){
        if(strcmp(cl->nom,name)==0 && strcmp(cl->prenom,prename)==0){
            fclose(p);
            return cl->idClient;

        }
    }
    fclose(p);
    return 0;
}
int compClient(client *cl, int idClient){
    while(fread(cl,sizeof(struct client),1,p)==1){
        if(idClient==cl->idClient){
            return 1;
        }
    }
    return 0;
}
int compnameclient(client *cl, char name[],char prename[]){
    p=fopen("client.txt","rb");
    while(fread(cl,sizeof(struct client),1,p)==1){
        if((strcmp(cl->nom,name)==0) && (strcmp(cl->prenom,prename)==0)){
            fclose(p);
            return cl->idClient;
        }
    }
    fclose(p);
    return 0;
}
void ajouterClient(client *cl){
    int on;
    int n,i;
    int clientId;
    p=fopen("client.txt","ab+");
            printf("\n\t-------------- AJOUTER CLIENT: --------------\n");
            printf("\n\t saisir l'id du client: ");
            scanf("%d",&clientId);
            if(compClient(cl,clientId)==1){
                system("cls");
                printf("\n\t-------------- AJOUTER CLIENT: --------------\n");
                printf("\n\tL'ID %d DEJA EXISTE...VEUILLER SAISIR UN AUTRE ID.",clientId);
                sleep(3);
                system("cls");
                ajouterClient(&cl);
            }else{
                cl->idClient=clientId;
            }
            do{
                printf("\n\tsairir le nom du client (max: 20 caractere): ");
                scanf("%s",cl->nom);
                fflush(stdin);
            }while(strlen(cl->nom)>20);
            do{
                printf("\n\tsaisir le prenom du client (max: 20 caractere): ");
                scanf("%s",cl->prenom);
                fflush(stdin);
            }while(strlen(cl->prenom)>20);
            printf("\n\tsaisir le CIN du client: ");
            scanf("%d",&cl->cin);
            do{
                printf("\n\t saisir l'adress du client (max: 15 caractere): ");
                fflush(stdin);
                gets(cl->adress);
            }while(strlen(cl->adress)>15);
            printf("\n\tsaisir le numero de telephone du client: ");
            scanf("%d",&cl->telephone);
            printf("\n\t_______________________________\n");
            fwrite(cl,sizeof(struct client),1,p);
            system("cls");
            printf("\n\t-------------- AJOUTER CLIENT: --------------\n");
            printf("\n\t   ==>CREATION AVEC SUCCES...!\n");
            sleep(2);
            system("cls");
            printf("\n\t-------------- AJOUTER CLIENT: --------------\n");
            printf("\n\t==>vouler vous ajouter un autre client:  ");
            printf("\n\t 0-non                         1-oui");
            printf("\n\t             votre choix:");
            scanf("%d",&on);
            system("cls");
            if(on==1){
                fclose(p);
                ajouterClient(&cl);
            }else{
                fclose(p);
                system("cls");
                gestionClient();
            }

}
int rechercherClient(client *cl, int id){
    p = fopen("client.txt","rb");
    int pos=0;
    while(fread(cl, sizeof(struct client), 1, p)==1){
        if(cl->idClient==id){
            fclose(p);
            return pos;
        }else pos++;
    }
    fclose(p);
    return -1;
}
void modifierClient(client *cl){
    int pos;
    int id;
    printf("\n\t-------------- MODIFIER CLIENT: --------------\n");
    printf("\n\t ==> Veuiller entrer l'id de la voiture a modifier: ");
    scanf("%d",&id);
    system("cls");
    pos = rechercherClient(cl,id);
    p = fopen("client.txt","rb+");
    if(pos < 0){
        printf("\n\t ==> AUCUNE CLIENT AVEC L'ID %d ...",id);
        sleep(3);
        fclose(p);
        system("cls");
        gestionClient();
    }else{
        fseek(p, pos*sizeof(struct client), SEEK_SET);
        fread(cl,sizeof(struct client),1,p);
        int c=0;
        int choix;
        while(1){
            do{
                printf("\n\t-------------- MODIFIER CLIENT: --------------\n");
                printf("\n\t 1- changer le nom.");
                printf("\n\t 2- changer le prenom.");
                printf("\n\t 3- changer le CIN.");
                printf("\n\t 4- changer l'adress.");
                printf("\n\t 5- changer le numero de telephone.");
                printf("\n\t 6- retour.");
                printf("\n\t       votre choix : ");
                scanf("%d",&choix);
                system("cls");
            }while(choix < 0 || choix > 6);
                if(choix==1){
                    do{
                        printf("\n\t-------------- MODIFIER CLIENT: --------------\n");
                        printf("\n\t => le nouveau nom du client (max: 20 caractere): ");scanf("%s",cl->nom);c++;
                        system("cls");
                    }while(strlen(cl->nom)>20);
                }
                else if(choix==2){
                    do{
                        printf("\n\t-------------- MODIFIER CLIENT: --------------\n");
                        printf("\n\t => le nouveau prenom du client (max: 20 caractere): ");scanf("%s",cl->prenom);c++;
                        system("cls");
                    }while(strlen(cl->prenom)>20);
                }
                else if(choix==3){
                        printf("\n\t-------------- MODIFIER CLIENT: --------------\n");
                        printf("\n\t => le nouveau CIN du client: ");scanf("%d",&cl->cin);c++;
                }else if(choix==4){
                    do{
                        printf("\n\t-------------- MODIFIER CLIENT: --------------\n");
                        printf("\n\t => la nouvelle adress du client (max: 15 caractere): ");fflush(stdin);gets(cl->adress);c++;
                        system("cls");
                    }while(strlen(cl->adress)>15);
                }else if(choix==5){
                    printf("\n\t-------------- MODIFIER CLIENT: --------------\n");
                    printf("\n\t => le nouveau numero de telephone du client: ");scanf("%d",&cl->telephone);c++;
                }

                else if(choix==6){
                    if(c!=0){
                        system("cls");
                        printf("\n\t-------------- MODIFIER CLIENT: --------------\n");
                        printf("\n\t ==> MODIFICATION AVEC SUCCES...");
                        sleep(2);
                        system("cls");
                        fseek(p, -sizeof(struct client), SEEK_CUR);
                        fwrite(cl, sizeof(struct client), 1, p);
                        fclose(p);
                    }else{
                        system("cls");
                        printf("\n\t-------------- MODIFIER CLIENT: --------------\n");
                        printf("\n\t ==> PAS DE MODIFICATION...");
                        sleep(2);
                        system("cls");
                        fclose(p);
                    }
                }
        system("cls");

        }
    }
}
void suppClient(client *cl){
    int id,choix;
    int detection=0;
    printf("\n\t-------------- SUPPRIMER CLIENT: --------------\n");
    do{
        printf("\n\t 1- supprimer tous les client.");
        printf("\n\t 2- supprimer le client par id.");
        printf("\n\t 3- retourner au menu.");
        printf("\n\t          votre choix: ");
        scanf("%d",&choix);
    }while(choix < 1 || choix > 3);
    system("cls");
    printf("\n\t-------------- SUPPRIMER CLIENT: --------------\n");
    if(choix == 2){
        printf("\n\t ==> saisir l'id du client a supprimer :  ");
        scanf("%d",&id);
        system("cls");
        printf("\n\t-------------- SUPPRIMER CLIENT: --------------\n");
        p = fopen("client.txt","rb");
            ptr = fopen("client1.txt","wb");
                while(fread(cl,sizeof(struct client),1,p)==1){
                    if(cl->idClient==id){
                        printf("\n\t ==> LE CLIENT D'ID %d A ETE SUPPRIMEE AVEC SUCCES!!!",id);
                        sleep(3);
                        detection=1;
                    }else{
                        fwrite(cl,sizeof(struct client),1,ptr);
                    }
                }
            fclose(p);
            fclose(ptr);
            if(detection==1){
                remove("client.txt");
                rename("client1.txt","client.txt");
            }else{
                remove("client1.txt");
            }
        system("cls");
        printf("\n\t-------------- SUPPRIMER CLIENT: --------------\n");
    }else if(choix==1){
        remove("client.txt");
        printf("\n\t ==> TOUS LES CLIENTS SONT SUPPRIMER AVEC SUCCES...");
        sleep(3);
    }
    system("cls");
}


int main(){
    int n;
    while(1){
        do{
            printf("\n\t\tMenu Principal\n\n");
            printf("\tLocation.....................1\n");
            printf("\tGestion voiture..............2\n");
            printf("\tGestion client...............3\n");
            printf("\tQuitter......................4\n\n");
            printf("\t\tVotre choix   :   ");
            scanf("%d",&n);
            system("cls");
        }while(n<1 || n>4);
            switch(n){
                case 1:Location();break;
                case 2:gestionVoiture();break;
                case 3:gestionClient();break;
                default:return 0;
            }
    }

}
