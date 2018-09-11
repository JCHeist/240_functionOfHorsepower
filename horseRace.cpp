//install library
#include <iostream>//input/output
#include <string>//for strings
#include <cstdlib>//for random
#include <sstream>//for string streams
#include <ctime>//time
using namespace std;

//establish prototypes
int coinFlip();
void printTrack(int horse, int spot);


bool keepGoing = true;//set keepGoing to be true. This means the game will keep going
int horses [5];//create array of horses. indexes are the horse number and value is what spot the horse is on the track
int length = sizeof(horses)/sizeof(*horses);//establish variable for the length of the array


int main(){
	srand(time(NULL));//set random seed based off of current time

	//declare variables for for loop
	int i;
	int coin;
	
	printTrack( i, horses[0]);//print starting track postions
	printTrack( i, horses[1]);
	printTrack( i, horses[2]);
	printTrack( i, horses[3]);
	printTrack( i, horses[4]);

	cout << endl << "Ready... Set... GO!!!" << endl;
	
	//take a turn by going throgh each horse
	while(keepGoing){

		for(i = 0; i < length; i++){//look at every horse's spot
			coin = coinFlip();//see if horse should move or not by "flipping a coin"
			horses[i] += coin;//add value of coin flip (1 or 0)
			printTrack( i, horses[i]);//print the track of this horse
		} 
		cout << endl;		//leave space for next turn

		//create bool to say whether enter is pressed or not		
		bool enter = false;
		string resp = "";//ensure resp is nothing. this means just enter was pressed		


		while(enter == false){//while enter is not pressed keep asking for enter
		

			if(keepGoing == true){

				cout << "Press RETURN to advance a turn!";
			}else{

				cout << "Press enter to end the race.";				

			}
			getline(cin, resp);//ask for enter each time that is not all that is pressed
			
			if(resp == ""){

				enter = true;//enter has been pressed
	
			}
		}
	}


return 0;
}

int coinFlip(){
	
	int result;//declare variable to return
	
	result = rand() % 2;//generate a random number between 0 and the max rand number. if odd, return 1 if even return 0

	return result;
}

void printTrack(int horse, int spot){

	stringstream track;//create variable
	int i;
	//go through each possible spot in the track for selected horse
	for(i = 0; i < 15; i ++){
		//check if horse is there.
		if(spot == i){
		
			 track << horse;//if the horse is there print horse number

			
		}else{
			track << ".";//if the horse is not there print a period
				
		}
	
	}	
	cout << track.str() <<  endl;//new line
	

	if((horses[horse] > 14) && (keepGoing == true)){//check to see if the horse has won (is past space 15) and another horse has not yet

		cout << "Horse " << horse << " wins!!" << endl;//print message that this horse has won
		keepGoing = false;//stop taking turns in the race. it has ended
	
	}
}

