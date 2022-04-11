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

#include "khajiitbot.h"
#include "commands.h"

// ----------------------------------------------------------------------------------------------------

enum {
	EIGHTBALL_RESPONSE_POSITIVE,
	EIGHTBALL_RESPONSE_NEUTRAL,
	EIGHTBALL_RESPONSE_NEGATIVE
};

struct eightball_entry {
	const char *response;
	const int type;
};

struct eightball_entry eightball_phrases[] = {	// list of 8ball phrases/responses
	{ .response = "It is certain.", .type = EIGHTBALL_RESPONSE_POSITIVE },
	{ .response = "It is decidedly so.", .type = EIGHTBALL_RESPONSE_POSITIVE },
	{ .response = "Without a doubt.", .type = EIGHTBALL_RESPONSE_POSITIVE },
	{ .response = "Yes definitely.", .type = EIGHTBALL_RESPONSE_POSITIVE },
	{ .response = "You may rely on it.", .type = EIGHTBALL_RESPONSE_POSITIVE },
	{ .response = "As I see it, yes.", .type = EIGHTBALL_RESPONSE_POSITIVE },
	{ .response = "Most likelby.", .type = EIGHTBALL_RESPONSE_POSITIVE },
	{ .response = "Outlook good.", .type = EIGHTBALL_RESPONSE_POSITIVE },
	{ .response = "Yes.", .type = EIGHTBALL_RESPONSE_POSITIVE },
	{ .response = "Signs Point to Yes.", .type = EIGHTBALL_RESPONSE_POSITIVE },
	{ .response = "Reply hazy, try again.", .type = EIGHTBALL_RESPONSE_NEUTRAL },
	{ .response = "Ask again later.", .type = EIGHTBALL_RESPONSE_NEUTRAL },
	{ .response = "Better not tell you now.", .type = EIGHTBALL_RESPONSE_NEUTRAL },
	{ .response = "Cannot predict now.", .type = EIGHTBALL_RESPONSE_NEUTRAL },
	{ .response = "Concentrate and ask again.", .type = EIGHTBALL_RESPONSE_NEUTRAL },
	{ .response = "Don't count on it.", .type = EIGHTBALL_RESPONSE_NEGATIVE },
	{ .response = "My reply is no.", .type = EIGHTBALL_RESPONSE_NEGATIVE },
	{ .response = "My sources say no.", .type = EIGHTBALL_RESPONSE_NEGATIVE },
	{ .response = "Outlook not so good.", .type = EIGHTBALL_RESPONSE_NEGATIVE },
	{ .response = "Very doubtful.", .type = EIGHTBALL_RESPONSE_NEGATIVE }
};

void eight_ball(struct discord *client, const struct discord_message *msg) {
	if (msg->author->bot) return;	// ignore bots	
	char *phrases[] = {	// list of 8ball phrases/responses
		"It is certain.",
		"It is decidedly so.",
		"Without a doubt.",
		"Yes definitely.",
		"You may rely on it.",
		"As I see it, yes.",
		"Most likely.",
		"Outlook good.",
		"Yes.",
		"Signs Point to Yes.",
		"Reply hazy, try again.",
		"Ask again later.",
		"Better not tell you now.",
		"Cannot predict now.",
		"Concentrate and ask again.",
		"Don't count on it.",
		"My reply is no.",
		"My sources say no.",
		"Outlook not so good.",
		"Very doubtful."
	};
	
	srand(time(0));					// generate seed for randomizer
	int answer = rand() % (sizeof(phrases) / sizeof(phrases[0]));	// random number from 0 - 20
	int color;
	switch (eightball_phrases[answer].type) {
		case EIGHTBALL_RESPONSE_POSITIVE:
			color = KBCOLOR_TRUE;
			break;
		case EIGHTBALL_RESPONSE_NEUTRAL:
			color = KBCOLOR_UNDETERMINED;
			break;
		case EIGHTBALL_RESPONSE_NEGATIVE:
			color = KBCOLOR_FALSE;
			break;
	}
	
	struct discord_embed embeds[] = { // simple embed message
		{
			.color = color,
			.title = "8-Ball",
			.description = eightball_phrases[answer].response
		}		
	};
	
	struct discord_create_message params = {
		.embeds = &(struct discord_embeds) {
			.size = sizeof(embeds) / sizeof *embeds,
			.array = embeds,
		},
	};
	discord_create_message(client, msg->channel_id, &params, NULL);
	
} 
