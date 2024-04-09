# Music-Generation-using-Genetic-Algorithms

This program demonstrates a genetic algorithm approach to generate musical sequences and produce MIDI files based on evolving musical patterns.

# Overview

The project implements a genetic algorithm that evolves sequences of musical notes (chords) over multiple generations. The genetic algorithm follows these key steps:

# Initialization:
Initializes settings such as maximum number of chords, maximum number of generations, and tempo.
Defines a set of musical chord mappings used for generating and evaluating sequences.
## Parent Generation:
Generates an initial population of parent sequences (parent1 and parent2) consisting of randomly generated musical note combinations.
## Evolutionary Process:
Iteratively applies genetic operations (crossover and mutation) to generate new sequences (children) from parent sequences.
Evaluates and selects the best-performing children based on similarity scores to parent sequences.
## MIDI File Creation:
Produces MIDI files (Final_Child1.mid and Final_Child2.mid) based on the best-performing children sequences obtained after the specified number of generations.
# Usage

## Prerequisites

C++ compiler supporting C++11 or later.
Standard Template Library (STL) 
Standard MIDI File(SMF) from 
External Library MidiFile.h for MIDI file manipulation.

## Compilation
Compile the program using a C++ compiler:

g++ -o music_genetic_algorithm main.cpp

## Execution

### Run the compiled program with optional command-line arguments:
 ./music_genetic_algorithm [max_chords] [max_generations] [tempo_bpm]
 [max_chords]: Maximum number of musical chords in each sequence (default: 8).
 [max_generations]: Maximum number of generations to evolve sequences (default: 25).
 [tempo_bpm]: Tempo (beats per minute) for the generated MIDI files (default: 120 BPM).
 #### Example
 ./music_genetic_algorithm 10 20 100
  
  This command runs the genetic algorithm with 10 chords per sequence, evolving over 20 generations,   and sets the tempo to 100 BPM.

# File Structure

### main.cpp: 
 Main source code implementing the genetic algorithm.
### MidiFile.h: 
 External library for MIDI file manipulation.
### README.md: 
 Documentation file providing an overview of the project and usage instructions.
# Credits
 This project utilizes concepts from genetic algorithms and MIDI file manipulation.
 The MidiFile.h library is used for creating and manipulating MIDI files.
# License

This project is licensed under the BSD license.
