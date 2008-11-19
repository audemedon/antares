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

#ifndef ANTARES_PLAYER_INTERFACE_ITEMS_HPP_
#define ANTARES_PLAYER_INTERFACE_ITEMS_HPP_

// Player Interface Items.h

#include "AnyChar.hpp"
#include "NateDraw.hpp"

#pragma options align=mac68k

typedef enum
{
    kPlainRect = 1,
    kLabeledRect = 2,
    kListRect = 3,
    kTextRect = 4,
    kPlainButton = 5,
    kRadioButton = 6,
    kCheckboxButton = 7,
    kPictureRect = 8,
    kTabBox = 9,
    kTabBoxTop = 10,
    kTabBoxButton = 11
} interfaceKindType;

typedef enum
{
    kDimmed = 1,
    kActive = 2,
    kIH_Hilite = 3
} interfaceItemStatusType;

typedef enum
{
    kLarge = 1,
    kSmall = 2
} interfaceStyleType;

typedef struct
{
    short               stringID;
    short               stringNumber;
} interfaceLabelType;

typedef struct
{
    interfaceLabelType  label;
    unsigned char       color;
    TEHandle            teData;
    Boolean             editable;
} interfaceLabeledRectType;

typedef struct
{
    interfaceLabelType          label;
    short                       (*getListLength)( void);
    void                        (*getItemString)( short, anyCharType *);
    Boolean                     (*itemHilited)( short, Boolean);
//  void                        (*hiliteItem)( short);
    short                       topItem;
    interfaceItemStatusType     lineUpStatus;
    interfaceItemStatusType     lineDownStatus;
    interfaceItemStatusType     pageUpStatus;
    interfaceItemStatusType     pageDownStatus;
} interfaceListType;

typedef struct
{
    short               textID;
    Boolean             visibleBounds;
} interfaceTextRectType;

typedef struct
{
    short               topRightBorderSize;
} interfaceTabBoxType;

typedef struct
{
    short               pictureID;
    Boolean             visibleBounds;
} interfacePictureRectType;

typedef struct
{
    interfaceLabelType          label;
    short                       key;
    Boolean                     defaultButton;
    interfaceItemStatusType     status;
} interfaceButtonType;

typedef struct
{
    interfaceLabelType          label;
    short                       key;
    Boolean                     on;
    interfaceItemStatusType     status;
} interfaceRadioType; // also tab box button type

typedef struct
{
    interfaceLabelType          label;
    short                       key;
    Boolean                     on;
    interfaceItemStatusType     status;
} interfaceCheckboxType;

typedef struct
{
    longRect            bounds;
    union
    {
        interfaceLabeledRectType    labeledRect;
        interfaceListType           listRect;
        interfaceTextRectType       textRect;
        interfaceButtonType         plainButton;
        interfaceRadioType          radioButton;
        interfaceCheckboxType       checkboxButton;
        interfacePictureRectType    pictureRect;
        interfaceTabBoxType         tabBox;
    } item;

    unsigned char       color;
    interfaceKindType   kind;
    interfaceStyleType  style;
} interfaceItemType;

#pragma options align=reset

#endif // ANTARES_PLAYER_INTERFACE_ITEMS_HPP_