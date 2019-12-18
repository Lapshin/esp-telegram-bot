/*
 * telegram_result.c
 *
 *  Created on: Dec 18, 2019
 *      Author: alapshin
 */

#include "parser/telegram_result.h"

int json_parse_telegram_result_callback(json_parser_t *parser, int i, void *data)
{
	telegram_parsed_msg_t *rlt = data;
	int result = SUCCESS;
	const char *key = &parser->json[parser->t[i].start];
	size_t key_lenght = parser->t[i].end - parser->t[i].start;

	if (IS_JSON_KEY("update_id"))
	{
		result = json_parse_int(parser, i, &rlt->update_id);
	}
	else if (IS_JSON_KEY("message"))
	{
		rlt->message = calloc(sizeof(*(rlt->message)), 1);
		json_parse_core(parser, i, rlt->message, json_parse_telegram_message_callback);
	}
	else
	{
		ESP_LOGE(__func__, "Unknown field \"%.*s\"", key_lenght, key);
	}

	return result;
}
