/* Example code for Software Systems at Olin College.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define NUM_TRACKS 5

char tracks[][80] = {
    "So What",
    "Freddie Freeloader",
    "Blue in Green",
    "All Blues",
    "Flamenco Sketches"
};


// Finds all tracks that contain the given string.
//
// Prints track number and title.
void find_track(char search_for[])
{
    int i;
    for (i=0; i<NUM_TRACKS; i++) {
	if (strstr(tracks[i], search_for)) {
	    printf("Track %i: '%s'\n", i, tracks[i]);
	}
    }
}

// Finds all tracks that match the given pattern.
//
// Prints track number and title.
void find_track_regex(char pattern[])
{
    regex_t regex;
    int reti = regcomp(&regex, pattern, 0);
    char msgbuf[100];
    if (reti) {
        puts("Could not compile regex pattern\n");
        exit(1);
    }
    for (int i = 0; i < NUM_TRACKS; i++) {
        reti = regexec(&regex, tracks[i], 0, NULL, 0);
        if (!reti) {
            printf("%s\n",tracks[i]);
        } else if (reti != REG_NOMATCH) {
            regerror(reti, &regex, msgbuf, sizeof(msgbuf));
            printf("Regex match failed: %s\n", msgbuf);
            exit(1);
        }
    }
    regfree(&regex);
}

// Truncates the string at the first newline, if there is one.
void rstrip(char s[])
{
    char *ptr = strchr(s, '\n');
    if (ptr) {
	*ptr = '\0';
    }
}

int main (int argc, char *argv[])
{
    char search_for[80];

    /* take input from the user and search */
    printf("Search for: ");
    fgets(search_for, 80, stdin);
    rstrip(search_for);

    find_track_regex(search_for);
    //find_track_regex(search_for);

    return 0;
}
