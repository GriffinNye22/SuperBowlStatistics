/**
 * @file SBgame.cpp
 * @author Griffin Nye
 * @brief Implementation of the SBgame class
 */
 
#include "Date.h"
#include "SBGame.h"
#include <string>

using namespace std;
 
/**SBGame()
 * @brief Constructs a new SBGame object with default values
 */ 
SBGame::SBGame() {
 gameDate.setDate(0,0,0);
 SBTitle = "";
 Winner = "";
 Loser = "";
 MVP = "";
 Stadium = "";
 City = "";
 State = "";
 SBNum = 0;
 WinnerPts = 0;
 LoserPts = 0;
 CombinedPts = 0;
}//end Constructor

/**getDate:
 * @brief Retrieves the gameDate member of SBGame
 * @return gameDate- Member instance of the Date object
 */ 
Date SBGame::getDate() {
 return gameDate;
}//end getDate

/**getTitle:
 * @brief Retrieves the SBTitle member of SBGame
 * @return SBTitle- the title of the SBGame
 */ 
string SBGame::getTitle() {
 return SBTitle;
}//end getTitle

/**getWinner:
 * @brief Retrieves the Winner member of SBGame
 * @return Winner- the winner of the SBGame
 */ 
string SBGame::getWinner() {
 return Winner;
}//end getWinner

/**getLoser:
 * @brief Retrieves the Loser member of SBGame
 * @return Loser- the loser of the SBGame
 */ 
string SBGame::getLoser() {
 return Loser;
}//end getLoser

/**getMVP:
 * @brief Retrieves the MVP member of SBGame
 * @return MVP- the MVP of the SBGame
 */ 
string SBGame::getMVP() {
 return MVP;
}//end getMVP

/**getStadium:
 * @brief Retrieves the Stadium member of SBGame
 * @return Stadium- the stadium hosting the SBGame
 */ 
string SBGame::getStadium() {
 return Stadium;
}//end getStadium

/**getCity:
 * @brief Retrieves the City member of SBGame
 * @return SBTitle- the city hosting the SBGame
 */ 
string SBGame::getCity() {
 return City;
}//end getCity

/**getState:
 * @brief Retrieves the State member of SBGame
 * @return SBTitle- the state hosting the SBGame
 */ 
string SBGame::getState() {
 return State;
}//end getState

/**getSBNum:
 * @brief Retrieves the SBNum member of SBGame
 * @return SBNum- the number of the SBGame in Arabic form
 */ 
int SBGame::getSBNum() {
  return SBNum;
}//end getSBNum

/**getWinnerPts:
 * @brief Retrieves the WinnerPts member of SBGame
 * @return WinnerPts- the number of points scored by the winner of SBGame
 */ 
int SBGame::getWinnerPts() {
  return WinnerPts;
}//end getWinnerPts

/**getLoserPts:
 * @brief Retrieves the LoserPts member of SBGame
 * @return LoserPts- the number of points scored by the loser of SBGame
 */ 
int SBGame::getLoserPts() {
  return LoserPts;
}//end getWinnerPts

/**getCombinedPts:
 * @brief Retrieves the CombinedPts member of SBGame
 * @return CombinedPts- the number of points scored by both teams of SBGame
 */ 
int SBGame::getCombinedPts() {
  return CombinedPts;
}//end getWinnerPts

/**operator<(const SBGame&):
 * @brief Compares an SBGame to this SBGame by their SBNum members
 * @param sb- the SBGame object being compared to this SBGame
 * @return SBNum < sb.SBNum - boolean evaluation of the comparison
 */
bool SBGame::operator<(const SBGame& sb) const {
  return (SBNum < sb.SBNum);
}//end operator<(const SBGame&)

/**operator<(const string&):
 * @brief Compares a string to this SBGame by comparing it to the SBNum
 * @param s- the string being compared to this SBGame
 * @return SBNum < stoi(s) - boolean evaluation of the comparison
 */
bool SBGame::operator<(const string& s) const {
  return (SBNum < stoi(s));
}//end operator<(const string&)

/**operator<(const SBGame&):
 * @brief Compares an SBGame to this SBGame by their SBNum members
 * @param sb- the SBGame object being compared to this SBGame
 * @return SBNum == sb.SBNum - boolean evaluation of the comparison
 */
bool SBGame::operator==(SBGame sb) {
  return (SBNum == sb.SBNum);
}//end operator==(SBGame)

/**operator==(string s):
 * @brief Compares an SBGame to a string by the SBNum member
 * @param s - the string being compared to this SBGame
 * @return SBNum == stoi(s) - boolean evaluation of the comparison
 */
bool SBGame::operator==(string s) {
  return (SBNum == stoi(s) );
}//end operator==(string)

/**operator>(string s):
 * @brief Compares an SBGame to a string by the SBNum member
 * @param s - the string being compared to this SBGame
 * @return SBNum > stoi(s) - boolean evaluation of the comparison
 */
bool SBGame::operator>(string s) {
  return ( SBNum > stoi(s) );
}//end operator>(string)

/**getNextField:
 * @brief Retrieves field before delimiter and removes field from source
 * @param line - the source string
 * @param delimiter - the delimiter character
 * @return temp - the field removed from the source string
 */
string getNextField(string& line, char delimiter) {
  int pos;     //Position variable for marking delimiters
  string temp; //Holds the contents of a field from file
  
  pos = int( line.find(delimiter) ); //Find next comma in line  
  temp = line.substr(0, pos);      //Store field in temp
  line.erase(0, pos+1);              //Erase field from line
  
  return temp;
}//end getNextFieldc

/**toUpper:
 * @brief Converts all alphabetical characters in a string to uppercase
 * @param str - the string to convert to uppercase
 */
void toUpper(string& str) {
  //Convert all alphabetical characters to uppercase
  for (int i = 0; i < str.length(); i++) {
    if (str[i] >= 'a' && str[i] <= 'z') {
			str[i] = toupper(str[i]);
		}//end if 
  }//end for
  
}//end toUpper

/**operator>>:
 * @brief Overloads the stream insertion operator for easier population
 * @param src - the input stream
 * @param sb - the SBGame object
 * @return src - the input stream
 */
istream &operator>>(istream& src, SBGame& sb) {
  int month, day, year; //Variables for month, day, year
  
  string line;          //Holds the contents of each line
  string temp;          //Holds the contents of a field from file
  
  getline(src, line);   //Read the line and store in line
  
  if (line.length() != 0) {
    //Remove '\357', '\273', and '\277' character
    if (line.at(0) < 0) {
      line = line.substr(3, line.length() - 3);
    }//end if
    
    temp = getNextField(line,',');          //Retrieve the date field; store in temp
    
    month = stoi( getNextField(temp,'/') ); //Retrieve the month field from temp; store in month
    day = stoi( getNextField(temp, '/') );  //Retrieve the day field from temp; store in day
    year = stoi(temp);                      //Retrieve the year field and store it in year
    
    sb.gameDate.setDate(month,day,year);    //Set the gameDate member
    
    temp = getNextField(line,',');          //Retrieve the title field; store in temp
    toUpper(temp);                          //Convert temp to uppercase
    sb.SBTitle =  temp;                     //Set the SBTitle member
    
    temp = getNextField(line,',');          //Retrieve the number field; store in temp
    sb.SBNum = stoi(temp);                  //Set the SBNum member
    
    temp = getNextField(line,',');          //Retrieve the winner field; store in temp
    toUpper(temp);                          //Convert temp to uppercase
    sb.Winner = temp;                       //Set the Winner member
    
    temp = getNextField(line,',');          //Retrieve the winnerPts field; store in temp
    sb.WinnerPts = stoi(temp);              //Set the WinnerPts member
     
    temp = getNextField(line,',');          //Retrieve the loser field; store in temp
    toUpper(temp);                          //Convert temp to uppercase
    sb.Loser = temp;                        //Set the Loser member

    temp = getNextField(line,',');          //Retrieve the loserPts field; store in temp
    sb.LoserPts = stoi(temp);               //Set the LoserPts member
    
    sb.CombinedPts = sb.WinnerPts +
                     sb.LoserPts;           //Set the CombinedPts member
                      
                     
    temp = getNextField(line,',');          //Retrieve the MVP field; store in temp
    toUpper(temp);                          //Convert temp to uppercase
    sb.MVP = temp;                          //Set the MVP member

    temp = getNextField(line,',');          //Retrieve the Stadium field; store in temp
    toUpper(temp);                          //Convert temp to uppercase
    sb.Stadium = temp;                      //Set the Stadium member
    
    temp = getNextField(line,',');          //Retrieve the City field; store in temp
    toUpper(temp);                          //Convert temp to uppercase
    sb.City = temp;                         //Set the City member
    
    temp = line.substr(0,line.length() - 1);//Retrieve the State field (removing '\r'); store in temp
    toUpper(temp);                          //Convert temp to uppercase
    sb.State = temp;                        //Set the State member 
  }//end if
  
  return src;
}//end operator>>

/**operator<<:
 * @brief Overloads the stream extraction operator for easier output
 * @param dest - the output stream
 * @param sb - the SBGame object
 * @return dest - the output stream
 */
ostream &operator<<(ostream& dest, const SBGame& sb) {
  dest << endl;
  dest << left << setw(40) << "SUPER BOWL " + sb.SBTitle;
  dest << setw(24) << right << "Date: " << sb.gameDate << endl;
  dest << right << setw(9) << "Winner: " << left << setw(30) << sb.Winner;
  dest << right << setw(32) << "Winner Pts: " << left << setw(2) << sb.WinnerPts << endl;
  dest << right << setw(9) << "Loser: " << left << setw(30) << sb.Loser;
  dest << right << setw(32) << "Loser Pts: " << left << setw(2) << sb.LoserPts << endl;
  dest << right << setw(9) << "MVP: " << left << setw(30) << sb.MVP;
  dest << right << setw(32) << "Combined Pts: " << left << setw(2) << sb.CombinedPts << endl;
  dest << "Stadium: " << left << setw(30) << sb.Stadium;
  dest << left << setw(7) << "City : " << setw(18) << sb.City;
  dest << left << setw(7) << "State: " << left << setw(10) << sb.State << endl;
  
  return dest;
}//end operator<<

