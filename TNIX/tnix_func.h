#pragma once
#ifndef _tnixfunc_h_
#define _tnixfunc_h_
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tnix_features.h"
#include "tnix_extern.h"
#endif
char usrname[20], passwd[20];
void SleepInt(int k) {
	while (k--);
}
char *splitString(char *input, int split) {
	char *temp, *ftemp; int len, delta, i = 0;
	static char rechar[0xff];
	memset(rechar,0,sizeof(rechar));
	temp = strchr(input, split);
	len = strlen(input);
	delta = temp - input;
	for (ftemp = temp+1; ftemp < temp + len - delta; ftemp++) {
		rechar[i] = *ftemp;
		i++;
	}
	return rechar;
}
int loadInfo() {
	FILE *fp;
	fp = fopen("data\\info.dat","rb");
	if (fp == NULL) return 0;
	fread(usrname,20*sizeof(char),1,fp);
	fread(passwd, 20*sizeof(char),1,fp);
	fclose(fp);
	return 1;
}
void setInfo() {
	FILE *fp;
	printf("Enter the root username:");
	scanf("%s",usrname);
	printf("\nEnter the root password:");
	scanf("%s", passwd);
	if (usrname == NULL || passwd == NULL) return;
	fp = fopen("data\\info.dat", "wb");
	fwrite(usrname, 20 * sizeof(char), 1, fp);
	fwrite(passwd, 20 * sizeof(char), 1, fp);
	fclose(fp);
	printf("Setting finished.");
	SleepInt(3000);
	system("cls");
}
int checkInput(char *input) {
	char *temp=NULL,*command=NULL,origininput[0xff];
	strcpy(origininput,input);
	temp = strtok(input," ");
	if((strstr(origininput," "))!=NULL) 
		command = splitString(origininput,' ');
	int t = do_command_work(temp,command, tnix_command, sizeof(tnix_command)/8);
	if (t != 0) return t;
	return 0;
}
int externCommand(char *input) {

	return 0;
}
void loopCheckInput() {
	char input[0xff]; int temp = 0;
	printf("%s",sysinfo);
	if (!loadInfo()) setInfo();
	while (1) {
		printf("%s:>",usrname);
		gets_s(input,0xff);
		temp = checkInput(input);
		if (strcmp(input, "exit") == 0) return;
		if (temp==0) {
			temp = externCommand(input);
			if (temp == 0) printf("No command \'%s\' found.\n",input);
		}
	}
}





