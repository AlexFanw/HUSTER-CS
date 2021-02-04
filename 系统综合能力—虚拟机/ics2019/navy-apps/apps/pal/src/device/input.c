/* -*- mode: c; tab-width: 4; c-basic-offset: 3; c-file-style: "linux" -*- */
//
// Copyright (c) 2009, Wei Mingzhi <whistler_wmz@users.sf.net>.
// Portions Copyright (c) 2009, netwan.
//
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

#include "main.h"

volatile PALINPUTSTATE   g_InputState;
#ifdef PAL_HAS_JOYSTICKS
static SDL_Joystick     *g_pJoy = NULL;
#endif
BOOL                     g_fUseJoystick = TRUE;

#if defined(GPH)
#define MIN_DEADZONE -16384
#define MAX_DEADZONE 16384
#endif

#if defined(__WINPHONE__)
unsigned int g_uiLastBackKeyTime = 0;
#endif

VOID
PAL_KeyPressHandler(
	int keycode
)
/*++
  Purpose:

    Handle key press events.

  Parameters:

    [IN]  keycode - code of the key.

  Return value:

    None.

--*/
{
	switch (keycode)
	{

		case K_UP:
			g_InputState.prevdir = (gpGlobals->fInBattle ? kDirUnknown : g_InputState.dir);
			g_InputState.dir = kDirNorth;
			g_InputState.dwKeyPress |= kKeyUp;
			break;

		case K_DOWN:
			g_InputState.prevdir = (gpGlobals->fInBattle ? kDirUnknown : g_InputState.dir);
			g_InputState.dir = kDirSouth;
			g_InputState.dwKeyPress |= kKeyDown;
			break;

		case K_LEFT:
			g_InputState.prevdir = (gpGlobals->fInBattle ? kDirUnknown : g_InputState.dir);
			g_InputState.dir = kDirWest;
			g_InputState.dwKeyPress |= kKeyLeft;
			break;

		case K_RIGHT:
			g_InputState.prevdir = (gpGlobals->fInBattle ? kDirUnknown : g_InputState.dir);
			g_InputState.dir = kDirEast;
			g_InputState.dwKeyPress |= kKeyRight;
			break;

		case K_ESCAPE:
			g_InputState.dwKeyPress |= kKeyMenu;
			break;

		case K_RETURN:
		case K_SPACE:
			g_InputState.dwKeyPress |= kKeySearch;
			break;

		case K_PAGEUP:
			g_InputState.dwKeyPress |= kKeyPgUp;
			break;

		case K_PAGEDOWN:
			g_InputState.dwKeyPress |= kKeyPgDn;
			break;

		case K_r:
			g_InputState.dwKeyPress |= kKeyRepeat;
			break;

		case K_a:
			g_InputState.dwKeyPress |= kKeyAuto;
			break;

		case K_d:
			g_InputState.dwKeyPress |= kKeyDefend;
			break;

		case K_e:
			g_InputState.dwKeyPress |= kKeyUseItem;
			break;

		case K_w:
			g_InputState.dwKeyPress |= kKeyThrowItem;
			break;

		case K_q:
			g_InputState.dwKeyPress |= kKeyFlee;
			break;

		case K_s:
			g_InputState.dwKeyPress |= kKeyStatus;
			break;

		case K_f:
			g_InputState.dwKeyPress |= kKeyForce;
			break;

		case K_p:
			VIDEO_SaveScreenshot();
			break;

		default:
			break;
	}
}

VOID
PAL_KeyReleaseHandler(
	int keycode
)
/*++
  Purpose:

    Handle key release events.

  Parameters:

    [IN]  keycode - code of the key.

  Return value:

    None.

--*/
{
	switch (keycode)
	{
		case K_UP:
			if (g_InputState.dir == kDirNorth)
			{
				g_InputState.dir = g_InputState.prevdir;
			}
			g_InputState.prevdir = kDirUnknown;
			break;

		case K_DOWN:
			if (g_InputState.dir == kDirSouth)
			{
				g_InputState.dir = g_InputState.prevdir;
			}
			g_InputState.prevdir = kDirUnknown;
			break;

		case K_LEFT:
			if (g_InputState.dir == kDirWest)
			{
				g_InputState.dir = g_InputState.prevdir;
			}
			g_InputState.prevdir = kDirUnknown;
			break;

		case K_RIGHT:
			if (g_InputState.dir == kDirEast)
			{
				g_InputState.dir = g_InputState.prevdir;
			}
			g_InputState.prevdir = kDirUnknown;
			break;

		default:
			break;
	}
}

VOID
PAL_ClearKeyState(
   VOID
)
/*++
  Purpose:

    Clear the record of pressed keys.

  Parameters:

    None.

  Return value:

    None.

--*/
{
   g_InputState.dwKeyPress = 0;
}

VOID
PAL_InitInput(
   VOID
)
/*++
  Purpose:

    Initialize the input subsystem.

  Parameters:

    None.

  Return value:

    None.

--*/
{
   memset((void *)&g_InputState, 0, sizeof(g_InputState));
   g_InputState.dir = kDirUnknown;
   g_InputState.prevdir = kDirUnknown;

   //
   // Check for joystick
   //
#ifdef PAL_HAS_JOYSTICKS
   if (SDL_NumJoysticks() > 0 && g_fUseJoystick)
   {
      g_pJoy = SDL_JoystickOpen(0);
      if (g_pJoy != NULL)
      {
         SDL_JoystickEventState(SDL_ENABLE);
      }
   }
#endif
}

VOID
PAL_ShutdownInput(
   VOID
)
/*++
  Purpose:

    Shutdown the input subsystem.

  Parameters:

    None.

  Return value:

    None.

--*/
{
#ifdef PAL_HAS_JOYSTICKS
#if SDL_VERSION_ATLEAST(2,0,0)
   if (g_pJoy != NULL)
   {
      SDL_JoystickClose(g_pJoy);
      g_pJoy = NULL;
   }
#else
   if (SDL_JoystickOpened(0))
   {
      assert(g_pJoy != NULL);
      SDL_JoystickClose(g_pJoy);
      g_pJoy = NULL;
   }
#endif
#endif
}

VOID
PAL_ProcessEvent(
   VOID
)
/*++
  Purpose:

    Process all events.

  Parameters:

    None.

  Return value:

    None.

--*/
{
#ifdef PAL_HAS_NATIVEMIDI
   MIDI_CheckLoop();
#endif
   while (PAL_PollEvent(NULL));
}


