/*
 * telegram_message.c
 *
 *  Created on: Dec 18, 2019
 *      Author: alapshin
 */

#include "parser/telegram_message.h"

int json_parse_telegram_message_callback (json_parser_t *parser, int i, void *data)
{
	message_t *msg = data;
	int result = SUCCESS;
	const char *key = &parser->json[parser->t[i].start];
	size_t key_lenght = parser->t[i].end - parser->t[i].start;

	if (IS_JSON_KEY("message_id"))
	{
		result = json_parse_int(parser, i, &msg->message_id);
	}
	else if (IS_JSON_KEY("from"))
	{
		json_parse_core(parser, i, &msg->from, json_parse_telegram_message_from_callback);
	}
	else if (IS_JSON_KEY("chat"))
	{
		// TODO
	}
	else if (IS_JSON_KEY("date"))
	{
		result = json_parse_int(parser, i, (int *) &msg->date);
	}
	else if (IS_JSON_KEY("text"))
	{
		size_t text_size = parser->t[i].end - parser->t[i].start + 1;
		msg->text = calloc(text_size, 1);
		result = json_parse_string(msg->text, text_size, parser, i);
	}
	else
	{
		ESP_LOGE(__func__, "Unknown field \"%.*s\"", key_lenght, key);
	}

	return result;
}
