#include <libbuddy/buddy.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

/* Set the Buddy device's light color */
static int set_color(int which, buddy_light color)
{
    buddy_t *devices;
    devices = buddy_init();

    if (!devices)
    {
        fputs("No connected buddy devices\n", stderr);
        return 1;
    }

    int result = buddy_activate(devices, which);
    if (result != BUDDY_CORRECT)
    {
        fprintf(stderr, "Cannot activate device %d\n", which);
        return 1;
    }

    result = buddy_state(devices, BUDDY_OFF, color, 0, 0);
    if (result != BUDDY_CORRECT)
    {
        fputs("Cannot set buddy color\n", stderr);
        return 1;
    }

    buddy_free(devices);
    return 0;
}

int main(int argc, char **argv)
{
    int which = 0;
    buddy_light color = BUDDY_GREEN;

    for (int i = 1; i < argc; i++)
    {
        /* If it looks like a number, use it as the device number */
        char *endptr;
        int numarg = strtol(argv[i], &endptr, 0);
        if (endptr != argv[i])
        {
            which = numarg;
            continue;
        }

        /* Otherwise, check if it's a color name */
        if (strcasecmp(argv[i], "off") == 0)
            color = BUDDY_OFF;
        else if (strcasecmp(argv[i], "red") == 0)
            color = BUDDY_RED;
        else if (strcasecmp(argv[i], "green") == 0)
            color = BUDDY_GREEN;
        else if (strcasecmp(argv[i], "yellow") == 0)
            color = BUDDY_YELLOW;
        else if (strcasecmp(argv[i], "blue") == 0)
            color = BUDDY_BLUE;
        else if (strcasecmp(argv[i], "magenta") == 0)
            color = BUDDY_MAGENTA;
        else if (strcasecmp(argv[i], "cyan") == 0)
            color = BUDDY_CYAN;
        else if (strcasecmp(argv[i], "white") == 0)
            color = BUDDY_WHITE;
        else
        {
            /* Neither a number nor a color */
            fprintf(stderr, "Unrecognized argument: %s\n", argv[i]);
            return 1;
        }
    }

    if (set_color(which, color) != 0)
        return 2;

    return 0;
}
