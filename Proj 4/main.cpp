/*main.cpp*/

//
// myDB project using AVL trees
//
// <<YOUR NAME>>
// U. of Illinois, Chicago
// CS 251: Fall 2019
// Project #04
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cassert>
#include <algorithm>


#include "avl.h"
#include "util.h"

using namespace std;


//
// tokenize
//
// Given a string, breaks the string into individual tokens (words) based
// on spaces between the tokens.  Returns the tokens back in a vector.
//
// Example: "select * from students" would be tokenized into a vector
// containing 4 strings:  "select", "*", "from", "students".
//
vector<string> tokenize(string line)
{
  vector<string> tokens;
  stringstream  stream(line);
  string token;

  while (getline(stream, token, ' '))
  {
    tokens.push_back(token);
  }

  return tokens;
}

int metaRead(string metaFilename, vector<string> &columnIndex, vector<string> &columnName)
{
  string   filename = metaFilename + ".meta";
  ifstream meta(filename, ios::in | ios::binary);
	
  string   value;
  int RSsize;
  int num_columns;
	
  if (!meta.good())
  {
    cout << "**Error: unable to open file '" << filename << "', exiting" << endl;
    return -1;
  }

  meta.seekg(0, meta.beg);  
  	
  //Read in record size and the number of columns
  meta >> RSsize;  
  meta >> num_columns;
  

  meta >> value;
	
  //Read data until the end of the file
  while (!meta.eof())
  {
	  if(value == "0" ||
		 value == "1"){
		  columnIndex.push_back(value);
	  }
	  else{
		  columnName.push_back(value);
	  }
	  
	  
	  meta >>value;
  } 

	return RSsize;
}

void BuildIndexTree(string tablename, streamoff RSsize, int num_columns, avltree<string, streamoff> &IndexTree, int colIndex)
{	
  string   filename = tablename + ".data";
  ifstream data(filename, ios::in | ios::binary);

  if (!data.good())
  {
    cout << "**Error: couldn't open data file '" << filename << "'." << endl;
    return;
  }

  //
  // Okay, read file record by record, and output each record of values:
  //
  data.seekg(0, data.end);  // move to the end to get length of file:
  streamoff length = data.tellg();

  streamoff pos = 0;  // first record at offset 0:
  string value;
  
  while(pos < length){
	  data.seekg(pos, data.beg);  // move to start of record:
	  
	  vector<string> GRVector;
	  GRVector = GetRecord(tablename, pos, num_columns);
	  IndexTree.insert(GRVector[colIndex], pos);
	  pos += RSsize; 
  }
}

// Return index of key in vector
// int ReturnIndex(vector<string> ColumnName, string key){
// 	for(unsigned int i = 0; i < ColumnName.size(); i++){
// 		if(ColumnName[i] == key){
// 			return i;
// 		}
// 	}
// }

int main()
{
  string tablename; // = "students";
  vector<string> columnName;
  vector<string> columnIndex;
  vector<avltree<string, streamoff>> indexTrees;
  int recordsize;
  
  cout << "Welcome to myDB, please enter tablename> ";
  getline(cin, tablename);

  cout << "Reading meta-data..." << endl;
  recordsize = metaRead(tablename, columnIndex, columnName);
	
  cout << "Building index tree(s)..." << endl; 
	
  int num_columns = columnName.size();
	
  //BUILDING INDEX TREES
  for(unsigned int colIndex = 0; colIndex < columnName.size(); colIndex++){
	  avltree<string, streamoff> tree;
	  //If it is indexed, build an index tree, if it is 0, build an empty tree
	  if(columnIndex[colIndex] == "1"){
		  BuildIndexTree(tablename, recordsize, num_columns, tree, colIndex);
		  indexTrees.push_back(tree);
		  cout << "Index column: " << columnName[colIndex] << endl; 
		  cout << "  Tree size: " << indexTrees[colIndex].size() << endl;
		  cout << "  Tree height: " << indexTrees[colIndex].height() << endl;
	  }
	  else{
		  indexTrees.push_back(tree);
	  }
  }
  // Main loop to input and execute queries from the user:
  string query;
  
  cout << endl;
  cout << "Enter query> ";
  getline(cin, query);

  while (query != "exit")
  {
    vector<string> tokens = tokenize(query);
    
    //check if tokens[0] is not "select" and "exit"
	if(tokens[0] != "select" &&
	   tokens[0] != "exit"){
		cout << "Unknown query, ignored..." << endl;
	}
	//check if tokens[0] is "select" and tokens[1] is not "*" and tokens[1] is not a valid column name
	else if(tokens[0] == "select" &&
		    tokens[1] != "*" &&
		    (std::find(columnName.begin(), columnName.end(), tokens[1]) == columnName.end())){
		cout << "Invalid select column, ignored..." << endl;
	}
	//check if tokens[2] is not "from"
	else if(tokens[2] != "from"){
		cout << "Invalid select query, ignored..." << endl;
	}
	//check if the table name is not tokens[3]
	else if(tablename != tokens[3]){
		cout << "Invalid table name, ignored..." << endl;
	}
	//check if tokens[4] is not "where"
	else if(tokens[4] != "where"){
		cout << "Invalid query, ignored..." << endl;
	}
	//check if tokens[5] is not a valid column name
	else if((std::find(columnName.begin(), columnName.end(), tokens[5]) == columnName.end())){
		cout << "Invalid where column, ignored..." << endl;
	}
	//check if tokens[6] is not "="
	else if(tokens[6] != "="){
		cout << "Unknown query" << endl;
	}
	//check if tokens.size() is not 8
	else if(tokens.size() != 8){
		cout << "Unknown query" << endl;
	}
	else {	
// 		vector<streamoff> LRVector = LinearSearch(tablename, recordsize, num_columns, tokens[7], MatchColumnIndex + 1);
// 		if(LRVector.size() == 0){
// 			cout << "Not found..." << endl;			
// 		}
		// if user wants all info
// 		if(tokens[1] == "*"){
// 			int ColumnNameIndex = 0;		
// 			for(int i = 0; i < num_columns; i++){
// 				ColumnNameIndex = ReturnIndex(columnName, columnName[i]);	
// 				if(columnIndex[ColumnNameIndex] == 1){
// 					cout << indexTrees[ColumnNameIndex].search() << endl;
// 				}
// 		}
			
// 			cout << "first" << endl;
// 			streamoff* returnVal = indexTrees[0].search("456789");
// 		    cout << "second" << endl;
// 			cout << returnVal;
			vector<string> UINtree = indexTrees[0].inorder_keys();

// 			vector<string> UINvect = GetRecord(tablename, 0, num_columns);
				for(int h = 0; h < UINtree.size(); h++){
				cout << "this is element " << h << " " << UINtree[h] << endl;
			}
	    }
		
	
// 	else{
// 		int MatchColumnIndex = ReturnIndex(columnName, tokens[5]);
// 		vector<streamoff> LRVector = LinearSearch(tablename, recordsize, num_columns, tokens[7], MatchColumnIndex + 1);
		
// 		// If input data is not in the data file
// 		if(LRVector.size() == 0){
// 			cout << "Not found..." << endl;
			
// 		}
// 		// if user wants all info
// 		else if(tokens[1] == "*"){
// 			for(int i = 0; i < LRVector.size(); i++){
// 				streamoff LRStreamoff = LRVector[i];
// 				vector<string> GRFinalVector = GetRecord(tablename, LRStreamoff, num_columns);

// 				for(int i = 0; i < columnName.size(); i++){
// 					cout << columnName[i] << ": " << GRFinalVector[i] << endl;
// 				}
// 			}
// 	    }
// 	    else{
// 			// if user wants only one piece of info
// 			for(int i = 0; i < LRVector.size(); i++){
// 				streamoff LRStreamoff = LRVector[i];
// 				vector<string> GRFinalVector = GetRecord(tablename, LRStreamoff, num_columns);

// 				int TokenTwoIndex = ReturnIndex(columnName, tokens[1]);
// 				cout << columnName[TokenTwoIndex] << ": " << GRFinalVector[TokenTwoIndex] << endl;
// 			}
// 		}
// 	}
	  
    cout << endl;
    cout << "Enter query> ";
    getline(cin, query);
  }

  //
  // done:
  //
  return 0;
}
