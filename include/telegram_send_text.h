/*
 * telegram_send_text.h
 *
 *  Created on: Dec 17, 2019
 *      Author: alapshin
 */

#ifndef INCLUDE_TELEGRAM_SEND_TEXT_H_
#define INCLUDE_TELEGRAM_SEND_TEXT_H_

void telegram_send_text(const int chat_id, const char *text, const int reply_to_message_id);

#endif /* INCLUDE_TELEGRAM_SEND_TEXT_H_ */
