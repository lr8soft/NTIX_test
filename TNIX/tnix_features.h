#pragma once
#ifndef _tnixfeatures_h_
#define _tnixfeatures_h_
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <string.h>
#include "bnix_basic_func.h"
#endif
extern char sysinfo[] = "TNIX v0.0\nPowered by LT_lrsoft\n";
const char truepath[] = "file\\";
char showpath[0xff] = "";
void command_ls(char *input);
void command_cd(char *input);
typedef void (*callback)(char*);
typedef struct {
	const char *name;
	callback func;
}tnix_func_define;
tnix_func_define tnix_command[10] = {
	{"ls",command_ls},
	{"cd",command_cd}
};
void command_ls(char *input) {
	char temp[0xff]; int i,jlen=0;FileInfo fd;
	char tx[0xff]="";
	strcpy(temp, getSysPath());
	strcat(temp,"*.*");
	_finddata_t info;
	long handle = _findfirst(temp,&info);
	do{
		if (strlen(info.name) > jlen) {
			jlen = strlen(info.name);
		}
	} while (_findnext(handle, &info) == 0);
	_findclose(handle);

	long handle2= _findfirst(temp, &info);
	int kkk;
	do {
		int l;
		kkk = strlen(info.name);
		strcpy(tx,"");
		for (l = 0; l < jlen-kkk; l++) {
			if (jlen - kkk == 0) break;
			strcat(tx, " ");
		}
		printf("%s%s| %u\n",info.name,tx,tx,info.size);
	} while (_findnext(handle2, &info) == 0);
	_findclose(handle2);
}
void command_cd(char *input) {
	char path[0xfff];
	if (input!=NULL) {
		strcpy(path, getSysPath());
		strcat(path, input);
		_finddata_t info;
		long handle = _findfirst(path, &info);
		if (handle == -1) printf("No folder \'%s\'.\n", input); return;
		writeSysPath(path);
		printf("%s", showpath);
	}
	else {
		printf("No folder \'%s\'.\n", input);
	}
}
int do_command_work(const char *name, char *command,tnix_func_define *temp, int len) {
	int i; static int ktemp=1;
	for (i = 0; i < len;i++) {
		if (!(strcmp(temp[i].name, name))) {
			temp[i].func(command);
			return 1;
		}
	}
	return 0;
}