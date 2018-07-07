#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef _WIN32

#define _DRIVE getenv("homedrive")
#define _PATH getenv("homepath")
#define _MKDIR_(__arg__) mkdir(__arg__)

#endif
#ifdef linux

#include <sys/stat.h>

#define _DRIVE ""
#define _PATH getenv("HOME")
#define _MKDIR_(__arg__) mkdir(__arg__,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH )

#endif

void run_cmd(char* data) {

    FILE* fptr = fopen(data, "r");
    fptr == NULL? printf("The command is not exist\n"), exit(0), NULL : NULL;

    char cmdtest[1000] = {'\0'};
    int temp = -1, cnt = 0;
    while ((temp = fgetc(fptr)) != -1) cmdtest[cnt++] = (char)temp;
    cmdtest[cnt] = '\0';

    system(cmdtest);
    fclose(fptr);
}

void change_cmd(char* data, char* cmd) {

    FILE* fptr = fopen(data, "w");
    fwrite(cmd, strlen(cmd), 1, fptr);

    fclose(fptr);

    printf("Changed the command to \'%s \'\n", cmd);
}

int main(int argc, char* argv[])
{
	if (argc == 1) {
        printf("Quick Command Version :1.0.0.\n");
        printf("Copyright@ GPL v2.0 Made by YXJIANG and Yang Jiazhen.\n");
        return 0;
    }

	char data[1000];
	memset(data, 0 , sizeof(data));
	strcat(strcat(strcpy(data, _DRIVE), _PATH), "/.qcdata/");
    _MKDIR_(data);

    strcat(data, argv[1]);

    char cmdtest[1000] = {'\0'};
    for (int i=2; i<argc; ++i) {
        strcat(cmdtest, " ");
        strcat(cmdtest, argv[i]);
    }

    if (strlen(cmdtest) == 0) {
        run_cmd(data);
    } else {
        change_cmd(data, cmdtest);
    }
	
	return 0;
}

