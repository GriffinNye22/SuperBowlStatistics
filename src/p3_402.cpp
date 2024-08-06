/**
 * @file p3_402.cpp
 * @author Griffin Nye
 * @brief Loads the SB dataset, and allows the user to print the dataset, 
				  reorder the dataset on various attributes, search various attributes
				  of entries for a contained letter, and search various attributes for a 
				  matching string.
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include "SBGame.h"
#include <string>
#include <utility>
#include <vector>



using namespace std;

//Functors
struct sortByNum {
	bool operator()(int num1, int num2) {
		return (num1 > num2);
	}//end operator()
};//end sortByNum

//Prototypes
void displayMVP(multimap<int, pair<string, vector<string>>, sortByNum>& mvp);
void displayRings(multimap<int, pair<string, vector<string>>, sortByNum>& rings);
vector<SBGame>::iterator findByAttribute(vector<SBGame>& dataset, char attr, 
																				 string searchterm, vector<SBGame>::iterator itr);
void loadDataset(vector<SBGame>& dataset);
void loadMenu(vector<SBGame>& dataset, 
							multimap<int, pair<string, vector<string>>, sortByNum>& rings,
							multimap<int, pair<string, vector<string>>, sortByNum>& mvp);
void populateMaps(vector<SBGame>& dataset,
                  multimap<int, pair<string, vector<string>>, sortByNum>& rings,
                  multimap<int, pair<string, vector<string>>, sortByNum>& mvp);
void populateMVPMap(vector<SBGame>& dataset, 
		     						multimap<int, pair<string, vector<string>>, sortByNum>& mvp);
void populateRingMap(vector<SBGame>& dataset,
										 multimap<int, pair<string, vector<string>>, sortByNum>& rings);
void printDataset(vector<SBGame>& dataset);
void reorder(vector<SBGame> & dataset, char sortType);
string retrieveSearchterm();
void search(vector<SBGame>& dataset);
void searchAttribute(string searchterm, char attr, vector<SBGame>& dataset);

/**main:
 * @brief Calls the functions in the proper order necessary to run the program
 * @return 0 - indicates success of the program
 */
int main() {
	vector<SBGame> dataset;
	multimap<int, pair<string, vector<string> >, sortByNum> rings;
	multimap<int, pair<string, vector<string> >, sortByNum> mvp;

	loadDataset(dataset);	
	populateMaps(dataset,rings, mvp);
	loadMenu(dataset, rings, mvp);
	return 0;
}//end main

void displayMVP(multimap<int, pair<string, vector<string>>, sortByNum>& mvp) {
	multimap<int, pair<string, vector<string>>, sortByNum>::iterator mapItr;
	vector<string>::iterator vecItr;
	int rank = 1; //Counter for Rank
	
	for (mapItr = mvp.begin(); mapItr != mvp.end(); mapItr++) {
		//Print "#) MVP Name"	
		cout << right << setw(2) << rank << ") "; //Print "#)"
		cout << left << setw(30) << mapItr->second.first;
		
		//Print " MVP Awards: # Super Bowls Awarded: "
		cout << " MVP Awards: " << mapItr->first << " Super Bowls Awarded: ";

		int elt = 0; //counter for element
		for (vecItr = mapItr->second.second.begin();
		     vecItr != mapItr->second.second.end(); vecItr++) {
		  
		  cout << *vecItr << " "; //Output Super Bowls delimited by a space;
		  elt++;; //increment element counter			
		}//end for	

		cout << endl; //Final Form: "#) MVP Name MVP Awards: # Super Bowls Awarded: romNum romNum romNum..."
		rank++; //increment rank counter		
	}//end for
}//end displayMVP

/**displayRings:
 * @brief Prints a list of Teams and their victories in descending order of rings
 * @param rings - the map of rings to teams and their victories
 */
void displayRings(multimap<int, pair<string, vector<string>>, sortByNum>& rings) {
	multimap<int, pair<string, vector<string>>, sortByNum>::iterator mapItr;
	vector<string>::iterator vecItr;
	int rank = 1; //Counter for Rank
	
	for (mapItr = rings.begin(); mapItr != rings.end(); mapItr++) {
		//Print "#) Team Name"
		cout << right << setw(2) << rank << ") "; //Print "#)"
 		cout << left << setw(30) << mapItr->second.first; 
		
		cout << " Rings: " << mapItr-> first << " Titles: ";      //Print " Rings: # Titles: "
		
		int elt = 0; //counter for element
		for (vecItr = mapItr->second.second.begin(); 
				 vecItr != mapItr->second.second.end(); vecItr++) {
					
			cout << *vecItr << " "; //Output titles delimited by a space
			elt++; //increment element counter
		}//end for
		
		cout << endl; //Final Form: "#) Team Name Rings: # Titles: romNum romNum romNum..."
		rank++; //increment rank counter
	}//end for
}//end displayRings

/**findByAttribute:
 * @brief Finds and returns an iterator to the next SBGame object whose 
 *        attribute (specified by attr) matches the searchterm.
 * @param dataset - the vector of SBGame objects
 * @param attr - the character selection for which attribute to search
 * @param searchterm - the searchterm
 * @param itr - iterator pointing to the beginning of search range
 * @return vector<SBGame>::iterator - iterator pointing to the next SBGame 
 *         object with matching attribute. dataset.end(), if none found.
 */
vector<SBGame>::iterator 
	findByAttribute(vector<SBGame>& dataset, char attr, string searchterm,
									vector<SBGame>::iterator itr) {
	switch(attr) {
			case 'A': //Super Bowl Number (default)
				return find(itr, dataset.end(), searchterm); 
			case 'B': //Winning Team
				return find_if(itr, dataset.end(), SBGame::searchByWinner(searchterm) );
			case 'C': //Losing Team
				return find_if(itr, dataset.end(), SBGame::searchByLoser(searchterm) );
			case 'D': //WinnerPts
				return find_if(itr, dataset.end(), SBGame::searchByWinnerPts(searchterm) );
			case 'E': //LoserPts
				return find_if(itr, dataset.end(), SBGame::searchByLoserPts(searchterm) );
			case 'F': //CombinedPts
				return find_if(itr, dataset.end(), SBGame::searchByCombinedPts(searchterm) );
			case 'G': //MVP
				return find_if(itr, dataset.end(), SBGame::searchByMVP(searchterm) );
			case 'H': //Stadium
				return find_if(itr, dataset.end(), SBGame::searchByStadium(searchterm) );
			case 'I': //City
				return find_if(itr, dataset.end(), SBGame::searchByCity(searchterm) );
			case 'J': //State
				return find_if(itr, dataset.end(), SBGame::searchByState(searchterm) );
		}//end switch
		
		
}//end findByAttribute

/**loadDataset:
 * @brief Populates the vector of SBGame objects with the Super Bowl dataset
 * @param dataset- the vector of SBGame objects
 */
void loadDataset(vector<SBGame>& dataset) {
	ifstream input;
	SBGame gameStats;
	
	input.open("superbowl.csv");
	
	while (input >> gameStats) {
		dataset.push_back(gameStats);
	}//end while
	
	input.close();

	sort(dataset.begin(), dataset.end());
}//end loadDataset

/**loadMenu:
 * @brief Displays a menu with various options to the user and processes selection
 * @param dataset- the vector of SBGame objects
 */
void loadMenu(vector<SBGame>& dataset, 
							multimap<int, pair<string, vector<string>>, sortByNum>& rings,
							multimap<int, pair<string, vector<string>>, sortByNum>& mvp) {
	
	char selection;
	char sortType = 'A';
	
	do {
		cout << "Menu: " << endl;
		cout << "P)rint the Dataset" << endl;
		cout << "S)earch the Dataset" << endl;
		cout << "V)iew Teams by Rings" << endl;
		cout << "L)ist of MVPs" << endl;
		cout << "R)eorder" << endl;
		cout << "Q)uit" << endl;
		cout << ">";
		
		selection = toupper( cin.get() );
		cin.get(); //Eat the carriage return
		
		switch(selection) {
			case 'P':
				printDataset(dataset);
				break;
			case 'S':
				search(dataset);
				break;
			case 'V':
				displayRings(rings);
				break;
			case 'L':
				displayMVP(mvp);
				break;
			case 'R':
				reorder(dataset, sortType);
				break;
			case 'Q':
				break;
			default:
				cout << "Invalid Option" << endl;
				cout << ">";
		}//end switch
		
	} while(selection != 'Q');
	
}//end loadMenu

/**populateMaps:
 * @brief Populates the rings map using members of the dataset
 * @param dataset- the vector of SBGame objects
 * @param rings- the rings map (maps number of rings to team and the games won)
 */
void populateMaps(vector<SBGame>& dataset,
                  multimap<int, pair<string, vector<string>>, sortByNum>& rings,
                  multimap<int, pair<string, vector<string>>, sortByNum>& mvp) {
	populateRingMap(dataset, rings);										
	populateMVPMap(dataset, mvp);
}//end populateMaps

/**populateMVPMap:
 * @brief Populates the MVP map
 * @param dataset - the vector of SBGame objects
 * @param mvp - the MVP map
 */
void populateMVPMap(vector<SBGame>& dataset, 
		     						multimap<int, pair<string, vector<string>>, sortByNum>& mvp) {
	map<string, vector<string>> tempMap;
	map<string, vector<string>>::iterator itr;
	string title;
	
	//Loop through each SBGame
	for (int i = 0; i < dataset.size(); i++) {
		itr = tempMap.find( dataset[i].getMVP() ); //Search the map for MVP name
		title = dataset[i].getTitle();
		
		if (itr != tempMap.end() ) { //Entry for MVP exists in the map
		
			//Insert Bowl Title into vector of games for which MVP was received
			itr->second.push_back(title);
			
		} else { //No entry for MVP exists in the map
			vector<string> tempVec;
			
			//Insert Bowl Title into a vector of games for which MVP was received
			tempVec.push_back(title);
			
			//Map vector of games for which MVP was received to MVP name
			tempMap.insert(make_pair(dataset[i].getMVP(), tempVec) );
			
		}//end if
	}//end for
	
	//tempMap now contains all MVPs mapped to a vector of the games for which they 
	//received the MVP award
	
	//Loop through the tempMap
	for (itr = tempMap.begin(); itr != tempMap.end(); itr++) {
		pair<string, vector<string> > tempPair;
		int i = itr->second.size(); //Get the number of MVP awards for each player
		
		//Create pair of player and their MVP Games
		tempPair = make_pair(itr->first, itr->second);
		
		//Map this pair to the number of MVP awards
		mvp.insert(make_pair(i,tempPair) );
	}//end for
}//end populateMVPMap

/**PopulateRingMap:
 * @brief Populates the Ring map
 * @param dataset - the vector of SBGame objects
 * @param rings - the Ring map
 */
void populateRingMap(vector<SBGame>& dataset,
										 multimap<int, pair<string, vector<string>>, sortByNum>& rings) {
	map<string, vector<string>> tempMap;
	map<string, vector<string>>::iterator itr;
	string title;
	
	//Loop through each SBGame
	for (int i = 0; i < dataset.size(); i++) {
		itr = tempMap.find( dataset[i].getWinner() );	//Search the map for Winning Team name
		title = dataset[i].getTitle();
		
		if( itr != tempMap.end() ){ //Entry for Team exists in the map
			
			//Insert Bowl Title into vector of won games
			itr->second.push_back(title); 
			
		} else { //No entry for Team exists in the map
			vector<string> tempVec;
			
			//Insert Bowl Title into a vector of won games
			tempVec.push_back(title);
			
			//Map Vector of won games to Team name
			tempMap.insert(make_pair(dataset[i].getWinner(), tempVec) );
					
		}//end if
	}//end for
	
	//tempMap now contains all teams mapped to a vector of their victories
	
	//Loop through the tempMap
	for (itr = tempMap.begin(); itr != tempMap.end(); itr++) {
		pair<string, vector<string> > tempPair;
		int i = itr->second.size(); //Get the number of rings for the teams
		
		//Create pair of Team and their victories
		tempPair = make_pair(itr->first, itr->second);
		
		//Map this pair to the number of rings
		rings.insert(make_pair(i,tempPair) );		
	}//end for
}//end populateRingMap

/**printDataset:
 * @brief Prints the contents of the vector of SBGame objects
 * @param dataset- the vector of SBGame objects
 */
void printDataset(vector<SBGame>& dataset) {
	vector<SBGame>::iterator itr; 
	
	for (itr = dataset.begin(); itr != dataset.end(); itr++) {
		cout << *itr << endl;
	}//end for
	
}//end printDataset

/**reorder:
 * @brief Reorders the contents of the vector of SBGame objects based on a 
 *        user-specified attribute
 * @param dataset- the vector of SBGame objects
 */
void reorder(vector<SBGame>& dataset, char sortType) {
	char selection;
	
	do {
		cout << "Choose an attribute to sort by:" << endl;
		cout << " A) Super Bowl Number" << endl;
		cout << " B) Winning Team" << endl;
		cout << " C) Losing Team" << endl;
		cout << " D) Points Scored by Winning Team" << endl;
		cout << " E) Points Scored by Losing Team" << endl;
		cout << " F) Total Points Scored by Both Teams" << endl;
		cout << " G) Name of MVP" << endl;
		cout << " H) Hosting Stadium" << endl;
		cout << " I) Hosting City" << endl;
		cout << " J) Hosting State" << endl;
		cout << "< P)revious Menu" << endl;
		cout << ">";
		
		selection = toupper(	cin.get() );
		cin.get(); //Eat the carriage return
		
		if (selection == sortType) {
			return;
		}//end if
		
		switch(selection) {
			case 'A': //Super Bowl Number (default)
				sort(dataset.begin(), dataset.end());
				break;
			case 'B': //Winning Team
				sort(dataset.begin(), dataset.end(), SBGame::sortByWinner() );
				break;
			case 'C': //Losing Team
				sort(dataset.begin(), dataset.end(), SBGame::sortByLoser() );
				break;
			case 'D': //WinnerPts
				sort(dataset.begin(), dataset.end(), SBGame::sortByWinnerPts() );
				break;
			case 'E': //LoserPts
				sort(dataset.begin(), dataset.end(), SBGame::sortByLoserPts() );
				break;
			case 'F': //CombinedPts
				sort(dataset.begin(), dataset.end(), SBGame::sortByTotalPts() );
				break;
			case 'G': //MVP
				sort(dataset.begin(), dataset.end(), SBGame::sortByMVP() );
				break;
			case 'H': //Stadium
				sort(dataset.begin(), dataset.end(), SBGame::sortByStadium() );
				break;
			case 'I': //City
				sort(dataset.begin(), dataset.end(), SBGame::sortByCity() );
				break;
			case 'J': //State
				sort(dataset.begin(), dataset.end(), SBGame::sortByState() );
				break;
			default:
				cout << "Invalid Option" << endl;
				cout << ">";
		}//end switch
		
		if (selection >= 'A' && selection <= 'J') {
			sortType = selection;
			return;
		}//end if
		
	} while (selection != 'P');
	
	return;
}//end reorder

/**retrieveSearchterm:
 * @brief Prompts the user for a searchterm and returns it
 * @return searchterm - the entered searchterm
 */
string retrieveSearchterm() {
	string searchterm;
	
	cout << "Enter string to search for: " << endl;
	cout << ">";
	
	getline(cin, searchterm);

	return searchterm;	
}//end RetrieveSearchterm

/**search:
 * @brief Displays a list of searchable attributes and prompts the user for
 *        selection. Calls the helper functions to perform the search.
 * @param dataset - the vector of SBGame objects
 */
void search(vector<SBGame>& dataset) {
	string searchterm;
	char selection;
	
	do {
		cout << "Choose an attribute to search:" << endl;
		cout << " A) Super Bowl Number" << endl;
		cout << " B) Winning Team" << endl;
		cout << " C) Losing Team" << endl;
		cout << " D) Points Scored by Winning Team" << endl;
		cout << " E) Points Scored by Losing Team" << endl;
		cout << " F) Total Points Scored by Both Teams" << endl;
		cout << " G) Name of MVP" << endl;
		cout << " H) Hosting Stadium" << endl;
		cout << " I) Hosting City" << endl;
		cout << " J) Hosting State" << endl;
		cout << "< P)revious Menu" << endl;
		cout << ">";
		
		selection = toupper(	cin.get() );
		cin.get(); //Eat the carriage return
		
		//Check for valid input
		if (selection >= 'A' && selection <= 'J') {
			searchterm = retrieveSearchterm();               //Get the searchterm
			searchAttribute(searchterm, selection, dataset); //Search for matches
			return;
		} else if (selection == 'P') {
			return;
		} else { //Invalid Input
			cout << "Invalid Option" << endl;
			cout << ">";
		}//end if
		
	} while (selection!= 'P');
}//end search

/**searchAttribute:
 * @brief Converts searchterm to uppercase and prints all iterator instances
 *        returned by findByAttribute
 * @param searchterm - the searchterm
 * @param attr - the character selection for which attribute to search
 * @param dataset - the vector of SBGame objects
 */
void searchAttribute(string searchterm, char attr, vector<SBGame>& dataset) {
	
	//Convert all alphabetical characters in searchterm to uppercase
	for (int i = 0; i < searchterm.length(); i++) {
		if (searchterm[i] >= 'a' && searchterm[i] <= 'z') {
			searchterm[i] = toupper(searchterm[i]);
		}//end if
	}//end for
	
	vector<SBGame>::iterator itr;
	
	//Retrieve iterator pointing to first element
	itr = findByAttribute(dataset, attr, searchterm, dataset.begin() );

	//Return error message if nothing found
	if (itr == dataset.end() ) {
		cout << "No attribute found matching '" << searchterm << "'." << endl;
		return;
	} else { 
	  cout << "Matching Records:" << endl;
		
		//Loop through dataset until no more matching terms found
		while(itr != dataset.end() ) {
		  cout << *itr << endl; //Print the matching term
		  itr = findByAttribute(dataset, attr, searchterm, itr+1); //Find next match
		}//end while		
	
	}//end if
	
}//end searchAttribute
