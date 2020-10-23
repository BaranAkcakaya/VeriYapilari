/*
 * File:   main.c
 * Author: BM
 * Created on 22 Ekim 2014 Çarşamba, 12:58
 *
 */

#include <stdio.h>
#include <stdlib.h>

/*
*
 */

#define SENTINEL -100000000

struct dugum {
    int icerik;
    struct dugum *sol;
    struct dugum *sag;
};

struct ikili_arama_agaci{
    struct dugum *kok;
};

void ikili_arama_agaci_olustur(struct ikili_arama_agaci **agac){
    *agac=(struct ikili_arama_agaci*)malloc(sizeof(struct ikili_arama_agaci));
    if(*agac==NULL){
        printf("Heapte gerekli yer ayrilamadi... exit ...\n");
        exit(1);
    }
    (*agac)->kok=NULL;
}

int ikili_agac_bosmu(struct ikili_arama_agaci *agac){
   if(agac->kok==NULL) return 1;
   else return 0;
}

struct dugum* dugum_olustur(int icerik){
    struct dugum *d = (struct dugum*)malloc(sizeof(struct dugum));
    if(d==NULL){
        printf("Heapte gerekli yer ayrilamadi... exit ...\n");
        exit(1);
    }
    d->icerik = icerik; //(*d).icerik=icerik;
    d->sol=d->sag=NULL;
    return d;
}


void ekle(struct ikili_arama_agaci *agac,int icerik){
    struct dugum *dugum;
    struct dugum *d;
    struct dugum *geri;

    d=agac->kok;
    while(d!=NULL){
        geri=d;
        if(icerik < d->icerik) d=d->sol;
        else if(icerik > d->icerik) d= d->sag;
        else return;
    }
    dugum=dugum_olustur(icerik);
    if(agac->kok==NULL){
        agac->kok = dugum;
        return;
    }
    if(icerik < geri->icerik) geri->sol = dugum;
    else geri->sag = dugum;

}

void inorder_yardimci(struct dugum *kok){

    if(kok==NULL) return;
    inorder_yardimci(kok->sol);
    printf("%4d ",kok->icerik);
    inorder_yardimci(kok->sag);

}

void inorder(struct ikili_arama_agaci *agac){
    if(agac==NULL) return;
    inorder_yardimci(agac->kok);
    printf("\n");
}

void preorder_yardimci(struct dugum *kok){

    if(kok==NULL) return;
    printf("%4d ",kok->icerik);
    preorder_yardimci(kok->sol);
    preorder_yardimci(kok->sag);

}
void preorder(struct ikili_arama_agaci *agac){
    if(agac==NULL) return;
    preorder_yardimci(agac->kok);
    printf("\n");
}

void postorder_yardimci(struct dugum *kok){
    if(kok==NULL) return;
    postorder_yardimci(kok->sol);
    postorder_yardimci(kok->sag);
    printf("%4d ",kok->icerik);

}

void postorder(struct ikili_arama_agaci *agac){
    if(agac==NULL) return;
    postorder_yardimci(agac->kok);
    printf("\n");
}


void sil(struct ikili_arama_agaci *agac, int silinen){

    struct dugum *d=agac->kok;
    struct dugum *parent=NULL;
    struct dugum *d1,*d2;
    int sol;
    while(d!=NULL){
        if(silinen < d->icerik){
            parent=d; d=d->sol; sol=1;
        }
        else if(silinen > d->icerik){
            parent=d; d=d->sag; sol = 0;
        }
        else break;
    }
    if(d==NULL) return;
    if(d->sol==NULL){ // silinen dugumun solu bos
        if(parent==NULL) agac->kok=d->sag;
        else{
            if(sol==1) parent->sol=d->sag;
            else parent->sag=d->sag;
        }
    }
    else if(d->sag==NULL){  // silinen dugumun sagi bos
        if(parent==NULL) agac->kok=d->sol;
        else {
            if(sol==1) parent->sol=d->sol;
            else parent->sag = d->sol;
        }
    }
  /*  else { // silinen dugumun hem sagi hem de solu dolu
           // silinencek dugumun solunun en sagina git
           // en sagdaki dugum silinen dugumun konumunu alir
        d1=d->sol;
        d2=NULL;
        while(d1->sag!=NULL){
            d2=d1;
            d1=d1->sag;
        }
        if(d2!=NULL){
            d2->sag= d1->sol;
            d1->sol=d->sol;
        }
        d1->sag = d->sag;
        if(parent==NULL) agac->kok=d1; // agacin koku degisti
        else {
            if(sol==1) parent->sol=d1;
            else parent->sag=d1;
        }
    } */

    else { // silinen dugumun hem sagi hem de solu dolu
           // silinencek dugumun saginin en soluna git
           // en soldaki dugum silinen dugumun konumunu alir
        d1=d->sag;
        d2=NULL;
        while(d1->sol!=NULL){
            d2=d1;
            d1=d1->sol;
        }
        if(d2!=NULL){
            d2->sol= d1->sag;
            d1->sag=d->sag;
        }
        d1->sol = d->sol;
        if(parent==NULL) agac->kok=d1; // agacin koku degisti
        else {
            if(sol==1) parent->sol=d1;
            else parent->sag=d1;
        }
    }
    free(d);
}

void yoket(struct dugum **kok){
    if(*kok!=NULL){
        yoket(&(*kok)->sol);
        yoket(&(*kok)->sag);
        free(*kok);
        *kok=NULL;
    }
}



int dugum_sayisi(struct dugum *kok){
    if(kok==NULL) return 0;
    return 1+dugum_sayisi(kok->sol)+dugum_sayisi(kok->sag);
}

int yaprak_sayisi(struct dugum *kok){
    if(kok==NULL) return 0;
    if(kok->sol==NULL && kok->sag == NULL) return 1;
    else return yaprak_sayisi(kok->sol)+yaprak_sayisi(kok->sag);
}
int foo(struct dugum *kok){ // ic dugum sayisi
    if(kok==NULL) return 0;
    else if(kok->sol!=NULL || kok->sag!=NULL)
        return 1+foo(kok->sol) + foo(kok->sag);
    else return 0;
}
int maxDepth(struct dugum *kok){
   if (kok==NULL)
       return 0;
   else{
       int lDepth = maxDepth(kok->sol);
       int rDepth = maxDepth(kok->sag);
       if (lDepth > rDepth)
           return(lDepth+1);
       else return(rDepth+1);
   }
}
int ikili_mi(struct dugum* kok){
    if(kok == NULL)
        return 1;
    if (kok-> sol != NULL && (kok->sol->icerik) > (kok-> icerik) ||
        kok->sag != NULL && (kok->sag->icerik) < (kok->icerik))
        return 0;

    ikili_mi(kok -> sol);
    ikili_mi(kok -> sag);
}

int kardes_mi2(struct dugum* kok, struct dugum* dugum1, struct dugum* dugum2) {
    if (kok == NULL)
        return 0;
    if (kok -> sol && kok -> sag ){
        if (dugum1 -> icerik == kok -> sol -> icerik && dugum2 -> icerik == kok ->sag -> icerik)
            return 1;
        if (dugum2 -> icerik == kok -> sol -> icerik && dugum1 -> icerik == kok ->sag -> icerik)
            return 1;
    }
    if(kok -> sol)
        kardes_mi2(kok -> sol, dugum1, dugum2);
    if (kok -> sag)
        kardes_mi2(kok -> sag, dugum1, dugum2);
}
int koke_uzaklik(struct dugum *kok, struct dugum*a){
    int uzaklik = 0;
    struct dugum *gezici = kok;
    int icerik = a -> icerik;
    while (gezici -> icerik != icerik) {
        if (icerik > gezici -> icerik)
            gezici = gezici -> sag;
        else
            gezici = gezici -> sol;
        uzaklik = uzaklik + 1 ;
    }
    return uzaklik;
}
int koke_uzaklik2(struct dugum *kok, int sayi){
    int uzaklik = 0;
    struct dugum *gezici = kok;
    int icerik = sayi;
    while (gezici -> icerik != icerik) {
        if (icerik > gezici -> icerik)
            gezici = gezici -> sag;
        else
            gezici = gezici -> sol;
        uzaklik = uzaklik + 1 ;
    }
    return uzaklik;
}
int ikili_mi(struct dugum* kok){
    if (kok-> sol || kok->sag == NULL) return 1;
    else if((kok-> sag != NULL && kok -> icerik < kok -> sag -> icerik) || (kok->sol != NULL &&kok -> icerik > kok -> sol -> icerik) )
        return 1 * ikili_mi(kok->sol) * ikili_mi(kok->sag);
    else return 0;
}


int main(int argc, char** argv) {
    struct ikili_arama_agaci *agac;
    ikili_arama_agaci_olustur(&agac);

    ekle(agac,100);
    /*ekle(agac,50);
    ekle(agac,200);
    /*ekle(agac,25);
    ekle(agac,5);
    ekle(agac,20);
    ekle(agac,35);
    ekle(agac,98);*/
    int uzaklik = koke_uzaklik2(agac -> kok, 100);
    printf("uzaklik : %d\n", uzaklik );
    int iki = ikili_mi(agac -> kok);
    printf("ikili_mi : %d\n", iki );

    /*ekle(agac,99);
    ekle(agac,500);
    ekle(agac,400);
    ekle(agac,300);
    ekle(agac,210);
    ekle(agac,375);
    ekle(agac,30);
    ekle(agac,173);*/
    inorder(agac);
    int a;
    int b;
    printf("Ic dugum sayisi: %4d\n",foo(agac->kok));
    a = maxDepth(agac -> kok);
    //b = ikili_mi(agac -> kok);
    printf("%d\n", a );
    //printf("%d\n", b );
    struct dugum *dugum1 = dugum_olustur(5);
    struct dugum *dugum2 = dugum_olustur(35);

    int c = kardes_mi2(agac->kok,dugum1, dugum2 );
    printf("%d\n", c );

    return (EXIT_SUCCESS);
}