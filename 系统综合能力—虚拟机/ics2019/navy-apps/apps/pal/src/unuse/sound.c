/* -*- mode: c; tab-width: 4; c-basic-offset: 3; c-file-style: "linux" -*- */
//
// Copyright (c) 2009, Wei Mingzhi <whistler_wmz@users.sf.net>.
// All rights reserved.
//
// This file is part of SDLPAL.
//
// SDLPAL is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#include "palcommon.h"
#include "_common.h"
#include "sound.h"
#include "rixplay.h"
#include "util.h"

#ifdef PAL_HAS_NATIVEMIDI
#include "midi.h"
#endif

#ifdef PAL_HAS_MP3
#include "libmad/music_mad.h"
#endif

BOOL         g_fNoSound = FALSE;
BOOL         g_fNoMusic = FALSE;

#ifdef PAL_HAS_NATIVEMIDI
BOOL         g_fUseMidi = FALSE;
#endif

#ifdef __SYMBIAN32__
INT          g_iVolume  = SDL_MIX_MAXVOLUME * 0.1;
#endif

#ifdef PAL_CLASSIC
int          g_iCurrChannel = 0;
#endif


INT
SOUND_OpenAudio(
   VOID
)
/*++
  Purpose:

    Initialize the audio subsystem.

  Parameters:

    None.

  Return value:

    0 if succeed, others if failed.

--*/
{
   return 0;
}

VOID
SOUND_CloseAudio(
   VOID
)
/*++
  Purpose:

    Close the audio subsystem.

  Parameters:

    None.

  Return value:

    None.

--*/
{
	return;
}

VOID
SOUND_PlayChannel(
   INT    iSoundNum,
   INT    iChannel
)
/*++
  Purpose:

    Play a sound in voc.mkf file.

  Parameters:

    [IN]  iSoundNum - number of the sound.

    [IN]  iChannel - the number of channel (0 or 1).

  Return value:

    None.

--*/
{
	return;
}

VOID
PAL_PlayMUS(
   INT       iNumRIX,
   BOOL      fLoop,
   FLOAT     flFadeTime
)
{
	return;
}

BOOL
SOUND_PlayCDA(
   INT    iNumTrack
)
/*++
  Purpose:

    Play a CD Audio Track.

  Parameters:

    [IN]  iNumTrack - number of the CD Audio Track.

  Return value:

    TRUE if the track can be played, FALSE if not.

--*/
{
   return FALSE;
}
