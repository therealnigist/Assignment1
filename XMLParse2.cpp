#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include "XMLParse2.h"

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
      				if( endTag == stack.top().ID){
			       		status = "nottag";
			       		if(tagList.size() == 0){ // checks to see if taglist is empty bc if not, need to loop through all tags
                            stack.top().numTags++;
                            //stack.top().text = tagText;
			       			tagList.push_back(stack.top());
                            stack.pop();
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
			       					tagList[j].text += stack.top().text;
                                    stack.pop();
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
								stack.top().numTags++;
		       					tagList.push_back(stack.top());
                                stack.pop();
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
					if(tagText != ""){
                        stack.top().text = tagText;
                    }	
					stack.push(TagStruct {.ID = tagName });
                    tagName = "";
                    tempText = "";	
					//maybe pusback tag here
			        continue;
		      	}

		      	if((c == '/') && (status == "tag")){
			        tempText = "";
			        status = "endtag";
			        continue;
		        }

		      	if ((c == '<') && (status == "nottag")){
					tagText += tempText; //adds the current temp text to tag text incase
                    if(!stack.empty()){
                        stack.top().text += tagText; //adds tag text to the tag at top of stack
                    }
					tempText += "<";
                    tagText = "";
			        status = "tag";
			        continue;
		      	}

				if ((c == '>') && (status == "nottag")){
			        tempText += ">";
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




