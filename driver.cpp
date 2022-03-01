#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "XMLParse2.h"

int main(int argc, char const *argv[]){

	// std::string name;
	std::string filename;
	char choice;
	std::vector<KRNHAN003::TagStruct> l;
	std::vector<std::string> d;

	for(;;){
		std::cout << "Please select a command." << std::endl;
		std::cout << "1. 'r' - Read and parse a specified input file" << std::endl;
		std::cout << "2. 'p' - Print all tags" << std::endl;
		std::cout << "3. 'd' - Write tags and data to a file called \"tag.txt\"" << std::endl;
		std::cout << "4. 'l' - Print tag data for given tag" << std::endl;
		std::cout << "5. 'q' - Quit" << std::endl;
		std::cout << std::endl;
		std::cin >> choice;		
		if(choice == 'q'){
			break;
		}

		if(choice == 'r'){
			std::cout << std::endl;
			std::cout << "Please input file name:" << std::endl;
			std::cin >> filename;
			d = KRNHAN003::readFile(filename);
			if(d[0] == "Failed"){
					continue;
			}
			l = KRNHAN003::parse(d);
			continue;
		}

		if(choice == 'l'){
			if(filename.empty()){
				std::cout << "Please input file name:" << std::endl;
				std::cin >> filename;
				d = KRNHAN003::readFile(filename);
				if(d[0] == "Failed"){
					continue;
				}
				l = KRNHAN003::parse(d);
			}

			std::string tag;
			std::cout << std::endl;
			std::cout << "Please input tag name:" << std::endl;
			std::cin >> tag;
			for(int i = 0; i<l.size(); i++){
				if(!tag.compare(l[i].ID)){
					std::cout << "Tag data: " << l[i].text;
					break;
				}
				if(i == (l.size()-1)){
					std::cout << "Tag not found.";
				}
			}
 			std::cout << std::endl;
 			continue;
		}

		if(choice == 'p'){
			for(int i = 0; i<l.size(); i++){
				std::cout << "\"" << l[i].ID << "\"," << l[i].numTags<< ",\"" << l[i].text << "\""  << std::endl;
			}
			std::cout << std::endl;
			continue;
		}

		if(choice == 'd'){
			std::ofstream file;
			file.open ("tag.txt");
			for(int i = 0; i<l.size(); i++){
				file << "\"" << l[i].ID << "\"," << l[i].numTags<< ",\"" << l[i].text << "\""  << std::endl;
			}
			file.close();
			continue;
		}
	}
	return 0;
}