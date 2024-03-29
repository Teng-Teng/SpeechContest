#include "speechManagement.h"

int main() {
	// random number seed
	srand((unsigned int)time(NULL));

	SpeechManagement sm;

	/*for (map<int, Speaker>::iterator it = sm.map_Speaker.begin(); it != sm.map_Speaker.end(); it++) {
		cout << "Speaker number: " << it->first << " Name: " << it->second.m_Name
			<< " Score: " << it->second.m_Score[0] << endl;
	}*/

	int choice = 0;

	while (true) {
		sm.showMenu();

		cout << "Please enter your choice: " << endl;
		cin >> choice;

		switch (choice) {
			case 1:
				// Start speech contest
				sm.startSpeech();
				break;
			case 2:
				// View previous records
				sm.showRecord();
				break;
			case 3:
				// Clear contest record
				sm.clearRecord();
				break;
			case 0:
				// Exit speech contest
				sm.exitSystem();
				break;
			default:
				system("cls");
				break;
		}

	}

	system("pause");
	return 0;
}