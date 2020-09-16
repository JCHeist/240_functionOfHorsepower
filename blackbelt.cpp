//install library
#include <iostream>//input/output
#include <string>//for strings
#include <cstdlib>//for random
#include <sstream>//for string streams
#include <ctime>//time
#include <fstream>//reading csv files:
#include <algorithm>//for std::find

struct HorseStruct {
		
	std::string number;
	std::string name;
	std::string races;
	std::string wins;
	std::string country;


};


//establish prototypes
int coinFlip();
void printTrack(int horse,int ln,  int spot);
void race();
void menu();
void stats();
int selectHorse(int[], int);


const int TRACK_LENGTH = 15;
bool keepGoing = true;//set keepGoing to be true. This means the game will keep going
int lane [5];//create array of horses. indexes are the horse number and value is what spot the horse is on the track
int length = sizeof(lane)/sizeof(*lane);//establish variable for the length of the array


void menu(){
	bool exit = false;
	std::string resp;	

	while(exit == false){
		

		//ask user what they would like to do
		std::cout << "What would you like to do?" << std::endl;
		std::cout << "1) Race" << std::endl;
		std::cout << "2) Look at horse stats" << std::endl;
		std::cout << "3) Quit" << std::endl;
		std::cin >> resp;
		std::cout << std::endl << std::endl;
		
		if(resp == "1"){

			race();

		}else if(resp == "2"){
			
			stats();

		}else if(resp == "3"){

			std::cout << "Thanks for playing!." << std::endl;
			exit = true;

		}else{
			//if 1 2 or 3 is not entered, ask for input again
			std::cout << "I'm sorry, I do not understand..." << std::endl << std::endl;
	
		}

	}
}


void race(){
	std::srand(time(NULL));//set random seed based off of current time
	
	std::cin.ignore();//ignore last input of enter
	
	//declare variables for for loop
	int i;
	int coin;
	int selected[5]; 

	for(i = 0; i < 5; i++){

		selected[i] = -1;

	}
	
	keepGoing = true;	
	
	//select horses
	for(i = 0; i < 5; i++){

		std::cout << "Select horse number " << i;
		selected[i] = selectHorse( selected, length);//assign a selected horse to this lane

	}

	//reset horse positions
	for(i = 0; i < length; i++){

		lane[i] = 0;
	
	}

	std::cout << std::endl << std::endl << "Here are your valient racers!" << std::endl;
	for(i = 0; i < length; i++){
		printTrack( selected[i], i,  lane[i]);//print starting track postions
	}
	std::cout << std::endl << "Ready... Set... GO!!!" << std::endl;
	
	//take a turn by going throgh each horse
	while(keepGoing){

		for(i = 0; i < length; i++){//look at every horse's spot
			coin = coinFlip();//see if horse should move or not by "flipping a coin"
			lane[i] += coin;//add value of coin flip (1 or 0)
			printTrack( selected[i], i, lane[i]);//print the track of this horse
		} 
		std::cout << std::endl;		//leave space for next turn

		//create bool to say whether enter is pressed or not		
		bool enter = false;
		std::string resp = "";//ensure resp is nothing. this means just enter was pressed		


		while(enter == false){//while enter is not pressed keep asking for enter
		

			if(keepGoing == true){

				std::cout << "Press RETURN to advance a turn!";
			}else{

				std::cout << "Press enter to end the race.";				

			}
			std::getline(std::cin, resp);//ask for enter each time that is not all that is pressed
			
			if(resp == ""){

				enter = true;//enter has been pressed
	
			}
		}
	}
}

int coinFlip(){
	
	int result;//declare variable to return
	
	result = std::rand() % 2;//generate a random number between 0 and the max rand number. if odd, return 1 if even return 0

	return result;
}




void printTrack(int horse, int ln, int spot){

	std::stringstream track;//create variable
	int i;
	//go through each possible spot in the track for selected horse
	for(i = 0; i < TRACK_LENGTH; i ++){
		//check if horse is there.
		if(spot == i){
		
			 track << horse;//if the horse is there print horse number

			
		}else{
			track << ".";//if the horse is not there print a period
				
		}
	
	}	
	std::cout << track.str() <<  std::endl;//new line
	

	if((lane[ln] == TRACK_LENGTH) && (keepGoing == true)){//check to see if the horse has won (is past space 15) and another horse has not yet

		std::cout << "Horse " << horse << " wins!!" << std::endl;//print message that this horse has won
		keepGoing = false;//stop taking turns in the race. it has ended
	
	}
}




void stats(){

	//create an array of structs for eack horse
	HorseStruct arr[10];
	int i;	

	std::ifstream selection("records.csv");
        std::string number;
        std::string name;
        std::string races;
        std::string wins;
        std::string country;


	std::cout << "----------------------------Horse Stats------------------------" << std::endl;


	for(i = 0; i < 10; i++){
		 	
			//assign data in csv file to array of horseStructs
               		std::getline(selection, arr[i].number, ',');//get data for each horse
                        std::getline(selection, arr[i].name, ',');
                        std::getline(selection, arr[i].races, ',');
                        std::getline(selection, arr[i].wins, ',');
                        std::getline(selection, arr[i].country, ';');

	}


	for(i = 0; i < 10; i++){

				//print data
                        std::cout << "Number: " << arr[i].number << std::endl;
                        std::cout << "Name: " << arr[i].name << std::endl;
                        std::cout << "Races: " << arr[i].races << std::endl;
                        std::cout << "Wins: " << arr[i].wins << std::endl;
                        std::cout << "Country: " << arr[i].country << std::endl <<  std::endl;

	
	}

	std::cout << "----------------------------------------------------------------" << std::endl;
selection.close();
}


int selectHorse(int selected[], int length){

	int val;	
	bool unavailable = true;	
	int i;
	std::string hold;

	stats();//show stats
	
	//ask user what horse they would like to put in this lane
	while(unavailable){
		std::cout << "What horse would you like to race here?" << std::endl;
		
		//store input in val
		std::cin >> val;
		
		//if an int is not entered display warning message, clear cin, ignore cin
		if(std::cin.fail()){
	
			std::cout << "Nice try, please pick a numeric value." << std::endl;
			std::cin.clear();
			std::cin.ignore(256,'\n');
		}else{//if an int is entered check to see if the value is from 0-9.. available horse numbers
			unavailable = false;
			if((val >= 0) && (val<= 9)){
				for(i = 0; i < 5; i ++){
			
					if(selected[i] == val){//if horse is already selected, make the user select another one

						std::cout << "That horse in not available to race. Please select another horse." << std::endl;
						unavailable = true;	
					}
				}
			}else{
				//if an int is entered that is not 0-9 ask for a new number
				std::cout << "Please pick a valid horse's number." << std::endl;
				unavailable = true;
				std::cin.clear();
				val = 0;		
			}
		}
	}	

	
return val;
}



int main(){

	menu();


return 0;
}
