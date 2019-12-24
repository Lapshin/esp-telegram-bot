/*
 * telegram_send_text.c
 *
 *  Created on: Dec 17, 2019
 *      Author: alapshin
 */


#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include "esp_http_client.h"
#include "esp_log.h"
#include "telegram.h"
#include "telegram_api.h"

#include "telegram_send_text.h"

static char rfc3986[256] = {0};

static void init_rfc3986(void)
{
    int i;
    for (i = 0; i < 256; i++) {
        rfc3986[i] = isalnum(i) ||
                i == '~' ||
                i == '-' ||
                i == '.' ||
                i == '_' ? i : 0;
    }
}

static void encode(const unsigned char *s, char *enc)
{
    if (rfc3986['-'] == 0)
    {
        init_rfc3986();
    }
    for (; *s != 0; s++) {
        enc += (rfc3986[*s]) ? sprintf(enc, "%c", rfc3986[*s]) : sprintf(enc, "%%%02X", *s);
    }
}

void telegram_send_text(const int chat_id, const char *text, const int reply_to_message_id)
{
    char *answer = NULL;
    char *encoded_text = calloc(strlen(text) * 3 + 1, 1);
    encode((unsigned char *)text, encoded_text);
    char *telegram_photo_url = calloc(
                                   strlen(TELEGRAM_API_URL) +
                                   strlen(encoded_text) +
                                   TELEGRAM_BOT_TOKEN_SIZE +
                                   strlen(TELEGRAM_METHOD_SEND_MESSAGE) +
                                   128, 1);
    sprintf(telegram_photo_url, "%s/bot%s/%s?chat_id=%d&text=%s&reply_to_message_id=%d",
            TELEGRAM_API_URL,
            telegram_get_bot_token(),
            TELEGRAM_METHOD_SEND_MESSAGE,
            chat_id,
            encoded_text,
            reply_to_message_id);

    telegram_send_response(telegram_photo_url, &answer);
    ESP_LOGI(__FUNCTION__, "response %s", answer);
    free(answer);
    free(encoded_text);
    answer = NULL;
}
