#include <stdio.h> 
				   #include <stdlib.h> 
				   #include "TNIX_libs.h"
typedef void (*callback)(char*);
typedef struct {
							const char *name; 
							callback func;
						}tnix_func_define;
tnix_func_define tnix_command[] = {
{"test",test},{"test2",test2}};
char *splitString(char *input, int split) {
 							char *temp, *ftemp; int len, delta, i = 0;
 							static char rechar[0xff];
							memset(rechar, 0, sizeof(rechar));
 							temp = strchr(input, split); 
							len = strlen(input); 
							delta = temp - input; 
							for (ftemp = temp + 1; ftemp < temp + len - delta; ftemp++) { 
								rechar[i] = *ftemp;
 								i++;
 							} 							return rechar;
						    }
int do_func(const char *name, char *command) { 
						 int i; static int ktemp = 1; 
						 for (i = 0; i < sizeof(tnix_command)/8; i++) {
 							if (!(strcmp(tnix_command[i].name, name))) { 
								tnix_command[i].func(command);
 								return 1; 
							 } 
						 } 
					 	return 0;
 					}
