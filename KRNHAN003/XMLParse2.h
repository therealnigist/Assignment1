#ifndef XMLPARSE2_H
#define XMLPARSE2_H

#include <string>
#include <vector>

namespace KRNHAN003
{
	std::vector<std::string> readFile(std::string f); //method to read in text file & store lines in a vectorstream
	struct TagStruct{
		std::string ID;
		int numTags = 0; // number of tag pairs found in given file
		std::string text;
	};
	std::vector<TagStruct> parse(std::vector<std::string> d);
	// { // DS to store tag name, text and number of occurences
	// 	std::string ID;
	// 	std::string text;
	// 	int numTags;
	// }; 
	//std::vector<TagStruct> TagList; // List of all the TagStruct objects
}
#endif