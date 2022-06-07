#include "Note.h"

using namespace std;

Note::Note(const string name, int octave, int duration) : Pitch(duration), name(name) {
    this->octave = octave;
}

Note::~Note() {

}

int Note::GetHalfStepID() const {
	int halfstep;
	int modifier = 0; // determines if there is a flat or sharp

	// decided to use a map so I could link notes to halfstep values since they
	// weren't perfect eg. no F flat
	map<char, int> baseline = {
		{'C', 0}, {'D', 2}, {'E', 4}, {'F', 5}, {'G', 7}, {'A', 9}, {'B', 11}
	};

	if (name[1] == '+') {
		modifier = 1;
	} else if (name[1] == '-') {
		modifier = -1;
	}

	// find the note in baseline and get the value (second)
	// and modify based on octave and sharp/flat
	halfstep = baseline.find(name[0])->second + (octave * 12) + modifier;

    return halfstep;
}

float Note::GetFrequency() const {
    float A4_freq = 440.0;
    float magic_number = pow(2.0, (1.0/12.0));

    // A0 half step is 9, add 12 4 times to get A4 half step
    int A4_half_step = 9 + (12 * 4);

    float distance = ((float)GetHalfStepID() - A4_half_step);

	return A4_freq * pow(magic_number, distance);
}

Note* Note::Clone() const {
    return new Note(this->name, this->octave, this->duration);
}


