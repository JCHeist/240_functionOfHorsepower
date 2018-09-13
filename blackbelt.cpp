//install library
#include <iostream>//input/output
#include <string>//for strings
#include <cstdlib>//for random
#include <sstream>//for string streams
#include <ctime>//time
#include <fstream>//reading csv files:

//establish prototypes
int coinFlip();
void printTrack(int horse, int spot);
void race();
void menu();
void stats();

const int TRACK_LENGTH = 15;
bool keepGoing = true;//set keepGoing to be true. This means the game will keep going
int horses [5];//create array of horses. indexes are the horse number and value is what spot the horse is on the track
int length = sizeof(horses)/sizeof(*horses);//establish variable for the length of the array

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
	keepGoing = true;	

	//reset horse positions
	for(i = 0; i < length; i++){

		horses[i] = 0;
	
	}

	printTrack( 0, horses[0]);//print starting track postions
	printTrack( 1, horses[1]);
	printTrack( 2, horses[2]);
	printTrack( 3, horses[3]);
	printTrack( 4, horses[4]);

	std::cout << std::endl << "Ready... Set... GO!!!" << std::endl;
	
	//take a turn by going throgh each horse
	while(keepGoing){

		for(i = 0; i < length; i++){//look at every horse's spot
			coin = coinFlip();//see if horse should move or not by "flipping a coin"
			horses[i] += coin;//add value of coin flip (1 or 0)
			printTrack( i, horses[i]);//print the track of this horse
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

void printTrack(int horse, int spot){

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
	

	if((horses[horse] > TRACK_LENGTH - 1) && (keepGoing == true)){//check to see if the horse has won (is past space 15) and another horse has not yet

		std::cout << "Horse " << horse << " wins!!" << std::endl;//print message that this horse has won
		keepGoing = false;//stop taking turns in the race. it has ended
	
	}
}

void stats(){




        std::ifstream file ( "records.csv" ); // declare file stream

        std::string horse;

        std::string number;
        std::string name;
        std::string races;
        std::string wins;
        std::string country;

        int i;

        for (i = 0; i < 10; i++){
               
                        std::getline(file, number, ',');//get data for each horse
                        std::getline(file, name, ',');
                        std::getline(file, races, ',');
                        std::getline(file, wins, ',');
                        std::getline(file, country, ';');


			//print data
                        std::cout << "Number: " << number << std::endl;
                        std::cout << "Name: " << name << std::endl;
                        std::cout << "Races: " << races << std::endl;
                        std::cout << "Wins: " << wins << std::endl;
                        std::cout << "Country: " << country << std::endl <<  std::endl;

        }

}



int main(){

	menu();


return 0;
}
