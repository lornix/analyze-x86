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

int main(int argc, char **argv)
{
    char tmp[8192];
    char *s;
    FILE *f;
    int i;
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
        s = strtok(tmp, "\t");
        if (!s) {
            continue;
        }
        s = strtok(NULL, "\t");
        if (!s) {
            continue;
        }
        s = strtok(NULL, "\t"); /* 3rd column contains instruction */
        if (!s) {
            continue;
        }
        s = strtok(s, " \r\n");  /* formatting as spaces */
        /* comparison */
        count++;
        if (!strcmp(s, "cpuid")) {
            cpuid++;
            goto DONE;
        }
        for (i = 0; i < NUMNOPS; i++) {
            if (!strcmp(s, setnops[i])) {
                nop++;
                goto DONE;
            }
        }
        for (i = 0; i < NUMCALLS; i++) {
            if (!strcmp(s, setcalls[i])) {
                call++;
                goto DONE;
            }
        }
        for (i = 0; i < NUMMOVS; i++) {
            if (!strcmp(s, setmovs[i])) {
                mov++;
                goto DONE;
            }
        }
        for (i = 0; i < NUM686; i++) {
            if (!strcmp(s, set686[i])) {
                i686++;
                goto DONE;
            }
        }
        for (i = 0; i < NUMMMX; i++) {
            if (!strcmp(s, setmmx[i])) {
                immx++;
                goto DONE;
            }
        }
        for (i = 0; i < NUMSSE; i++) {
            if (!strcmp(s, setsse[i])) {
                isse++;
                goto DONE;
            }
        }
        for (i = 0; i < NUMSSE2; i++) {
            if (!strcmp(s, setsse2[i])) {
                isse2++;
                goto DONE;
            }
        }
        for (i = 0; i < NUM486; i++) {
            if (!strcmp(s, set486[i])) {
                i486++;
                goto DONE;
            }
        }
        for (i = 0; i < NUM586; i++) {
            if (!strcmp(s, set586[i])) {
                i586++;
                goto DONE;
            }
        }
        for (i = 0; i < NUMSSE3; i++) {
            if (!strcmp(s, setsse3[i])) {
                isse3++;
                goto DONE;
            }
        }
        for (i = 0; i < NUMSSSE3; i++) {
            if (!strcmp(s, setssse3[i])) {
                issse3++;
                goto DONE;
            }
        }
        for (i = 0; i < NUMSSE41; i++) {
            if (!strcmp(s, setsse41[i])) {
                isse41++;
                goto DONE;
            }
        }
        for (i = 0; i < NUMSSE42; i++) {
            if (!strcmp(s, setsse42[i])) {
                isse42++;
                goto DONE;
            }
        }
        for (i = 0; i < NUMSSE4a; i++) {
            if (!strcmp(s, setsse4a[i])) {
                isse4a++;
                goto DONE;
            }
        }
        for (i = 0; i < NUM3DNOW; i++) {
            if (!strcmp(s, set3dnow[i])) {
                i3dnow++;
                goto DONE;
            }
        }
        for (i = 0; i < NUM3DNOWEXT; i++) {
            if (!strcmp(s, set3dnowext[i])) {
                i3dnowext++;
                goto DONE;
            }
        }
        for (i = 0; i < NUMAES; i++) {
            if (!strcmp(s, setaes[i])) {
                iaes++;
                goto DONE;
            }
        }
        for (i = 0; i < NUMPCLMUL; i++) {
            if (!strcmp(s, setpclmul[i])) {
                ipclmul++;
                goto DONE;
            }
        }
        /* don't know this opcode */
        unknown++;
        printf(">%s<\n",s);
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
