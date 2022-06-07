#ifndef PITCH_INCLUDE
#define PITCH_INCLUDE
#define _USE_MATH_DEFINES

#include <math.h>
#include <stdlib.h>

using namespace std;

class Pitch {
    public:
        int duration;

        Pitch(int duration);
        virtual ~Pitch();
        virtual float GetFrequency() const = 0;
        short *GenerateSamples(int bpm, int& nsamples) const;
        virtual Pitch *Clone() const = 0;

    private:
};

#endif
