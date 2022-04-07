#include "RunTSP.h"
#include "DynamicProgramming.h"
#include "NaiveBruteForce.h"
#include "Node.h"
#include <iostream>
#include <fstream>

using namespace std;

RunTSP::RunTSP() {
    load();
}

RunTSP::~RunTSP() {
    delete naiveBF;
    delete dynamicProg;
}

void RunTSP::load() {
    string file1 = "Data\\Graph\\graph.txt";
    //stores graph.txt
    string file2 = "Data\\Graph\\positions.txt";
    //stores positions.txt

    src.setData(1);
      //sets source node equal to 1

    ifstream file(file1);
    if(!file){
        cout << "Could not load " << file1 << endl;
        perror ( "Stream Failed to open because: " );
        return;
    }  //prints error statement if file can't be loaded in

    else if(file.is_open()) {
        string source, destination, token;
        string delim = ",";
        size_t pos = 0;

        while (getline(file, source, ',')) {
            Node temp(stoi(source));
            //read in source node
            int x = stoi(source);

            getline(file, destination);
            //gets connected nodes
            while ((pos = destination.find(delim)) != string::npos) {
                token = destination.substr(0, pos);
                temp.setConnections(Node(stoi(token)));
                destination.erase(0, pos + delim.length());
                //adds connected nodes to connectedNodes vector
            }
            temp.setConnections(Node(stoi(destination)));
            //add last int in list to vector
            graph.insert({x, temp});
        }
    }
    file.close();

    file.open(file2);
    if (file.is_open()) {
        string source;
        //holds int value of source node
        string x, y, z;
        //holds position value of source
        while (getline(file, source, ',') && getline(file, x, ',') && getline(file, y, ',') && getline(file, z, '\n')) {
            (graph)[stoi(source)].setPosition(stoi(x), stoi(y), stoi(z));
            //add position to source node
            if((graph)[stoi(source)].getData() == src.getData()) {
                src.setPosition(stoi(x), stoi(y), stoi(z));
            } else if((graph)[stoi(source)].getData() == dest.getData()) {
                dest.setPosition(stoi(x), stoi(y), stoi(z));
            }  //if/else statement sets position of src and dest node once that node is found
        }
    }
    file.close();
}

void RunTSP::execute() {
    chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();

      //executes the different algorithms
    if(algoExecute == 0 || algoExecute == 1) {
        if (algoExecute == 0) {
              //run TSP Naive
            NaiveBruteForce::NaiveAlgo(graph, src);
            lowestDistance = NaiveBruteForce::returnCost();
            numIterations = NaiveBruteForce::returnIterations();
            bestPath = NaiveBruteForce::returnPath();
        } else if (algoExecute == 1) {
              //run TSP Dynamic
            DynamicProgramming::load(graph, 1);
            DynamicProgramming::DynamicAlgo(src);
            lowestDistance = DynamicProgramming::returnCost();
            numIterations = DynamicProgramming::returnIterations();
            bestPath = NaiveBruteForce::returnPath();
        }
    }
    chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
    runTime = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
}


void RunTSP::display() {
    cout << "Path: " << "1";

    for(int n : bestPath) {
        cout << " -> " << n;
    }  //loops through vector and outputs path
    cout << " -> " << "1" << endl;
}

void RunTSP::stats() {
    if(algoExecute == 0) {
        cout << "--------STATS FOR NAIVE BRUTE FORCE--------" << endl;
    } else {
        cout << "--------STATS FOR DYNAMIC PROGRAMMING--------" << endl;
    }
    display();
      //calls display function which actually displays the path
    cout << "Number of Nodes in path: " << graph.size()+1 << endl;
    cout << "Time: " << runTime.count() << endl;
    cout << "Distance: " << lowestDistance << endl;
    cout << "Iterations: " << numIterations << endl << endl;
}

void RunTSP::select(int x) {
    algoExecute = x;
}
