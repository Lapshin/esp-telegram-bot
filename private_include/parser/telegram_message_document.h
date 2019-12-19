/*
 * telegram_message_document.h
 *
 *  Created on: Dec 19, 2019
 *      Author: alapshin
 */

#ifndef INCLUDE_TELEGRAM_MESSAGE_DOCUMENT_H_
#define INCLUDE_TELEGRAM_MESSAGE_DOCUMENT_H_

#include "../telegram_parser.h"

int json_parse_telegram_message_document_callback(json_parser_t *parser, int i, void *data);

#endif /* INCLUDE_TELEGRAM_MESSAGE_DOCUMENT_H_ */
