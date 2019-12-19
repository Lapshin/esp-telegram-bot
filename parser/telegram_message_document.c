/*
 * telegram_message_document.c
 *
 *  Created on: Dec 19, 2019
 *      Author: alapshin
 */


#include "parser/telegram_message_document.h"

int json_parse_telegram_message_document_callback(json_parser_t *parser, int i, void *data)
{
	document_t *doc = data;
    int result = SUCCESS;
    const char *key = &parser->json[parser->t[i].start];
    size_t key_lenght = parser->t[i].end - parser->t[i].start;


    if (IS_JSON_KEY("file_id"))
    {
        result = json_parse_string(doc->file_id, sizeof(doc->file_id), parser, i);
    }
    else if (IS_JSON_KEY("file_name"))
    {
        result = json_parse_string(doc->file_name, sizeof(doc->file_name), parser, i);
    }
    else if (IS_JSON_KEY("file_size"))
    {
        result = json_parse_int(parser, i, (int *) &doc->size);
    }
    else
    {
        ESP_LOGE(__func__, "Unknown field \"%.*s\"", key_lenght, key);
    }

    return result;
}
