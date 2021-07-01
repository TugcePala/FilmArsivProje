#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

struct filmler{
	char FilmAd[60];
	char Yonetmen[60];
	char senarist[60];
	char basrol[60]; 
	int yil;
};

//fonksiyonlar
void menu();
void structaKaydet(int N);
void dosyayaYaz(int N);
void filmAra();
void dosyadanOku();
void ekranaYaz(struct filmler Film[100], int y);
void dosyadanFilmSil(int x);

//struct dizisi
struct filmler film[100];
struct filmler film2[100];

//değişkenler
int satirlarinSayisi = 0, N, M;
int gercekSiralar[100];

int main() {
	
	int secim, silinecek, silinecekId;
	
	while(1){
		
		//arsivde kac film olduğu bilgisini tutan dosyanın olup olmadığını kontrol eden kod
		FILE * miktar;
		if(miktar = fopen("verisayisi.txt", "r")){
			fscanf(miktar, " %d", &satirlarinSayisi);	//text dosyası varsa içindeki değeri okuyoruz				
		}
		else{
			fclose(miktar);
			miktar = fopen("verisayisi.txt", "w");	//verisayisi.txt dosyası yoksa yenisini oluşturup içine 0 değerini yazıyoruz
			fprintf(miktar, "%d", 0);
		}fclose(miktar);
		
		
		system("cls");
		menu();
		dosyadanOku();
	    scanf("%d",&secim);
		
		switch(secim) {
			case 1:
				system("cls");
				printf("Arsive kac film eklemek istiyorsunuz: ");
				scanf(" %d",&N);
				
				structaKaydet(N);
				dosyayaYaz(N);
				
				break;
				
			case 2:
				break;		
			
			case 3:
			break;
			
			case 4:
				
				system("cls");
				printf("silmek istediginiz filmi bulunuz\n\n");
				
				filmAra();
				ekranaYaz(film2, M);
				
				printf("silinecek filmin numarasini giriniz:  ");
				scanf(" %d", &silinecek);
				
				if((silinecek > 0) && (silinecek <= M)){
					
					silinecekId = gercekSiralar[silinecek-1];
					
					system("cls");
					
					printf("\n\n(1) Devam    (2) Iptal\n\nSecilen film silinecek:  ");
					scanf(" %d", &secim);
					
					if(secim == 1){
						dosyadanFilmSil(silinecekId);
					}
					else if(secim == 0){
						break;
					}
					else{
						printf("gecersiz bir sayi girildi");
						system("pause");
						break;
					}
				}
				else{
					printf("gecersiz bir sayi girildi");
					system("pause");
				}
				
				break;
				
			case 5:
				system("cls");
				
				filmAra();
				
				system("cls");
				
				if(M != 0)
					ekranaYaz(film2, M);
				else
					printf("\nhicbir sonuc bulunamadi\n\n");
					
				system("pause");
				
				break;
				
			case 0:
				printf("\nProgramdan cikis yaptiniz.\nHoscakalin.\n");
				exit(0);
			break;
			
			default:
				printf("\n\n\t         !!!Girdiginiz deger gecersiz.Lutfen 1-6 arasi sayi giriniz!!! \n\n\n");
		}
	}
}


void menu(){
	printf("\n\t\t|--------------------------------------------------|\n\t\t\t\tFilm Arsiv Programi\n");
    printf("\t\t|--------------------------------------------------|\n\t\t|                                                  |\n\t\t|--------------------------------------------------|\n                |                                                  |");
	printf("\n\t\t|\t1-\t Arsive Film Ekle                  |\n");
    printf("\t\t|\t2-\t Filmleri Listele	    	   |\n");
    printf("\t\t|\t3-\t Film Guncelleme                   |\n");
    printf("\t\t|\t4-\t Arsivden Film Sil                 |\n");
    printf("\t\t|\t5-\t Arsivde Film Ara                  |\n");
    printf("\t\t|\t0-\t Cikis                             |\n\t\t|                                                  |\n\t\t\\--------------------------------------------------/ \n\n\n");
    printf("\t         Lutfen yapmak istediginiz islemin numarasini girin: ");
}

void structaKaydet(int N){
	
	int i;
	
	for(i=0; i<N; i++){
		
		printf("%d. Filmin bilgilerini giriniz:\n", i+1);
		
		printf("  filmin adi:");
		_flushall();
		gets(film[i].FilmAd);
		printf("  filmin yonetmeni:  ");
		_flushall();
		gets(film[i].Yonetmen);
		printf("  filmin senaristi:  ");
		_flushall();
		gets(film[i].senarist);
		printf("  filmin basrolu:  ");
		_flushall();
		gets(film[i].basrol);
		printf("  filmin yayin yili:  ");
		scanf(" %d", &film[i].yil);
	}
}

void dosyayaYaz(int N){
	
	FILE *miktar, *dosya = fopen("filmarsiv.txt", "a");
	
	int i;
	for(i=0; i<N; i++){
		fprintf(dosya, "%s %s %s %s %d\n", film[i].FilmAd, film[i].Yonetmen, film[i].senarist, film[i].basrol, film[i].yil);
	}
	
	fclose(dosya);
	
	miktar = fopen("verisayisi.txt", "w");
	fprintf(miktar, "%d", satirlarinSayisi+N);
	fclose(miktar);
	
}

void filmAra(){
	
	int arama, sayi;
	int i = 0;
	int k = 0; // arama sonucu bulunan filmlerin sayısı
	char kelime[30];
	
	printf("\nisme gore aramak icin 1\n");
	printf("yonetmene gore aramak icin 2\n");
	printf("senariste gore aramak icin 3\n");
	printf("basrole gore aramak icin 4\n");
	printf("yayin yilina gore aramak icin 5\n");
	printf("menuye donmek icin 0\n");
	printf("arama turu secin: ");
	

	scanf(" %d", &arama);
	if((arama > 0) && (arama < 6)){
		switch(arama){
		case 0:
			return;
			break;
			
		case 1:
			printf("\n\nAranacak film ismini yazin: ");
			_flushall();
			gets(kelime);
			while(i<satirlarinSayisi){
				if(!strcmp(film[i].FilmAd, kelime)){
					
					strcpy(film2[k].FilmAd, film[i].FilmAd);
					strcpy(film2[k].Yonetmen, film[i].Yonetmen);
					strcpy(film2[k].senarist, film[i].senarist);
					strcpy(film2[k].basrol, film[i].basrol);
					film2[k].yil = film[i].yil;
					
					gercekSiralar[k] = i;
					k++;
					
				}
			i++;
			}
			
			M = k; //başka bir fonksiyonda kullanmak için k değerini global bir değişkene kopyaladık
			
			break;
		
		case 2:
			printf("\n\nYonetmen ismini yazin: ");
			_flushall();
			gets(kelime);
			while(i<satirlarinSayisi){
				if(!strcmp(film[i].Yonetmen, kelime)){
					
					strcpy(film2[k].FilmAd, film[i].FilmAd);
					strcpy(film2[k].Yonetmen, film[i].Yonetmen);
					strcpy(film2[k].senarist, film[i].senarist);
					strcpy(film2[k].basrol, film[i].basrol);
					film2[k].yil = film[i].yil;
					
					gercekSiralar[k] = i;
					k++;
					
				}
			i++;
			}
			
			M = k; //başka bir fonksiyonda kullanmak için k değerini global bir değişkene kopyaladık
			break;
		
		case 3:
			printf("\n\nSenarist ismini yazin: ");
			_flushall();
			gets(kelime);
			while(i<satirlarinSayisi){
				if(!strcmp(film[i].senarist, kelime)){
					
					strcpy(film2[k].FilmAd, film[i].FilmAd);
					strcpy(film2[k].Yonetmen, film[i].Yonetmen);
					strcpy(film2[k].senarist, film[i].senarist);
					strcpy(film2[k].basrol, film[i].basrol);
					film2[k].yil = film[i].yil;
					
					gercekSiralar[k] = i;
					k++;
					
				}
			i++;
			}
			
			M = k; //başka bir fonksiyonda kullanmak için k değerini global bir değişkene kopyaladık
			break;
			
		case 4:
			printf("\n\nBasrol ismini yazin: ");
			_flushall();
			gets(kelime);
			while(i<satirlarinSayisi){
				if(!strcmp(film[i].basrol, kelime)){
					
					strcpy(film2[k].FilmAd, film[i].FilmAd);
					strcpy(film2[k].Yonetmen, film[i].Yonetmen);
					strcpy(film2[k].senarist, film[i].senarist);
					strcpy(film2[k].basrol, film[i].basrol);
					film2[k].yil = film[i].yil;
					
					gercekSiralar[k] = i;
					k++;
					
				}
			i++;
			}
			
			M = k; //başka bir fonksiyonda kullanmak için k değerini global bir değişkene kopyaladık
			break;
			
		case 5:
			printf("\n\nFilmin yayinlanma senesini yazin: ");
			scanf(" %d", &sayi);
			while(i<satirlarinSayisi){
				if(film[i].yil == sayi){
					
					strcpy(film2[k].FilmAd, film[i].FilmAd);
					strcpy(film2[k].Yonetmen, film[i].Yonetmen);
					strcpy(film2[k].senarist, film[i].senarist);
					strcpy(film2[k].basrol, film[i].basrol);
					film2[k].yil = film[i].yil;
					
					gercekSiralar[k] = i;
					k++;
					
				}
			i++;
			}
			
			M = k; //başka bir fonksiyonda kullanmak için k değerini global bir değişkene kopyaladık
			break;			
		}
	}
	else {
		printf("gecersiz bir sayi girildi");
	}
	
	
	
}


void dosyadanOku(){
	
	FILE * dosya = fopen("filmarsiv.txt", "r");
	
	int i;
	for(i=0; i<satirlarinSayisi; i++){
		fscanf(dosya, "%s %s %s %s %d\n", film[i].FilmAd, film[i].Yonetmen, film[i].senarist, film[i].basrol, &film[i].yil);	
	}
	
	fclose(dosya);
	
}


void ekranaYaz(struct filmler Film[100], int y){
	
	printf("\n");
	int i;
	for(i=0; i<y; i++){
		printf("%s %s %s %s %d    (%d)\n", Film[i].FilmAd, Film[i].Yonetmen, Film[i].senarist, Film[i].basrol, Film[i].yil, i+1);
	}
	
	printf("\n");
}


void dosyadanFilmSil(int x){
	int i;
	
	FILE * dosya = fopen("gecici.txt", "w");
	
	for(i=0; i<satirlarinSayisi; i++){
		if(i != x){
			fprintf(dosya, "%s %s %s %s %d\n", film[i].FilmAd, film[i].Yonetmen, film[i].senarist, film[i].basrol, film[i].yil);
		}
	}
	fclose(dosya);
	
	FILE * miktar = fopen("verisayisi.txt", "w");
	
	fprintf(miktar, "%d", satirlarinSayisi-1);
	fclose(miktar);
	
	remove("filmarsiv.txt");
	rename("gecici.txt", "filmarsiv.txt");
}


