#include <sys/stat.h>
#include <iostream>
#include <string>
#include <sstream>
#include <dirent.h>
#include <vector>
#include <limits.h>
#include <unistd.h>
using namespace std;
//adds leading zeros for numbers that are less than 3 digits
string ZeroPadNumber(int num){
	stringstream ss;
	// the number is converted to string with the help of stringstream
	ss << num;
	string ret;
	ss >> ret;
	// Append zero chars
	int str_length = ret.length();
	for (int i = 0; i < 3 - str_length; i++)
		ret = "0" + ret;
	return ret;
}
string getexepath(){
  char result[ PATH_MAX ];
  ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
  return std::string( result, (count > 0) ? count : 0 );
}
int main() {
    cout<<"Getting latest build... "<<endl;
    //global varaible intialization for finding latest build
    int maxBuild=0;
	string s= getexepath();
	string path = s.substr(0,s.length()-9);
	const char* PATH = path.c_str();
	cout<<PATH<<endl;
    //gets list of variables
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(PATH)) != NULL) {
      /* print all the files and directories within directory */
      while ((ent = readdir (dir)) != NULL) {
          string directoryNames = ent->d_name;
          if(directoryNames.substr(0,5)=="build"){
              string s = directoryNames.substr(6,directoryNames.length()-6);
              int num=0;
              stringstream test(s);
              test >> num;
              if(num>maxBuild){
                  maxBuild=num;
              }
          }
       }
    closedir (dir);
    } else {
        /* could not open directory */
        perror ("");
        return EXIT_FAILURE;
    }
    auto maxBuildString = ZeroPadNumber(++maxBuild);
    string nameDirectory = "build" + maxBuildString;
    cout<<"Making latest build... "<<endl;
    string command = "cd " + nameDirectory +" && cmake .. && make && echo Done! && ./stereo";
    const char *makeDirectory = nameDirectory.c_str();
    const char *makeBuild = command.c_str();
    const int dir_err = mkdir(makeDirectory, S_IRWXU);
    if (-1 == dir_err){
        printf("Error creating directory!\n");
        return 1;
    }
    system(makeBuild);
    return 0;
}
