/*
 * telegram_message.h
 *
 *  Created on: Dec 18, 2019
 *      Author: alapshin
 */

#ifndef PRIVATE_INCLUDE_TELEGRAM_MESSAGE_FROM_H_
#define PRIVATE_INCLUDE_TELEGRAM_MESSAGE_FROM_H_

#include "../telegram_parser.h"

int json_parse_telegram_message_from_callback(json_parser_t *parser, int i, void *data);

#endif /* PRIVATE_INCLUDE_TELEGRAM_MESSAGE_FROM_H_ */
