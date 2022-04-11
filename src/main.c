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

void on_fallback(struct discord *client, const struct discord_message *msg) {
	const size_t MAX_FSIZE = 5e6; // 5 mb
	const size_t MAX_CHARS = 2000;
	FILE *fp;
	
	if (NULL == (fp = popen(msg->content, "r"))) {
		perror("Failed to run command");
		return;
	}
	
	char *path = calloc(1, MAX_FSIZE);
	char *pathtmp = calloc(1, MAX_FSIZE);
	while (NULL != fgets(path, MAX_FSIZE, fp)) {
		strncat(pathtmp, path, MAX_FSIZE - 1);
	}
	
	const size_t fsize = strlen(pathtmp);
	
	if (fsize <= MAX_CHARS) {
		struct discord_create_message params = { .content = pathtmp };
		discord_create_message(client, msg->channel_id, &params, NULL);
	}
	else {
		struct discord_attachment attachment = {
			.content = pathtmp,
			.size = fsize,
		};
		
		struct discord_create_message params = {
			.attachments =
			&(struct discord_attachments){
				.size = 1,
				.array = &attachment,
			}
		};
		discord_create_message(client, msg->channel_id, &params, NULL);
	}
	
	pclose(fp);
	free(path);
	free(pathtmp);
}

void on_ready(struct discord *client) {
	const struct discord_user *bot = discord_get_self(client);
	
	log_info("8ball-Bot succesfully connected to Discord as %s#%s!", bot->username, bot->discriminator);
}

// ----------------------------------------------------------------------------------------------------

int main (int argc, char **argv) {
	const char *config_file;
	struct discord *client;
	
	printf("KhajiitBot 2.0a\n");
	
	if (argc > 1) config_file = argv[1];	// if any arguments are passed, assume the first one is the path to the config
	else config_file = "../config.json";	// otherwise default to a known relative location
	
	ccord_global_init();
	client = discord_config_init(config_file);
	assert(NULL != client && "Couldn't initialize client");
	
	discord_set_prefix(client, KBOT_PREFIX);	// Set the command prefix
	discord_set_on_ready(client, &on_ready);
	
	discord_set_on_command(client, NULL, &on_fallback);
	discord_set_on_command(client, "8ball", &eight_ball);
	
	discord_run(client);
	
	discord_cleanup(client);
	ccord_global_cleanup();
}
