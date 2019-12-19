/*
 * telegram.h
 *
 *  Created on: Sep 24, 2019
 *      Author: alapshin
 */

#ifndef MAIN_TELEGRAM_H_
#define MAIN_TELEGRAM_H_

enum
{
    SUCCESS = 0,
    GENERAL_ERROR = -1,
    MESSAGE_FROM_BOT = -2,
    TOO_LONG_STRING = -3,
    PARSING_INT = -4,
    UNEXPECTED_TOKEN = -5,
    PARSING_ERROR = -6,
};

typedef struct message_from_s
{
    int id;
    int is_bot;
    char first_name[64];
    char username[64];
    char language_code[8];
} message_from_t;

typedef struct document_s
{
    char file_name[256];
    char file_id[256];
    size_t size;
} document_t;

typedef struct message_s
{
    int message_id;
    unsigned int date;
    message_from_t from;
    char *text;
    document_t *document;
} message_t;

typedef struct telegram_parsed_msg_s
{
    int update_id;
    message_t *message;
} telegram_parsed_msg_t;

void telegram_set_update_callback(void (*callback) (telegram_parsed_msg_t *msg));
void telegram_bot_start(unsigned int _poling_time);;
void telegram_bot_stop(void);
void telegram_set_bot_token(char *bot_token);
const char *telegram_get_bot_token(void);
int telegram_send_response(const char *link, char **answer);
void telegram_bot_set_polling_time(unsigned int _poling_time);

#endif /* MAIN_TELEGRAM_H_ */
