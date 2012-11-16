#include <stdio.h>
#include <stdlib.h>

#include "xc164cs.h"

int main()
{
	struct ecpu* pcpu = create_cpu();
	release_cpu(pcpu);

    printf("Hello world!\n");
    return 0;
}
