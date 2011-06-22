#include "redpill.h"
#include "io.h"
#include "rpstring.h"



int main(void)
{

    char *content = rp_slurp("csv.txt");
    char **broken = rp_split(content, ",");

    int i = 0;
    for (; broken[i]; i++)
	printf("\n\tString %u: %s", i, broken[i]);

    printf("\n\n");
    return 0;
}
