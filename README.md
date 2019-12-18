#Build

* `git clone` into your esp-idf/components
* `./idf.py menuconfig` --->  `Component config` ---> `jsmn` ---> `Enable parent links`

#Example echo request

```
#include "telegram.h"
#include "telegram_send_text.h"

#define TELEGRAM_BOT_TOKEN "YOUR_BOT'S_TOKEN"
#define TELEGRAM_POLLING_TIMEOUT 5 /* in seconds */

void callback(telegram_parsed_msg_t *msg)
{
    if (msg->message == NULL)
    {
        ESP_LOGD(__FUNCTION__, "No new messages");
        return;
    }
    ESP_LOGI(__FUNCTION__, "message received");
    ESP_LOGI(__FUNCTION__, "message_id %d date %d", msg->message->message_id, msg->message->date);
    ESP_LOGI(__FUNCTION__, "id %d first_name %s username %s language_code %s",
            msg->message->from.id,
            msg->message->from.first_name,
            msg->message->from.username,
            msg->message->from.language_code);
    if (msg->message->text)
    {
        ESP_LOGI(__FUNCTION__, "text \"%s\"", msg->message->text);
        telegram_send_text(msg->message->from.id, msg->message->text, msg->message->message_id);
    }
    else
    {
        ESP_LOGI(__FUNCTION__, "have NOT text in message");
        telegram_send_text("have NOT text in message");
    }
}

/* Bot initialization and start */ 
    telegram_set_bot_token(TELEGRAM_BOT_TOKEN);
    telegram_set_update_callback(&callback);
    telegram_bot_start(TELEGRAM_POLLING_TIMEOUT);

```