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

const static char *grope_response_self[] = {
	"gropes themselves?",
	"grops theiw own bulgy wulgy uwu owo uwu!!!!",
	"slaps their own balls?"
};

const static char *grope_response[] = {
	"grops **%s**'s bulgy woolgy!",
	"gwabs **%s**'s buwlgy wulgy uwu owo uwu!!!!",
	"sexually assults **%s**",
	"grops **%s**'s bulgy woolgy!",
	"gwabs **%s**'s buwlgy wulgy uwu owo uwu!!!!",
	"grabs **%s** by the :b:ussy!",
	", you may need to seriously reconsider your life choices if you're going to virtua-grope someone on a furry discord."
};

// ----------------------------------------------------------------------------------------------------

void action_grope(struct discord *client, const struct discord_message *msg) {
	if (msg->author->bot) return;	// ignore bots
	handle_action(client, msg, grope_response_self, STR_ARRAY_LEN(grope_response_self),
		grope_response, STR_ARRAY_LEN(grope_response));
}
