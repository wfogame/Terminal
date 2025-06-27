#include <iostream>
#include <string>
using namespace std;


	bool Terminal(string prompt = "none"){
		if(prompt == "none"){


			return false;
		}
	
		
	

		return true;	
	}






	int main(){
	string command;

		cout << R"(
 _______                  _             _    _____
|__   __|                (_)           | |  / ____|
   | | ___ _ __ _ __ ___  _ _ __   __ _| | | |  __  __ _ _ __ ___   ___
   | |/ _ \ '__| '_ ` _ \| | '_ \ / _` | | | | |_ |/ _` | '_ ` _ \ / _ \
   | |  __/ |  | | | | | | | | | | (_| | | | |__| | (_| | | | | | |  __/
   |_|\___|_|  |_| |_| |_|_|_| |_|\__,_|_|  \_____|\__,_|_| |_| |_|\___|

	 )";


	cin >> command;
	Terminal(command);


	}
