#include "tnix_func.h"
#include "tnix_features.h"
#include <io.h>
void main() {
/*	_finddata_t filedir;
	long lfdir = _findfirst("file\\*.*", &filedir);
	do {
		printf("%s\n",filedir.name);
	} while (_findnext(lfdir,&filedir)==0);
	_findclose(lfdir);*/
	loopCheckInput();
	system("pause>null");
}