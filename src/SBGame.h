/**
 * @file SBgame.h
 * @author Griffin Nye
 * @brief Declaration of the SBgame class
 */
 
#ifndef H_SBGame 
#define H_SBGame
 
#include "Date.h"
#include <string>
#include <iomanip>
 
class SBGame {
 public:
 	
	/*** FUNCTORS ***/
	
	/**searchByWinner
	 *@brief Allows searching by the Winner attribute in find_if().
	 *@param string s - the string to be searched.
	 *@return sb.getWinner() == term - boolean evaluation of the comparison.
	 */
	struct searchByWinner {
		explicit searchByWinner(string s) : term(s) { };
		bool operator()(SBGame& sb) const {
			return (sb.getWinner() == term);
		}//end operator()
		private:
			string term;		
	};//end searchByWinner
	
	/**searchByLoser
	 *@brief Allows searching by the Loser attribute in find_if().
	 *@param string s - the string to be searched.
	 *@return sb.getLoser() == term - boolean evaluation of the comparison.
	 */
	struct searchByLoser {
		explicit searchByLoser(string s) : term(s) { };
		bool operator()(SBGame& sb) const {
			return (sb.getLoser() == term);
		}//end operator()
		private:
			string term;		
	};//end searchByLoser
	
	/**searchByWinnerPts
	 *@brief Allows searching by the WinnerPts attribute in find_if().
	 *@param string s - the string to be searched.
	 *@return sb.getWinnerPts() == term - boolean evaluation of the comparison.
	 */
	struct searchByWinnerPts {
		explicit searchByWinnerPts(string s) : term(s) { };
		bool operator()(SBGame& sb) const {
			return (sb.getWinnerPts() == stoi(term) );
		}//end operator()
		private:
			string term;		
	};//end searchByWinnerPts
	
	/**searchByLoserPts
	 *@brief Allows searching by the LoserPts attribute in find_if().
	 *@param string s - the string to be searched.
	 *@return sb.getLoserPts() == term - boolean evaluation of the comparison.
	 */
	struct searchByLoserPts {
		explicit searchByLoserPts(string s) : term(s) { };
		bool operator()(SBGame& sb) const {
			return (sb.getLoserPts() == stoi(term) );
		}//end operator()
		private:
			string term;		
	};//end searchByLoserPts
	
	/**searchByCombinedPts
	 *@brief Allows searching by the CombinedPts attribute in find_if().
	 *@param string s - the string to be searched.
	 *@return sb.getCombinedPts() == term - boolean evaluation of the comparison.
	 */
	struct searchByCombinedPts {
	explicit searchByCombinedPts(string s) : term(s) { };
	bool operator()(SBGame& sb) const {
		return (sb.getCombinedPts() == stoi(term) );
	}//end operator()
	private:
		string term;		
	};//end searchByCombinedPts
	
	/**searchByMVP
	 *@brief Allows searching by the MVP attribute in find_if().
	 *@param string s - the string to be searched.
	 *@return sb.getMVP() == term - boolean evaluation of the comparison.
	 */
	struct searchByMVP {
	explicit searchByMVP(string s) : term(s) { };
	bool operator()(SBGame& sb) const {
		return (sb.getMVP() == term);
	}//end operator()
	private:
		string term;		
	};//end searchByMVP
	
	/**searchByStadium
	 *@brief Allows searching by the Stadium attribute in find_if().
	 *@param string s - the string to be searched.
	 *@return sb.getStadium() == term - boolean evaluation of the comparison.
	 */
	struct searchByStadium {
	explicit searchByStadium(string s) : term(s) { };
	bool operator()(SBGame& sb) const {
		return (sb.getStadium() == term);
	}//end operator()
	private:
		string term;		
	};//end searchByStadium
	
	/**searchByCity
	 *@brief Allows searching by the City attribute in find_if().
	 *@param string s - the string to be searched.
	 *@return sb.getCity() == term - boolean evaluation of the comparison.
	 */
	struct searchByCity {
	explicit searchByCity(string s) : term(s) { };
	bool operator()(SBGame& sb) const {
		return (sb.getCity() == term);
	}//end operator()
	private:
		string term;		
	};//end searchByCity
	
	/**searchByState
	 *@brief Allows searching by the State attribute in find_if().
	 *@param string s - the string to be searched.
	 *@return sb.getState() == term - boolean evaluation of the comparison.
	 */
	struct searchByState {
	explicit searchByState(string s) : term(s) { };
	bool operator()(SBGame& sb) const {
		return (sb.getState() == term);
	}//end operator()
	private:
		string term;		
	};//end searchByState
	
	/**sortByWinner
	 *@brief Allows sorting by the Winner attribute in sort().
	 *@param sb1 - this SBGame
	 *@param ab2 - SBGame to be compared to this SBGame
	 *@return sb.getWinner() == term - boolean evaluation of the comparison.
	 */
	struct sortByWinner : public binary_function<SBGame, SBGame, bool> {
		bool operator()(SBGame sb1, SBGame sb2) {
			return ( sb1.getWinner() < sb2.getWinner() );
		}//end operator()
	};//end sortByWinner
 
  /**sortByLoser
	 *@brief Allows sorting by the Loser attribute in sort().
	 *@param sb1 - this SBGame
	 *@param ab2 - SBGame to be compared to this SBGame
	 *@return sb.getLoser() == term - boolean evaluation of the comparison.
	 */
 struct sortByLoser : public binary_function<SBGame, SBGame, bool> {
		bool operator()(SBGame sb1, SBGame sb2) {
			return ( sb1.getLoser() < sb2.getLoser() );
		}//end operator() 
	};//end sortByLoser
	
	/**sortByWinnerPts
	 *@brief Allows sorting by the WinnerPts attribute in sort().
	 *@param sb1 - this SBGame
	 *@param ab2 - SBGame to be compared to this SBGame
	 *@return sb.getWinnerPts() == term - boolean evaluation of the comparison.
	 */
	struct sortByWinnerPts : public binary_function<SBGame, SBGame, bool> {
		bool operator()(SBGame sb1, SBGame sb2) {
			return ( sb1.getWinnerPts() < sb2.getWinnerPts() );
		}//end operator()
	};//end sortByWinnerPts
 
  /**sortByLoserPts
	 *@brief Allows sorting by the LoserPts attribute in sort().
	 *@param sb1 - this SBGame
	 *@param ab2 - SBGame to be compared to this SBGame
	 *@return sb.getLoserPts() == term - boolean evaluation of the comparison.
	 */
 struct sortByLoserPts : public binary_function<SBGame, SBGame, bool> {
		bool operator()(SBGame sb1, SBGame sb2) {
			return ( sb1.getLoserPts() < sb2.getLoserPts() );
		}//end operator()
	};//end sortByLoserPts
	
	/**sortByTotalPts
	 *@brief Allows sorting by the TotalPts attribute in sort().
	 *@param sb1 - this SBGame
	 *@param ab2 - SBGame to be compared to this SBGame
	 *@return sb.getTotalPts() == term - boolean evaluation of the comparison.
	 */
	struct sortByTotalPts : public binary_function<SBGame, SBGame, bool> {
		bool operator()(SBGame sb1, SBGame sb2) {
			return ( sb1.getCombinedPts() < sb2.getCombinedPts() );
		}//end operator()
	};//end sortByTotalPts
	
	/**sortByMVP
	 *@brief Allows sorting by the MVP attribute in sort().
	 *@param sb1 - this SBGame
	 *@param ab2 - SBGame to be compared to this SBGame
	 *@return sb.getMVP() == term - boolean evaluation of the comparison.
	 */
	struct sortByMVP : public binary_function<SBGame, SBGame, bool> {
		bool operator()(SBGame sb1, SBGame sb2) {
			return ( sb1.getMVP() < sb2.getMVP() );
		}//end operator()
	};//end sortByMVP
	
	/**sortByStadium
	 *@brief Allows sorting by the Stadium attribute in sort().
	 *@param sb1 - this SBGame
	 *@param ab2 - SBGame to be compared to this SBGame
	 *@return sb.getStadium() == term - boolean evaluation of the comparison.
	 */
	struct sortByStadium : public binary_function<SBGame, SBGame, bool> {
		bool operator()(SBGame sb1, SBGame sb2) {
			return ( sb1.getStadium() < sb2.getStadium() );
		}//end operator()
	};//end sortByStadium
	
	/**sortByCity
	 *@brief Allows sorting by the City attribute in sort().
	 *@param sb1 - this SBGame
	 *@param ab2 - SBGame to be compared to this SBGame
	 *@return sb.getCity() == term - boolean evaluation of the comparison.
	 */
 struct sortByCity : public binary_function<SBGame, SBGame, bool> {
		bool operator()(SBGame sb1, SBGame sb2) {
			return ( sb1.getCity() < sb2.getCity() );
		}//end operator()
	};//end sortByCity
	
	/**sortByState
	 *@brief Allows sorting by the State attribute in sort().
	 *@param sb1 - this SBGame
	 *@param ab2 - SBGame to be compared to this SBGame
	 *@return sb.getState() == term - boolean evaluation of the comparison.
	 */
	struct sortByState : public binary_function<SBGame, SBGame, bool> {
		bool operator()(SBGame sb1, SBGame sb2) {
			return ( sb1.getState() < sb2.getState() );
		}//end operator()
	};//end sortByState
 
 	/*** END FUNCTORS ***/
	
	SBGame();              //Constructor
	
	Date getDate();        //Returns gameDate
	
	string getTitle();     //Returns SBTitle
	string getWinner();    //Returns Winner
	string getLoser();     //Returns Loser
	string getMVP();       //Returns MVP
	string getStadium();   //Returns Stadium
	string getCity();      //Returns City
	string getState();     //Returns State
 
	int getSBNum();        //Returns SBNum
	int getWinnerPts();    //Returns WinnerPts
	int getLoserPts();     //Returns LoserPts
	int getCombinedPts();  //Returns CombinedPts
	
	bool operator<(const SBGame&) const;  //Compare SBGames by SBNum
	bool operator<(const string& s) const;//Compare SBGame to a string by SBNum 
	bool operator==(SBGame);              //Check for equality of States by SBNum
	bool operator==(string s);            //Check for equality between State and string
 	bool operator>(string s);             //Compare SBGame to a string by SBNum
 private:
	Date gameDate;  //date of the game
	
	string SBTitle; //Title of the game (Form: "Super Bowl <roman numeral>")
	string Winner;  //Winning team
	string Loser;   //Losing team
	string MVP;     //Most valuable player
	string Stadium; //Stadium hosting the game
	string City;    //City hosting the game
	string State;   //State hosting the game

	int SBNum;       //Super Bowl Number (the Arabic form of the numeral in SBTitle)
	int WinnerPts;   //Number of Winner Points
	int LoserPts;    //Number of Loser Points
	int CombinedPts; //Number of Combined Points

	void toUpper(string& str);          //Converts string to uppercase
	string getNextField(string&, char); //Helper for overloaded stream insertion 
	
//input SBGame
friend istream &operator>>(istream&, SBGame& sb);

//output SBGame
friend ostream &operator<<(ostream&, const SBGame& sb);

};//end SBgame

#endif