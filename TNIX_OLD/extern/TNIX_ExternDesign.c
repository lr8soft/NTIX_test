#include "TNIX_ExternFeature.h"
void main(){ 
							FILE *fp,*fp2;char input[0xff],cinput[0xff],*temp=NULL,*command=NULL; 
							fp=fopen("temp\\extern_exchange.dat","r+");
							fgets(input,0xff,fp);
							fclose(fp);
							strcpy(cinput,input);temp=strtok(input," ");
							command=splitString(cinput,' ');
							int rtemp=do_func(temp,command);
							if(rtemp==1) fp2=fopen("temp\\extern_exchange.dat","wb");fwrite(1,sizeof(int),1,fp2);fclose(fp2);
						}

