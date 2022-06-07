#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

#include "Pitch.h"
#include "Note.h"
#include "Rest.h"

using namespace std;

class Nullaby {
    public:
        static const int SAMPLES_PER_SECOND;

        Nullaby();
        ~Nullaby();
        short *GenerateSamples(int bpm, int& nsamples) const;
        void WriteWAV(int bpm, const string& path);
        const Pitch& operator[](int index) const;
        void Add(const Pitch& p);
        void Add(const Nullaby& n);
        int GetPitchCount() const;

    private:
        vector<Pitch*> *song;
};
