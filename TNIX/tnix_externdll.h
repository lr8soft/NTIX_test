#pragma once
#ifndef _tnix_externdll_
#define _tnix_externdll_
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "tnix_basic_func.h"
#endif
typedef void(*externfunc)(char*);
typedef struct {
	const char *name;
	externfunc efunc;
}ExternDllFunc;
ExternDllFunc dllAFunc[10];
int dllFuncCount = 0;
/*void loadExternDll(char *path,char *funcname) {
	HINSTANCE edll = LoadLibrary(path);
	externfunc efunc = NULL;
	efunc = (externfunc)GetProcAddress(edll,funcname);
	if (edll&&efunc) {
		if (dllFuncCount >= 10) {
			TNIXError("Max functions count is 10!");
			return;
		}
		else {
			dllAFunc[dllFuncCount].name = funcname;
			dllAFunc[dllFuncCount].efunc = efunc;
			dllFuncCount++;
		//	FreeLibrary(edll);
		}
	}
	else {
		char info[0xff]="Can\'t load ";
		strcat(info,path);
		strcat(info, ":");
		strcat(info, funcname);
		TNIXError(info);
	}
}
int doExternFunc(char *funcname,char *command) {
	int i;
	if (funcname == NULL) return 0;
	for (i = 0; i < dllFuncCount;i++) {
		printf("%s %s\n", dllAFunc[i].name,funcname);
		if (strcmp(dllAFunc[i].name,funcname)==0) {
			dllAFunc[i].efunc(command);
			return 1;
		}
	}
	//dllAFunc[0].efunc(a);
	return 0;
}
void externDllInit() {
	FILE *fp;
	memset(dllAFunc,0,sizeof(dllAFunc));
	char config[0xff] = {0}, *dllpath=NULL,*dlltemp=NULL;
	fp = fopen("data\\dll.dat","r+");
	if (fp == NULL) return;
	fgets(config,0xff,fp);
	dlltemp = strtok(config,"|");
	if (dlltemp == NULL) return;
	dllpath = dlltemp;
	while ((dlltemp = strtok(NULL, ","))!=NULL) {
		loadExternDll(dllpath, dlltemp); 
	}
	fclose(fp);
}*/
int useDllFunc(char *funcname,char *command) {
	FILE *fp;
	memset(dllAFunc, 0, sizeof(dllAFunc));
	char config[0xff] = { 0 }, *dllpath = NULL;
	fp = fopen("data\\dll.dat", "r+");
	if (fp == NULL) return 0;
	fgets(config, 0xff, fp);
	fclose(fp);
	dllpath = strtok(config, "|");
	if (dllpath == NULL) return 0;
	HINSTANCE edll = LoadLibrary(dllpath);
	externfunc efunc = NULL;
	efunc = (externfunc)GetProcAddress(edll, funcname);
	if (efunc&&edll) {
		efunc(command);
		return 1;
	}
	else {
		while ((dllpath=strtok(NULL,"|"))!=NULL) {
			edll = LoadLibrary(dllpath);
			efunc = (externfunc)GetProcAddress(edll, funcname);
			if (edll&&efunc) {
				efunc(command);
				return 1;
			}
			else {
				continue;
			}
		}
	}
	return 0;
}