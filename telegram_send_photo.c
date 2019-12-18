/*
 * telegram_send_photo.c
 *
 *  Created on: Dec 12, 2019
 *      Author: alapshin
 */

#include <unistd.h>
#include <string.h>
#include "esp_http_client.h"
#include "esp_log.h"
#include "telegram.h"
#include "telegram_api.h"

#include "telegram_send_photo.h"

#define BOUNDARY "BADBEAFFFDEADBABBY"

static int send_multipart_chunk(esp_http_client_handle_t client, unsigned char send, char *name, char *cont_type, const char *value, size_t vlen)
{
    int len = vlen;
    int res;
    char buff[256];
    len += sprintf(buff, "\r\n--%s\r\nContent-Disposition: form-data; name=%s%s%s\r\n\r\n",
                   BOUNDARY,
                   name,
                   cont_type == NULL ? "" : "\r\nContent-Type:",
                   cont_type == NULL ? "" : cont_type);
    if (send != 0)
    {
        res = esp_http_client_write(client, buff, strlen(buff));
        if (res <= 0)
        {
            return res;
        }
        res = esp_http_client_write(client, value, vlen);
        if (res <= 0)
        {
            return res;
        }
    }
    return len;
}

static int send_multipart_end(esp_http_client_handle_t client, unsigned char send)
{
    char buff[32];
    int len = sprintf(buff, "\r\n--%s--\r\n", BOUNDARY);
    if(send != 0)
    {
        esp_http_client_write(client, buff, strlen(buff));
    }
    return len;
}


void telegram_send_photo(const size_t chat_id, const char *image, const size_t image_length)
{
    size_t cont_len = 0;
    char chat_id_str[32] = {0};
    char telegram_photo_url[128] = {0};
    sprintf(telegram_photo_url, "%s/bot%s/%s",
            TELEGRAM_API_URL,
            telegram_get_bot_token(),
            TELEGRAM_METHOD_SEND_PHOTO);
    esp_err_t err = ESP_OK;
    esp_http_client_config_t config = {0};
    config.url = telegram_photo_url;
    ESP_LOGI(__FUNCTION__, "%s", telegram_photo_url);
    esp_http_client_handle_t client = esp_http_client_init(&config);
    if (client == NULL)
    {
        ESP_LOGE(__FUNCTION__, "Error on esp_http_client_init()");
        return;
    }
    esp_http_client_set_method(client, HTTP_METHOD_POST);
    esp_http_client_set_header(client, "Content-Type", "multipart/form-data; boundary="BOUNDARY);
    sprintf(chat_id_str, "%u", chat_id);

    cont_len += send_multipart_chunk(client, 0, "chat_id", NULL, chat_id_str, strlen(chat_id_str));
    cont_len += send_multipart_chunk(client, 0, "photo; filename=1.jpeg", "image/jpeg", image, image_length);
    cont_len += send_multipart_end(client, 0);
    esp_http_client_open(client, cont_len);
    cont_len += send_multipart_chunk(client, 1, "chat_id", NULL, chat_id_str, strlen(chat_id_str));
    cont_len += send_multipart_chunk(client, 1, "photo; filename=1.jpeg", "image/jpeg", image, image_length);
    cont_len += send_multipart_end(client, 1);
    err = esp_http_client_perform(client);
    if (err == ESP_OK)
    {
        ESP_LOGI(__FUNCTION__, "HTTP POST Status = %d, content_length = %d",
                 esp_http_client_get_status_code(client),
                 esp_http_client_get_content_length(client));
    }
    else
    {
        ESP_LOGE(__FUNCTION__, "HTTP POST request failed: %s", esp_err_to_name(err));
    }
    size_t content_lenght = esp_http_client_get_content_length(client);
    char *content = calloc(content_lenght + 1, 1);
    if(content == NULL)
    {
        ESP_LOGE(__FUNCTION__, "%s:%d Bad, bad, bad... malloc returned NULL", __FUNCTION__, __LINE__);
    }

    esp_http_client_read(client, content, content_lenght);
    content[content_lenght] = 0;
    ESP_LOGE(__FUNCTION__, "%s", content);

    free(content);
    content = NULL;
    esp_http_client_close(client);
    esp_http_client_cleanup(client);
}
