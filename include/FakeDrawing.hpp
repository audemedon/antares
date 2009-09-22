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

#ifndef ANTARES_FAKE_DRAWING_HPP_
#define ANTARES_FAKE_DRAWING_HPP_

#include <stdint.h>
#include <Quickdraw.h>

#include "Fakes.hpp"

class FakePixMap : public PixMap {
  public:
    FakePixMap(int width, int height) {
        SetRect(&bounds, 0, 0, width, height);
        rowBytes = width | 0x8000;
        baseAddr = new unsigned char[width * height];
        pixelSize = 1;
    }

    ~FakePixMap() {
        delete[] baseAddr;
    }

    int width() const { return bounds.right - bounds.left; }
    int height() const { return bounds.bottom - bounds.top; }

    unsigned char& PixelAt(int x, int y) { return baseAddr[(y * rowBytes) + x]; }

  private:
    DISALLOW_COPY_AND_ASSIGN(FakePixMap);
};

class ClippedTransfer {
  public:
    ClippedTransfer(const Rect& from, const Rect& to)
            : _from(from),
              _to(to) {
        // Rects must be the same size.
        assert(_from.right - _from.left == _to.right - _to.left);
        assert(_from.bottom - _from.top == _to.bottom - _to.top);
    }

    void ClipSourceTo(const Rect& clip) {
        ClipFirstToSecond(_from, clip);
    }

    void ClipDestTo(const Rect& clip) {
        ClipFirstToSecond(_to, clip);
    }

    int Height() const { return _from.bottom - _from.top; }
    int Width() const { return _from.right - _from.left; }

    int SourceRow(int i) const { return _from.top + i; }
    int SourceColumn(int i) const { return _from.left + i; }

    int DestRow(int i) const { return _to.top + i; }
    int DestColumn(int i) const { return _to.left + i; }

  private:
    inline void ClipFirstToSecond(const Rect& rect, const Rect& clip) {
        if (clip.left > rect.left) {
            int diff = clip.left - rect.left;
            _to.left += diff;
            _from.left += diff;
        }
        if (clip.top > rect.top) {
            int diff = clip.top - rect.top;
            _to.top += diff;
            _from.top += diff;
        }
        if (clip.right < rect.right) {
            int diff = clip.right - rect.right;
            _to.right += diff;
            _from.right += diff;
        }
        if (clip.bottom < rect.bottom) {
            int diff = clip.bottom - rect.bottom;
            _to.bottom += diff;
            _from.bottom += diff;
        }
    }

    Rect _from;
    Rect _to;
};

uint8_t NearestColor(uint16_t red, uint16_t green, uint16_t blue);
uint8_t GetPixel(int x, int y);
void SetPixel(int x, int y, uint8_t c);
void SetPixelRow(int x, int y, uint8_t* c, int count);

class GWorld {
  public:
    GWorld(int width, int height)
            : pixMap(width, height),
              pixMapPtr(&pixMap) { }

    FakePixMap pixMap;
    PixMap* pixMapPtr;

  private:
    DISALLOW_COPY_AND_ASSIGN(GWorld);
};

class FakeWindow : public Window {
  public:
    FakeWindow(int width, int height, GWorld* world) {
        SetRect(&portRect, 0, 0, width, height);
        portBits = world->pixMap;  // Copying here, is that right?
    }
};

class FakeGDevice : public GDevice {
  public:
    FakeGDevice(int width, int height, GWorld* world_) {
        gdPMap = &world_->pixMapPtr;
        SetRect(&gdRect, 0, 0, width, height);
        world = world_;
    }
};

extern GWorld* gOffWorld;
extern GWorld* gRealWorld;
extern GWorld* gSaveWorld;

void DumpTo(const std::string& path);
void FakeDrawingInit();

#endif  // ANTARES_FAKE_DRAWING_HPP_
