#pragma once

#include <string>
#include <list>
#include <libtcod.hpp>
#include "palette.h"

namespace mom
{
	struct Message
	{
		std::string messageText;
		tcod::ColorRGB messageColor;
		int count;

		Message(std::string messageText, tcod::ColorRGB messageColor) : messageText(messageText), messageColor(messageColor), count(1) {}
	};


	class MessageLog
	{
	public:
		const std::list<Message>& log = messages;

		static MessageLog& getInstance()
		{
			if (instance == NULL)
				instance = new MessageLog();
			return *instance;
		}

		void writeMessage(std::string newMessage, tcod::ColorRGB newMessageColor)
		{
			if (messages.size() > 0 && messages.front().messageText == newMessage && messages.front().count < 5)
			{
				messages.front().count++;
			}
			else
			{
				messages.push_front(Message(newMessage, newMessageColor));
				if (messages.size() > MAX_MESSAGES)
					messages.pop_back();
			}
		}

		void clearLog()
		{
			messages.clear();
		}

	private:
		MessageLog() {}

		const int MAX_MESSAGES = 50;
		std::list<Message> messages;

		static MessageLog* instance;
	};
}