#include "Nullaby.h"

using namespace std;

const int Nullaby::SAMPLES_PER_SECOND = 22050;

Nullaby::Nullaby() {
	song = new vector<Pitch*>;
}

Nullaby::~Nullaby() {
	for (int i = 0; i < this->GetPitchCount(); i++) {
		delete song->at(i);
	}
	delete song;
}

short* Nullaby::GenerateSamples(int bpm, int& nsamples) const {
    // create buffer to hold all samples
	// not really sure how much to actually malloc here?
	// could be pretty bad since I'm using samples a second, what if a note is longer than a second?

	short *samples = (short*) malloc(sizeof(short) * GetPitchCount() * Nullaby::SAMPLES_PER_SECOND);
	int index = 0;

    for (int i = 0; i < this->GetPitchCount(); i++) {
    	// get samples from each pitch that was added
    	short *pitch_samples = song->at(i)->GenerateSamples(bpm, nsamples);

    	for (int j = 0; j < nsamples; j++) {
    		// put every sample from pitch into the buffer of all samples
    		samples[index] = pitch_samples[j];
    		index++;
    	}
    	// free samples from pitch since they have been added to other buffer
    	free(pitch_samples);
    }

    // set nsamples to the total number of samples instead of the pitch samples
    // so when I write to wav file it knows how many to write
    nsamples = index;

	return samples;
}

void Nullaby::WriteWAV(int bpm, const string& path) {
	ofstream wav;
	wav.open(path.c_str(), ofstream::binary);

	// initialize variables for wav header
	short num_channels = 1;
	short bits_per_sample = 16;
	int chunk_size = 36 * Nullaby::SAMPLES_PER_SECOND * num_channels * (bits_per_sample / 8);
	int sub_chunk_1_size = 16;
	short audio_format = 1;
	int sample_rate = Nullaby::SAMPLES_PER_SECOND;
	int byte_rate = Nullaby::SAMPLES_PER_SECOND * num_channels * (bits_per_sample / 8);
	short block_align = 2;
	int sub_chunk_2_size = chunk_size - 36;

	int nsamples;

	short *all_samples = GenerateSamples(bpm, nsamples);

	// write out all header data for wav
	wav.write("RIFF", 4);
	wav.write((char*) &chunk_size, 4);
	wav.write("WAVEfmt ", 8); // includes format and sub_chunk_1_id all in one
	wav.write((char*) &sub_chunk_1_size, 4);
	wav.write((char*) &audio_format, 2);
	wav.write((char*) &num_channels, 2);
	wav.write((char*) &sample_rate, 4);
	wav.write((char*) &byte_rate, 4);
	wav.write((char*) &block_align, 2);
	wav.write((char*) &bits_per_sample, 2);
	wav.write("data", 4); // sub_chunk_2_id
	wav.write((char*) &sub_chunk_2_size, 4);

	// actually write samples to wav file
	wav.write((char*) (&all_samples[0]), nsamples * sizeof(short));

	wav.close();

	// free all samples since I'm done with them now
	free(all_samples);
}

const Pitch& Nullaby::operator[](int index) const {
	return *song->at(index);
}

void Nullaby::Add(const Pitch& p) {
	song->push_back(p.Clone());
}

void Nullaby::Add(const Nullaby& n) {
	for(int i = 0; i < n.GetPitchCount(); i++) {
		song->push_back(n.song->at(i)->Clone());
	}
}

int Nullaby::GetPitchCount() const {
    return song->size();
}
