/*
 * parser.h
 *
 *  Created on: Dec 18, 2019
 *      Author: alapshin
 */

#ifndef PRIVATE_INCLUDE_TELEGRAM_PARSER_H_
#define PRIVATE_INCLUDE_TELEGRAM_PARSER_H_

#include <string.h>
#include "jsmn.h"
#include "telegram.h"
#include "esp_log.h"

#define IS_JSON_KEY(x) (strncmp((x), key, key_lenght) == 0 && i++)

typedef struct
{
    const char *json;
    jsmntok_t *t;
    int r;
} json_parser_t;

int parse_updates_message(char *json, telegram_parsed_msg_t *message);

int json_parse_core (json_parser_t *parser, int index, void *data, int (*callback)(json_parser_t *parser, int index, void *data));
int compare_json_value (const char *str, const char *json, jsmntok_t *t, int i);
int json_parse_string (char *str, int str_len, json_parser_t *parser, int index);
int json_parse_int(json_parser_t *parser, int index, int *val);


#endif /* PRIVATE_INCLUDE_TELEGRAM_PARSER_H_ */
