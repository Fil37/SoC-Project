#include<stdio.h>
#include<string.h>

int main(void)
{
	char* msg = "hello world";
	int i=0;
	FILE *fp;
	fp = fopen("/dev/JTAG_UART", "w");
	if(fp){
		for(i=0; i<10; i++){
			fprintf(fp, "%s", msg);
		};
		fclose(fp);
	}
	
	return 0;
}