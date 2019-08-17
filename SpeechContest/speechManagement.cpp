#include "speechManagement.h"

SpeechManagement::SpeechManagement() {
	// initialize containers and properties
	this->initSpeech();

	// create the 12 contestants
	this->createSpeaker();

	// load previous records
	this->loadRecord();
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
	this->map_Record.clear();

	this->m_Index = 1;
}

// create the 12 contestants
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

// contest flow control function
void SpeechManagement::startSpeech() {

	// the first round started
	for (int i = 0; i < 2; i++) {
		// 1. group by lot
		this->speechDraw();

		// 2. start contest
		this->speechContest();

		// 3. show the contestants who advance in the contest
		this->showScore();

		// the second round started
		if (i == 0)
			this->m_Index++;
	}

	// 4. save the score to file
	this->saveRecord();

	// initialize containers and properties
	this->initSpeech();

	// create the 12 contestants
	this->createSpeaker();

	// load previous records
	this->loadRecord();

	cout << "The speech contest is over!" << endl;
	system("pause");
	system("cls");
}

// group by lot
void SpeechManagement::speechDraw() {
	cout << "The contestants are drawing lots in the " << this->m_Index << " round" << endl;
	cout << "----------------------" << endl;
	cout << "The speech sequence after the lottery is as follows: " << endl;

	if (this->m_Index == 1) {
		// the first round
		random_shuffle(v1.begin(), v1.end());

		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
			cout << *it << " ";
		cout << endl;

	}
	else {
		// the second round
		random_shuffle(v2.begin(), v2.end());

		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
			cout << *it << " ";
		cout << endl;
	}

	cout << "----------------------" << endl;
	system("pause");
	cout << endl;
}

void SpeechManagement::speechContest() {
	cout << "---------- The " << this->m_Index << " round started ----------" << endl;

	// prepare temporary container to store group scores
	multimap<double, int, greater<double>> groupScore;

	// record the number of people, 6 contestants form a group
	int num = 0;

	vector<int> v_Src;

	if (this->m_Index == 1)
		v_Src = v1;
	else
		v_Src = v2;

	// traverse all contestants to start the contest
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++) {
		num++;

		// judges give score to the contestants
		deque<double> d;

		for (int i = 0; i < 10; i++) {
			double score = (rand() % 401 + 600) / 10.f;
			//cout << score << " ";
			d.push_back(score);
		}

		// descending sort
		sort(d.begin(), d.end(), greater<double>());

		// remove the highest and lowest scores
		d.pop_front();
		d.pop_back();

		// total score 
		double sum = accumulate(d.begin(), d.end(), 0.0f);

		// average score
		double avg = sum / (double)d.size();

		// print average score
		/*cout << "Number: " << *it << " Name: " << this->map_Speaker[*it].m_Name
			 << " Average score: " << avg << endl;*/

		// put the average score into the map
		this->map_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		// put scoring data into a temporary container, key--score, value--contestant number
		groupScore.insert(make_pair(avg, *it));

		// take the top 3 for every 6 people
		if (num % 6 == 0) {
			cout << "Ranking for the " << num / 6 << " group: " << endl;

			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++) {
				cout << "Number: " << it->second << " Name: " << this->map_Speaker[it->second].m_Name
					<< " Score: " << this->map_Speaker[it->second].m_Score[this->m_Index - 1] << endl;
			}

			// get the top three speakers
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++) {
				if (this->m_Index == 1)
					v2.push_back((*it).second);
				else
					vVictory.push_back((*it).second);

			}

			groupScore.clear();
			cout << endl;
		}
	}

	cout << "---------------The "<< this->m_Index << " round of the contest is over---------------" << endl;
	system("pause");
}

void SpeechManagement::showScore() {
	// show the speakers who advance in the contest
	cout << "The contestants information who advance in the " << this->m_Index 
		 << " round of the contest is as follows:" << endl;

	vector<int> v;

	if (this->m_Index == 1)
		v = v2;
	else
		v = vVictory;

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) 
		cout << "Number: " << *it << " Name: " << this->map_Speaker[*it].m_Name
		     << " Score: " << this->map_Speaker[*it].m_Score[this->m_Index - 1] << endl;

	cout << endl;

	system("pause");
	system("cls");
	this->showMenu();
}

void SpeechManagement::saveRecord() {
	ofstream ofs;

	// write file in append manner
	ofs.open("speech.csv", ios::out | ios::app);

	// write winning contestants information to a file
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++) {
		ofs << *it << "," << this->map_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;

	ofs.close();
	cout << "Record has been saved!" << endl;
	this->isFileEmpty = false;
}

// load previous record
void SpeechManagement::loadRecord() {
	// read file
	ifstream ifs("speech.csv", ios::in);

	// file doesn't exist
	if (!ifs.is_open()) {
		this->isFileEmpty = true;
		//cout << "File doesn't exist!" << endl;
		ifs.close();
		return;
	}

	// file has been emptied
	char ch;
	ifs >> ch;

	if (ifs.eof()) {
		//cout << "File is empty!" << endl;
		this->isFileEmpty = true;
		ifs.close();
		return;
	}

	// file isn't empty
	this->isFileEmpty = false;
	ifs.putback(ch);

	string data;
	int index = 0;

	while (ifs >> data) {
		vector<string> v;

		// comma position
		int pos = -1;
		int start = 0;

		while (true) {
			pos = data.find(",", start);

			if (pos == -1)
				break;
			
			string temp = data.substr(start, pos - start);
			v.push_back(temp);

			start = pos + 1;
		}

		this->map_Record.insert(make_pair(index, v));
		index++;
	}

	ifs.close();

	/*for (map<int, vector<string>>::iterator it = map_Record.begin(); it != map_Record.end(); it++) {
		cout << it->first << " Champion number: " << it->second[0]
			 << " Score: " << it->second[1] << endl;
	}*/
}

// show previous record
void SpeechManagement::showRecord() {
	if (this->isFileEmpty)
		cout << "File doesn't exist or file is empty!" << endl;
	else {
		for (int i = 0; i < map_Record.size(); i++) {
			cout << "The " << i + 1 << " speech contest "
				<< " Champion number: " << this->map_Record[i][0] << " Score: " << this->map_Record[i][1] << " "
				<< " Second place number: " << this->map_Record[i][2] << " Score: " << this->map_Record[i][3] << " "
				<< " Third place number: " << this->map_Record[i][4] << " Score: " << this->map_Record[i][5] << endl;
		}
	}

	system("pause");
	system("cls");
}

void SpeechManagement::clearRecord() {
	cout << "Are you sure to empty the file?" << endl;
	cout << "1. Yes" << endl;
	cout << "2. No" << endl;

	int select = 0;
	cin >> select;

	if (select == 1) {
		// open mode--ios::trunc, if the file exists, delete the file and recreate it
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		// initialize containers and properties
		this->initSpeech();

		// create the 12 contestants
		this->createSpeaker();

		// load previous records
		this->loadRecord();

		cout << "Empty the file successfully!" << endl;
	}

	system("pause");
	system("cls");
}

SpeechManagement::~SpeechManagement() {

}