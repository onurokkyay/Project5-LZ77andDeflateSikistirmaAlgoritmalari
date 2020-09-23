#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <Stdint.h>
#define MAX_TREE_HT 50


struct token{
uint8_t uzaklik;
char c;
uint8_t benzerlik;

}token[20000];

struct huffmantoken{
char harf;
int syc_t;
uint8_t dizi[25];

}huffman_token[20000];
int hf_sayac=0;
int syc=0;


struct MinHeapNode
{
  char data;
  unsigned frequency;
  struct MinHeapNode *left, *right;
};

struct MinHeap
{
  unsigned size;
  unsigned capacity;
  struct MinHeapNode **array;
};

struct MinHeapNode *newNode(char data, unsigned frequency)
{
  struct MinHeapNode *temp = (struct MinHeapNode *)malloc(sizeof(struct MinHeapNode));

  temp->left = temp->right = NULL;
  temp->data = data;
  temp->frequency = frequency;

  return temp;
}

struct MinHeap *createMinHeap(unsigned capacity)
{
  struct MinHeap *minHeap = (struct MinHeap *)malloc(sizeof(struct MinHeap));

  minHeap->size = 0;

  minHeap->capacity = capacity;

  minHeap->array = (struct MinHeapNode **)malloc(minHeap->capacity * sizeof(struct MinHeapNode *));
  return minHeap;
}

void swapMinHeapNode(struct MinHeapNode **a, struct MinHeapNode **b)
{
  struct MinHeapNode *t = *a;
  *a = *b;
  *b = t;
}

void minHeapify(struct MinHeap *minHeap, int idx)
{
  int smallest = idx;
  int left = 2 * idx + 1;
  int right = 2 * idx + 2;

  if (left < minHeap->size && minHeap->array[left]->frequency < minHeap->array[smallest]->frequency)
    smallest = left;

  if (right < minHeap->size && minHeap->array[right]->frequency < minHeap->array[smallest]->frequency)
    smallest = right;

  if (smallest != idx)
  {
    swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
    minHeapify(minHeap, smallest);
  }
}

int isSizeOne(struct MinHeap *minHeap)
{
  return (minHeap->size == 1);
}

struct MinHeapNode *extractMin(struct MinHeap *minHeap)
{
  struct MinHeapNode *temp = minHeap->array[0];
  minHeap->array[0] = minHeap->array[minHeap->size - 1];

  --minHeap->size;
  minHeapify(minHeap, 0);

  return temp;
}

void insertMinHeap(struct MinHeap *minHeap, struct MinHeapNode *minHeapNode)
{
  ++minHeap->size;
  int i = minHeap->size - 1;

  while (i && minHeapNode->frequency < minHeap->array[(i - 1) / 2]->frequency)
  {
    minHeap->array[i] = minHeap->array[(i - 1) / 2];
    i = (i - 1) / 2;
  }
  minHeap->array[i] = minHeapNode;
}

void buildMinHeap(struct MinHeap *minHeap)
{
  int n = minHeap->size - 1;
  int i;

  for (i = (n - 1) / 2; i >= 0; --i)
    minHeapify(minHeap, i);
}

void printArray(int arr[], int n)
{
  int i;
  for (i = 0; i < n; ++i){
    printf("%d", arr[i]);
    huffman_token[hf_sayac].dizi[i]=arr[i];
    syc++;
  }
    huffman_token[hf_sayac].syc_t=syc;
  hf_sayac++;


  printf("\n");
}


int isLeaf(struct MinHeapNode *root)
{

  return !(root->left) && !(root->right);
}

struct MinHeap *createAndBuildMinHeap(char data[], int frequency[], int size)
{
  struct MinHeap *minHeap = createMinHeap(size);

  for (int i = 0; i < size; ++i)
    minHeap->array[i] = newNode(data[i], frequency[i]);

  minHeap->size = size;
  buildMinHeap(minHeap);

  return minHeap;
}

struct MinHeapNode *buildHuffmanTree(char data[], int frequency[], int size)
{
  struct MinHeapNode *left, *right, *top;
  struct MinHeap *minHeap = createAndBuildMinHeap(data, frequency, size);

  while (!isSizeOne(minHeap))
  {

    left = extractMin(minHeap);
    right = extractMin(minHeap);

    top = newNode('$', left->frequency + right->frequency);

    top->left = left;
    top->right = right;

    insertMinHeap(minHeap, top);
  }
  return extractMin(minHeap);
}

void printCodes(struct MinHeapNode *root, int arr[], int top)
{
  if (root->left)
  {

    arr[top] = 0;
    printCodes(root->left, arr, top + 1);
  }
  if (root->right)
  {

    arr[top] = 1;
    printCodes(root->right, arr, top + 1);
  }
  if (isLeaf(root))
  {

    printf("  %c   | ", root->data);
    huffman_token[hf_sayac].harf=root->data;
    printArray(arr, top);
  }
}



void HuffmanCodes(char data[], int frequency[], int size)
{
  struct MinHeapNode *root = buildHuffmanTree(data, frequency, size);

  int arr[MAX_TREE_HT], top = 0;

  printCodes(root, arr, top);


}




int main()
{
    char ileri_Tampon[100000];
    char aranan_Tampon[100000];
    int token_Sayac=0;
    aranan_Tampon[0]=1;
    int gecici_j,gecici_x;
    int x,y,benzerlik_Gecici;
    uint16_t uzunluk;
    uint16_t sayac=0;



    int i=0;
    FILE *belge;
    char karakter;
    belge=fopen("input.txt","r");
    do
        {
    karakter=getc(belge);
    printf("%c",karakter);
    ileri_Tampon[i]=karakter;
    i++;
        }while(karakter!=EOF);
   fclose(belge);

    for(int i=0;i<strlen(ileri_Tampon);i++){
        uzunluk=0;

            for(int j=strlen(aranan_Tampon)-1;j>-1;j--){
            x=i;
            y=j,benzerlik_Gecici=0;
            //printf("\n J NIN DEGERI:%d \n",j);
             //printf("\n \n ileri tampon:%c    ve   aranan tampon: %c  \n",ileri_Tampon[x],aranan_Tampon[y]);
            //printf("\n \n ileri tampon:%s    ve   aranan tampon: %s  \n",ileri_Tampon,aranan_Tampon);
                   while(ileri_Tampon[x]==aranan_Tampon[y] && aranan_Tampon[y]!=NULL)
                    {
                         // printf("\n J NIN WHILE DEGERI:%d \n",j);
                            benzerlik_Gecici++;

                   // printf("\n");
                   // printf("i=%d ve j=%d, x=%d ve y=%d \n",i,j,x,y);
                            if(benzerlik_Gecici>uzunluk){
                                uzunluk=benzerlik_Gecici;
                                gecici_j=j;
                               // printf("\n GECICI J:%d \n",gecici_j);
                                gecici_x=x;
                              //  printf("gecicix: %d ,ileri:  %c  ,aranan:  %c  ,uzunluk:%d \n",gecici_x,ileri_Tampon[x],aranan_Tampon[y],uzunluk);

                            }
                          // printf("X IN ARTMADAN ONCE DEGERI:%d \n",x);
                            x++;
                           // printf("X IN ARTTIKTAN SONRAKI DEGERI:%d \n",x);
                            y++;
                                    //printf("=================== \n");
                    }


        }

        if(uzunluk==1){
            aranan_Tampon[sayac]=ileri_Tampon[i];
            sayac++;
            aranan_Tampon[sayac]=ileri_Tampon[i+1];
            sayac++;

             // printf("UZUNLUK 1 KARAKTER:  %c   %c FORUN IC KISMI ===i=%d ve, x=%d ve y=%d \n",ileri_Tampon[i],ileri_Tampon[i+1],i,x,y);
        }
        else if(uzunluk==0)
        {
        aranan_Tampon[sayac]=ileri_Tampon[i];
        sayac++;
         // printf("UZUNLUK 1 KARAKTER:  %c FORUN IC KISMI ===i=%d ve, x=%d ve y=%d \n",ileri_Tampon[i],i,x,y);
        }else
        {
            for(int k=0;k<uzunluk+1;k++)
                {
            aranan_Tampon[sayac]=ileri_Tampon[i+k];
        //printf("KARAKTER:  %C  ",ileri_Tampon[i+k]);
            sayac++;
                }
                // printf("  FORUN IC KISMI ===i=%d ve, x=%d ve y=%d \n",i,x,y);
        }

  if(uzunluk>0){


    token[token_Sayac].benzerlik=uzunluk;
     token[token_Sayac].uzaklik=fabs(i-gecici_j);
     token[token_Sayac].c=ileri_Tampon[gecici_x+1];
     token_Sayac++;



  }


  if(uzunluk==0) {

        token[token_Sayac].benzerlik=0;
           token[token_Sayac].uzaklik=0;
           token[token_Sayac].c=ileri_Tampon[x];
          token_Sayac++;

       }
       if(strlen(ileri_Tampon)-1==gecici_x)
        break;
       // printf("X IN DEGERI KAC %d",gecici_x);
                if(uzunluk==1){
                    i++;
                }
                else if(uzunluk==0){
                    i=x;
                }
                else
                    i=gecici_x+1;
    }



    printf("\nLZ77 Sonucu Olusan Tokenler\n");

 FILE* dosya1=fopen("EncodedLZ77.txt","wb");
    for(int i=0;i<token_Sayac;i++){
        printf("\n%d %d %c",token[i].uzaklik,token[i].benzerlik,token[i].c);
        //printf(": %d\n",sizeof(token[i]));
       // fprintf(dosya1,"%d,%d,%c-",token[i].uzaklik,token[i].benzerlik,token[i].c);
       fwrite(&token[i].uzaklik,sizeof(uint8_t),1,dosya1);
        fwrite(&token[i].benzerlik,sizeof(uint8_t),1,dosya1);
        fwrite(&token[i].c,1,1,dosya1);

    }
    printf("NULL\n");

fclose(dosya1);
//printf(" ileri tm %s \n",ileri_Tampon);

char *harfler=(char*)malloc(sizeof(ileri_Tampon));
//int frekanslar[strlen(ileri_Tampon)];

int sayac_Def=0;
int sayac_H=0;
for(int i=0;i<strlen(ileri_Tampon);i++){
    sayac_Def=0;
    for(int j=0;j<strlen(harfler);j++){
            if(ileri_Tampon[i]==harfler[j]){
                sayac_Def++;

            }


    }
    if(sayac_Def==0){
        harfler[sayac_H]=ileri_Tampon[i];
        //printf("sayac %d  ",sayac_H);

        //printf(" --> %c ",harfler[sayac_H]);
            sayac_H++;


        //printf("-x> %c ",harfler[sayac_H-1]);
    }



}

int frekanslar[strlen(harfler)];
//printf("HARFLER %s %d %d",harfler,strlen(harfler),strlen(ileri_Tampon));
int harf_frekans=0;
for(int i=0;i<strlen(harfler);i++){
        harf_frekans=0;
    for(int j=0;j<strlen(ileri_Tampon);j++ ){

        if(harfler[i]==ileri_Tampon[j]){
            harf_frekans++;

        }
    }

    frekanslar[i]=harf_frekans;


}

for(int i=0;i<strlen(harfler);i++){
    //printf("%c --> %d\n",harfler[i],frekanslar[i]);
}




  int size = sizeof(harfler) / sizeof(harfler[0]);

  printf(" Char | Huffman code ");
  printf("\n--------------------\n");

  HuffmanCodes(harfler, frekanslar, strlen(harfler)-1);
//printf("hf sayac %d",hf_sayac);

FILE* dosya2=fopen("HuffmanaDonusmusHali.txt","wb");



for(int i=0;i<strlen(ileri_Tampon);i++){
    for(int j=0;j<strlen(harfler);j++){
        if(ileri_Tampon[i]==harfler[j]){
                for(int k=0;k<hf_sayac;k++){
                    if(harfler[j]==huffman_token[k].harf){
                        for(int p=0;p<(sizeof(huffman_token[k].dizi)/sizeof(huffman_token[k].dizi[0]));p++){
                                //fprintf(dosya2,"%d",huffman_token[k].dizi[p]);
                            fwrite(&huffman_token[k].dizi[p],sizeof(uint8_t),1,dosya2);
                        }
                       // fprintf(dosya2,"");
                    }

                }

        }
    }

}
fclose(dosya2);



    belge=fopen("HuffmanaDonusmusHali.txt","r");
    do
        {
    karakter=getc(belge);
    //printf("%c",karakter);
    ileri_Tampon[i]=karakter;
    i++;
        }while(karakter!=EOF);
   fclose(belge);

    for(int i=0;i<strlen(ileri_Tampon);i++){
        uzunluk=0;

            for(int j=strlen(aranan_Tampon)-1;j>-1;j--){
            x=i;
            y=j,benzerlik_Gecici=0;
            //printf("\n J NIN DEGERI:%d \n",j);
             //printf("\n \n ileri tampon:%c    ve   aranan tampon: %c  \n",ileri_Tampon[x],aranan_Tampon[y]);
            //printf("\n \n ileri tampon:%s    ve   aranan tampon: %s  \n",ileri_Tampon,aranan_Tampon);
                   while(ileri_Tampon[x]==aranan_Tampon[y] && aranan_Tampon[y]!=NULL)
                    {
                         // printf("\n J NIN WHILE DEGERI:%d \n",j);
                            benzerlik_Gecici++;

                   // printf("\n");
                   // printf("i=%d ve j=%d, x=%d ve y=%d \n",i,j,x,y);
                            if(benzerlik_Gecici>uzunluk){
                                uzunluk=benzerlik_Gecici;
                                gecici_j=j;
                               // printf("\n GECICI J:%d \n",gecici_j);
                                gecici_x=x;
                              //  printf("gecicix: %d ,ileri:  %c  ,aranan:  %c  ,uzunluk:%d \n",gecici_x,ileri_Tampon[x],aranan_Tampon[y],uzunluk);

                            }
                          // printf("X IN ARTMADAN ONCE DEGERI:%d \n",x);
                            x++;
                           // printf("X IN ARTTIKTAN SONRAKI DEGERI:%d \n",x);
                            y++;
                                    //printf("=================== \n");
                    }


        }

        if(uzunluk==1){
            aranan_Tampon[sayac]=ileri_Tampon[i];
            sayac++;
            aranan_Tampon[sayac]=ileri_Tampon[i+1];
            sayac++;

             // printf("UZUNLUK 1 KARAKTER:  %c   %c FORUN IC KISMI ===i=%d ve, x=%d ve y=%d \n",ileri_Tampon[i],ileri_Tampon[i+1],i,x,y);
        }
        else if(uzunluk==0)
        {
        aranan_Tampon[sayac]=ileri_Tampon[i];
        sayac++;
         // printf("UZUNLUK 1 KARAKTER:  %c FORUN IC KISMI ===i=%d ve, x=%d ve y=%d \n",ileri_Tampon[i],i,x,y);
        }else
        {
            for(int k=0;k<uzunluk+1;k++)
                {
            aranan_Tampon[sayac]=ileri_Tampon[i+k];
        //printf("KARAKTER:  %C  ",ileri_Tampon[i+k]);
            sayac++;
                }
                // printf("  FORUN IC KISMI ===i=%d ve, x=%d ve y=%d \n",i,x,y);
        }

  if(uzunluk>0){


    token[token_Sayac].benzerlik=uzunluk;
     token[token_Sayac].uzaklik=fabs(i-gecici_j);
     token[token_Sayac].c=ileri_Tampon[gecici_x+1];
     token_Sayac++;



  }


  if(uzunluk==0) {

        token[token_Sayac].benzerlik=0;
           token[token_Sayac].uzaklik=0;
           token[token_Sayac].c=ileri_Tampon[x];
          token_Sayac++;

       }
       if(strlen(ileri_Tampon)-1==gecici_x)
        break;
       // printf("X IN DEGERI KAC %d",gecici_x);
                if(uzunluk==1){
                    i++;
                }
                else if(uzunluk==0){
                    i=x;
                }
                else
                    i=gecici_x+1;
    }

    dosya1=fopen("EncodedDeflate.txt","wb");
    for(int i=0;i<token_Sayac;i++){
        //printf("%d(%d) %d(%d) %c(%d)",token[i].uzaklik,sizeof(token[i].uzaklik),token[i].benzerlik,sizeof(token[i].benzerlik),token[i].c,sizeof(token[i].c));
        //printf(": %d\n",sizeof(token[i]));
        //fprintf(dosya1,"%d,%d,%c-",token[i].uzaklik,token[i].benzerlik,token[i].c);
        fwrite(&token[i].uzaklik,sizeof(uint8_t),1,dosya1);
        fwrite(&token[i].benzerlik,sizeof(uint8_t),1,dosya1);
        fwrite(&token[i].c,1,1,dosya1);

    }

fclose(dosya1);







    return 0;
}



