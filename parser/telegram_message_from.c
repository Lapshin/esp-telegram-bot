/*
 * telegram_message.c
 *
 *  Created on: Dec 18, 2019
 *      Author: alapshin
 */

#include "parser/telegram_message_from.h"

int json_parse_telegram_message_from_callback (json_parser_t *parser, int i, void *data)
{
    int result = SUCCESS;
    message_from_t *from = data;
    const char *key = &parser->json[parser->t[i].start];
    size_t key_lenght = parser->t[i].end - parser->t[i].start;

    if (IS_JSON_KEY("id"))
    {
        result = json_parse_int(parser, i, &from->id);
    }
    else if (IS_JSON_KEY("is_bot"))
    {
        from->is_bot =  compare_json_value("true", parser->json, parser->t, result) ? 1 : 0;
    }
    else if (IS_JSON_KEY("first_name"))
    {
        result = json_parse_string(from->first_name, sizeof(from->first_name), parser, i);
    }
    else if (IS_JSON_KEY("username"))
    {
        result = json_parse_string(from->username, sizeof(from->username), parser, i);
    }
    else if (IS_JSON_KEY("language_code"))
    {
        result = json_parse_string(from->language_code, sizeof(from->language_code), parser, i);
    }
    else
    {
        ESP_LOGE(__func__, "Unknown field \"%.*s\"", key_lenght, key);
    }

    return result;
}
