#include "redpill.h"
#include "io.h"

int main(void)
{

	char **sourcecode = rp_loadtxt("teste.txt");
	rp_printstrings(sourcecode, "\n", stdout);
	return 0;
}
