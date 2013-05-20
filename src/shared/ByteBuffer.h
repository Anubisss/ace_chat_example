/*
 * This file is part of ace_chat_example.
 *
 * ace_chat_example is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * ace_chat_example is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with ace_chat_example.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __BYTE_BUFFER_H__
#define __BYTE_BUFFER_H__

#include <cstring>
#include <cstdio>
#include <vector>
#include <string>

#include "BasicTypes.h"

/**
 *  @brief  This class is a byte buffer which meens it's buffering binary data.
 *          Basically this container is used to send and receive data.
 *          This class should be abstract.
 */
class ByteBuffer
{
    public:
        ByteBuffer() : _writePos(0), _readPos(0)
        {
            _storage.reserve(128);
        }
        ~ByteBuffer()
        {
            Reset();
        }

        /**
         *  @brief  Returns the size in bytes.
         */
        size_t GetSize() const { return _storage.size(); }
        /**
         *  @brief  Returns the raw content (bytes array).
         */
        const uint8* GetContent() const { return &_storage[0]; }

        /**
         *  @brief  Nulling the container.
         */
        void Reset()
        {
            _storage.clear();
            _writePos = 0;
            _readPos = 0;
        }

        /*void Dump()
        {
            printf("%.8lX ", GetSize() > 0x10 ? 0x10 : GetSize());
            for (size_t i = 0; i < GetSize(); ++i)
            {
                uint8 Temp = Read<uint8>();
                if (Temp < 0x10)
                    printf("0%X ", Temp);
                else
                    printf("%X ", Temp);

                if ((i + 1) % 16 == 0)
                {
                    size_t RowSize = i + 0x01 + 0x10;
                    printf("\n");
                    printf("%.8lX ", RowSize > GetSize() ? GetSize() : RowSize);
                }
            }
            printf("\n");
        }*/


        /**
         *  The following functions are writing operators.
         *  To write something to the buffer use
         *  the following format: buffer << 1
         *
         *  These functions are cover all the types which can be written
         *  into to the buffer. Generally ints, float, double and string.
         */


        ByteBuffer& operator<<(uint8 value)
        {
            Write<uint8>(value);
            return *this;
        }

        ByteBuffer& operator<<(int8 value)
        {
            Write<int8>(value);
            return *this;
        }

        ByteBuffer& operator<<(uint16 value)
        {
            Write<uint16>(value);
            return *this;
        }

        ByteBuffer& operator<<(int16 value)
        {
            Write<int16>(value);
            return *this;
        }

        ByteBuffer& operator<<(uint32 value)
        {
            Write<uint32>(value);
            return *this;
        }

        ByteBuffer& operator<<(int32 value)
        {
            Write<int32>(value);
            return *this;
        }

        ByteBuffer& operator<<(uint64 value)
        {
            Write<uint64>(value);
            return *this;
        }

        ByteBuffer& operator<<(int64 value)
        {
            Write<int64>(value);
            return *this;
        }

        ByteBuffer& operator<<(float value)
        {
            Write<float>(value);
            return *this;
        }

        ByteBuffer& operator<<(double value)
        {
            Write<double>(value);
            return *this;
        }

        ByteBuffer& operator<<(const char* value)
        {
            WriteString(value);
            return *this;
        }

        ByteBuffer& operator<<(std::string const& value)
        {
            WriteString(value);
            return *this;
        }

        /**
         *  @brief  Copies all the content from another byte buffer.
         */
        void Append(ByteBuffer const& anotherBuffer)
        {
            if (_storage.size() < (_writePos + anotherBuffer.GetSize()))
                _storage.resize(_writePos + anotherBuffer.GetSize());
            memcpy(&_storage[_writePos], anotherBuffer.GetContent(), anotherBuffer.GetSize());
            _writePos += anotherBuffer.GetSize();
        }
        /**
         *  @brief  Copies a specific number of content (in bytes) from another buffer.
         */
        void Append(uint8 const* buffer, size_t size)
        {
            if (_storage.size() < (_writePos + size))
                _storage.resize(_writePos + size);
            memcpy(&_storage[_writePos], buffer, size);
            _writePos += size;
        }


        /**
         *  Reading operators.
         *  To read a value from the buffer use
         *  the following format: buffer >> value
         */


        ByteBuffer& operator>>(uint8& value)
        {
            value = Read<uint8>();
            return *this;
        }

        ByteBuffer& operator>>(int8& value)
        {
            value = Read<int8>();
            return *this;
        }

        ByteBuffer& operator>>(uint16& value)
        {
            value = Read<uint16>();
            return *this;
        }

        ByteBuffer& operator>>(int16& value)
        {
            value = Read<int16>();
            return *this;
        }

        ByteBuffer& operator>>(uint32& value)
        {
            value = Read<uint32>();
            return *this;
        }

        ByteBuffer& operator>>(int32& value)
        {
            value = Read<int32>();
            return *this;
        }

        ByteBuffer& operator>>(uint64& value)
        {
            value = Read<uint64>();
            return *this;
        }

        ByteBuffer& operator>>(int64& value)
        {
            value = Read<int64>();
            return *this;
        }

        ByteBuffer& operator>>(float& value)
        {
            value = Read<float>();
            return *this;
        }

        ByteBuffer& operator>>(double& value)
        {
            value = Read<double>();
            return *this;
        }

        ByteBuffer& operator>>(std::string& value)
        {
            value.clear();
            while (_readPos < GetSize())
            {
                char Temp;
                Temp = Read<char>();
                value += Temp;

                // stop on NULL character
                if (Temp == '\0')
                    break;
            }
            return *this;
        }


        /**
         *  Some functions which are used to skip some bytes.
         */


        /**
         *  @brief  Skips bytes.
         */
        void SkipBytes(size_t size)
        {
            _readPos += size;
        }

        /**
         *  @brief  Skips size of the given type bytes.
         */
        template <typename T> void Skip()
        {
            _readPos += sizeof(T);
        }

        /**
         *  @brief  Skips a string.
         */
        void SkipString()
        {
            while (_readPos < GetSize())
            {
                char Temp;
                Temp = Read<char>();

                // break on NULL char
                if (Temp == '\0')
                    break;
            }
        }

    private:
        void Resize(size_t size) { _storage.resize(size); }

        template <typename T> void Write(T Value)
        {
            if (_storage.size() < (_writePos + sizeof(Value)))
                Resize(_writePos + sizeof(Value));
            memcpy(&_storage[_writePos], &Value, sizeof(Value));
            _writePos += sizeof(Value);
        }

        template <typename T> T Read()
        {
            T temp;
            memcpy(&temp, &_storage[_readPos], sizeof(T));
            _readPos += sizeof(T);
            return temp;
        }

        void WriteString(const char* value)
        {
            size_t length = strlen(value);

            if (_storage.size() < (_writePos + length))
                Resize(_writePos + length);
            memcpy(&_storage[_writePos], value, length);
            _writePos += length;

            Write<uint8>(uint8(0)); // NULL character
        }

        void WriteString(std::string const& value)
        {
            WriteString(value.c_str());
        }

        /**
         *  @brief  This vector stores the raw data.
         */
        std::vector<uint8> _storage;

        /**
         *  @brief  _writePos stores the actually Writing Position,
         *          so how many bytes writed in the buffer.
         *          _readPos stored the actually Reading Position,
         *          so how many bytes read from the buffer.
         */
        size_t _writePos, _readPos;
};

#endif /* __BYTE_BUFFER_H__ */
