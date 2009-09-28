// Ares, a tactical space combat game.
// Copyright (C) 1997, 1999-2001, 2008 Nathan Lamont
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

#ifndef ANTARES_ERROR_HPP_
#define ANTARES_ERROR_HPP_

// Error.h

#include <Base.h>

#define kErrorStrID                 800

#define kNoError                    0
#define PIX_DEPTH_ERROR             1
#define OFFSCREEN_GRAPHICS_ERROR    2
#define RESOURCE_ERROR              3
#define SPRITE_CREATE_ERROR         4
#define MEMORY_ERROR                5
#define COLOR_TABLE_ERROR           6
#define PREFERENCES_ERROR           7
#define NETWORK_ERROR               8
#define SOUND_CHANNEL_ERROR         9
#define EXPIRED_ERROR               10
#define SPRITE_DATA_ERROR           11
#define MUSIC_ERROR                 12
#define kToolboxError               21
#define kInitNetSprocketError       22
#define kNSpProtocolListError       23
#define kNSpProtocolATError         24
#define kNSpProtocolTCPIPError      25
#define kOccurredError              26
#define kNSpHostError               27
#define kNSpJoinError               28
#define kFactoryPrefsError          29
#define kNewerPrefsError            30
#define kWritePrefsError            31
#define kCharSetError               32
#define kNoMoreHandlesError         33
#define kInterfacesFileError        34
#define kDataFolderError            35
#define kAddScreenLabelError        36
#define kAdjacentError              37
#define kInitMusicLibraryError      38
#define kCreateMusicDriverError     39
#define kReadRaceDataError          40
#define kReadRotationDataError      41
#define kScenariosFileError         42
#define kScenarioDataError          43
#define kScenarioInitialDataError   44
#define kScenarioConditionDataError 45
#define kScenarioBriefDataError     46
#define kLoadSpriteError            47
#define kSoundsFileError            48
#define kLoadSoundError             49
#define kSoundDataError             50
#define kReadBaseObjectDataError    51
#define kReadObjectActionDataError  52
#define kIntraLevelLoadSpriteError  53
#define kSpritesFileError           54
#define kDataFileResourceError      55
#define kNoMoreSpriteTablesError    56
#define kLoadPictError              57
#define kLoadColorTableError        58
#define kCreatePaletteError         59
#define kGetPaletteError            60
#define kNetworkSynchError          61
#define kPlaySongError              62
#define kLoadSongError              63
#define kDemoDataFileError          64
#define kNoMoreSoundsError          65
#define kCorruptedNetDataError      66
#define kNameIDIncorrect            67
#define kOpenTransportError         68
#define kNSpMemError                69
#define kNSpInvalidAddressError     70
#define kInvalidPublicSerial1       71
#define kInvalidPublicSerial2       72
#define kOlderVersionError          73
#define kNewerVersionError          74
#define kSameSerialNumberError      75

enum errorRecoverType {
    eContinueErr,
    eQuitErr,
    eExitToShellErr,
    eContinueOnlyErr
};

void ShowErrorNoRecover ( int, const unsigned char*, int);
void ShowErrorRecover ( int, const unsigned char*, int);
void ShowSimpleStringAlert( const unsigned char*, const unsigned char*, const unsigned char*, const unsigned char*);
void ShowSimpleStrResAlert( short, short, short, short, short);
void ShowErrorAny(errorRecoverType, short, const unsigned char*, const unsigned char*, const
        unsigned char*, const unsigned char*, long, long, long, long, const char*, long);
void ShowErrorOfTypeOccurred(errorRecoverType, short, short, OSErr, const char*, long);
void MyDebugString( const unsigned char*);

#endif // ANTARES_ERROR_HPP_
