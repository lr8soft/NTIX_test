#include "stdafx.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
const char info[]= "TNIX NotePad v1.0:\n-d [address]open a file as txt\n-h show help infomation \n";
void delayint(int time) {
	while(time--);
}
void EditXLine(char *text,int line) {
	
}
void solvetxt(char *address) {
	FILE *fp; int i, j = 0,count=0,k,artline=0;
	fp = fopen(address,"r+");
	char text[0xffff],ttemp[0xfff];
	while (fgets(ttemp,0xfff,fp)!=NULL) {
		for (i = 0; i < strlen(ttemp);i++) {
			text[j] = ttemp[i];
			j++;
		}
	}
	text[j] = '\0';
	printf("Line 0 ");
	for (k = 0; k < j;k++) {
		printf("%c",text[k]);
		count++;
		if (count == 20) artline++,printf("\nLine %d ", artline),count=0;
	}
	printf("\n MENU:E:edit line x S:save file Q:quit tnix_notepad");
	fclose(fp);
}
void tnixnote(char *input) {
	char *ad = NULL, *address=NULL, *help = NULL;
	FILE *fp;
	if (input == NULL) printf("%s", info); return;
	ad = strstr(input, "-d");
	help= strstr(input, "-h");
	if (help!=NULL) {
		printf("%s",info);
	}else if (ad!=NULL) {
		address = strtok(input,"-d ");
		if (address!=NULL) {
			fp = fopen(address,"r");
			if (fp == NULL) printf("File \'%s\' isn't exist!", address);return;
			if (fp != NULL) fclose(fp); solvetxt(address);
		}
	}
}