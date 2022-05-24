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

const static char *vore_response_self[] = {
	"manages to vore themselves. Impressive!",
	"vores himself?",
	"chows down on his own arm!"
};

const static char *vore_response[] = {
	"vores **%s**!",
	"glomps **%s** with their big wide mouth!",
	"glomps **%s** with their big wide mouth!",
	"attempts to vore **%s**! Unfortunately that's an impossible task and all they did was get **%s**'s arm wet.",
	"starts devouring **%s**'s ass.",
	"starts devouring **%s**'s ass.",
	"frikin murders **%s** and eats the remains.",
	"vores **%s**. \\*burp\\*.",
	"swallows **%s** in one gulp! They were never seen again."
};

// ----------------------------------------------------------------------------------------------------

void action_vore(struct discord *client, const struct discord_message *msg) {
	if (msg->author->bot) return;	// ignore bots
	handle_action(client, msg, vore_response_self, STR_ARRAY_LEN(vore_response_self),
		vore_response, STR_ARRAY_LEN(vore_response));
}
