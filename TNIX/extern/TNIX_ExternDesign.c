#include "TNIX_ExternFeature.h"
void main(){ 							FILE *fp;char input[0xff],cinput[0xff],*temp; 							fp=fopen("temp\extern_exchange.dat","r+");							fgets(input,0xff,fp);							fclose(fp);							strcpy(cinput,input);temp=strtok(input,)							int temp=do_func(temp,strtok(input,));							if(temp==1) fp=fopen("temp\extern_exchange.dat","wb");fwrite(1,sizeof(int),1,fp);fclose(fp);						}
