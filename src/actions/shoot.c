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

// ----------------------------------------------------------------------------------------------------

const static char *shoot_response_self[] = {
	"shoots themselves!",
	"shoots themselves with a toy pistol; It wasn't very effective.",
	"commits auto-shootification!"
};

const static char *shoot_response[] = {
	"shoots **%s**! Tragic.",
	"gets into a knife fight with **%s**! Evidently, guns make great knives. ",
	"performs advanced facial surgery on **%s** using a shotgun!",
	"shoots **%s** point blank with a nerf blaster! They are immediately gibbed into hundreds of pieces.",
	"duels to the death with **%s**! There are no survivors...",
	"blasts **%s** right in their chest with a .22! It bounces right off.",
	"dumps a pound of lead into **%s**!",
	"lays down the law with **%s**."
};

// ----------------------------------------------------------------------------------------------------

void action_shoot(struct discord *client, const struct discord_message *msg) {
	if (msg->author->bot) return;	// ignore bots
	handle_action(client, msg, shoot_response_self, STR_ARRAY_LEN(shoot_response_self),
		shoot_response, STR_ARRAY_LEN(shoot_response));
}
