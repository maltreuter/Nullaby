#include "Pitch.h"
#include "Nullaby.h"

using namespace std;

Pitch::Pitch(int duration) {
    this->duration = duration;
}

Pitch::~Pitch() {

}

short* Pitch::GenerateSamples(int bpm, int& nsamples) const {
    float beats_per_second = bpm / 60.0;
    float seconds_per_beat = 1.0 / beats_per_second;
    float seconds_per_whole_note = seconds_per_beat * 4.0;
	float nseconds = seconds_per_whole_note / duration;
	nsamples = nseconds * Nullaby::SAMPLES_PER_SECOND;



	short *samples = (short*) malloc(nsamples * sizeof(short));

	float cycles_per_sample = this->GetFrequency() / Nullaby::SAMPLES_PER_SECOND;

	for (int i = 0; i < nsamples; i++) {
		samples[i] = (short) (sin(2 * M_PI * i * cycles_per_sample) * 32767);
	}

	return samples;
}


