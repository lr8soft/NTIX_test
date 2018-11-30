#pragma once
#ifndef _tnixbasic_func_h_
#define _tnixbasic_func_h_
#include <stdio.h>
#include <stdlib.h>
#endif
typedef struct {
	char *name;
	double size;
}FInfo;
typedef struct {
	FInfo finfo[0xff];
	int len=0;
}FileInfo;
/*int getMaxFromFile(FileInfo fd,int len) {
	int i,max=NULL;
	for (i = 0; i < len-1;i++) {
		max = strlen(fd.finfo[i].name);
		if (strlen(fd.finfo[i+1].name)>max) {
		//	max = strlen(fd[i + 1].name);
		}
	}
	return max;
}*/
void makePathStandard(char *path) {
	int len, klen;
	char *lastword;
	len = strlen(path);
	lastword = strrchr(path, '\\');
	if (strcmp(lastword, path + len - 1) != 0) {
		strcat(path, "\\");
	}
}
char *getSysPath() {
	FILE *fp;
	static char path[0xff];
	fp = fopen("data\\path.dat","r");
	if (fp == NULL) return NULL;
	fgets(path,0xff,fp);
	fclose(fp);
	return path;
}
void writeSysPath(char *path) {
	FILE *fp;
	fp = fopen("data\\path.dat", "w");
	makePathStandard(path);
	fputs(path,fp);
	fclose(fp);
}
void removePathTail(char *path) {
	char *tail;
	int len = strlen(path);
	if (strcmp(path + len - 1,"\\")==0) {
		*(path + len - 1) = '\0';
	}
}
/*char *removeStringFromString(char *string,char *remove) {
	static char rechar[0xff];
	
	return rechar;
}*/
char *getNowPath() {
	static char path[0xfff];
	_getcwd(path,0xfff);
	return path;
}
void setNewInfo() {
	FILE *fp; int reg=233;
	char usrname[20], passwd[20];
	printf("Enter the new root username:");
	scanf("%s", usrname);
	printf("\nEnter the new root password:");
	scanf("%s", passwd);
	if (usrname == NULL || passwd == NULL) return;
	fp = fopen("data\\info.dat", "wb+");
	fwrite(&reg,sizeof(int),1,fp);
	fwrite(usrname, 20 * sizeof(char), 1, fp);
	fwrite(passwd, 20 * sizeof(char), 1, fp);
	fclose(fp);
}
void FileInit(const char *name) {
	char folder[0xff];
	strcpy(folder, getNowPath());
	strcat(folder, "\\");
	strcat(folder, name);
	_mkdir(folder);
}
void TNIXError(const char *info) {
	printf("TNIX Err:%s\n",info);
}