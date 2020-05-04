#include <stdio.h>

void swap(int* x, int* y, int* z){
        int tmp = *x;
        int tmp1 = *y;

        *x = *z;
	*y = tmp;
	*z = tmp1;
        return;
}

int main(){
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        swap(&x,&y,&z);
        printf("%d\n%d\n%d\n", x, y, z);
        return 0;
}

