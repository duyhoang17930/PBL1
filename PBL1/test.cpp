#include <stdio.h>

int main(){
	FILE *x1, *x2, *y;
	x1 = fopen("dulieux1.txt","r");
	x2 = fopen("dulieux2.txt", "r");
	y = fopen("dulieuy.txt", "r");

	int n=fscanf("dulieux1.txt", "%d", &n);
	int X1[n],X2[n],Y[n];
	int i=0;
	printf("%d\n",n);
	while (getc(x1)!=EOF){
		X1[i]=getc(x1);
		X2[i]=getc(x2);
		Y[i]=getc(y);
		i++;
	}
	for(int i=0;i<n;i++){
		printf("%d %d %d\n",X1[i],X2[i],Y[i]);
	}
	
	fclose(x1);
	fclose(x2);
	fclose(y);
	return 0;
}
