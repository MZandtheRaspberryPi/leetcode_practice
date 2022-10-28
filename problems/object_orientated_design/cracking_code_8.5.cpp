// design the datastructures for an online book reader system

/* handle ambiguities 

who -- seniors, easy ui and simplified features, or techies with lots of feature needs
what -- is this a for profit thing wtih a store or non profit platform like a library?
where -- is this online only, no offline features?
when -- this is for individaul people to consume, not robots using apis?
why -- for fun or for school?
how -- via laptop, tablet, web browser?

will assume it is a non-profit library like tool that only supports viewing in web browser targeted to general public.

core objects
books
user library
user
library manager

relationships
a library manager can have multiple users 
a user can have a library
a user library has multiple books

actions
a library manager can give books to Users
a user can request books from the library manager. they can also read books in their user library. they can also search books in the library manager.
a book can be read
a user library can expire books based on their expiry date, as well as add books and search for books

singleton model for user library
*/


#include <deque>
#include <vector>
#include <string>

struct BookMetadata
{
	std::string author;
	std::string title;
	int publishDate;
	
};

class Book
{
	public:
	  Book(BookMetadata metadata) : metadata(metadata)
		{
		
		}
		
		std::string read();
		BookMetadata getMetadata();
	
	
	private:
	  BookMetadata metadata;
};

struct BookLoan
{
	Book* book;
	int expiry_date;

};

class UserLibrary
{
	public:
		UserLibrary();
		// adds a book to the queue, FIFO style
		void takeBookLoan(BookLoan loan);
		// checks the front of the queue and if expired pops
		void expireFinishedLoans();
		std::vector<BookMetadata> searchBooks(std::string);
		std::string read_book(Book book);
	
	private:
	  int user_id;
		std::deque<BookLoan> loans;
};

class User
{
	public:
	  User(int user_id);
		// gets singleton instance of lib manager and requests book to see if available and borrows if so
		bool requestBook(BookMetadata metadata);
		// search through available books
		std::vector<BookMetadata> searchAvailableBooks(std::string search_str);
		void expireFinishedLoans();
		void setUserLibrary(UserLibrary user_library);
	private:
	  int user_id;
		UserLibrary user_library;
		
};

class LibraryManager
{
	public:
	  static LibraryManager& getInstance()
    {
			static LibraryManager instance;
			return instance;
		}
		
		
		LibraryManager(LibraryManager const&) = delete;
		void operator=(LibraryManager const&) = delete;
		
		void addUser(User user);
		void removeUser(User user);
		bool isBookAvailable(BookMetadata metadata);
		BookLoan grantBookLoan(BookMetadata metadata);
	
	private:
	  LibraryManager() {}
		std::vector<User> users;
};

/*

singleton wasnt needed here. didnt make a display, but if online system we probably need one.
they stored data as hash table with id and book, constant lookup, and made simplifying assumption
like only one user and one book active at a time

also their model all fit together cleary, getters/setters/ all was pretty well thought out.

also before adding a book they checked if it was there, and only added it if not

their api was consistent, for example they used a user.getId method that they implmeented.




*/


int main()
{
	
}














