
#include <stdio.h>
#include <stdlib.h>

/*
 *
 */

struct hucre{
    int icerik;
    struct hucre *sonraki;
};

struct hucre* hucre_olustur(int icerik){
    struct hucre *a;
    a=(struct hucre*)malloc(sizeof(struct hucre));
    /*if(a==NULL){
    *    printf("Heap alaninda yer ayrilamadi ...\n");
    *    exit(1);
    *}*/
    a->icerik=icerik;
    a->sonraki=NULL;
    return a;
}
void en_kucuk_sil(struct hucre **liste_basi){
    struct hucre *temp = *liste_basi;
    struct hucre *tempDel;
    int tempInt;
    if(*liste_basi == NULL) return;
    tempInt = temp ->icerik;
    while (temp ->sonraki !=NULL){
        if(temp ->icerik < tempInt)
            tempInt = temp -> icerik;
        temp = temp ->sonraki;
    }
    temp = *liste_basi;
    if(tempInt == temp ->icerik){
        *liste_basi = temp ->sonraki;
        free(temp);
    }
    else{
        while (temp->sonraki->icerik != tempInt)
            temp = temp ->sonraki;
        tempDel = temp->sonraki;
        temp->sonraki = tempDel->sonraki;
        free(tempDel);
    }
}

void liste_basina_ekle(int icerik,struct hucre **liste_basi){
    struct hucre* a=hucre_olustur(icerik);
    a->sonraki=*liste_basi;
    *liste_basi=a;
}

void liste_sonuna_ekle(int icerik,struct hucre **liste_basi){
    struct hucre* a=hucre_olustur(icerik);
    if(*liste_basi==NULL){
        a->sonraki=*liste_basi;
        *liste_basi=a;
    }
    else {
        struct hucre *x=*liste_basi;
        while(x->sonraki!=NULL){
            x=x->sonraki;
        }
        x->sonraki=a;
    }
}

void liste_yaz(struct hucre *liste_basi){
    while(liste_basi!=NULL){
        printf("%4d ",liste_basi->icerik);
        liste_basi=liste_basi->sonraki;
    }
    printf("\n");
}

void liste_yaz_recursive(struct hucre *liste_basi){
    if(liste_basi!=NULL) {
    printf("%4d ",liste_basi->icerik);
    liste_yaz_recursive(liste_basi->sonraki);
    }
    else{
        printf("\n");
    }
}
void tersten_liste_yaz_recursive(struct hucre *liste_basi){

    if(liste_basi!=NULL){
        tersten_liste_yaz_recursive(liste_basi->sonraki);
        printf("%4d ",liste_basi->icerik);
    }

}
void liste_yok_et(struct hucre **liste_basi){
    struct hucre *simdiki;
    while(*liste_basi!=NULL){
        simdiki=(*liste_basi);
        *liste_basi=(*liste_basi)->sonraki;
        free(simdiki);
        //free(*liste_basi);
        //*liste_basi=(*liste_basi)->sonraki;
    }
}

void liste_sirali_ekle(int icerik, struct hucre **liste_basi){
   struct hucre *a, *b, *eklenen;
   b=*liste_basi;
   while(b!=NULL && b->icerik <= icerik){
       if(b->icerik==icerik) return;
       a = b;
       b= b->sonraki;
   }
   eklenen=hucre_olustur(icerik);
   if(b==*liste_basi){
       eklenen->sonraki=*liste_basi;
       *liste_basi=eklenen;
   }
   else {
       a->sonraki=eklenen;
       eklenen->sonraki=b;
   }
}

void liste_eleman_sil(int silinen, struct hucre **liste_basi){
    struct hucre *temp=*liste_basi;
    struct hucre *once;

    while(temp!=NULL && temp->icerik!=silinen){
        once = temp;
        temp=temp->sonraki;
    }
    if(temp==NULL) return;
    else {
        if(temp==*liste_basi) *liste_basi=(*liste_basi)->sonraki;
        else once->sonraki=temp->sonraki;
        free(temp);
    }

   }
void liste_sirala(struct hucre **liste_basi){
    struct hucre *a,*b,*c,*d;

    if(*liste_basi == NULL || (*liste_basi)->sonraki==NULL) return;

    d=(*liste_basi)->sonraki;
    (*liste_basi)->sonraki=NULL;

    while(d!=NULL){
        c=d;
        d=d->sonraki;
        b=*liste_basi;
        while(b!=NULL && b->icerik < c->icerik){
            a=b;
            b=b->sonraki;
        }
        if(b==*liste_basi){
            c->sonraki=*liste_basi;
            *liste_basi=c;
        }
        else {
            a->sonraki = c;
            c->sonraki = b;
        }
    }
}

void liste_ters_cevir(struct hucre **liste_basi){

    struct hucre *a,*b;

    a=NULL;
    while(*liste_basi!=NULL){
        b=*liste_basi;
        *liste_basi=(*liste_basi)->sonraki;
        b->sonraki=a;
        a=b;
    }
    *liste_basi=a;
}
void sirali_listeye_ekle(struct hucre **liste_basi, int icerik) {
    struct hucre *a;
    a = *liste_basi;
    while (a != NULL && a -> sonraki -> icerik <= icerik) {
        if (a -> icerik == icerik) return;
        a = a-> sonraki;
    }
    struct hucre *eklenen;
    eklenen -> icerik = icerik;
    if (*liste_basi == a && 0){
        eklenen -> sonraki = NULL;
        *liste_basi = eklenen;
    }
    else{
        eklenen -> sonraki = a -> sonraki;
        a -> sonraki = eklenen;
    }
}
void cift_tek_say(struct hucre *liste_basi, int *teklerin_sayisi) {
    teklerin_sayisi = (int*)malloc(sizeof(int));
    *teklerin_sayisi = 0;
    while (liste_basi != NULL) {
        if (liste_basi->icerik % 2 == 1){
            *teklerin_sayisi = *(teklerin_sayisi) + 1;
            printf("sayici :%d\n ", *teklerin_sayisi );
        }
        liste_basi = liste_basi -> sonraki;
    }
}





int main(int argc, char** argv) {

    struct hucre *liste1=NULL;

    liste_basina_ekle(20,&liste1);
    liste_basina_ekle(35,&liste1);
    liste_basina_ekle(201,&liste1);
    liste_basina_ekle(22,&liste1);
    liste_basina_ekle(491,&liste1);
    /*liste_basina_ekle(41,&liste1);
    liste_basina_ekle(81,&liste1);
    liste_basina_ekle(5,&liste1);
    liste_basina_ekle(10,&liste1);
    liste_basina_ekle(15,&liste1);*/

    //liste_sirali_ekle(155,&liste1);
    liste_yaz(liste1);
    //int *teklerin_sayisi;
    //cift_tek_say(liste1,teklerin_sayisi );
    //printf("%4d\n",*teklerin_sayisi );
    en_kucuk_sil(&liste1);
    printf("1. alttaki liste yazdirma \n");
    liste_yaz(liste1);
    en_kucuk_sil(&liste1);
    printf("2. alttaki liste yazdirma \n");
    liste_yaz(liste1);
    en_kucuk_sil(&liste1);
    printf("3. alttaki liste yazdirma \n");
    liste_yaz(liste1);
    en_kucuk_sil(&liste1);
    printf("4. alttaki liste yazdirma \n");
    liste_yaz(liste1);    
    //liste_ters_cevir(&liste1);
    //liste_yaz(liste1);
    //printf("\n");

    //tersten_liste_yaz_recursive(liste1);
    //printf("\n");

    return (EXIT_SUCCESS);
}
