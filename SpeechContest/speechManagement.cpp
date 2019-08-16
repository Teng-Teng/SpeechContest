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

// Game flow control function
void SpeechManagement::startSpeech() {
	// the first round started

	// 1. group by lot
	this->speechDraw();

	// 2. start contest
	this->speechContest();

	// 3. show the speakers who advance in the contest


	// the second round started


	// 1. group by lot


	// 2. start contest


	// 3. show final result


	// 4. save the score to file


}

// group by lot
void SpeechManagement::speechDraw() {
	cout << "The speakers are drawing lots in the " << this->m_Index << " round" << endl;
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

	// record the number of people, 6 speakers form a group
	int num = 0;

	vector<int> v_Src;

	if (this->m_Index == 1)
		v_Src = v1;
	else
		v_Src = v2;

	// traverse all speakers to start the contest
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++) {
		num++;

		// judges give score to the speakers
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

		// put scoring data into a temporary container, key--score, value--speaker number
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

SpeechManagement::~SpeechManagement() {

}