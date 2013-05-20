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

#ifndef __PACKET_H__
#define __PACKET_H__

#include "BasicTypes.h"
#include "ByteBuffer.h"

/**
 *  @brief  This class should be used in client/server communication.
 */
class Packet : public ByteBuffer
{
    public:
        Packet(uint8 opcode) : _opcode(opcode), ByteBuffer() {}

        uint8 GetOpcode() const { return _opcode; }

    private:
        uint8 _opcode;
};

#endif /* __PACKET_H__ */
