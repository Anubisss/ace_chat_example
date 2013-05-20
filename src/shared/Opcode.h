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

#ifndef __OPCODE_H__
#define __OPCODE_H__

/**
 *  @brief  Stores the client (C2S_) and server (S2C_) opcodes.
 */

enum Opcode
{
    NULL_OPCODE,
    C2S_NICKNAME,
    S2C_CLIENT_HAS_JOINED,
    S2C_CLIENT_HAS_QUIT,
    C2S_SEND_MESSAGE,
    S2C_SEND_MESSAGE,

    OPCODE_NUMBERS
};

#endif /* __OPCODE_H__ */
