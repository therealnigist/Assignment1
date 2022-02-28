#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include "XMLParse.h"

namespace KRNHAN003{

	std::vector<std::string> readFile(std::string f){ // function to read text file
		std::vector<std::string> data; // vector to hold file lines
		std::ifstream in(f);
		if(!in){
			std::cout << "Couldn't open file " << f << std::endl;
			data.push_back("Failed");
			return data;
		}
		std::string line; // temp line variable for adding lines to vector
		while(std::getline(in, line)){
			data.push_back(line); // adds line to vector to create list of lines
		}
		in.close();
		return data;
	};

	std::vector<TagStruct> parse(std::vector<std::string> d){
		std::vector<TagStruct> tagList;
		std::string status = "nottag"; // status to show where in the tagging process we are - starts off at nottag
	  	std::string endTag = "";
	  	std::string tagName = "";
	  	std::string tagText = "";
	  	std::string tempText = "";
	  	int tagNum = 0;
		std::stack<TagStruct> stack; // created a stack for mastery
		for(int i = 0; i< d.size(); i++){ // loops through every line in the vector
    		for(char& c : d[i]) { // loops through each character in line

      			if ((c == '>') && (status == "endtag")){
      				if( endTag == tagName){
			       		status = "nottag";
			       		if(tagList.size() == 0){ // checks to see if taglist is empty bc if not, need to loop through all tags
			       			TagStruct firstTag;
			       			firstTag.ID = tagName;
			       			firstTag.text = tagText;
			       			firstTag.numTags = 1; // change to numtags ++ instead
			       			tagList.push_back(firstTag);
				    		tagName = "";
            				endTag = "";
							tagText = "";
 							tempText = "";
			       			continue;
			       		}
			       		else{
			       			bool repeat = false; //shows that a tag has been repeated
			       			for(int j = 0; j < tagList.size(); j++){ // goes through taglist
			       				if(tagList[j].ID == tagName){
			       					repeat = true;
			       					tagList[j].numTags++;
			       					tagList[j].text += ":";
			       					tagList[j].text += tagText;
									// resets the variables
								    tagName = "";
		            				endTag = "";
									tagText = "";
		 							tempText = "";
									break;
									 //should I break here??
		 						}
			       			}

			       			if(!repeat){			  // if tag doesn't match any existing tags in list, create a new one      					
								TagStruct newTag;
		       					newTag.ID = tagName;
		       					newTag.text = tagText;
		       					newTag.numTags = 1;
		       					tagList.push_back(newTag);
					            tagName = "";
					            endTag = "";
								tagText = "";
					 			tempText = "";
	       					}
			       			continue;	
			       		}

			            //std::cout << "Tag Name: " << tagName << std::endl;
			            //std::cout << "Tag Text: " << tagText << std::endl;
			            tagName = "";
			            endTag = "";
						tagText = "";
			 			tempText = "";
       				}
      			}
      
		    	if ((c == '>') && (status == "tag")){
			        status = "nottag";
			        tempText = "";
			        continue;
		      	}

		      	if((c == '/') && (status == "tag")){
			        tempText = "";
			        status = "endtag";
			        continue;
		        }

		      	if ((c == '<') && (status == "nottag")){
			        tempText += "<";
			        status = "tag";
			        continue;
		      	}
		      
		      	if((status == "endtag") && (c!= '>')){
			        endTag += c;
			        continue;
		      	}
		      
		      	if((c == ' ') && (status == "tag")){
        			status = "nottag";
			        tempText += " ";
			        tagText += tempText;
			        tempText = "";
			        continue;
			      }
		      
		      	if((c!= '>') && (status == "tag")){ // all other characters when tag
		        	tagName += c;
		      	}
		      
		      	if ((c!= '>') && (status == "nottag")){ // all other characters when nottag
		        	tagText += c;
		      	}
    		} 
		}	
	return tagList;	  	
	};
}




