/*
explain the datastructures and algorithms you would use to design an in memory filesystem.
illustrate with code where possible.

core objects
file
directory
filesystem

relationships
a directory can have 0 or more files in it. it also has a parent directory. and 0 or more child directories.
a filesystem has 0 or more child directories

actions
a filesystem can create, delete, or modify files
a filesystem can create a directory, move a directory, or delete a directory

directories double linked lists of parent/child? then to delete we simply make parent's child nullptr.

do we support complex file types, or just text files for now?


feedback: could have done a base class like entry, then subclass for directory and forfile. this could have a lot
of the metadata, as well as ways to get full paths and other stuff there already.

*/

#include <map>
#include <queue>
#include <string>


class File
{
	public:
		File(std::string file_contents)
		{
			contents_ = file_contents;
		}
		
		std::string getContents()
		{
			return contents_;
		}
		
		void setContents(std::string contents)
		{
			contents_ = contents;
		}
	private:
	  std::string contents_;
};

class Directory
{
	public:
	  Directory(Directory* parent, std::string name)
		{
			parent_ = parent;
			name_ = name;
		}
		
		bool addSubDirectory(Directory* sub_dir)
		{
			if (children_dirs_.find(sub_dir->getName()) == children_dirs_.end())
			{
				children_dirs_[sub_dir->getName()] = sub_dir;
				return true;
			}
			else
			{
				return false;
			}
		}
		
		bool removeSubDirectory(Directory* sub_dir)
		{
			if (children_dirs_.find(sub_dir->getName()) != children_dirs_.end())
			{
				children_dirs_.erase(sub_dir->getName());
				return true;
			}
			else
			{
				return false;
			}
		}
		
		bool addFile(File* file);
		bool removeFile(File* file);
		std::map<std::string, Directory*>  getChildrenDirs();
		std::string getName();
		
		
		
	private:
	  Directory* parent_;
		std::map<std::string, Directory*> children_dirs_;
		std::map<std::string, File*> children_files_;
		std::string name_;
};

class Filesystem
{
	public:
	  Filesystem()
		{
			root_ = new Directory(nullptr, "root");
		};
		
		~Filesystem()
		{
			std::queue<Directory *> dirs;
			dirs.push(root_);
			
			while (!dirs.empty())
			{
				Directory* dir = dirs.front();
				dirs.pop();
				
				std::map<std::string, Directory*>::iterator it;
				std::map<std::string, Directory*> children_dirs = dir->getChildrenDirs();
				for (it = children_dirs.begin(); it!= children_dirs.end(); it++)
				{
					dirs.push(it->second);
				}
				delete dir;
			}
			
		}
		
		// traces root down to end, then adds
		bool addDirectory(std::vector<std::string> dir_keys);
	  
		
	private:
	  Directory* root_;
	
	
};

int main()
{
	
	
}

