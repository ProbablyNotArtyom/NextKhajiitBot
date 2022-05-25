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

void command_rate(struct discord *client, const struct discord_message *msg) {
	CMD_IGNORE_BOTS();
	char strbuff[_MSG_MAX_LEN];
	char target_mention[_TARGET_MAX_LEN];
	u64snowflake target_id;
	
	/* run a parse for any targets in the message */
	target_id = find_target(client, msg, &target_mention, sizeof(target_mention));
	if (strlen(msg->content) == 0 && target_id == 0) {		// handle no inputs
		SEND_COLOR_EMBED("I can't rate nothing! I need at least 1 target.", KBCOLOR_ERROR);
		return;
	}
	
	/* create the format string, inserting the target and the rand call */
	snprintf(strbuff, sizeof(strbuff),
		"I rate %s a **%d/10**",
		target_mention, (rand() % 11));
	
	SEND_MSG_EMBED(strbuff);
}

// ----------------------------------------------------------------------------------------------------
