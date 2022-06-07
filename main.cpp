#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <expat.h>
#include <fstream>
#include <iostream>
#include <stack>
#include <string>

#include "Pitch.h"
#include "Note.h"
#include "Rest.h"
#include "Nullaby.h"

using namespace std;

typedef struct song {
	string song_path;
	int nrepeats;
	int default_duration;
	int default_octave;
	int bpm;
	stack<Nullaby*> songs;

} song;

void open_handler(void *data, const char *tag, const char **attributes) {
	song *my_song = (song*) data;

	int octave = my_song->default_octave;
	int duration = my_song->default_duration;
	string name;

	if (strcmp(tag, "song") == 0) {
		my_song->songs.push(new Nullaby());
		for (int i = 0; attributes[i] != NULL; i += 2) {
			if (strcmp(attributes[i], "octave") == 0) {
				my_song->default_octave = atoi(attributes[i + 1]);
			} else if (strcmp(attributes[i], "duration") == 0) {
				my_song->default_duration = atoi(attributes[i + 1]);
			} else if (strcmp(attributes[i], "bpm") == 0) {
				my_song->bpm = atoi(attributes[i + 1]);
			}
		}
	} else if (strcmp(tag, "note") == 0) {
		for (int i = 0; attributes[i] != NULL; i += 2) {
			if (strcmp(attributes[i], "octave") == 0) {
				octave = atoi(attributes[i + 1]);
			} else if (strcmp(attributes[i], "duration") == 0) {
				duration = atoi(attributes[i + 1]);
			} else if (strcmp(attributes[i], "name") == 0) {
				name = attributes[i + 1];
			}
		}
		my_song->songs.top()->Add(Note(name, octave, duration));
	} else if (strcmp(tag, "rest") == 0) {
		for (int i = 0; attributes[i] != NULL; i += 2) {
			if (strcmp(attributes[i], "duration") == 0) {
				duration = atoi(attributes[i + 1]);
			}
		}
		my_song->songs.top()->Add(Rest(duration));
	} else if (strcmp(tag, "repeat") == 0) {
		my_song->songs.push(new Nullaby());
		for (int i = 0; attributes[i] != NULL; i += 2) {
			if (strcmp(attributes[i], "times") == 0) {
				my_song->nrepeats = atoi(attributes[i + 1]);
			}
		}
	}

}

void close_handler(void *data, const char *tag) {
	song *my_song = (song*) data;

	if(strcmp(tag, "repeat") == 0) {
		Nullaby* repeat_song = (my_song->songs.top());
		my_song->songs.pop();
		// add the repeat song to the base song for however many repeats there were
		for (int i = 0; i < my_song->nrepeats; i++) {
			my_song->songs.top()->Add(*repeat_song);
		}
		delete repeat_song;
	} else if (strcmp(tag, "song") == 0) {
		Nullaby* song_reference = my_song->songs.top();
		my_song->songs.top()->WriteWAV(my_song->bpm, my_song->song_path);
		// can't forget to pop off base song and delete
		my_song->songs.pop();
		delete song_reference;

	}
}

int main(int argc, char* argv[]) {

	song my_song;

	my_song.song_path = string(argv[2]);

	XML_Parser parser = XML_ParserCreate(NULL);
	XML_SetElementHandler(parser, open_handler, close_handler);
	XML_SetUserData(parser, (void*) &my_song);

	string line;
	ifstream xml(argv[1]);
	if (xml.is_open()) {
		while (getline(xml, line)) {
			XML_Parse(parser, line.c_str(), line.size(), (int)xml.eof());
		}
	}

	xml.close();
	XML_ParserFree(parser);

	return 0;
}
