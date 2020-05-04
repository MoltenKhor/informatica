#include <stdio.h>
#include <string.h>

int anagramma(unsigned char *x, unsigned char *y){
	int i;
	int xc[256], yc[256];
	for(i=0; i<256; i++){ xc[i] = yc[i] = 0; }
	int lenx = strlen(x);
	int leny = strlen(y);
	if(lenx != leny){

		return 0;	
	}	

	for(i=0; i<lenx; i++){
		xc[x[i]]++;
		yc[y[i]]++;
	}

	for(i=0; i<256; i++){
		if(xc[i]!=yc[i]){
			return 0;
		}
	}
	return 1;
}

int main(){
	unsigned char X[1000];
	unsigned char Y[1000];

	scanf("%s", &X[0]);
	scanf("%s", &Y[0]);
	int scan = anagramma(X, Y);
	if(scan){
		printf("1\n");
	}else printf("0\n");
}
