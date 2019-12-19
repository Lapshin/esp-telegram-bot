/*
 * telegram_message.h
 *
 *  Created on: Dec 18, 2019
 *      Author: alapshin
 */

#ifndef PRIVATE_INCLUDE_PARSER_TELEGRAM_MESSAGE_H_
#define PRIVATE_INCLUDE_PARSER_TELEGRAM_MESSAGE_H_

#include "../telegram_parser.h"
#include "parser/telegram_message_from.h"
#include "parser/telegram_message_document.h"

int json_parse_telegram_message_callback(json_parser_t *parser, int i, void *data);

#endif /* PRIVATE_INCLUDE_PARSER_TELEGRAM_MESSAGE_H_ */
