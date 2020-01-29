/* getopt.c, getopt.h: (yet another) improved getopt clone
Daniel J. Bernstein, brnstnd@nyu.edu.
No dependencies.
Requires stdio.
10/20/91: Removed -DGETOPT_SHUT_UP. [sigh]
8/26/91: Added -DGETOPT_SHUT_UP.
8/25/91: Changed getopt to not skip blank arguments.
7/6/91: Baseline. getopt 1.0, public domain.
No known patent problems.

This is a clone of the usual getopt() functions. It includes opterr so
that you can turn off error handling, optpos so that you can find out
exactly where the processing is up to (instead of just which argument),
optproblem so that you can accurately diagnose errors yourself, and
optprogname so that you can set the program name for getopt-generated
errors. getopt() takes much more care to ensure that all the variables
still make sense upon errors and EOF. (optproblem is a character. If
argv[optind] is 0, the problem is a missing argument; otherwise it's an
illegal option character.) Unless you define GETOPTORIGDEF, the header
file redefines all names so that you don't have to worry about conflicts
with libc. Finally, the code is public-domain, so you should feel free
to use these extra features in your own programs and just attach a copy
of this.

Note that optind and optpos can be read (or set) any time, but the
official getopt interface only defines optind when getopt() returns EOF.
We define optproblem only when getopt() returns '?', optarg all the
time, and optprogram only after getopt() has been called at least once.

*/

#include <dbg.h>
#include <stdio.h> /* for EOF and stderr---talk about immodularity! */
#include <getopt.h>

int optind = 1;
int optpos = 0;
int opterr = 1;
char *optarg = 0;
int optproblem = 0;
char *optprogname = 0;
int opteof = EOF;

int getopt(int argc, char **argv, char *opts)
{
 int c;
 char *s;

 optarg = 0;
 if (!optprogname)
  {
   optprogname = *argv;
   if (!optprogname) /* oh boy */
     optprogname = ""; /*XXX*/
   for (s = optprogname;*s;++s)
     if (*s == '/')
       optprogname = s + 1;
  }
 if (!argv || (optind >= argc) || !argv[optind])
   return opteof;
 while (optpos && !argv[optind][optpos])
  {
   /* we simply skip blank arguments... not any more */
   ++optind;
   optpos = 0;
   if ((optind >= argc) || !argv[optind])
     return opteof;
  }
 if (!optpos)
  {
   if (argv[optind][0] != '-')
     return opteof;
   ++optpos;
   c = argv[optind][1];
   if ((c == '-') || (c == 0))
    {
     /* XXX: this behavior of "-" is stupid */
     if (c) {
       c = argv[optind][2];
       if (c != 0) {
         optarg = argv[optind] + 2;
         ++optind;
         optpos = 0;
         return '-';
       }
       ++optind;
     }
     optpos = 0;
     return opteof;
    }
   /* otherwise c is reassigned below */
  }
 c = argv[optind][optpos];
 ++optpos;
 s = opts;
 while (*s)
  {
   if (c == *s)
    {
     if (s[1] == ':')
      {
       optarg = argv[optind] + optpos;
       ++optind;
       optpos = 0;
       if (!*optarg)
        {
         optarg = argv[optind];
         if ((optind >= argc) || !optarg) /* argument past end */
          {
           optproblem = c;
           if (opterr)
             fprintf(stderr,"%s: option requires an argument -- %c\n"
               ,optprogname,c);
           return '?';
          }
	 ++optind;
        }
      }
     return c;
    }
   ++s;
   if (*s == ':')
     ++s;
  }
 optproblem = c;
 if (opterr)
   fprintf(stderr,"%s: illegal option -- %c\n",optprogname,c);
 return '?';
}
