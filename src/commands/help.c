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
#include <utils.h>

// ----------------------------------------------------------------------------------------------------

/* helper that defines the formatting of each help entry */
#define HELP_ENTRY(cmd, desc)	"**" cmd "**\n" " ​ ​ ​ ​ ​ ​ ​ ​ " desc "\n"

struct help_page {
	char *title;
	char *contents;
};

// ----------------------------------------------------------------------------------------------------

static struct help_page help_meta = {
	.title = "KhajiitBot Help Pages",
	.contents = \
		HELP_ENTRY("k.help general", "basic commands.")
		HELP_ENTRY("k.help action", "commands for peer interaction.")
		//HELP_ENTRY("k.help pool", "commands that use the image pools, such as k.image.")
		HELP_ENTRY("k.help misc", "miscellaneous commands, external website interfaces.")
		//HELP_ENTRY("k.help image", "commands that modify attached images.")
};

static struct help_page help_action = {
	.title = "Actions Help",
	.contents = \
		HELP_ENTRY("k.yiff @[user]", "​sends a yiffy message.")
		HELP_ENTRY("k.hug @[user]", "​hugs another user.")
		HELP_ENTRY("k.kiss @[user]", "​kisses another user.")
		HELP_ENTRY("k.stab @[user]", "​stabs another user.")
		HELP_ENTRY("k.shoot @[user]", "​shoots another user.")
		HELP_ENTRY("k.pet @[user]", "​pets another user.")
		HELP_ENTRY("k.bless @[user]", "​blesses another user.")
		HELP_ENTRY("k.nuke @[user]", "​nukes another user.")
		HELP_ENTRY("k.meow @[user]", "​meow at another user.")
		HELP_ENTRY("k.vore @[user]", "​vore another user.")
		HELP_ENTRY("k.grope @[user]", "​gropes another user. Why would you want that.")
		HELP_ENTRY("k.f @[user]", "​pays respects, optionally to another user.")
		HELP_ENTRY("k.boof @[user]", "rip da boof, or pass da boof to a fren.")
};

static struct help_page help_miscellaneous = {
	.title = "Miscellaneous Commands Help",
	.contents = \
		HELP_ENTRY("k.e6 [tags]", "sets up a search for the specified tags on e621.")
		HELP_ENTRY("k.e9 [tags]", "sets up a search for the specified tags on e926.")
		HELP_ENTRY("k.scp [number]", "links the SCP wiki entry for the requested SCP number.")
		HELP_ENTRY("k.define [word]", "reports the definition, along with any possible synonyms of a word")
};

static struct help_page help_general = {
	.title = "General Commands Help",
	.contents = \
		HELP_ENTRY("k.help", "shows this help page.")
		HELP_ENTRY("k.uptime", "displays the current uptime.")
		HELP_ENTRY("k.random [max]", "generates a truly random number with max value. (default 10)")
		HELP_ENTRY("k.8ball [question]", "answers any question with true randomness.")
		HELP_ENTRY("k.rate @[user]", "rates another user on a scale from 0 to 10.")
		HELP_ENTRY("k.chance [question]", "rates the likelihood a question is true.")
		HELP_ENTRY("k.e [emote]", "returns the link to the emote image.")
		HELP_ENTRY("k.a @[user]", "returns a link to the avatar of the user.")
};

// ----------------------------------------------------------------------------------------------------

void command_help(struct discord *client, const struct discord_message *msg) {
	struct help_page *page;

	if (!strcmp(msg->content, "general")) {
		page = &help_general;
	} else if (!strcmp(msg->content, "action")) {
		page = &help_action;
	} else if (!strcmp(msg->content, "misc")) {
		page = &help_miscellaneous;
	} else {	
		page = &help_meta;		// fall back to displaying the meta help page
	}

	struct discord_embed_thumbnail kbot_icon = {
		.url = "https://cdn.discordapp.com/app-icons/943660926840750170/0edaa162c44fc581bac56c6827ce4b7e.png",
		.height = 128,
		.width = 128
	};
	struct discord_embed embeds[] = {
		{
			.color = KBCOLOR_MSG,
			.title = page->title,
			.description = page->contents,
			.thumbnail = &kbot_icon
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
