#include "sound.h"

VOID
RIX_FillBuffer(
   LPBYTE     stream,
   INT        len
)
/*++
  Purpose:

    Fill the background music into the sound buffer. Called by the SDL sound
    callback function only (sound.c: SOUND_FillAudio).

  Parameters:

    [OUT] stream - pointer to the stream buffer.

    [IN]  len - Length of the buffer.

  Return value:

    None.

--*/
{
	return ;
}

INT
RIX_Init(
   LPCSTR     szFileName
)
/*++
  Purpose:

    Initialize the RIX player subsystem.

  Parameters:

    [IN]  szFileName - Filename of the mus.mkf file.

  Return value:

    0 if success, -1 if cannot allocate memory, -2 if file not found.

--*/
{
	return 0;
}

VOID
RIX_Shutdown(
   VOID
)
/*++
  Purpose:

    Shutdown the RIX player subsystem.

  Parameters:

    None.

  Return value:

    None.

--*/
{
	return ;
}

VOID
RIX_Play(
   INT       iNumRIX,
   BOOL      fLoop,
   FLOAT     flFadeTime
)
/*++
  Purpose:

    Start playing the specified music.

  Parameters:

    [IN]  iNumRIX - number of the music. 0 to stop playing current music.

    [IN]  fLoop - Whether the music should be looped or not.

    [IN]  flFadeTime - the fade in/out time when switching music.

  Return value:

    None.

--*/
{
	return ;
}
