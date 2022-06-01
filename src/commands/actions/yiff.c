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

const static char *yiff_response_self[] = {
	"yiffs themselves, somehow.",
	"attempts to stage a yiffing, yet somehow manages to yiff themselves.",
	"manages to dong themselves. Impressive!"
};

const static char *yiff_response[] = {
	"yiffs **%s** right in the mouth!",
	"yiffs **%s** right in the arse!",
	"sneaks up behind **%s** and yiffs them right in the arse!",
	"gets yiffy with **%s**!",
	"trades fluids with **%s**!",
	"does something entirely indescribable to **%s**...",
	"dicks **%s** in record speed!"
};

// ----------------------------------------------------------------------------------------------------

void action_yiff(struct discord *client, const struct discord_message *msg) {
	if (msg->author->bot) return;	// ignore bots
	
	DEBUG_PRINTF("<> Yiffing...\n");
	handle_action(client, msg, yiff_response_self, STR_ARRAY_LEN(yiff_response_self),
		yiff_response, STR_ARRAY_LEN(yiff_response));
}
