// design a musical jukebox using object orientated principles

/*
Ambiguities
Is this a jukebox in a bar you pay for, with drunk people, or one for private people inside of homes?

Core Objects
Song
Library
User Interface
Music Player
Jukebox

relationships
A library has many songs inside of it. 
Each jukebox has one library, unless we are making for many markets, in which case we may do a shared ptr approach.
Each jukebox has one music player, unless we are doing a multi-room bar setup.
Each jukebox has one user interface.

Actions
a user uses the user interface to pay for songs, to search songs in the library, and to play music, all on the jukebox
a library can search songs by identifying information like length of song, genre, ect. it can provide a list of songs similar.
a music player can play a given song
a jukebox coordinates all of this by listening to the user interface and then taking actions in response and in the background.
*/

#include <map>
#include <queue>
#include <string>
#include <vector>

class Song
{
	public:
	  // set song metadata, dont read data in until play. song data is a string in the song_string_data, indicates location.
		Song(const std::vector<std::pair<std::string, std::string>>& string_song_data, const std::vector<std::pair<std::string, int>>& int_song_data
		     )
				{
					
				}
				
		void readSongRawData();
		std::vector<std::byte> get_song_raw_data();
		std::map<std::string, std::string> getSongStringData();
		std::map<std::string, int> getSongIntData();
	private:
	  std::map<std::string, std::string> song_string_data;
	  std::map<std::string, int> song_int_data;

		std::vector<std::byte> song_raw_data;
};

class Library
{
	public:
		void addSong(Song song);
		std::vector<Song> searchSongsByString(std::string search_str);
	
	private:
	  std::vector<Song> songs;
	
};

class MusicPlayer
{
	public:
	  // a song can be played, paused, or stopped. Only 1 song at a time. 
	  void addSongToQueue(Song song);
		void playNextSong();
		void pauseSong();
		void stopSong();
		bool isSongFinished();
		
	private:
	  Song current_song;
		std::queue<Song> songs_to_play_next;
};

class UserInterface
{
	public:
	  std::vector<Song> searchSongs(std::string);
		// increment paid amount
		void payForSongs(int paid_amt);
		// checks paid amt, if valid decrements and plays song, if not returns message asking to pay
		bool playSong(Song);
	  
	private:
	  int amount_paid = 0;
    int price_per_song = 50;
};

class Jukebox
{
	public:
	  Jukebox();
	  Jukebox* getJukeboxInstance()
		{
			if (jukebox_instance == nullptr)
			{
				jukebox_instance = new Jukebox();
			}
				return jukebox_instance;
		}
		
		~Jukebox()
		{
			if (!(jukebox_instance == nullptr))
			{
				delete jukebox_instance;
			}
		}
		

		
		void addLibrary(Library library);
		// check ui and see if any new tasks to do
		void listenUI();
		// do things like playing songs, adding to song queue, ect
		void processTasks();
	
	private:
	  Jukebox* jukebox_instance = nullptr;
		Library library;
	  MusicPlayer player;
		UserInterface ui;
	
};

/*
didnt clarify if took cds and such and had to store them, or was digital.
just assumed digital.
didnt ask enough initial questions, also got too bogged down in intricacies of how stuff got played and all.


*/

int main()
{}

