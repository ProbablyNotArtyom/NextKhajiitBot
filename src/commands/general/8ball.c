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
#include <time.h>

#include <concord/discord.h>

#include <khajiitbot.h>
#include <commands.h>
#include <parse.h>

// ----------------------------------------------------------------------------------------------------

#define EIGHTBALL_RESPONSE_POSITIVE		0x11ff5c
#define EIGHTBALL_RESPONSE_NEGATIVE		0xff2600
#define EIGHTBALL_RESPONSE_NEUTRAL		0xff9602

struct eightball_entry {
	const char *response;
	const int type;
};

// ----------------------------------------------------------------------------------------------------

const struct eightball_entry eightball_phrases[] = {	// list of 8ball phrases/responses
	{ "It is certain.", EIGHTBALL_RESPONSE_POSITIVE },
	{ "It is decidedly so.", EIGHTBALL_RESPONSE_POSITIVE },
	{ "Without a doubt.", EIGHTBALL_RESPONSE_POSITIVE },
	{ "Yes definitely.", EIGHTBALL_RESPONSE_POSITIVE },
	{ "You may rely on it.", EIGHTBALL_RESPONSE_POSITIVE },
	{ "As I see it, yes.", EIGHTBALL_RESPONSE_POSITIVE },
	{ "Most likelby.", EIGHTBALL_RESPONSE_POSITIVE },
	{ "Outlook good.", EIGHTBALL_RESPONSE_POSITIVE },
	{ "Yes.", EIGHTBALL_RESPONSE_POSITIVE },
	{ "Signs Point to Yes.", EIGHTBALL_RESPONSE_POSITIVE },
	{ "Reply hazy, try again.", EIGHTBALL_RESPONSE_NEUTRAL },
	{ "Ask again later.", EIGHTBALL_RESPONSE_NEUTRAL },
	{ "Better not tell you now.", EIGHTBALL_RESPONSE_NEUTRAL },
	{ "Cannot predict now.", EIGHTBALL_RESPONSE_NEUTRAL },
	{ "Concentrate and ask again.", EIGHTBALL_RESPONSE_NEUTRAL },
	{ "Don't count on it.", EIGHTBALL_RESPONSE_NEGATIVE },
	{ "My reply is no.", EIGHTBALL_RESPONSE_NEGATIVE },
	{ "My sources say no.", EIGHTBALL_RESPONSE_NEGATIVE },
	{ "Outlook not so good.", EIGHTBALL_RESPONSE_NEGATIVE },
	{ "Very doubtful.", EIGHTBALL_RESPONSE_NEGATIVE }
};

void command_eight_ball(struct discord *client, const struct discord_message *msg) {
	CMD_IGNORE_BOTS();
	int answer = rand() % STRUCT_ARRAY_LEN(eightball_phrases);		// generate random index to our responses
	struct discord_embed embeds[] = {
		{
			.color = eightball_phrases[answer].type,
			.description = eightball_phrases[answer].response
		}
	};

	struct discord_create_message params = {
		.embeds = &(struct discord_embeds) {
			.size = sizeof(embeds) / sizeof *embeds,
			.array = embeds,
		}
	};

	discord_create_message(client, msg->channel_id, &params, NULL);
}

// ----------------------------------------------------------------------------------------------------
