#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void main (void)
{
   time_t now = time (NULL);

   struct tm tm_now = *localtime (&now);

   char s_now[sizeof "JJ/MM/AAAA HH:MM:SS"];

   strftime (s_now, sizeof s_now, "%d/%m/%Y %H:%M:%S", &tm_now);

   printf ("[get time] %s\n", s_now);
   exit(EXIT_SUCCESS);
}
