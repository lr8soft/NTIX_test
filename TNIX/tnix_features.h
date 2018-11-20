#pragma once
#ifndef _tnixfeatures_h_
#define _tnixfeatures_h_
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <string.h>
#include "bnix_basic_func.h"
#endif
void command_ls();
typedef void (*callback)(void);
typedef struct {
	const char *name;
	callback func;
}tnix_func_define;
extern char sysinfo[] = "TNIX v0.0\nPowered by LT_lrsoft\n";
const char truepath[] = "file\\";
char showpath[128]="";
tnix_func_define tnix_command[10] = {
	{"ls",command_ls}
};
void command_ls() {
	char temp[0xff]; int i,jlen=0,l;FileInfo fd;
	char tx[0xff]="";
	strcpy(temp,truepath);
	strcat(temp, showpath);
	strcat(temp,"*.*");
	_finddata_t info;
	long handle = _findfirst(temp,&info);
	do{
//		fd.finfo[fd.len].name = info.name;
//		fd.finfo[fd.len].size = info.size;
		if (strlen(info.name) > jlen) {
			jlen = strlen(info.name);
		}
//		printf("%s %lf\n", fd.finfo[fd.len].name,fd.finfo[fd.len].size);
//		fd.len++;
	} while (_findnext(handle, &info) == 0);
//	printf("%s %lf",fd.finfo[2].name,fd.finfo[2].size);
	_findclose(handle);
//	for (l = 0; l < jlen; l++) {
//		if (l == 0) strcpy(tx, " "); continue;
//		strcat(tx, " ");
//	}
/*	for (i = 0; i < fd.len;i++) {
		printf("%s",fd.finfo[i].name);
		printf("%s|%s",tx,tx);
		printf("%lf\n",fd.finfo[i].size);
	}*/
	handle = _findfirst(temp, &info);
	int kkk;
	do {
		kkk = strlen(info.name);
		printf("%d %d", jlen,kkk);
		for (l = 0; l < jlen-kkk; l++) {
			strcat(tx, " ");
		}
		printf("%s%s|%s%lf\n",info.name,tx,tx,info.size);
	} while (_findnext(handle, &info) == 0);
	_findclose(handle);
}
int do_command_work(const char *name, tnix_func_define *temp, int len) {
	int i; static int ktemp=1;
	for (i = 0; i < len;i++) {
		if (!(strcmp(temp[i].name, name))) {
			temp[i].func();
			return 1;
		}
	}
	return 0;
}