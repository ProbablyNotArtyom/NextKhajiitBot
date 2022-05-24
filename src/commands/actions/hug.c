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

const static char *hug_response_self[] = {
 	"hugs themselves, for some reason.",
 	"sets up for a hug, then somehow manages to hug themselves.",
 	"wraps their arms around themselves."
};

const static char *hug_response[] = {
	"walks right up to **%s** and hugs them!",
 	"sneaks up behind **%s** and hugs them!",
 	"nuzzles up close to **%s** for a hug!",
 	"gives a big 'ol flufferhug to **%s**!",
 	"surprises **%s** with a warm hug!",
 	"embraces with **%s**. How sweet!",
 	"spreads the love to **%s** through a big 'ol hug!"
};

// ----------------------------------------------------------------------------------------------------

void action_hug(struct discord *client, const struct discord_message *msg) {
	if (msg->author->bot) return;	// ignore bots
	handle_action(client, msg, hug_response_self, STR_ARRAY_LEN(hug_response_self),
		hug_response, STR_ARRAY_LEN(hug_response));
}
