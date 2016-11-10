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

int main(int argc, char **argv)
{
    char tmp[8192];
    char *s;
    FILE *f;
    long i486 = 0, i586 = 0, i686 = 0, immx = 0, isse = 0, isse2 = 0,
        isse3 = 0, issse3 = 0, isse41 = 0, isse42 = 0, isse4a = 0, i3dnow = 0,
        i3dnowext = 0, iaes = 0, ipclmul = 0, cpuid = 0, nop = 0, call = 0,
        count = 0, unknown = 0, mov = 0;

    if (argc != 2) {
        printf("Syntax: %s <binary>\n", argv[0]);
        return EXIT_FAILURE;
    }

    snprintf(tmp, 8191, "objdump -d %s", argv[1]);

    f = popen(tmp, "r");

    if (!f) {
        printf("%s: unable to disassemble given binary argument\n", argv[1]);
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
        COMPARE(NUMNOPS, setnops, nop);
        COMPARE(NUMCALLS, setcalls, call);
        COMPARE(NUMMOVS, setmovs, mov);
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
        /* don't know this opcode */
        unknown++;
        printf(">%s<\n", s);
      DONE:;
    }                           /* end parse */

    /* delete tmp file */
    fclose(f);

    /* print statistics */
    printf("%s:", argv[1]);
    if (count) {
        printf("\tcount: %lu", count);
    }
    if (nop) {
        printf("\tnop: %lu", nop);
    }
    if (call) {
        printf("\tcall: %lu", call);
    }
    if (mov) {
        printf("\tmov: %lu", mov);
    }
    if (unknown) {
        printf("\tunknown: %lu", unknown);
    }
    if (cpuid) {
        printf("cpuid: %lu", cpuid);
    }
    if (i486) {
        printf("\ti486: %lu", i486);
    }
    if (i586) {
        printf("\ti586: %lu", i586);
    }
    if (i686) {
        printf("\ti686: %lu", i686);
    }
    if (immx) {
        printf("\tmmx: %lu", immx);
    }
    if (isse) {
        printf("\tsse: %lu", isse);
    }
    if (isse2) {
        printf("\tsse2: %lu", isse2);
    }
    if (isse3) {
        printf("\tsse3: %lu", isse3);
    }
    if (issse3) {
        printf("\tssse3: %lu", issse3);
    }
    if (isse41) {
        printf("\tsse4.1: %lu", isse41);
    }
    if (isse42) {
        printf("\tsse4.2: %lu", isse42);
    }
    if (i3dnow) {
        printf("\t3dnow!: %lu", i3dnow);
    }
    if (i3dnowext) {
        printf("\t3dnowext: %lu", i3dnowext);
    }
    if (iaes) {
        printf("\taes: %lu", iaes);
    }
    printf("\n");
    return EXIT_SUCCESS;
}
