#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef struct Pitanja {
	char pitanje[80];
	char odg1[30];
	char odg2[30];
	char odg3[30];
	char odg4[30];
	int tacanOdg;
} Pitanja;

int getPitanja(const Pitanja* pit) { //Ispisuje pitanja u konzolu
	printf("%s\n", pit->pitanje);
	printf("1. %s\n", pit->odg1);
	printf("2. %s\n", pit->odg2);
	printf("3. %s\n", pit->odg3);
	printf("4. %s\n", pit->odg4);
	printf("\n");
	printf("\n");

	int odabrano;
	scanf("%d", &odabrano);
	if (odabrano == pit->tacanOdg)
	{
		return 1; //vraca 1 ako je odg tacan
	}
	else
	{
		return 0; //vraca 0 ako je odg netacan
	}
}

//Cita pitanje,odgovore i tacan odgovor iz fajla
void citajPitanja(Pitanja* pit, FILE* f)
{
	fscanf(f, "%s %s %s %s %s %d", pit->pitanje, pit->odg1, pit->odg2, pit->odg3, pit->odg4, &pit->tacanOdg);
}

//smesta pitanja u niz
Pitanja* smestiPitanja(int* brojac, Pitanja* niz) {
	*brojac = 0;
	FILE* fp;
	if ((fp = fopen("BazaPitanja.txt", "r")) == NULL)
	{
		fprintf(stderr, "Fajl ne moze da se otvori");
		return 0;
	}
	niz = (Pitanja*)malloc(sizeof(Pitanja));
	if (niz == NULL) {
		printf("Greska pri alociranju memorije!\n");
	}
	while (!feof(fp)) {
		niz = realloc(niz, (*brojac + 1) * sizeof(Pitanja));
		if (niz == NULL) {
			printf("greska, fajl je prazan!");
		}
		Pitanja p1;
		citajPitanja(&p1, fp);
		niz[*brojac] = p1;
		(*brojac)++;
	}
	fclose(fp);
	return niz;
}

int main()
{
	int brojac = 0;
	int tacno;
	Pitanja* niz;

	printf("****************\n** Dobrodosli **\n****************\n\n");

	int br = 1;
	//petalja za povratak na pocetak
	while (br != 0) {
		printf("Birate odgovor na pitanje tako sto unosite broj odgovora\n*********************************************************\n");
		printf("0 - Kraj Kviza\n1 - Zapocni Milioner\n\n");
		scanf("%d", &br);
		printf("\n");
		//izlaz iz programa
		if (br == 0)
		{
			return 0;
			break;
		}
		//Pocetak kviza
		else
		{
			niz = smestiPitanja(&brojac, &niz);
			tacno = 1;
			//petlja prolazi kroz sva pitanja iz fajla
			for (int i = 0; i < 5; i++) {
				if (getPitanja(&niz[i]) == 1) {
					printf("*******************\n** Tacan odgovor **\n*******************\n\n");
				}
				else
				{
					printf("*******************\n** Izgubili ste **\n*******************\n\n");
					tacno = 0;
					break;
				}
			}
			if (tacno == 1)
			{
				printf("\n    *************************\n    ** POSTALI STE MILONER **\n    *************************\n\n");
			}
		}

	}
	return 0;
}