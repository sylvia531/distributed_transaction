#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#include <float.h>
#include <time.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>  
#include <unistd.h>

int main(int argc, char *argv[]){
	
	char a[1024] = "Hello";
	size_t hash = genStrHash(a);
	
	printf("hash: %u\n", hash);
	
	return 0;
}