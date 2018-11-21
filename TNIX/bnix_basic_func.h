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
int getMaxFromFile(FileInfo fd,int len) {
	int i,max=NULL;
	for (i = 0; i < len-1;i++) {
		max = strlen(fd.finfo[i].name);
		if (strlen(fd.finfo[i+1].name)>max) {
		//	max = strlen(fd[i + 1].name);
		}
	}
	return max;
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
	fputs(path,fp);
	fclose(fp);
}