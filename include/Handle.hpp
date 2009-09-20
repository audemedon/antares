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

#ifndef ANTARES_HANDLE_HPP_
#define ANTARES_HANDLE_HPP_

#include <assert.h>
#include <stdint.h>
#include <algorithm>
#include <vector>

#include "Resource.hpp"

#define DISALLOW_COPY_AND_ASSIGN(CLASS) \
  private: \
    CLASS(const CLASS&); \
    CLASS& operator=(const CLASS&);

template <typename T> class TypedHandle;

template <typename T>
class TypedHandleBase {
  public:
    TypedHandleBase()
            : _data(NULL) { }

    TypedHandle<T> clone() const;

    void create(int count) {
        _data = new Data(count);
    }

    void resize(size_t new_count);
    void extend(TypedHandle<T> other);

    void destroy() {
        delete _data;
        _data = NULL;
    }

    void load_resource(uint32_t code, int id);

    T* operator*() const {
        return _data->_ptr;
    }

    T** get() const {
        return &_data->_ptr;
    }

    size_t count() const {
        return _data->_count;
    }

    size_t size() const {
        return count() * sizeof(T);
    }

  private:
    class Data {
      public:
        Data(int count)
                : _ptr(new T[count]),
                  _count(count) { }

        ~Data() {
            delete[] _ptr;
        }

      private:
        friend class TypedHandleBase;

        T* _ptr;
        size_t _count;

        DISALLOW_COPY_AND_ASSIGN(Data);
    };
    Data* _data;
};

template <typename T>
class TypedHandle : public TypedHandleBase<T> {
};

template <>
class TypedHandle<unsigned char> : public TypedHandleBase<unsigned char> {
  public:
    void load_resource(uint32_t code, int id) {
        Resource rsrc(code, id);
        create(rsrc.size());
        memcpy(**this, rsrc.data(), rsrc.size());
    }
};

template <typename T>
TypedHandle<T> TypedHandleBase<T>::clone() const {
    TypedHandle<T> cloned;
    cloned.create(count());
    for (size_t i = 0; i < count(); ++i) {
        (*cloned)[i] = (**this)[i];
    }
    return cloned;
}

template <typename T>
void TypedHandleBase<T>::resize(size_t new_count) {
    T* old_ptr = _data->_ptr;
    size_t old_count = _data->_count;
    _data->_ptr = new T[new_count];
    _data->_count = new_count;
    for (size_t i = 0; i < std::min(old_count, new_count); ++i) {
        _data->_ptr[i] = old_ptr[i];
    }
    delete[] old_ptr;
}

template <typename T>
void TypedHandleBase<T>::extend(TypedHandle<T> other) {
    if (other.count() > 0) {
        size_t old_count = count();
        resize(old_count + other.count());
        for (size_t i = 0; i < other.count(); ++i) {
            _data->_ptr[i + old_count] = other._data->_ptr[i];
        }
    }
}

template <typename T>
void TypedHandleBase<T>::load_resource(uint32_t code, int id) {
    Resource rsrc(code, id);
    std::vector<T> loaded;
    const char* data = rsrc.data();
    size_t remainder = rsrc.size();
    while (remainder > 0) {
        loaded.push_back(T());
        size_t consumed = loaded.back().load_data(data, remainder);
        assert(consumed <= remainder);
        data += consumed;
        remainder -= consumed;
    }
    create(loaded.size());
    for (size_t i = 0; i < loaded.size(); ++i) {
        (**this)[i] = loaded[i];
    }
}

long Random();
// TypedHandle<>s can no longer be registered using mHandleLockAndRegister, but simply deleting the
// call thereto would prevent HHClearHandle() from being called.  HHClearHandle() makes a call to
// Random() for each byte contained in the handle, so this function ensures that the stream of
// random values is unaltered by the removal of the call to HHClearHandle().
template <typename T>
inline void TypedHandleClearHack(TypedHandle<T> handle) {
    for (size_t i = 0; i < handle.size(); ++i) {
        Random();
    }
}

int Munger(TypedHandle<unsigned char> data, int pos, const unsigned char* search, size_t search_len,
        const unsigned char* replace, size_t replace_len);

#endif  // ANTARES_HANDLE_HPP_
