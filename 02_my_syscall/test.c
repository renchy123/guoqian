#include <unistd.h>
#include <sys/syscall.h>

int main(void)
{
	syscall(352);

	return 0;
}
