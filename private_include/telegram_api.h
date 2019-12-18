/*
 * telegram_api.h
 *
 *  Created on: Sep 27, 2019
 *      Author: alapshin
 */

#ifndef TELEGRAM_API_H_
#define TELEGRAM_API_H_

#define TELEGRAM_API_URL                      "https://api.telegram.org"
#define TELEGRAM_URL_SIZE                     1024
#define TELEGRAM_UPDATE_COUNT_MAX_LIMIT       5
#define TELEGRAM_USER_PROFILE_PHOTOS_LIMIT    1
#define TELEGRAM_BOT_TOKEN_SIZE               64

#define TELEGRAM_METHOD_GET_UPDATES                  "getUpdates"
#define TELEGRAM_METHOD_SET_WEBHOOK                  "setWebhook"
#define TELEGRAM_METHOD_DELETE_WEBHOOK               "deleteWebhook"
#define TELEGRAM_METHOD_GET_WEBHOOK_INFO             "getWebhookInfo"
#define TELEGRAM_METHOD_GET_ME                       "getMe"
#define TELEGRAM_METHOD_SEND_MESSAGE                 "sendMessage"
#define TELEGRAM_METHOD_FORWARD_MESSAGE              "forwardMessage"
#define TELEGRAM_METHOD_SEND_PHOTO                   "sendPhoto"
#define TELEGRAM_METHOD_SEND_AUDIO                   "sendAudio"
#define TELEGRAM_METHOD_SEND_DOCUMENT                "sendDocument"
#define TELEGRAM_METHOD_SEND_VIDEO                   "sendVideo"
#define TELEGRAM_METHOD_SEND_ANIMATION               "sendAnimation"
#define TELEGRAM_METHOD_SEND_VOICE                   "sendVoice"
#define TELEGRAM_METHOD_SEND_VIDEO_NOTE              "sendVideoNote"
#define TELEGRAM_METHOD_SEND_MEDIA_GROUP             "sendMediaGroup"
#define TELEGRAM_METHOD_SEND_LOCATION                "sendLocation"
#define TELEGRAM_METHOD_EDIT_MESSAGE_LIVE_LOCATION   "editMessageLiveLocation"
#define TELEGRAM_METHOD_STOP_MESSAGE_LIVE_LOCATION   "stopMessageLiveLocation"
#define TELEGRAM_METHOD_SEND_VENUE                   "sendVenue"
#define TELEGRAM_METHOD_SEND_CONTACT                 "sendContact"
#define TELEGRAM_METHOD_SEND_CHAT_ACTION             "sendChatAction"
#define TELEGRAM_METHOD_GET_USER_PHOTOS              "getUserProfilePhotos"
#define TELEGRAM_METHOD_GET_FILE                     "getFile"
#define TELEGRAM_METHOD_KICK_CHAT_MEMBER             "kickChatMember"
#define TELEGRAM_METHOD_UNBAN_CHAT_MEMBER            "unbanChatMember"
#define TELEGRAM_METHOD_RESTRICT_CHAT_MEMBER         "restrictChatMember"
#define TELEGRAM_METHOD_PROMOTE_CHAT_MEMBER          "promoteChatMember"
#define TELEGRAM_METHOD_EXPORT_CHAT_INVITE_LINK      "exportChatInviteLink"
#define TELEGRAM_METHOD_SET_CHAT_PHOTO               "setChatPhoto"
#define TELEGRAM_METHOD_DELETE_CHAT_PHOTO            "deleteChatPhoto"
#define TELEGRAM_METHOD_SET_CHAT_TITLE               "setChatTitle"
#define TELEGRAM_METHOD_SET_CHAT_DESCRIPTION         "setChatDescription"
#define TELEGRAM_METHOD_PIN_CHAT_MESSAGE             "pinChatMessage"
#define TELEGRAM_METHOD_UNPIN_CHAT_MESSAGE           "unpinChatMessage"
#define TELEGRAM_METHOD_LEAVE_CHAT                   "leaveChat"
#define TELEGRAM_METHOD_GET_CHAT                     "getChat"
#define TELEGRAM_METHOD_GET_CHAT_ADMINS              "getChatAdministrators"
#define TELEGRAM_METHOD_GET_CHAT_MEMBERS_COUNT       "getChatMembersCount"
#define TELEGRAM_METHOD_GET_CHAT_MEMBER              "getChatMember"
#define TELEGRAM_METHOD_SET_CHAT_STICKER_SET         "setChatStickerSet"
#define TELEGRAM_METHOD_DEL_CHAT_STICKER_SET         "deleteChatStickerSet"
#define TELEGRAM_METHOD_ANSWER_CALLBACK_QUERY        "answerCallbackQuery"
#define TELEGRAM_METHOD_EDIT_MESSAGE_TEXT            "editMessageText"
#define TELEGRAM_METHOD_EDIT_MESSAGE_CAPTION         "editMessageCaption"
#define TELEGRAM_METHOD_EDIT_MESSAGE_REPLY_MARKUP    "editMessageReplyMarkup"
#define TELEGRAM_METHOD_DELETE_MESSAGE               "deleteMessage"
#define TELEGRAM_METHOD_SEND_STICKER                 "sendSticker"

#endif /* TELEGRAM_API_H_ */
