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
#include "parse.h"

// ----------------------------------------------------------------------------------------------------

void on_fallback(struct discord *client, const struct discord_message *msg) {
	const size_t MAX_FSIZE = 5e6; // 5 mb
	const size_t MAX_CHARS = 2000;
	FILE *fp;

	if (NULL == (fp = popen(msg->content, "r"))) {
		perror("Failed to run command");
		return;
	}

	char *path = (char *)calloc(1, MAX_FSIZE);
	char *pathtmp = (char *)calloc(1, MAX_FSIZE);
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
			.attachments = &(struct discord_attachments) {
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

void handle_action(struct discord *client, const struct discord_message *msg,
	const char *response_self[], int response_self_len,
	const char *response[], int response_len) {

	srand(time(0));					// generate seed for randomizer
	int answer;
	char final[2000];
	char tmp[2000];
	char target_mention[2000];

	u64snowflake target_id = find_mention(client, msg);
	if (msg->author->id == target_id || target_id == 0) {	// handle targeting self
		printf("[Handling self]\n");
		answer = rand() % response_self_len;
		sprintf(final, "**<@%" PRIu64 ">** %s", msg->author->id, response_self[answer]);
	} else {
		printf("[Handling targeted]\n");
		answer = rand() % response_len;
		sprintf(tmp, "**<@%" PRIu64 ">** %s", msg->author->id, response[answer]);
		printf("tmp: %s\n", tmp);
		sprintf(target_mention, "**<@%" PRIu64 ">**", target_id);
		printf("target_mention: %s\n", target_mention);
		sprintf(final, tmp, target_mention);
		printf("final: %s\n", final);
	}

	struct discord_embed embeds[] = {
		{
			.color = KBCOLOR_MSG,
			.description = final
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

	discord_set_on_command(client, "bless", &action_bless);
	discord_set_on_command(client, "boof", &action_boof);
	discord_set_on_command(client, "grope", &action_grope);
	discord_set_on_command(client, "hug", &action_hug);
	discord_set_on_command(client, "kiss", &action_kiss);
	discord_set_on_command(client, "meow", &action_meow);
	discord_set_on_command(client, "nuke", &action_nuke);
	discord_set_on_command(client, "pet", &action_pet);
	discord_set_on_command(client, "respects", &action_respects);
	discord_set_on_command(client, "shoot", &action_shoot);
	discord_set_on_command(client, "stab", &action_stab);
	discord_set_on_command(client, "vore", &action_vore);
	discord_set_on_command(client, "yiff", &action_yiff);

	discord_run(client);

	discord_cleanup(client);
	ccord_global_cleanup();
}
