#pragma once
#include <iostream>
using namespace std;
#include <vector>
#include <deque>
#include <map>
#include <algorithm>
#include <functional>
#include <numeric>
#include <string>
#include <fstream>
#include "speaker.h"

class SpeechManagement {
public:
	SpeechManagement();

	void showMenu();

	void exitSystem();

	// initialize containers and properties
	void initSpeech();

	// create the 12 contestants
	void createSpeaker();

	// contest flow control function
	void startSpeech();

	// group by lot
	void speechDraw();

	void speechContest();

	void showScore();

	void saveRecord();

	~SpeechManagement();

	// save contestant number for the first round
	vector<int> v1;

	// save the contestant number which advance in the contest for the first round
	vector<int> v2;

	// save the top three contestant numbers for the second round
	vector<int> vVictory;

	// store number and corresponding contestant
	map<int, Speaker> map_Speaker;

	// number of rounds
	int m_Index;
};