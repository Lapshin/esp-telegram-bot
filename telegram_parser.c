/*
 * telegram_message_parser.c
 *
 *  Created on: Nov 14, 2019
 *      Author: alapshin
 */

#include <stdio.h>
#include <stdlib.h>
#include "telegram.h"
#include "telegram_parser.h"
#include "parser/telegram_result.h"
#include "private_include/telegram_parser.h"

#define GOTO_ERR do { ESP_LOGE(__func__, "error on line %d", __LINE__); goto err_exit; } while (0)

#define JSON_MAX_TOKENS 128

int compare_json_value (const char *str, const char *json, jsmntok_t *t, int i)
{
	int len_1 = strlen(str);
	int len_2 = t[i].end - t[i].start;
	return strncmp(str, json + t[i].start, (len_1 < len_2) ? len_1 : len_2);
}

int json_parse_string (char *str, int str_len, json_parser_t *parser, int index)
{
	int result = SUCCESS;
	int json_str_len = parser->t[index].end - parser->t[index].start;
	if(str_len < json_str_len)
	{
		result = TOO_LONG_STRING;
		GOTO_ERR;
	}
	strncpy(str, parser->json + parser->t[index].start, json_str_len);
err_exit:
	return result;
}

int json_parse_int(json_parser_t *parser, int index, int *val)
{
	int result = SUCCESS;
	char *endptr;
	*val = strtol(parser->json + parser->t[index].start, &endptr, 10);
	if (endptr != parser->json + parser->t[index].end)
	{
		*val = 0;
		result = PARSING_INT;
	}

	return result;
}

int json_parse_core (json_parser_t *parser, int index, void *data, int (*callback)(json_parser_t *parser, int index, void *data))
{
	int i, result = index;
	int object_parrent = parser->t[index].parent + 1;
	if (parser->t[index].type != JSMN_OBJECT)
	{
		goto err_exit;
	}

	for (i = index; parser->t[i].type < object_parrent && i < parser->r; i++)
	{
		if (parser->t[i].parent != object_parrent)
		{
			continue;
		}
		result = callback(parser, i, data);
		if (result != SUCCESS)
		{
			ESP_LOGE(__func__, "Error while parsing \"%.*s\"",
					parser->t[i].end - parser->t[i].start,
					&parser->json[parser->t[i].start]);
			goto err_exit;
		}
	}
	result = i;

err_exit:
	return result;
}

int parse_updates_message (const char *json, telegram_parsed_msg_t *message)
{
	int i = 0, result = SUCCESS;
	jsmn_parser p;
	jsmntok_t *t = calloc(sizeof(jsmntok_t), JSON_MAX_TOKENS);
	json_parser_t parser = {.json = json, .t = t, .r = 0};

	const char *key = NULL;
	size_t key_lenght = 0;

	jsmn_init(&p);
	parser.r = jsmn_parse(&p, json, strlen(json), t, JSON_MAX_TOKENS);
	if (parser.r < 0)
	{
		result = PARSING_ERROR;
		GOTO_ERR;
	}

	/* Assume the top-level element is an object */
	if (parser.r < 1 || t[i].type != JSMN_OBJECT)
	{
		result = PARSING_ERROR;
		GOTO_ERR;
	}

	i++;
	key = &parser.json[parser.t[i].start];
	key_lenght = parser.t[i].end - parser.t[i].start;
	if(!IS_JSON_KEY("ok"))
	{
		result = PARSING_ERROR;
		GOTO_ERR;
	}
	key = &parser.json[parser.t[i].start];
	key_lenght = parser.t[i].end - parser.t[i].start;
	if(!IS_JSON_KEY("true"))
	{
		result = PARSING_ERROR;
		GOTO_ERR;
	}
	key = &parser.json[parser.t[i].start];
	key_lenght = parser.t[i].end - parser.t[i].start;
	if(!IS_JSON_KEY("result"))
	{
		result = PARSING_ERROR;
		GOTO_ERR;
	}
	i++;
	memset(message, 0x00, sizeof(*message));
	json_parse_core(&parser, i, message, json_parse_telegram_result_callback);

	result = SUCCESS;

err_exit:
	free(t);
	t = NULL;
	return result;
}
