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

#define NUMSSE2 130

long isse2 = 0;

static char setsse2 [NUMSSE2] [12] = {
	"addpd",
	"addsd",
	"andnpd",
	"andpd",
	"clflush",
	"cmpeqpd",
	"cmpeqsd",
	"cmplepd",
	"cmplesd",
	"cmpltpd",
	"cmpltsd",
	"cmpneqpd",
	"cmpneqsd",
	"cmpnlepd",
	"cmpnlesd",
	"cmpnltpd",
	"cmpnltsd",
	"cmpordpd",
	"cmpordsd",
	"cmppd",
	"cmpsd",
	"cmpunordpd",
	"cmpunordsd",
	"comisd",
	"cvtdq2pd",
	"cvtdq2ps",
	"cvtpd2dq",
	"cvtpd2pi",
	"cvtpd2ps",
	"cvtpi2pd",
	"cvtps2dq",
	"cvtps2pd",
	"cvtsd2si",
	"cvtsd2ss",
	"cvtsi2sd",
	"cvtss2sd",
	"cvttpd2dq",
	"cvttpd2pi",
	"cvttps2dq",
	"cvttsd2si",
	"divpd",
	"divsd",
	"lfence",
	"maskmovdqu",
	"maxpd",
	"maxsd",
	"mfence",
	"minpd",
	"minsd",
	"movapd",
	"movd",
	"movdq2q",
	"movdqa",
	"movdqu",
	"movhpd",
	"movlpd",
	"movmskpd",
	"movntdq",
	"movnti",
	"movntpd",
	"movq",
	"movq2dq",
	"movsd",
	"movupd",
	"mulpd",
	"mulsd",
	"orpd",
	"packssdw",
	"packsswb",
	"packuswb",
	"paddb",
	"paddd",
	"paddq",
	"paddsb",
	"paddsw",
	"paddusb",
	"paddusw",
	"paddw",
	"pand",
	"pandn",
	"pause",
	"pavgb",
	"pavgw",
	"pcmpeqb",
	"pcmpeqd",
	"pcmpeqw",
	"pcmpgtb",
	"pcmpgtd",
	"pcmpgtw",
	"pextrw",
	"pinsrw",
	"pmaddwd",
	"pmaxsw",
	"pmaxub",
	"pminsw",
	"pminub",
	"pmovmskb",
	"pmulhuw",
	"pmulhw",
	"pmullw",
	"pmuludq",
	"por",
	"psadbw",
	"pshufd",
	"pshufhw",
	"pshuflw",
	"pslld",
	"pslldq",
	"psllq",
	"psllw",
	"psrad",
	"psraw",
	"psrld",
	"psrldq",
	"psrlq",
	"psrlw",
	"psubb",
	"psubd",
	"psubq",
	"psubsb",
	"psubsw",
	"psubusb",
	"psubusw",
	"psubw",
	"punpckhbw",
	"punpckhdq",
	"punpckhqdq",
	"punpckhwd",
	"punpcklbw",
	"punpckldq",
};
