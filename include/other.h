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

#define NUMCALLS 3

long calls = 0;

static char setcalls [NUMCALLS] [6] = {
	"call",
	"callq",
        "lcall",
};

#define NUMJMPS 22

long jmps = 0;

static char setjmps [NUMJMPS] [6] = {
	"jmp",
        "jne",
        "jmpq",
        "je",
        "jbe",
	"je,pn",
	"jcxz",
	"jno",
	"jnp",
	"jo",
	"jecxz",
	"jp",
	"jns",
	"jae",
	"jl",
	"jb",
	"jge",
	"js",
	"ja",
	"jg",
	"jle",
        "ljmp",
};

#define NUMMOVS 2

long movs = 0;

static char setmovs [NUMMOVS] [5] = {
	"mov",
        "movb",
};

#define NUMNOPS 3

long nops = 0;

static char setnops [NUMNOPS] [5] = {
	"nop",
        "nopw",
        "nopl",
};

#define NUMRETS 2

long rets = 0;

static char setrets [NUMRETS] [5] = {
        "ret",
        "retq",
};

#define NUMSTACK 10

long stack = 0;

static char setstack [NUMSTACK] [6] = {
	"push",
        "pusha",
        "pushf",
        "pushl",
        "pushq",
	"pop",
        "popa",
        "popf",
        "popl",
        "popq",
};
