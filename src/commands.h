//
// MIT License
//
// Copyright (c) 2022 Carson Herrington
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

// ====================================================================================================
// NextKhajiitBot - NotArtyom - 2022
// ----------------------------------------
// A new rendition of khajiitbot in C using the Concord discord library
// ====================================================================================================

#ifndef _KBOT_COMMANDS_H
#define _KBOT_COMMANDS_H

// ----------------------------------------------------------------------------------------------------

void command_help(struct discord *client, const struct discord_message *msg);

void command_eight_ball(struct discord *client, const struct discord_message *msg);
void command_define(struct discord *client, const struct discord_message *msg);
void command_chance(struct discord *client, const struct discord_message *msg);
void command_random(struct discord *client, const struct discord_message *msg);
void command_rate(struct discord *client, const struct discord_message *msg);
void command_ctof(struct discord *client, const struct discord_message *msg);
void command_ftoc(struct discord *client, const struct discord_message *msg);

// ----------------------------------------------------------------------------------------------------

#endif
