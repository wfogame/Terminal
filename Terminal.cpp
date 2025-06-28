#include <iostream>
#include <string>
using namespace std;

bool GameState = true;
	bool Terminal(string prompt = "none"){
        if(prompt == "exit" || prompt == "quit"){
            cout << "Exiting terminal..." << endl;
            return false;

        }
		if(prompt == "none" || prompt.rfind(":",0)){

            cout << "Invalid command. Type 'exit' or 'quit' to exit, or type : to type a real command" << endl;

		}
		
		cout << R"(What is your Command:)";	
        cin >> prompt;
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
   |_|\___|_|  |_| |_| |_|_|_| |_|\__,_|_|  \_____|\__,_|_| |_| |_|\___|)" <<	std::endl;
    cout << "Type 'exit' or 'quit' to exit the terminal:" << endl;
    cout << "Type ':' to type a real command:" << endl;
   

	cin >> command;
    
     
   
    if(!GameState){
     cout << "Exiting terminal..." << endl;
    GameState = false;
    return 0;

    }else{

   GameState = Terminal(command);


    }




    }
