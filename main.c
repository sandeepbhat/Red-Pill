#include "redpill.h"
#include "io.h"

int main(void)
{


	char **code = rp_loadtxt("redpill.c");

	rp_printstrings(code, "\n", stdout);

	return 0;
}
