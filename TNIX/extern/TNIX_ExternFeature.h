#include <stdio.h> 				   #include <stdlib.h> 				   #include "TNIX_libs.h"typedef void (*callback)(char*);typedef struct {							const char *name; 							callback func;						}tnix_func_define;tnix_func_define tnix_command[] = {{"test2",test2},};int do_command_work(const char *name, char *command) { 						 int i; static int ktemp = 1; 						 for (i = 0; i < sizeof(tnix_command)/8; i++) { 							if (!(strcmp(tnix_command[i].name, name))) { 								tnix_command[i].func(command); 								return 1; 							 } 						 } 					 	return 0; 					}