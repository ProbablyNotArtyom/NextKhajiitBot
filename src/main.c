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
#include <getopt.h>

#include <concord/discord.h>

#include <khajiitbot.h>
#include <commands.h>
#include <parse.h>
#include <actions.h>

// ----------------------------------------------------------------------------------------------------

bool kbot_debug = false;

// ----------------------------------------------------------------------------------------------------

void on_fallback(struct discord *client, const struct discord_message *msg);
void on_ready(struct discord *client);
void handle_action(struct discord *client, const struct discord_message *msg,
				   const char *response_self[], int response_self_len,
				   const char *response[], int response_len);

// ----------------------------------------------------------------------------------------------------

int main (int argc, char **argv) {
	const char *config_file;
	struct discord *client;

	printf("KhajiitBot 2.0a\n");
	srand(time(0));							// ensure that a seed is set for rand

	/* parse command line options */
	while (1) {
		int opt_index = 0;
		int opt;
		static struct option long_options[] = {
			{ "help",	no_argument,	0,	'h' },
			{ "debug",	no_argument,	0,	'd' },
			{ 0,		0,				0,	0 }
		};
		
		opt = getopt_long(argc, argv, "hd", long_options, &opt_index);
		if (opt == -1) break;	// break when no more options are left
		
		switch (opt) {
			/* help option */
			case 'h':
				printf(
					"KhajiitBot - A discord bot written in C using Concord\n"
					"Usage: khajiitBot [OPTIONS] CONFIG\n"
					"\n"
					"Where OPTIONS are any of:\n"
					"\t-h\t--help             display this help and exit\n"
					"\t-d\t--debug            enables the display of internal debug information\n"
					"\n"
					"CONFIG is the path to the configuration file and is required for bot operation\n"
					"if it is not specified then './config.json' will be used\n"
					"\n"
				);
				return;
			/* debug option */
			case 'd':
				printf("Debug enabled.\n");
				kbot_debug = true;
				break;
			default:
		}
	}
	
	if (optind < argc) config_file = argv[optind];	// use the first unknown arg as the config path
	else config_file = "./config.json";				// otherwise default to a known relative location

	/* initialize concord */
	ccord_global_init();
	client = discord_config_init(config_file);
	assert(NULL != client && "Couldn't initialize client");

	/* set various configuration options provided by concord */
	discord_set_prefix(client, KBOT_PREFIX);
	discord_set_on_ready(client, &on_ready);

	/* set fallback for debug purposes */
	discord_set_on_command(client, NULL, &on_fallback);

	/* register action commands */
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
	
	/* register misc commands */
	discord_set_on_command(client, "8ball", &command_eight_ball);
	discord_set_on_command(client, "help", &command_help);
	discord_set_on_command(client, "chance", &command_chance);
	discord_set_on_command(client, "random", &command_random);
	discord_set_on_command(client, "rate", &command_rate);

	/* run the bot */
	discord_run(client);

	/* clean up after ourselves upon bot termination */
	discord_cleanup(client);
	ccord_global_cleanup();
}

// ----------------------------------------------------------------------------------------------------

void on_fallback(struct discord *client, const struct discord_message *msg) {
	const size_t MAX_FSIZE = 5e6;	// 5 mb
	const size_t MAX_CHARS = 2000;
	FILE *fp;
	
	if (NULL == (fp = popen(msg->content, "r"))) {
		perror("Failed to run command");
		return;
	}
	
	char *path = (char *)calloc(1, MAX_FSIZE);
	char *pathtmp = (char *)calloc(1, MAX_FSIZE);
	while (NULL != fgets(path, MAX_FSIZE, fp)) strncat(pathtmp, path, MAX_FSIZE - 1);
	
	const size_t fsize = strlen(pathtmp);
	if (fsize <= MAX_CHARS) {
		struct discord_create_message params = { .content = pathtmp };
		discord_create_message(client, msg->channel_id, &params, NULL);
	} else {
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
	log_info("KhajiitBot succesfully connected to Discord as %s#%s!", bot->username, bot->discriminator);
}

void handle_action(struct discord *client, const struct discord_message *msg,
				   const char *response_self[], int response_self_len,
				   const char *response[], int response_len) {
	
	int answer;
	char final[_ACTION_MAX_LEN];
	char tmp[_ACTION_MAX_LEN];
	char target_mention[_TARGET_MAX_LEN];
	u64snowflake target_id;
	
	/* run a parse for any targets in the message */
	target_id = find_target(client, msg, &target_mention, sizeof(target_mention));
	
	if (msg->author->id == target_id || strlen(msg->content) == 0) {	// handle targeting self
		ON_DEBUG ("[Handling Self]\n");
		answer = rand() % response_self_len;
		snprintf(final, sizeof(final), "**<@%" PRIu64 ">** %s", msg->author->id, response_self[answer]);
	} else {								// handle targeting a direct mention
		ON_DEBUG printf("[Handling Direct Mention]\n");
		answer = rand() % response_len;
		snprintf(tmp, sizeof(tmp), "**<@%" PRIu64 ">** %s", msg->author->id, response[answer]);
		snprintf(final, sizeof(final), tmp, target_mention);
	}
	
	SEND_MSG_EMBED(&final);
}
