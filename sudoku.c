#include <stdio.h>
#define N 9

void liesSudoku(int (*spiel)[N][N]){
	int (*anfang)[N][N];
	FILE * stream=fopen("spiel.txt", "r");
	if(stream){
		int x;
		for(int i=0; i<N; i++){
			for(int j=0; j<N && fscanf(stream, "%d", &x)>0; j++){
				(*spiel)[i][j]=x;
				//printf("%d ", (*spiel)[i][j]);
			}
			//printf("\n");
		}
		fclose(stream);
	}	
	else{
		printf("Die Datei konnte nicht geöffnet werden.\n");
	}
}

int testeQuadrat(int mat[N][N], int x, int y){
	int quadrat[N]={0};
	for(int i=x; i<x+3; i++){
		for(int j=y; j<y+3; j++){
			int a=mat[i][j];
			quadrat[a-1]++;
		}
	}
	
	for(int k; k<N; k++){
		if(quadrat[k]!=1){
			printf("Werte im felherhaften Teilquadrat:\n");
			for(int l=0; l<N; l++){
				printf("%d: %d\n", l+1, quadrat[l]);
			}
			return 0;
		}
	}
	return 1;
}


int sudoku(int mat[N][N]){
	int i, j, k;
	for (i=0; i<N; i++){
		int row = 0;
		int col = 0;
		for(j=0; j<N; j++){
			row = row | (1 << mat[i][j]-1);
			col = col | (1 << mat[j][i]-1);

			int a=mat[i][j];
			int b=mat[j][i];
		}
		if (row != 511){
			printf("\nFehler in Zeile\n");
			return 0;
		}
		if (col != 511){
			printf("\nFehler in Spalte\n");
			return 0;
		}

	}
		
	int zaehler=0;
	for(i=0; i<N; i+=3){
		for(j=0; j<N; j+=3){
			if(testeQuadrat(mat, i, j)==0){
				printf("Fehler im Teilquadrat [%d][%d].\n", i+1, j+1);
				return 0;
			}
		}
	}
	
	return 1;
}

int main(){
	int spiel[N][N];
	int (*zeiger)[N][N];
	zeiger= &spiel;
	liesSudoku(zeiger);

	printf("\nSudoku:\n");
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			printf("%d ", spiel[i][j]);
		}
		printf("\n");
	}

	int ergebnis=sudoku(spiel);
	if(ergebnis==1)
		printf("Einwandfrei\n");
	else if(ergebnis==0)
		printf("\nFehler im Sudoku\n");

	return 0;
}
