# Super Bowl Statistics
An analysis of Super Bowl statistics using STL containers, functors, and iterators for storing, reordering, and reviewing key metrics from the dataset. 

|                       |                                                                                                                               |
|----------------------:|-------------------------------------------------------------------------------------------------------------------------------|
|**Last Modified Date:**| 4/29/2020                                                                                                                     |
|**Last Modifications:**| Fine-tuned output formatting for presentation of data                                                                         |
|     **Documentation:**| [Doc Site](https://codedocs.xyz/GriffinNye22/SuperBowlStatistics/)                                                              |  
|          **Platform:**| UNIX                                                                                                                          |
|          **Language:**| C++                                                                                                                           |

## Design Details

### Selecting & Preparing the Dataset
Selecting a dataset was not difficult. At the time of this project (Spring 2020), the NFL season was over and we had just entered the long-dreaded 7 month drought of our favorite players throwing around the ol' pigskin. At this point in time, the long victorious Patriot's dynasty was on the decline and a new challenger was on the rise, the Kansas City Chiefs. In an effort to satiate my desires for September to return, I decided to analyze a dataset containing statistics about all 54 Super Bowls (at the time). 

I selected my dataset from Kaggle.com and coincidentally, this also happened to be the first "large" dataset I had ever worked on in my Computer Science I class my freshman year (aside from the additional Super Bowls added). After realizing this, I knew that this dataset would be a perfect fit for the project. The original dataset was a comma-separated file containing a field header row, followed by the data for each Super Bowl newline-separated. Each record contained the following fields:
  - The date of the Super Bowl in MMM d, yyyy format
  - The Super Bowl number in Roman Numerals followed by the standard Arabic representation in parentheses
  - The winning team for the Super Bowl
  - The number of points scored by the Winning Team for the Super Bowl
  - The losing Team for the Super Bowl
  - The number of points scored by the Losing Team for the Super Bowl
  - The Super Bowl MVP
  - The Stadium the Super Bowl was played in
  - The City the Super Bowl was played in
  - The State the Super Bowl was played in

I then cleansed and reorganized the dataset slightly for easier importing. Mainly these changes included: removing the field header row, converting the date format to M/d/yyyy, and splitting the Super Bowl number field into two separate fields: one for the Roman Numeral representation and one for the Arabic Numeral representation. 

### Implementation
First I created a class called SBGame with private data members for each attribute from the dataset. For each private data member, I then added a corresponding inspector function. Next, I overloaded the <, >, and == operators for comparisons
of both SBGame and a string. I also overloaded the stream insertion and extraction operators to allow easy input and output of SBGame objects.

Included in my class definition is a variety of functors. The first 9 functors act as a unary predicate, for use with the find_if() function of the string library. These 9 functors allow me to search specific attribute fields of the SBGame object, rather than the default specified in the overloaded "==" operator function.
	 
The second 9 functors act as a Compare type, for use with the sort() function of the algorithm library. These 9 functors allow me to sort the vector of SBGame objects by specific attribute fields, rather than the default specified 
in the overloaded "<" operator function.

**Manipulations:**  
The first manipulation of the data that I implemented was a simple reorder. I created a menu detailing the available attributes for sorting, and prompted the user for input. If the selection is the same as the current sort type, I do nothing;
otherwise, I call the sort function for the user-specified attribute, passing it the corresponding functor for sorting by that attribute.
	 
The second manipulation of the data that I implemented was a search. I created a menu outlining the possible options for searching the data, and prompted the user for input. Once they made a selection, I then prompted them to enter a
searchterm. From there, I passed the searchterm, their selection, and the vector of SBGame objects to the searchAttribute() function. 
	 
> Once here, I converted the searchterm to uppercase and then passed the vector of SBGame objects, the attribute selected by the user, the searchterm, and an iterator to the first element in the vector of SBGame objects to the findByAttribute() 
> function. 
		 
> > In this function, I simply created a switch statement for each possible attribute the user could have selected. Within each case, I returned the results of find() (for the default attribute) and find_if() using their appropriate functors
> > defined in the SBGame class declaration, to allow myself to search the user's specified attribute. The result of each of these calls is an iterator to the first element in the vector of SBGame objects that match the searchterm. This result
> > is returned to the searchAttribute() function.

> Once back in the searchAttribute() function, I check if an element in the vector was found. If so, I print the resulting SBGame object and call findByAttribute() again, this time passing an iterator pointing to the next element in the vector,
> rather than the beginning. Printing and calling findByAttribute() continues until the end of the vector is reached.

Another manipulation of the data I implemented was the ability to view a list in descending order of the teams with the most Super Bowl rings. Along with each team, I also provided the number of rings they possess and a list of the Super
Bowls in which they were earned.
	 
> To implement this, I first created a multimap, mapping an integer to a pair. This pair maps a string to a vector of strings. After loading the dataset, I call populateMaps() to populate the container.
	 
> > To begin population, I first create a temporary map, mapping strings to a vector of strings. This map will contain the Team name as the key type, and a vector of their victorious Super Bowls as the value type. To populate this, I simply \
> > iterate through each SBGame and check if an entry exists for a team in the map. If an entry exists, I simply push_back the Super Bowl title to the vector of Super Bowls. Otherwise, I create an entry for the team in the map. 
	 
> Once this iteration is complete, I then must iterate through all the entries in the tempMap. I also create a temporary pair, again mapping the team name to the vector of victorious Super Bowls. This is done, as I cannot simply insert
> the map into the multimap as its value type because the tempMap contains the mapping for ALL teams, rather than just one. So, I retrieve the size of the vector of SuperBowls in tempMap and then insert a pair into tempPair, mapping the team
> name for the entry in tempMap to the vector of SuperBowls in that entry of tempMap. I then map the number of rings to this tempPair and insert it into the multimap.
	
One last manipulation of the data I implemented was the ability to view a list of the players with the most Super Bowl MVP awards. Along with each player in the list, I also provided the number of MVP awards earned by that player and a list of 
the Super Bowls in which they were earned. 
	 
> Populating the multimap is implemented in the same manner as the list of Super Bowl rings listed above, except with MVP name instead of the team name.		 
	 
One thing I should mention as well, is that both multimaps are provided a 3rd template argument, sortByNum, which is a functor in the implementation of this program, allowing the multimap to be sorted in descending order of number of rings/MVP 
awards.
	 
From there, I simply just printed the list with some special formatting.

## Plan Deviation
My original plan was to simply search for letters in one or two attributes, search a few attributes for a string, and reorder the dataset. I deviated from this plan because as I began working on my implementation I found it to be too simple.		
This is when I decided to allow searching and sorting of almost all of the attributes in my dataset, as well as, viewing the ordered list of teams by number of Super Bowl Rings. 

I also planned on implementing functionalities for displaying consecutive rings, MVP titles, and losses, but I was unable to implement them at the time due to scheduling constraints.
		
## Info to run
**compile:**  
```cpp
make
```
**run:**
```cpp
./p3_402
```
