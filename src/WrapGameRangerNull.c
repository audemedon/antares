/*
Ares, a tactical space combat game.
Copyright (C) 1997, 1999-2001, 2008 Nathan Lamont

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

/******************************************\
|**| Wrap_GameRanger.c
\******************************************/

#pragma mark **INCLUDES**
/******************************************\
|**| #includes
\******************************************/

#pragma mark _system includes_
/* - system
*******************************************/

#pragma mark _third party includes_
/* - third party libraries
*******************************************/
#include "GameRanger.h"

#pragma mark _bp libraries includes_
/* - bp libraries
*******************************************/

#pragma mark _this library includes_
/* - this project
*******************************************/
#include "Wrap_GameRanger.h"
#include "NetSprocketGlue.h"

#pragma mark **DEFINITIONS**
/******************************************\
|**| #defines
\******************************************/

/* - definitions
*******************************************/

#pragma mark _macros_
/* - macros
*******************************************/

#pragma mark **TYPEDEFS**
/******************************************\
|**| typedefs
\******************************************/

#pragma mark **EXTERNAL GLOBALS**
/******************************************\
|**| external globals
\******************************************/

#pragma mark **PRIVATE GLOBALS**
/******************************************\
|**| private globals
\******************************************/

#pragma mark **PRIVATE PROTOTYPES**
/******************************************\
|**| private function prototypes
\******************************************/

#pragma mark **PRIVATE FUNCTIONS**
/******************************************\
|**| private functions
\******************************************/

#pragma mark **PUBLIC FUNCTIONS**
/******************************************\
|**| public functions
\******************************************/

Boolean	Wrap_UseGameRanger( void)
{
	return true;
}

OSErr		Wrap_GRInstallStartupHandler(void)
{
	return noErr;
}

OSErr		Wrap_GRInstallResumeHandler(void)
{
	return noErr;
}

Boolean		Wrap_GRCheckAEForCmd(const AppleEvent *theEvent)
{
	#pragma unused( theEvent)
	
	return false;
}

Boolean		Wrap_GRCheckFileForCmd(void)
{
	return false;
}

Boolean		Wrap_GRCheckForAE(void)
{
	return false;
}

Boolean		Wrap_GRIsWaitingCmd(void)
{
	return false;
}

void		Wrap_GRGetWaitingCmd(void)
{
	
}

Boolean		Wrap_GRIsCmd(void)
{
	return false;
}

Boolean		Wrap_GRIsHostCmd(void)
{
	return false;
}

Boolean		Wrap_GRIsJoinCmd(void)
{
	return false;
}


char*		Wrap_GRGetHostGameName(void)
{
	return nil;
}

UInt16		Wrap_GRGetHostMaxPlayers(void)
{
	return 0;
}

UInt32		Wrap_GRGetJoinAddress(void)
{
	return 0;
}

char*		Wrap_GRGetPlayerName(void)
{
	return nil;
}

UInt16		Wrap_GRGetPortNumber(void)
{
	return 0;
}


void		Wrap_GRReset(void)
{

}


void		Wrap_GRHostReady(void)
{
	
}

void		Wrap_GRGameBegin(void)
{

}

void		Wrap_GRStatScore(SInt32 score)
{
	#pragma unused( score)	
}

void		Wrap_GRStatOtherScore(SInt32 score)
{
	#pragma unused( score)	
}

void		Wrap_GRGameEnd(void)
{
	
}

void		Wrap_GRHostClosed(void)
{
	
}


OSErr		Wrap_GROpenGameRanger(void)
{
	return noErr;
}

Boolean
Wrap_GRNSpDoModalHostDialog			(NSpProtocolListReference  ioProtocolList,
								 Str31 					ioGameName,
								 Str31 					ioPlayerName,
								 Str31 					ioPassword,
								 NSpEventProcPtr 		inEventProcPtr)
{
	return Glue_NSpDoModalHostDialog( ioProtocolList, ioGameName, ioPlayerName, ioPassword,
		inEventProcPtr);
}

NSpAddressReference
Wrap_GRNSpDoModalJoinDialog			(ConstStr31Param 		inGameType,
								 ConstStr255Param 		inEntityListLabel,
								 Str31 					ioName,
								 Str31 					ioPassword,
								 NSpEventProcPtr 		inEventProcPtr)
{
	return Glue_NSpDoModalJoinDialog( inGameType, inEntityListLabel, ioName, ioPassword,
		inEventProcPtr);
}

void
Wrap_GRNSpReleaseAddressReference	(NSpAddressReference	inAddr)
{
	Glue_NSpReleaseAddressReference( inAddr);
}