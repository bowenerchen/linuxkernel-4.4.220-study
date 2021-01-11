#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define DEMO_DEV_NAME "/dev/demo_dev"

int main()
{
    char buffer[64];
    int fd = -1;
    int i = 0;

    fd = open(DEMO_DEV_NAME, O_RDONLY);
    if (fd < 0)
    {
        printf("open device %s failed\n", DEMO_DEV_NAME);
        return -1;
    }

    memset(buffer, sizeof(buffer), 0x00);
    read(fd, buffer, 64);
    close(fd);
    printf("read from %s, length=%d, data=[", DEMO_DEV_NAME, sizeof(buffer));
    for (i = 0; i < sizeof(buffer); i++)
    {
        if (i == sizeof(buffer) - 1)
        {
            printf("%d", buffer[i]);
        }
        else
        {
            printf("%d,", buffer[i]);
        }
    }
    printf("]\n");
    return 0;
}