#include <stdio.h>

int main(){
    int somma=0;
    int numeri[100];
    int iter=0;
    int last=1;
    
    while(last){
        scanf("%d", &numeri[iter]);
        last=numeri[iter];
        iter++;
    }
    int i=0;
    for(i; i<iter; i++){   
        somma+=numeri[i];
    }
    
    printf("%d", somma);
    return 0;
}
