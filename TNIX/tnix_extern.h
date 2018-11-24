#pragma once
#ifndef _tnix_extern_h_
#define _tnix_extern_h_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif
void AddNewLib(const char *name,char *path) {
	char otext[0xff], ntext[0xfff];
	int i, j = 0;
	FILE *fp;
	fp = fopen("extern\\TNIX_libs.h","r+");
	if (fp == NULL) {
		fp = fopen("extern\\TNIX_libs.h", "w");
		fprintf(fp,"#pragma comment (lib,\"%s\")\n",path);
		fprintf(fp, "void %s(char *input); \n", name);
		fclose(fp);
	}
	while (fgets(otext, 0xff, fp) != NULL) {
		for (i = 0; i < strlen(otext);i++) {
			ntext[j] = otext[i];
			j++;
		}
	}
	ntext[j] = '\0';
	fprintf(fp, "#pragma comment (lib,\"%s\")\n", path);
	fprintf(fp,"%s\n",ntext);
	fprintf(fp, "void %s(char *input); \n", name);
//	printf("%s",ntext);
	fclose(fp);
}
