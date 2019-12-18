#include <unistd.h>
#include <string.h>
#include "stdatomic.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_http_client.h"
#include "esp_log.h"
#include "telegram.h"

#include "private_include/telegram_parser.h"
#include "telegram_api.h"

atomic_uint polling_time = ATOMIC_VAR_INIT(5);
atomic_bool bot_running = ATOMIC_VAR_INIT(false);

static char telegram_bot_token[TELEGRAM_BOT_TOKEN_SIZE] = {0};
static void (*update_callback)(telegram_parsed_msg_t *msg) = NULL;

void telegram_set_update_callback (void (*callback) (telegram_parsed_msg_t *msg))
{
	update_callback = callback;
}

void telegram_set_bot_token (char *bot_token)
{
    memset(telegram_bot_token, 0x00, sizeof(telegram_bot_token));
    strcpy(telegram_bot_token, bot_token);
}

const char *telegram_get_bot_token (void)
{
	return telegram_bot_token;
}

int telegram_send_response (const char *link, char **answer)
{
    int ret_code = 0;
    int content_lenght = -1;
    int content_lenght_read = -1;
    int status_code = 0;
    esp_err_t err = ESP_OK;
    ESP_LOGD(__func__, "send response to %s", link);
    esp_http_client_config_t config = { .url = link };
    esp_http_client_handle_t client = esp_http_client_init(&config);
    if (client == NULL)
    {
        ESP_LOGE(__func__, "Failed on esp_http_client_init()");
        goto err_exit;
    }
    err = esp_http_client_open(client, 0);
    if (err != ESP_OK)
    {
       ESP_LOGE(__func__, "Failed to open HTTP connection: %s", esp_err_to_name(err));
       goto err_exit;
    }
    content_lenght =  esp_http_client_fetch_headers(client);
    status_code = esp_http_client_get_status_code(client);
    ESP_LOGD(__func__, "HTTP Status = %d, content_length = %d", status_code, content_lenght);

    if(status_code != 200)
    {
        ESP_LOGE(__func__, "Bad status code (%d)", status_code);
        goto err_exit;
    }

    if(content_lenght == -1)
    {
        //TODO
        ESP_LOGE(__func__, "Chanked answer TODO");
        goto err_exit;
    }
    *answer = calloc(content_lenght + 1, 1);
    if(*answer == NULL)
    {
        ESP_LOGE(__func__, "%s:%d Bad, bad, bad... malloc returned NULL", __func__, __LINE__);
        goto err_exit;
    }

    content_lenght_read = esp_http_client_read(client, *answer, content_lenght);
    if(content_lenght_read != content_lenght)
    {
        ESP_LOGE(__func__, "%s:%d content_lenght_read (%d) != content_lenght (%d)", __func__, __LINE__, content_lenght_read, content_lenght);
        goto err_exit;
    }

    goto exit;

err_exit:
    free(*answer);
    *answer = NULL;
    ret_code = -1;
exit:
    esp_http_client_close(client);
    esp_http_client_cleanup(client);
    return ret_code;
}

int telegram_get_update (char **answer, const size_t offset)
{
    static char telegram_update_url[128] = {0};
    snprintf(telegram_update_url, sizeof(telegram_update_url) - 1, "%s/bot%s/%s?limit=1&offset=%u",
            TELEGRAM_API_URL,
            telegram_bot_token,
            TELEGRAM_METHOD_GET_UPDATES,
            offset);
    return telegram_send_response(telegram_update_url, answer);
}

static void character_replace(char *str, char in, char out)
{
    if (str == NULL)
    {
        return;
    }
    for(; *str != '\0'; str++)
    {
        if(*str != in)
        {
            continue;
        }
        *str = out;
    }
}

int telebot_check_updates (void)
{
    char *answer = NULL;
    int ret = -1, ret_val;
    telegram_parsed_msg_t msg = {0};
    static size_t offset = 0;

    ret_val = telegram_get_update(&answer, offset);
    if(ret_val != 0) {
        ESP_LOGE(__func__, "Got error on telegram_send_request");
        goto err_exit; //TODO
    }
    character_replace(answer, '\n', ' ');
    ESP_LOGD(__func__,"%s\n", answer);
    ret_val = parse_updates_message(answer, &msg);
    if (ret_val != 0)
    {
        ESP_LOGE(__func__, "Parsing error");
        goto err_exit; //TODO
    }

    update_callback(&msg);

    offset = msg.update_id + 1;

err_exit:
    if (msg.message != NULL)
    {
        free(msg.message->text);
        free(msg.message->document);
        free(msg.message);
    }
    free(answer);
    answer = NULL;
    return ret;
}

void telegram_bot_loop (void *param)
{
    while (atomic_load(&bot_running))
    {
        telebot_check_updates();
        sleep(atomic_load(&polling_time));
    }
}

void telegram_bot_start (unsigned int _poling_time)
{
    bool compare = false;
    if (update_callback == NULL)
    {
        ESP_LOGE(__func__, "update_callback is NULL, telegram bot stopped");
        return;
    }
    if (atomic_compare_exchange_strong(&bot_running, &compare, true) == false)
    {
        ESP_LOGE(__func__, "Bot is already running");
        return;
    }
    xTaskCreate(telegram_bot_loop,
                "telegram_bot_loop",
                 1024 * 8,
                 NULL,
                 1,
                 NULL);
}

void telegram_bot_stop(void)
{
	atomic_exchange(&bot_running, false);
}

