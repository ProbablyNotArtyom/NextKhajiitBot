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
#include <inttypes.h> /* SCNu64 */

#include <concord/discord.h>

#include <khajiitbot.h>
#include <commands.h>
#include <utils.h>

// ----------------------------------------------------------------------------------------------------

// Finds any @ mentions of users within a message string and returns the ID
// If the returned ID is 0, then no mention was found
// always returns the first mention in the message if multiple are present
u64snowflake find_mention(struct discord *client, const struct discord_message *msg) {
	DEBUG_PRINTF("<> Finding mention...\n");
	if (strlen(msg->content) == 0) return 0;	// if the message is blank then dont bother parsing
	
	int index = 0;
	u64snowflake ret = 0;
	char *newstr = (char *)malloc(strlen(msg->content) + 1);	// allocate a buffer for a copy of the msg
	char *newstr_orig = newstr;									// save the allocated pointer so we can free it later

	/* clone the message content */
	strcpy(newstr, msg->content);

	/* loop through each char until we hit a NULL */
	for (int i = 0; newstr[i] != '\0'; i++) {
		/* search for the opening '<@' that starts a mention */
		if (newstr[i] == '<' && newstr[i+1] == '@') {
			/* skip over the opening chars to index at the start of the ID */
			index = i + 2;
			/* rebase newstr to start at our found ID */
			newstr = &newstr[index];
			/* loop through the rest of newstr to make sure our supposed mention ends with > */
			for (int x = 0; newstr[x] != '\0'; x++) {
				if (newstr[x] == '>') {
					/* if we get here then the mention is valid */
					/* we overwrite the > mention terminator with a NULL so we can extract the ID */
					newstr[x] = '\0';
					break;
				}
			}
			/* extract the ID into an int and were done */
			ret = (u64snowflake)strtol(newstr, NULL, 10);
		}
	}
	
	free(newstr_orig);
	return ret;
}

// Searches for action targets
// If a direct mention is found, the user ID is returned and target_mention is populated with the formatted mention
// If the message is not empty but no valid mention is found, then 0 is returned and target_mention is still populated
// When the message is blank, 0 is returned and target_mention is untouched
u64snowflake find_target(struct discord *client, const struct discord_message *msg, char *target_mention[], size_t bufflen) {
	/* attempt to parse a direct mention */
	u64snowflake target_id = find_mention(client, msg);
	DEBUG_PRINTF("<> Finding target...\n");
	if (target_id == 0 && strlen(msg->content) != 0) {	// handle string target

		/* set up a query and search for any partial username matches */
		struct discord_guild_members members = { 0 };
		struct discord_ret_guild_members ret = { .sync = &members };
		struct discord_search_guild_members params = { .limit = 1000, .query = msg->content };
		discord_search_guild_members(client, msg->guild_id, &params, &ret);
		
		if (members.size == 0) {
			DEBUG_PRINTF("<> String target\n");
			snprintf(target_mention, bufflen, "**%s**", msg->content);			// if no matches were found, handle as a string target
		} else {
			DEBUG_PRINTF("<> Matched target\n");
			snprintf(target_mention, bufflen, "**<@%" PRIu64 ">**", members.array[0].user->id);	// otherwise, create a mention using the match
		}
	} else {
		DEBUG_PRINTF("<> Direct mention target\n");
		snprintf(target_mention, bufflen, "**<@%" PRIu64 ">**", target_id);	// handle direct mention
	}
	
	DEBUG_PRINTF("<> Returning\n");
	return target_id;
}

// ----------------------------------------------------------------------------------------------------

void handle_action(struct discord *client, const struct discord_message *msg,
				   const char *response_self[], int response_self_len,
				   const char *response[], int response_len) {
	
	int answer;
	char final[_ACTION_MAX_LEN];
	char tmp[_ACTION_MAX_LEN];
	char target_mention[_TARGET_MAX_LEN];
	u64snowflake target_id;
	
	DEBUG_PRINTF("<> Handling action\n");
	
	/* run a parse for any targets in the message */
	target_id = find_target(client, msg, &target_mention, sizeof(target_mention));
	
	if (msg->author->id == target_id || strlen(msg->content) == 0) {	// handle targeting self
		DEBUG_PRINTF("<> Targeting self\n");
		answer = rand() % response_self_len;
		snprintf(final, sizeof(final), "**<@%" PRIu64 ">** %s", msg->author->id, response_self[answer]);
	} else {								// handle targeting a direct mention
		DEBUG_PRINTF("<> Handling direct mention\n");
		answer = rand() % response_len;
		snprintf(tmp, sizeof(tmp), "**<@%" PRIu64 ">** %s", msg->author->id, response[answer]);
		snprintf(final, sizeof(final), tmp, target_mention);
	}
	
	SEND_MSG_EMBED(final);
}
