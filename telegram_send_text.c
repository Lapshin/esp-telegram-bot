/*
 * telegram_send_text.c
 *
 *  Created on: Dec 17, 2019
 *      Author: alapshin
 */


#include <unistd.h>
#include <string.h>
#include "esp_http_client.h"
#include "esp_log.h"
#include "telegram.h"
#include "telegram_api.h"

#include "telegram_send_text.h"

void telegram_send_text(const int chat_id, const char *text, const int reply_to_message_id)
{
    char *answer = NULL;
    char *telegram_photo_url = calloc(
                                   strlen(TELEGRAM_API_URL) +
                                   strlen(text) +
                                   TELEGRAM_BOT_TOKEN_SIZE +
                                   strlen(TELEGRAM_METHOD_SEND_MESSAGE) +
                                   128, 1);
    sprintf(telegram_photo_url, "%s/bot%s/%s?chat_id=%d&text=%s&reply_to_message_id=%d",
            TELEGRAM_API_URL,
            telegram_get_bot_token(),
            TELEGRAM_METHOD_SEND_MESSAGE,
            chat_id,
            text,
            reply_to_message_id);

    telegram_send_response(telegram_photo_url, &answer);
    ESP_LOGI(__FUNCTION__, "response %s", answer);
    free(answer);
    answer = NULL;
}
