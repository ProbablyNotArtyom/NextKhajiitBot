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
#include <parse.h>
#include <actions.h>

// ----------------------------------------------------------------------------------------------------

const static char *stab_response_self[] = {
	"stabs themselves. I dont know what they expected...",
	"gets into a knife fight! They manage to end up with their own knife in their gut.",
	"stabs themselves with a spoon. It isn't very effective..."
};

const static char *stab_response[] = {
	"stabs **%s** right in the gut!",
	"sneaks up behind **%s** and stabs them in the back!",
	"gets into a knife fight with **%s**!",
	"gets cheeky with **%s**!",
	"stabs **%s** in an attempt to steal their yiff! :scream_cat:",
	"lodges their blade directly into **%s**!",
	"tries to stab **%s**, but ends up grabbing their own knife by the blade.",
	"gives **%s** a friendly little eyepoke! Retina jelly, anyone?",
	"exercises their green thumb and plants a few knives into **%s**'s back!"
};

// ----------------------------------------------------------------------------------------------------

void action_stab(struct discord *client, const struct discord_message *msg) {
	if (msg->author->bot) return;	// ignore bots
	handle_action(client, msg, stab_response_self, STR_ARRAY_LEN(stab_response_self),
		stab_response, STR_ARRAY_LEN(stab_response));
}
