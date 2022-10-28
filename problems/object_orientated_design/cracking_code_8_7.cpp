/*
Design a chat server. in particular, provide details about the 
various backend components, classes and methods. what would
be the hardest problems to solve?


is this a chat service for friends to connect with each other, for customer service?
is this 1 to 1 or many to many?
is chat content sensitive? need to worry about security?

assume we will design a chat service for friends to chat with other friends, and it supports many to many.

core objects
User
Message
Text Message
Image Message
Chat Room
Chat service


relationships
a chat room contains at least 2 users, and may contain previous messages
a chat service can contain many chat rooms, and one message manager


actions
a user can create a chatroom with at least 1 other user from the chat service. a user can send a message to a chat room
a chat room stores messages and can give them on query. It also can send messages to users in it


the hardest problems to solve probably relate to choosing a communication protocol like web sockets,
and being flexible there 



Feedback from solution, didnt do hardest stuff well. 
Some of the harder challenges: 
How do we know if somone is online? When signed off, maybe connection dropped. potentially when user signed off,
	try pinging client.
	
How deal with conflicing information? Some in memory, some in db. how keep in sync, which one is right.

How do we scale? split data across servers, then concerned about out of sync data

How prevent dos attacks? Maybe auth and check client before doing action, keep track of last x times theyve done stuff.

also, user manager to add users and manage them and remove. how do they add each other?

she seperated gropu chat from singele chat. abstract base class for chat.

talk about how big system, database, clients, main server, interact. focus on small aspects for object orientated design.

*/

#include <map>
#include <string>
#include <vector>

class ChatRoom;
class User;
class Message;
class TextMessage;
class ChatService;

class ChatService
{
	public:
	  static ChatService& getInstance()
		{
			static ChatService instance;
			return instance;
			
			
		}
		
		ChatService& operator =(const ChatService&) = delete;
		
		// check if we already have chat room created and create if not
		ChatRoom* getChatRoom(std::vector<User> users);
		
  private:
	  std::map<std::vector<User>, ChatRoom> chat_rooms;
		ChatService();
};

class ChatRoom
{
	public:
	  void sendMessage(Message msg, int from_user);
		std::vector<Message> getPastMessages();
		
	private:
	  std::vector<User> users;
		std::vector<Message> messages;
};

class Message
{
	public:
		virtual std::string serializeMsg() = 0;
		// sets msg id
		Message(int id);
	private:
	  int msg_id;
};

class TextMessage : public Message
{
	public:
	  TextMessage(int id, std::string msg_contents) : Message(id)
		{
			contents = msg_contents;
		}
		
		std::string serializeMsg()
		{
			return contents;
		}
		
	private:
	  std::string contents;

};



class User
{
	public:
	  // gets instance of chat service and requests a chat room
	  ChatRoom * getChatRoom(std::vector<User> users);
		// calls the sendMessage function of chatroom passing from user id
		void sendMessage(ChatRoom* chatroom, Message msg);
		int getUserId();
	private:
	  int id;
};



int main()
{

}