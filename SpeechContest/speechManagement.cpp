#include "speechManagement.h"

SpeechManagement::SpeechManagement() {
	// initialize containers and properties
	this->initSpeech();

	// create the 12 speakers
	this->createSpeaker();
}

void SpeechManagement::showMenu(){
	cout << "***********************************************************" << endl;
	cout << "*************  Welcome to the speech contest  *************" << endl;
	cout << "*************     1. Start speech contest     *************" << endl;
	cout << "*************     2. View previous records    *************" << endl;
	cout << "*************     3. Clear contest record     *************" << endl;
	cout << "*************     0. Exit speech contest      *************" << endl;
	cout << "***********************************************************" << endl;
	cout << endl;
}

void SpeechManagement::exitSystem() {
	cout << "See you next time!" << endl;
	system("pause");
	exit(0);
}

// initialize containers and properties
void SpeechManagement::initSpeech() {
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->map_Speaker.clear();

	this->m_Index = 1;
}

// create the 12 speakers
void SpeechManagement::createSpeaker() {
	string nameSeed = "ABCDEFGHIJKL";

	for (int i = 0; i < nameSeed.size(); i++) {
		string name = "Speaker";
		name += nameSeed[i];

		Speaker sp;
		sp.m_Name = name;

		for (int j = 0; j < 2; j++) {
			sp.m_Score[j] = 0;
		}

		this->v1.push_back(i + 10001);
		this->map_Speaker.insert(make_pair(i + 10001, sp));

	}
}

SpeechManagement::~SpeechManagement() {

}