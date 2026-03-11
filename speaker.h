/**
Software License Agreement (BSD)

\authors   Chris Iverach-Brereton <ve4cib@gmail.com>
\copyright Copyright (c) 2012, 2026 Chris Iverach-Brereton, All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that
the following conditions are met:
 * Redistributions of source code must retain the above copyright notice, this list of conditions and the
   following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
   following disclaimer in the documentation and/or other materials provided with the distribution.
 * Neither the name of Clearpath Robotics nor the names of its contributors may be used to endorse or promote
   products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WAR-
RANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, IN-
DIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef SPEAKER_H
#define SPEAKER_H

//
// the following definitions were copied from sound.h in AVR-GCC
// they define various pitches that can be made by the speaker
//
#define A   2273        // tone 0
#define xA  2145        // tone 1
#define Ax  2145        // tone 1
#define B   2025        // tone 2
#define C0  1911        // tone 3
#define xC0 1804        // ...
#define Cx0 1804
#define D0  1703
#define xD0 1607
#define Dx0 1607
#define E0  1517
#define F0  1432
#define xF0 1351
#define Fx0 1351
#define G0  1275
#define xG0 1204
#define Gx0 1204
#define A0  1136
#define xA0 1073
#define Ax0 1073
#define B0  1012
#define C1  956
#define xC1 902
#define Cx1 902
#define D1  851
#define xD1 804
#define Dx1 804
#define E1  758
#define F1  716
#define xF1 676
#define Fx1 676
#define G1  638
#define xG1 602
#define Gx1 602
#define A1  568
#define xA1 536
#define Ax1 536

#define B1  506
#define C2  478
#define xC2 451
#define Cx2 451
#define D2  426
#define xD2 402
#define Dx2 402
#define E2  379
#define F2  356
#define xF2 338
#define Fx2 338
#define G2  319
#define xG2 301
#define Gx2 301
#define A2  284
#define xA2 268
#define Ax2 268
#define B2  253
#define C3  239
#define xC3 225
#define Cx3 225
#define D3  213
#define xD3 201
#define Dx3 201
#define E3  190
#define F3  179
#define xF3 169
#define Fx3 169
#define G3  159
#define xG3 150
#define Gx3 150
#define A3  142
#define xA3 134
#define Ax3 134
#define B3  127
#define C4  119

//note duations
#define WHOLE 	   120
#define HALF  		80
#define QUARTER		40
#define EIGHTH		20
#define SIXTEENTH	10

#include <inttypes.h>

//
// structure defining a pitch and a duration
// used to play a tune
//
struct NOTE_TYPE
{
	uint16_t note;
	uint16_t duration;
};

typedef struct NOTE_TYPE note_t;

extern uint8_t volume;

void init_Speaker(void);
void playNote(uint16_t pitch, uint16_t volume);

#endif
