#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <climits>
//for making the files:
#include "MidiFile.h"
#include <map>
int gidMax = 25;
int max_chords=0;
//the namespace std is the namespace of the standard library  
using namespace std;
//the namespace smf is the namespace of a simple midi file library
using namespace smf;
//vi stands for a vector of integers
typedef vector<int> vi; 
//Music Vein 
// A tuple of a string that Contains:
// 1. A music cord 
// 2. a vector of integers 
// It is the representation for the creation of the midi file.
typedef tuple<string,vi> MusicVein; 
//VS is a vector of strings.
typedef vector<string> vs; 
 //VVS is a vector of a vector of strings.
typedef vector<vs> vvs;
//Generation_X is a generation of children that are stored as a tuple of the following:
//1. a vector of strings of the bestChild.
//2. a vector of strings of the secondBestChild.
//3. a integer value holding the score of the bestChild.
//4. a integer value holding the score of the secondBestChild.
typedef tuple<vs,vs,int,int> generation_x; 
//VVI is a vector of a vector of integers.
typedef vector<vi> vvi;
//This is just to make a const string into a simpler variable.
typedef const string cstr;

// this is to set up the tempo of the created song.
int tempoInput=120;
// This variable stores a list of children, where each child is represented as a vector of strings.
// Each string likely represents a musical note or chord sequence.
vvs listOfChildren;

// This variable stores a list of musical notes or chords.
// It is expected to be populated with strings representing musical elements.
vs Notes;

// This variable represents the first parent in a genetic algorithm or similar process.
// It is likely used to hold a sequence of musical notes or chords that act as a parent generation.
vs parent1;

// This variable represents the second parent in a genetic algorithm or similar process.
// Similar to 'parent1', this variable holds a sequence of musical notes or chords for breeding.
vs parent2;
map<string,vector<int>> noteMappings={
	{"C", {60, 64, 67}},      // C major
    {"Cm", {60, 63, 67}},     // C minor
    {"C7", {60, 64, 67, 70}}, // C dominant 7th
    {"Db", {61, 65, 68}},     // Db major
    {"Dbm", {61, 64, 68}},    // Db minor
    {"Db7", {61, 65, 68, 71}}, // Db dominant 7th
    {"D", {62, 66, 69}},      // D major
    {"Dm", {62, 65, 69}},     // D minor
    {"D7", {62, 66, 69, 72}}, // D dominant 7th
    {"Eb", {63, 67, 70}},     // Eb major
    {"Ebm", {63, 66, 70}},    // Eb minor
    {"Eb7", {63, 67, 70, 73}}, // Eb dominant 7th
    {"E", {64, 68, 71}},      // E major
    {"Em", {64, 67, 71}},     // E minor
    {"E7", {64, 68, 71, 74}}, // E dominant 7th
    {"F", {65, 69, 72}},      // F major
    {"Fm", {65, 68, 72}},     // F minor
    {"F7", {65, 69, 72, 75}}, // F dominant 7th
    {"Gb", {66, 70, 73}},     // Gb major
    {"Gbm", {66, 69, 73}},    // Gb minor
    {"Gb7", {66, 70, 73, 76}}, // Gb dominant 7th
    {"G", {67, 71, 74}},      // G major
    {"Gm", {67, 70, 74}},     // G minor
    {"G7", {67, 71, 74, 77}}, // G dominant 7th
    {"Ab", {68, 72, 75}},     // Ab major
    {"Abm", {68, 71, 75}},    // Ab minor
    {"Ab7", {68, 72, 75, 78}}, // Ab dominant 7th
    {"A", {69, 73, 76}},      // A major
    {"Am", {69, 72, 76}},     // A minor
    {"A7", {69, 73, 76, 79}}, // A dominant 7th
    {"Bb", {70, 74, 77}},     // Bb major
    {"Bbm", {70, 73, 77}},    // Bb minor
    {"Bb7", {70, 74, 77, 80}}, // Bb dominant 7th
    {"B", {71, 75, 78}},      // B major
    {"Bm", {71, 74, 78}},     // B minor
    {"B7", {71, 75, 78, 81}}  // B dominant 7th
};
string array1[36]={"Eb","Ebm","Eb7","D","Dm","D7","A","Am","A7","Bb","Bbm","Bb7","G","Gm","G7","F","Fm","F7","Db","Dbm","Db7","Gb","Gbm","Gb7","E","Em","E7","C","Cm","C7","B","Bm","B7","Ab","Abm","Ab7"};
/*
	Function name: set_up_notes
	Arguments: None
	Returns: void
	Function Description: Initializes the global vector `Notes` with predefined chord names.
*/
void set_up_notes(){
	for (string obj:array1){
		Notes.push_back(obj);
	}
}
/*
	Function name: generateCombinations
	Arguments: int max_notes
	Returns: vector<string>
	Function Description: Generates a vector of strings representing random musical notes and octaves based on `max_notes`.
*/
vs generateCombinations(int max_notes){
	vs  NotesToPlay;
	int octave;
		set_up_notes();
		for(int i=0;i<max_notes;i++){
		octave=rand()%8;
		NotesToPlay.push_back(to_string(octave)+Notes[rand()%Notes.size()]);
	};
	return NotesToPlay;
}
/*
Function name: printVectors
Arguments: vector<string> in
Returns: void
Function Description: Prints the contents of a vector of strings `in` to the console.
*/
void printVectors(vs in){
	cout<<"[";
	for(int i=0; i<in.size(); i++){
		cout<<in[i]<<" ";
	}
	cout<<"]";
}
/*
Function name: mutate
Arguments: vector<string> child
Returns: vector<string>
Function Description: Mutates a given `child` vector by potentially changing a random element to a different musical note and octave.
*/
vs  mutate(vs child){
	int octave=rand()%8;
	if (rand()%3==0){
		int positionToMutate=rand()%child.size();
		child[positionToMutate]=to_string(octave)+Notes[rand()%Notes.size()];
	}
	return child;
}
/*
Function name: levenshteinDistance
Arguments: const string& s1, const string& s2
Returns: int
Function Description: Computes the Levenshtein distance (edit distance) between two strings `s1` and `s2`.
*/
int levenshteinDistance(cstr& s1, cstr& s2) {
	int len1 = s1.length();
	int len2 = s2.length();
	//create a new matrix of integers with the size 
	//being equal to the (length of s1)+1 * (length of s2)+1
	vvi dp(len1 + 1, vector<int>(len2 + 1, 0));
	// Iterate over each prefix of string s1 and string s2
	for (int i = 0; i <= len1; i++) {
		for (int j = 0; j <= len2; j++) {
        	// Base case: If the prefix of s1 is empty, dp[i][j] = j (number of insertions)
			if (i == 0) {
				dp[i][j] = j;
			} 
        	// Base case: If the prefix of s2 is empty, dp[i][j] = i (number of deletions)
			else if (j == 0) {
				dp[i][j] = i;
			}
        	// Calculate edit distance using dynamic programming recurrence
			else {
            	// Determine cost of substitution (0 if characters are the same, 1 otherwise)
				int cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1;
            	// Compute minimum of three possible operations:
            	// 1. Deletion (moving up in the matrix): dp[i - 1][j] + 1
            	// 2. Insertion (moving left in the matrix): dp[i][j - 1] + 1
            	// 3. Substitution or no change: dp[i - 1][j - 1] + cost
				int deletion=dp[i - 1][j] + 1;
				int insertion=dp[i][j - 1] + 1;
				int substitution=dp[i - 1][j - 1] + cost;
				dp[i][j] = min(deletion, min(insertion,substitution));
			}
		}
	}
	return dp[len1][len2];
}
/*
Function name: chordSimilarityScore
Arguments: const string& chord1, const string& chord2
Returns: int
Function Description: Computes a similarity score between two musical chords `chord1` and `chord2` based on their Levenshtein distance.
*/
int chordSimilarityScore(cstr& chord1, cstr& chord2) {
		// Here you can define your own scoring based on chord characteristics
		// For example, compare root notes, chord type (major, minor, dominant, etc.)
		// and assign a score based on similarity
		if (chord1 == chord2) {
				return 0; // Exact match
		} else {
				return levenshteinDistance(chord1, chord2); // Use Levenshtein distance for similarity
		}
}
/*
Function name: generateChildren
Arguments: vector<string> parent1, vector<string> parent2
Returns: vector<string>
Function Description: Generates a child vector by combining elements from `parent1` and `parent2` and potentially mutating it.
*/
vs generateChildren(vs parent1,vs parent2){
	vs child;
	for (int i=0; i<parent1.size(); i++){
		if (parent1[i]==parent2[i]){
			child.push_back(parent1[i]);
		}else{
			if (rand()%2==0){
				child.push_back(parent1[i]);
			}else{
				child.push_back(parent2[i]);
			}
		}
	}
	child=mutate(child);
	return child;
}
/*
Function name: bestChildren
Arguments: vector<vector<string>>& children, const vector<string>& parent1, const vector<string>& parent2
Returns: tuple<vector<string>, vector<string>, int, int>
Function Description: Finds the best and second-best child vectors from a list of children based on similarity scores to `parent1` and `parent2`.
*/
generation_x bestChildren(vvs& children, const vs& parent1, const vs& parent2) {
    vs bestChild;
    vs secondBestChild;
    int bestScore = INT_MAX;  // Start with a large value for bestScore
    int secondBestScore = INT_MAX;  // Start with a large value for secondBestScore

    for (int i = 0; i < children.size(); i++) {
        vs child = children[i];
        int score1 = 0, score2 = 0;

        // Calculate similarity scores for the child compared to both parents
        for (int j = 0; j < child.size(); j++) {
            score1 += chordSimilarityScore(child[j], parent1[j]);
            score2 += chordSimilarityScore(child[j], parent2[j]);
        }

        // Determine the minimum score between score1 and score2
        int score = min(score1, score2);

        // Update bestChild and bestScore
        if (score < bestScore) {
            secondBestChild = bestChild;
            secondBestScore = bestScore;
            bestChild = child;
            bestScore = score;
        } else if (score < secondBestScore) {
            secondBestChild = child;
            secondBestScore = score;
        }
    }
    return make_tuple(bestChild, secondBestChild, bestScore, secondBestScore);
}
/*
Function name: generate
Arguments: vector<string>& parent1, vector<string>& parent2
Returns: void
Function Description: Generates children vectors from `parent1` and `parent2`, calculates their similarity scores, and stores them in `listOfChildren`.
*/
void generate(vs &parent1,vs &parent2){
	if (parent1==parent2){
		parent1=mutate(parent1);
		parent2=mutate(parent2);
	}
	listOfChildren.clear();
	int i = 1;
	while (i < 6) {
		vs child = generateChildren(parent1, parent2);
		// Calculate and print the score for the child
		int score = 0;
		cout << "Child " << i << ":";
		printVectors(child);
		for (int j = 0; j < child.size(); j++) {
			score += chordSimilarityScore(child[j], parent1[j]);
			score += chordSimilarityScore(child[j], parent2[j]);
		}
		cout << "\tScore: " << score << endl;
		listOfChildren.push_back(child);
		i++;
	}
}
/*
Function name: generation1
Arguments: vector<string>& parent1, vector<string>& parent2, int max
Returns: void
Function Description: Initializes `parent1` and `parent2` with randomly generated musical note combinations, calculates their initial similarity score, and initiates the first generation of children.
*/
void generation1(vs &parent1,vs &parent2,int max){
		int score=0;
		parent1=generateCombinations(max);
		parent2=generateCombinations(max);
		for (int j=0;j<parent2.size();j++){
			score += chordSimilarityScore(parent1[j], parent2[j]);
		}
		if (parent1==parent2){
			parent1=mutate(parent1);
			parent2=mutate(parent2);
		}
		cout<<"Parent1:";
		printVectors(parent1);
		cout<<"\tScore: "<<score<<endl;
		cout<<"Parent2:";
		printVectors(parent2);
		cout<<"\tScore: "<<score<<endl;
		generate(parent1,parent2);
};
/*
Function name: generation2max
Arguments: vector<string>& parent1, vector<string>& parent2
Returns: void
Function Description: Selects the best children from `listOfChildren` to become the next generation's parents, and generates subsequent children, until we get to the max generation set by main.
*/
void generation2max(vs &parent1,vs &parent2){
	int score1,score2;
	tie(parent1,parent2,score1,score2)=bestChildren(listOfChildren,parent1,parent2);
	if (parent1==parent2){
		parent1=mutate(parent1);
		parent2=mutate(parent2);
	}
	cout<<"Parent1:";
	printVectors(parent1);
	cout<<"\tScore:"<<(score1)<<endl;
	cout<<"========================================"<<endl;
	cout<<"Parent2:";
	printVectors(parent2);
	cout<<"\tScore:"<<(score2)<<endl;
	cout<<"========================================"<<endl;
	generate(parent1,parent2);
}
/*
Function name: makeMusic
Arguments: vector<string> ending_parent1, vector<string> ending_parent2
Returns: void
Function Description: Creates MIDI files based on the `ending_parent1` and `ending_parent2` musical note vectors.
*/
void makeMusic(vs ending_parent1, vs ending_parent2){
	cout<<"Making the Music file for each ending music vector."<<endl;
	cout<<"Vector 1:";
	printVectors(ending_parent1);
	cout<<endl;
	cout<<"Vector 2:";
	printVectors(ending_parent2);
	cout<<endl;
	MidiFile midiFile;
	for(int i=0; i<ending_parent1.size();i++){
		int track = 0;
		midiFile.addTracks(1);
		midiFile.addTempo(track, 0, tempoInput);
		int startTime = 0;
		int ticksPerMeasure = midiFile.getTicksPerQuarterNote();
		for (i=0; i<ending_parent1.size(); i++){
			int octave = ending_parent1[i][0]-'0';
			string chordName = ending_parent1[i].substr(1);
       		// Get MIDI note numbers for the chord
			vi notes=noteMappings[chordName];
        	// Add note-on events for each note in the chord
            for (int note : notes) {
            	midiFile.addNoteOn(track, startTime, 0, note, 64); // Add note-on event
            	midiFile.addNoteOff(track, startTime + ticksPerMeasure, 0, note); // Add note-off event at end of bar
			}
       		// Advance the start time for the next chord
        	startTime += ticksPerMeasure; // Move one quarter note forward (assuming 120 BPM)
		}
	}
	MidiFile midiFile2;
	for(int i=0; i<ending_parent2.size();i++){
		int track = 0;
		midiFile2.addTracks(1);
		midiFile2.addTempo(track, 0, tempoInput);
		int startTime = 0;
		int ticksPerMeasure = midiFile2.getTicksPerQuarterNote();
		for (i=0; i<ending_parent2.size(); i++){
			int octave = ending_parent2[i][0]-'0';
			string chordName = ending_parent2[i].substr(1);
       		// Get MIDI note numbers for the chord
			vi notes=noteMappings[chordName];
        	// Add note-on events for each note in the chord
            for (int note : notes) {
            	midiFile2.addNoteOn(track, startTime, 0, note, 64); // Add note-on event
            	midiFile2.addNoteOff(track, startTime + ticksPerMeasure, 0, note); // Add note-off event at end of bar
			}
       		// Advance the start time for the next chord
        	startTime += ticksPerMeasure; // Move one quarter note forward (assuming 120 BPM)
		}
	}
	cout<<endl;
	cout<<"MIDI File 1: Final Child 1: Sorting track:"<<endl;
		midiFile.sortTracks(); 
	cout<<"MIDI File 1: Final Child 1: Writing track:"<<endl;
		midiFile.write("Final_Child1.mid");
	cout<<"MIDI File 2: Final Child 2: Sorting track:"<<endl;
		midiFile2.sortTracks();
	cout<<"MIDI File 2: Final Child 2: Writing track:"<<endl;
		midiFile2.write("Final_Child2.mid");
}
/*
Function name: main
Arguments: int argc, char * argv[]
Returns: int
Function Description: The main entry point of the program, which initializes settings, performs generations of musical note combinations, and produces MIDI files for the best children.
*/
int main(int argc,char * argv[]) {
	if (argc==1){
		max_chords=8;
		gidMax=25;
		tempoInput=120;
	}else if (argc==2){
		max_chords=atoi(argv[1]);
		gidMax=25;
		tempoInput=120;
	}else if(argc==3){
		max_chords=atoi(argv[1]);
		gidMax=atoi(argv[2]);
		tempoInput=120;
	}else if (argc==4){
		max_chords=atoi(argv[1]);
		gidMax=atoi(argv[2]);
		tempoInput=atoi(argv[3]);
	}else{
		cerr<<"Error: Too many arguments. Arguments should be at most 4 arguments."
		<<"\n1:Program out file:\t\t\t\t\t\t"<<argv[0]
		<<"\n2:Max Chords(optional: defaults to 8)\t\t\t\t"<<argv[1]
		<<"\n3:Max Number of DE Generations: (optional: defaults to 25)\t"<<argv[2]
		<<"\n4:Tempo of the song(optional: defaults to 120 bpm) \t\t"<<argv[3]
		<<endl;
		return -1;
	}
	cout<<"========================================"<<endl;
	cout<<"Using the following settings:"<<endl;
	cout<<"========================================"<<endl;
	cout<<"1: Max Chords: "<<max_chords<<endl;
	cout<<"2: Max Number of DE Generations: "<<gidMax<<endl;
	cout<<"3: Tempo of the songs generated: "<<tempoInput<<endl;
	cout<<"========================================"<<endl;



	srand(time(NULL));
	int generation_id=1;
	while (generation_id<=gidMax+1){
		if (generation_id==1){
			cout<<"========================================"<<endl;
			cout<<"Generation "<<generation_id<<endl;
			cout<<"========================================"<<endl;
			generation1(parent1, parent2,max_chords);
			cout<<"========================================"<<endl;
		}
		else if(generation_id<gidMax+1){
			cout<<"========================================"<<endl;
			cout<<"Generation "<<generation_id<<endl;
			cout<<"========================================"<<endl;
			generation2max(parent1, parent2);
			cout<<"========================================"<<endl;
		}
		else if(generation_id==gidMax+1){
			cout<<"Best children:(After "<<generation_id-1<<" generations)"<<endl;
			int score1=0;
			int score2=0;
			tie(parent1,parent2,score1,score2)=bestChildren(listOfChildren,parent1,parent2);
			printVectors(parent1);
			cout<<"Score: "<<score1<<endl;
			cout<<"========================================"<<endl;
			printVectors(parent2);
			cout<<"Score: "<<score2<<endl;
			cout<<"========================================"<<endl;
			makeMusic(parent1,parent2);
		}
		generation_id+=1;
	}
	return 0;
}

