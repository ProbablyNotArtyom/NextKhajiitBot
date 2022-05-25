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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <limits.h>
#include <errno.h>

#include <concord/discord.h>

#include <khajiitbot.h>
#include <commands.h>
#include <utils.h>
#include <actions.h>

// ----------------------------------------------------------------------------------------------------

const static char *pet_response_self[] = {
	"pets their own head.",
	"attempts to pet someone on the head, yet somehow manages to pet their own.",
	"wasn't even trying to pet anyone, yet still ends up petting themselves."
};

const static char *pet_response[] = {
	"pets **%s** on their head!",
	"gives **%s** pets!",
	"sneaks up behind **%s** and surprizes them with a swarm of petting!",
	"fuzzily pets **%s**!",
	"pets **%s**'s warm fuzzy fluff!",
	"pets **%s** like the animal they are."
};

// ----------------------------------------------------------------------------------------------------

void action_pet(struct discord *client, const struct discord_message *msg) {
	if (msg->author->bot) return;	// ignore bots
	handle_action(client, msg, pet_response_self, STR_ARRAY_LEN(pet_response_self),
		pet_response, STR_ARRAY_LEN(pet_response));
}
