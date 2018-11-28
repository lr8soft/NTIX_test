#pragma once
#pragma comment(lib,"TNIX_NotePad.lib")
#ifndef _tnixfeatures_h_
#define _tnixfeatures_h_
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <string.h>
#include <inttypes.h> 
#include <direct.h>
#include "tnix_basic_func.h"
#endif
extern char sysinfo[] = "TNIX v0.0\nPowered by LT_lrsoft\n";
void command_ls(char *input);
void command_cd(char *input);
void command_mkdir(char *input);
void command_clear(char *input);
void command_pwd(char *input);
void command_rmdir(char *input);
void command_tcc(char *input);
void command_txteditor(char *input);
void command_cp(char *input);
void showAllCommandHelp(char *input);
void tnixnote(char *input);
typedef void (*callback)(char*);
typedef struct {
	const char *name;
	const char *info;
	callback func;
}tnix_func_define;
tnix_func_define tnix_command[] = {
	{"ls","Show all files in the folder.",command_ls},
	{"cd","Change the user path.",command_cd},
	{"mkdir","Create a new folder.",command_mkdir},
	{"clear","Clean the screen.",command_clear},
	{"pwd","Show now user path.",command_pwd},
	{"rmdir","Delete the folder.",command_rmdir},
	{"tcc","Use the TinyCC compiler.",command_tcc},
	{"tnote","Use TNIX note editor.",command_txteditor},
	{"cp","Copy those files.",command_cd},
	{"help","Show all command help.",showAllCommandHelp}
};

void command_ls(char *input) {
	char temp[0xff]; int i,jlen=0;FileInfo fd;
	char tx[0xff]="";
	unsigned fsize;
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
		fsize = (unsigned)info.size;
		printf("%s%s| %lu \n",info.name,tx,tx,fsize);
	} while (_findnext(handle2, &info) == 0);
	_findclose(handle2);
}
void command_cd(char *input) {
	char path[0xfff],wpath[0xfff];
	char originpath[] = "file\\";
	if (input==NULL) return;
	if (strcmp(input,"..")==0|| strcmp(input, ".") == 0) {
		char *tail, *cpath = getSysPath();
		if (strcmp(cpath, "file\\") == 0) return;
		removePathTail(cpath);
		char *temp = strrchr(cpath, '\\');
		int len = strlen(getSysPath());
		for (tail = temp; tail < temp+len;tail++) {
			*tail = '\0';
		}
		if (strcmp(cpath,"file")==0) {
			writeSysPath(originpath);
			return;
		}
		writeSysPath(cpath);
		return;
	}
	if (input!=NULL) {
		strcpy(path, getSysPath());
		strcat(path, input);
		int handle = _access(path,0);
		if (handle == -1) {
			printf("No folder \'%s\'.\n", input); 
			return;
		}
		else {
			strcpy(wpath, path);
			writeSysPath(wpath);
		}
	}
	else {
		printf("No folder \'%s\'.\n", input);
	}
}
void command_mkdir(char *input) {
	char newpath[0xfff];
	if (input == NULL) return;
	strcpy(newpath,getSysPath());
	strcat(newpath,input);
	int temp=_mkdir(newpath);
	if (temp != 0) printf("Can\'t create \'%s\' directory!\n",input);
}
void command_clear(char *input) {
	system("cls");
}
void command_pwd(char *input) {
	printf("%s\n",getSysPath());
}
void command_rmdir(char *input) {
	if (input == NULL) return;
	char newpath[0xfff];
	strcpy(newpath, getSysPath());
	strcat(newpath, input);
	int temp = _rmdir(newpath);
	if (temp != 0) printf("Can\'t delete \'%s\' directory!\n", input);
}
void command_tcc(char *input) {
	if (input == NULL) return;
	char tccpath[0xfff];
	strcpy(tccpath,getNowPath());
	strcat(tccpath,"\\tcc\\tcc.exe ");
	strcat(tccpath,input);
	system(tccpath);
}
void command_txteditor(char *input) {
	tnixnote(input);
}
void command_cp(char *input) {
	
}
void showAllCommandHelp(char *input) {
	int i;
	for (i = 0; i < sizeof(tnix_command) / sizeof(tnix_func_define);i++) {
		printf("%s -%s\n",tnix_command[i].name,tnix_command[i].info);
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
