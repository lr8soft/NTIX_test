#pragma once
#ifndef _tnix_extern_h_
#define _tnix_extern_h_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

#ifndef _tnix_used_
#define _tnix_banned_
void AddNewLib(char *path) {
	FILE *fp;
	fp = fopen("extern\\TNIX_libs.h","a");
	if (fp == NULL) {
		fp = fopen("extern\\TNIX_libs.h", "w");
		fprintf(fp, "#pragma comment(lib,\"%s\")\n", path);
	}
	else {
		fprintf(fp, "#pragma comment(lib,\"%s\")\n", path);
	}
	fclose(fp);
}
void DefineNewFunc(const char *name) {
	FILE *fp;
	fp = fopen("extern\\TNIX_libs.h", "a");
	fprintf(fp, "void %s(char *input);\n", name);
	fclose(fp);
}
void RefreshLib() {
	int i=0, j = 0,k,frun=0;
	int funccount=0;
	FILE *fp,*fp2;
	char input[0xfff], tinput[0xff], *dfunc, funcname[0xff] = {0};
	memset(input,0,sizeof(input));
	remove("extern\\TNIX_libs.h");
	fp = fopen("data\\extern.dat", "r");
	fp2 = fopen("data\\funccount.dat", "wb");
	if (fp!=NULL) {
		while ((fgets(tinput,0xff,fp))!=NULL) {
			strcat_s(input,tinput);
		}
		dfunc = strtok(input, "|");
		if (dfunc == NULL) return;
		AddNewLib(dfunc);
		funccount++;
		while ((dfunc = strtok(NULL, "|"))!=NULL) {
			if (frun==0) {
				DefineNewFunc(dfunc);
				strcat(funcname, dfunc);
				strcat(funcname, "|");
				frun++;
			}
			else {
				AddNewLib(dfunc);
				dfunc = strtok(NULL, "|");
				if (dfunc == NULL) break;
				DefineNewFunc(dfunc);
				strcat(funcname,dfunc);
				strcat(funcname, "|");
				funccount++;
			}
		}
		int temp = sizeof(funcname);
		fwrite(&funccount,sizeof(int),1,fp2);//set function count
		fwrite(&temp, sizeof(int), 1, fp2);//function size
		fwrite(funcname,sizeof(funcname),1,fp2);//function name?
		fclose(fp2);
	}
	else {
		return;
	}
}

void DefineFeature() {//Not finish
	int i=0, j=0,size=0,l=0;
	char funcname[0xff] = {0},*temp=NULL;
	FILE *fp,*fp2;
	fp = fopen("data\\funccount.dat","rb");
	if (fp == NULL) return;
	fp2 = fopen("extern\\TNIX_ExternFeature.h","w");
	fread(&i,sizeof(int),1,fp);
	fread(&size, sizeof(int), 1, fp);
	fread(funcname,size,1,fp);
	fclose(fp);
	char head[] = "#include <stdio.h> \n\
				   #include <stdlib.h> \n\
				   #include \"TNIX_libs.h\"\n";
	char def[] = "typedef void (*callback)(char*);\n";
	char defstruct[] = "typedef struct {\n\
							const char *name; \n\
							callback func;\n\
						}tnix_func_define;\n";
	char makestruct[0xfff] = "tnix_func_define tnix_command[] = {\n";
	for (temp = strtok(funcname, "|"); temp != NULL;temp = strtok(NULL, "|")) {
		strcat(makestruct, "{\"");
		strcat(makestruct, temp);
		strcat(makestruct, "\",");
		strcat(makestruct, temp);
		strcat(makestruct, "}");
		if (j!=i) strcat(makestruct, ","),j++;
		j++;
	}
	char splitfunc[] = "\nchar *splitString(char *input, int split) {\n \
							char *temp, *ftemp; int len, delta, i = 0;\n \
							static char rechar[0xff];\n\
							memset(rechar, 0, sizeof(rechar));\n \
							temp = strchr(input, split); \n\
							len = strlen(input); \n\
							delta = temp - input; \n\
							for (ftemp = temp + 1; ftemp < temp + len - delta; ftemp++) { \n\
								rechar[i] = *ftemp;\n \
								i++;\n \
							} \
							return rechar;\n\
						    }\n";
	strcat(makestruct, "};");
	char dofunc[] = "int do_func(const char *name, char *command) { \n\
						 int i; static int ktemp = 1; \n\
						 for (i = 0; i < sizeof(tnix_command)/8; i++) {\n \
							if (!(strcmp(tnix_command[i].name, name))) { \n\
								tnix_command[i].func(command);\n \
								return 1; \n\
							 } \n\
						 } \n\
					 	return 0;\n \
					}\n"; 
	fprintf(fp2,"%s",head);
	fprintf(fp2, "%s", def);
	fprintf(fp2, "%s", defstruct);
	fprintf(fp2, "%s", makestruct);
	fprintf(fp2, "%s", splitfunc);
	fprintf(fp2, "%s", dofunc);
	fclose(fp2);
}
void DefineMainFunc() {
	char head[] = "#include \"TNIX_ExternFeature.h\"";
	char body_par1[] = "void main(){ \n\
							FILE *fp,*fp2;char input[0xff],cinput[0xff],*temp=NULL,*command=NULL; \n\
							fp=fopen(\"temp\\\\extern_exchange.dat\",\"r+\");\n\
							fgets(input,0xff,fp);\n\
							fclose(fp);\n\
							strcpy(cinput,input);temp=strtok(input,\" \");\n\
							command=splitString(cinput,\' \');\n\
							int rtemp=do_func(temp,command);\n\
							if(rtemp==1) fp2=fopen(\"temp\\\\extern_exchange.dat\",\"wb\");fwrite(1,sizeof(int),1,fp2);fclose(fp2);\n\
						}\n";
	FILE *fp;
	fp = fopen("extern\\TNIX_ExternDesign.c","w");
	fprintf(fp,"%s\n",head);
	fprintf(fp, "%s\n", body_par1);
	fclose(fp);
}
void CompileSRC() {
	DefineFeature();
	RefreshLib();
	DefineMainFunc();
	char command_src[0xff] = {0}, tcommand[] = "\\tcc\\tcc.exe -o";
	strcat(command_src, getNowPath());
	strcat(command_src,tcommand);
	strcat(command_src, getNowPath());
	strcat(command_src, "\\extern\\TNIX_Extern.exe ");
	strcat(command_src, getNowPath());
	strcat(command_src, "\\extern\\TNIX_ExternDesign.c");
	system(command_src);
}
#endif