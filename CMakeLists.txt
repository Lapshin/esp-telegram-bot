idf_component_register(SRCS "telegram.c"
                            "telegram_send_photo.c"
                            "telegram_send_text.c"
                            "telegram_parser.c"
                            "parser/telegram_message_from.c"
                            "parser/telegram_message.c"
                            "parser/telegram_result.c"
                    INCLUDE_DIRS include
                    PRIV_INCLUDE_DIRS private_include
                    REQUIRES jsmn esp_http_client)