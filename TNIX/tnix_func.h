#pragma once
#ifndef _tnixfunc_h_
#define _tnixfunc_h_
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tnix_features.h"
#include "tnix_extern.h"
#include "tnix_externdll.h"
#endif
char usrname[20], passwd[20];
void SleepInt(int k) {
	while (k--);
}
int loadInfo() {
	FILE *fp; int reg = 0;
	fp = fopen("data\\info.dat", "rb");
	if (fp == NULL) return 0;
	fread(&reg, sizeof(int), 1, fp);
	if (reg != 233) return 0;
	fread(usrname, 20 * sizeof(char), 1, fp);
	fread(passwd, 20 * sizeof(char), 1, fp);
	fclose(fp);
	return 1;
}
int checkInfo(char *usr, char *pwd) {
	loadInfo();
	if (strcmp(usr, usrname) == 0 && strcmp(pwd, passwd) == 0) {
		return 1;
	}
	return 0;
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
void setInfo() {
	FILE *fp; int reg = 233;
	printf("Enter the root username:");
	scanf("%s",usrname);
	printf("\nEnter the root password:");
	scanf("%s", passwd);
	if (usrname == NULL || passwd == NULL) return;
	fp = fopen("data\\info.dat", "wb+");
	fwrite(&reg,sizeof(int),1,fp);
	fwrite(usrname, 20 * sizeof(char), 1, fp);
	fwrite(passwd, 20 * sizeof(char), 1, fp);
	fclose(fp);
	FileInit("extern");
	FileInit("file");
	FileInit("data");
	printf("Setting finished.");
	SleepInt(3000);
	system("cls");
}
int checkInput(char *input) {
	char *temp=NULL,*command=NULL,origininput[0xff];
	strcpy(origininput,input);
	temp = strtok(input," ");
	if (temp == NULL) return -1;
	if((strstr(origininput," "))!=NULL) 
		command = splitString(origininput,' ');
	int t = do_command_work(temp,command, tnix_command, sizeof(tnix_command)/12);
	if (t != 0) return t;
	return 0;
}
int externCommand(char *input) {
/*	FILE *fp;
	char command[]="extern\\TNIX_ExternDesign.exe";
	int finput=0;
	fp = fopen("extern\\temp\\extern_exchange.dat","w+");
	fprintf(fp,"%s",input);
	fclose(fp);
	system(command);
	SleepInt(1500);
	fp = fopen("extern\\temp\\extern_exchange.dat", "rb");
	fread(&finput, 1, sizeof(int), fp);
	if (finput==1) {
		fclose(fp);
		return 1;
	}
	fclose(fp);*/
	char *command=NULL, *addition=NULL;
	int temp = 0;
	addition = strtok(input," ");
	command = addition;
	addition = strtok(NULL, " ");
	//printf("%s %s",command,addition);
	temp= useDllFunc(command,addition);
	if (temp != 0) printf("\n");
	return temp;
}
int checkCommandRun(char *input) {
	if (input == NULL) return 0;
	FILE *fp;
	int len = strlen(input);
	char temp[3],ctemp[0xff],path[0xff];
	strcpy(path, getSysPath());
	strcat(path, "/");
	if (len>=2) {
		memcpy(temp,input,sizeof(char)*2);
		temp[2] = '\0';
		input += 2;
		memcpy(ctemp, input, sizeof(char)*(len - 2));
		ctemp[len - 2] = '\0';
		if (strcmp(temp,"./")==0) {
			strcat(path,ctemp);
			fp = fopen(path,"r");
			if (fp!=NULL) {
				system(ctemp);
				printf("\n");
				return 1;
			}
			else {
				printf("Can\'t run \'%s\'!\n", path);
				return -1;
			}
		}
	}
	return 0;
}
void loopCheckInput() {
	char input[0xff],kinput[0xff+1]; int temp = 0;
	printf("%s",sysinfo);
	if (!loadInfo()) setInfo();
	while (1) {
		printf("%s:>",usrname);
		gets_s(input,0xff);
		strcpy(kinput,input);
		temp = checkCommandRun(kinput);
		if (temp == 1||temp==-1) continue;
		temp = 0;
		temp = checkInput(input);
		if (strcmp(input, "exit") == 0) return;
		if (temp == -1) continue;
		if (temp==0) {
			temp = externCommand(kinput);
			if (temp == 0) printf("No command \'%s\' found.\n",kinput);
		}
	}
}





