/*      analyze-x86
 *
 *      Copyright 2010 Meya Argenta <fierevere@ya.ru>
 *      Copyright 2012 Alexey Shvetsov <alexxy@gentoo.org>
 *
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include "analyze-x86.h"

#define COMPARE(num,array,counter) { \
        for (int i = 0; i < (num); i++) { \
            if (!strcmp(s, (array)[i])) { \
                (counter)++; \
                goto DONE; \
            } \
        } \
}
#define SHOW(var, str) { \
    if (var) { \
        printf("\t%s: %lu (%lu%%)", str, var, ((var * 100) / count)); \
    } \
} 

int main(int argc, char **argv)
{
    char tmp[8192];
    char *s;
    FILE *f;
    long count = 0, unknown = 0, cpuid = 0;

    if (argc != 2) {
        fprintf(stderr, "Syntax: %s <binary>\n", argv[0]);
        return EXIT_FAILURE;
    }

    snprintf(tmp, 8191, "objdump -d %s", argv[1]);

    f = popen(tmp, "r");

    if (!f) {
        fprintf(stderr, "%s: unable to disassemble given binary argument\n", argv[1]);
        return EXIT_FAILURE;
    }

    while (fgets(tmp, 8191, f)) {
        s = strtok(tmp, "\t");  /* first column */
        s = strtok(NULL, "\t"); /* second column */
        s = strtok(NULL, "\t"); /* 3rd column contains instruction */
        s = strtok(s, " \r\n"); /* only want first column of instruction */
        /* did we end up with an empty string? ignore it */
        if (!s) {
            continue;
        }
        /* total count of instructions */
        count++;
        /* do we know this instruction? */
        if (!strcmp(s, "cpuid")) {
            cpuid++;
            goto DONE;
        }
        COMPARE(NUMNOPS, setnops, nops);
        COMPARE(NUMCALLS, setcalls, calls);
        COMPARE(NUMRETS, setrets, rets);
        COMPARE(NUMSTACK, setstack, stack);
        COMPARE(NUMMOVS, setmovs, movs);
        COMPARE(NUMJMPS, setjmps, jmps);
        COMPARE(NUM686, set686, i686);
        COMPARE(NUMMMX, setmmx, immx);
        COMPARE(NUMSSE, setsse, isse);
        COMPARE(NUMSSE2, setsse2, isse2);
        COMPARE(NUM486, set486, i486);
        COMPARE(NUM586, set586, i586);
        COMPARE(NUMSSE3, setsse3, isse3);
        COMPARE(NUMSSSE3, setssse3, issse3);
        COMPARE(NUMSSE41, setsse41, isse41);
        COMPARE(NUMSSE42, setsse42, isse42);
        COMPARE(NUMSSE4a, setsse4a, isse4a);
        COMPARE(NUM3DNOW, set3dnow, i3dnow);
        COMPARE(NUM3DNOWEXT, set3dnowext, i3dnowext);
        COMPARE(NUMAES, setaes, iaes);
        COMPARE(NUMPCLMUL, setpclmul, ipclmul);
        COMPARE(NUMOTHER, setother, other);
        /* don't know this opcode */
        unknown++;
        fprintf(stderr, "\t\"%s\",\n", s);
      DONE:;
    }                           /* end parse */

    /* delete tmp file */
    fclose(f);

    /* print statistics */
    printf("%s:", argv[1]);
    SHOW(count, "count");
    SHOW(unknown, "unk");
    SHOW(other, "other");
    SHOW(nops, "nop");
    SHOW(calls, "call");
    SHOW(rets, "ret");
    SHOW(stack, "stack");
    SHOW(movs, "mov");
    SHOW(jmps, "jmp");
    SHOW(cpuid, "cpuid");
    SHOW(i486, "i486");
    SHOW(i586, "i586");
    SHOW(i686, "i686");
    SHOW(immx, "mmx");
    SHOW(isse, "sse");
    SHOW(isse2, "sse2");
    SHOW(isse3, "sse3");
    SHOW(issse3, "ssse3");
    SHOW(isse41, "sse4.1");
    SHOW(isse42, "sse4.2");
    SHOW(isse4a, "sse4a");
    SHOW(i3dnow, "3dnow");
    SHOW(i3dnowext, "3dnowext");
    SHOW(iaes, "aes");
    SHOW(ipclmul, "pclmul");
    printf("\n");
    return EXIT_SUCCESS;
}
