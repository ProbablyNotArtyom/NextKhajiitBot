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

#include "khajiitbot.h"
#include "commands.h"

// ----------------------------------------------------------------------------------------------------

// Finds any @ mentions of users within a message string and returns the ID
// If the returned ID is 0, then no mention was found
// always returns the first mention in the message is multiple are present
u64snowflake find_mention(struct discord *client, const struct discord_message *msg) {
	int index = 0;
	u64snowflake ret = 0;
	char *newstr = (char *)malloc(strlen(msg->content) + 1);
	char *newstr_orig = newstr;
	bool valid = false;
	strcpy(newstr, msg->content);
	for (int i = 0; newstr[i] != '\0'; i++) {
		if (newstr[i] == '<' && newstr[i+1] == '@') {
			index = i + 2;
			newstr = &newstr[index];
			for (int x = 0; newstr[x] != '\0'; x++) {
				if (newstr[x] == '>') {
					newstr[x] = '\0';
					break;
				}
			}
			ret = (u64snowflake)strtol(newstr, NULL, 10);
		}
	}
	printf("newstr: %s\n", newstr);
	printf("ret: %" PRIu64 "\n", ret);
	free(newstr_orig);
	return ret;
}
