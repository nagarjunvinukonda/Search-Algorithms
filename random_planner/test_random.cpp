#include "random.cpp"
#include <fstream>
#include <sstream>
using std::ifstream;
using std::istringstream;

/**
 * Parse the string (with consecutive number and comma).
 * @param line The string 
 */
vector<int> ParseLine(string line) {
    istringstream sline(line);
    int n;
    char c;
    vector<int> row;
    while (sline >> n >> c && c == ',') {
        if (n == 0) {
            row.push_back(0);
        } else {
            row.push_back(1);
        }
    }
    return row;
}


/**
 * Read the text file.
 * @param path The path to the file
 */
vector<vector<int>> ReadBoardFile(string path) {
    ifstream myfile(path);
    vector<vector<int>> board{};
    if (myfile) {
        string line;
        while (getline(myfile, line)) {
            vector<int> row = ParseLine(line);
            board.push_back(row);
        }
    } else {
        cout << "File \"" << path << "\" not exists!" << endl;
        return vector<vector<int>>{};
    }
    return board;
}




bool IsValidInput(int i, int j, vector<vector<int>> map) {

    if(map.empty()){
		// cout<<"Input Map is Empty"<<endl;
		return false;
	}

	bool res = true;
	bool verbose =false;

    if (i < 0 || i > map.size()-1) {
		verbose = true;
        if (verbose)
            // cout << "Input x coord is invalid" << endl;
        res = false;
    }
    if (j < 0 || j > map[1].size()-1) {
		verbose = true;
        if (verbose)
            // cout << "Input y coord is invalid" << endl;
        res = false;
    }
    return res;
    
}



/**
 * Check if the x, y coordinates are valid
 * @param x X coordinate (row)
 * @param y Y coordinate (col)
 * @param grid The grid
 */


void TestValidInput(){

    vector<vector<int>> test_1= ReadBoardFile("/home/nagarjunv/Desktop/Brain_Corp/brain_final/1.board");

    vector<vector<int>> test_2 = ReadBoardFile("/home/nagarjunv/Desktop/Brain_Corp/brain_final/1.board");

    vector<vector<int>> test_3;

    int i_1 = 0;
    int j_1 = 2; 

    int i_2 = -1;
    int j_2 = 3;

    if(IsValidInput( i_1, j_1, test_1) && !IsValidInput( i_2, j_2, test_2) && !IsValidInput( i_1, j_1, test_3)){

        cout << "----------------------------------------------------------"
        << "\n";
        cout << "ValidInput Function Test: ";
        cout<<"passed"<<endl;

    }
    else{

        cout << "----------------------------------------------------------"
        << "\n";
        cout << "ValidInput Function Test: ";
        cout<<"failed"<<endl;

    }

}


void TestSearch(){

    vector<vector<int>> test_1= ReadBoardFile("/home/nagarjunv/Desktop/Brain_Corp/brain_final/3.board");

    array<int, 2> start = {1, 0};
	array<int, 2> goal = {3, 4};
    vector<array<int, 2>> path = search(test_1, start, goal);

    vector<array<int,2>>test_solution_1 = {{0, 0},{0, 1},{0, 2},{0, 3},{1, 3},{1, 4},{2, 4},{3, 4}};

    if(path.empty()){
        cout << "----------------------------------------------------------"
        << "\n";
        cout << "Search Function Test: ";
        cout<<"failed"<<endl;
    }
    else if(path==test_solution_1){
        cout << "----------------------------------------------------------"
        << "\n";
        cout << "Search Function Test: ";
        cout<<"passed: perfect solution"<<endl;

    }
    else{
        cout << "----------------------------------------------------------"
        << "\n";
        cout << "Search Function Test: ";
        cout<<"passed"<<endl;
    }

}



int main(int argc, char *argv[]) {

    // Note: The serach algorithm sometimes might fail due to its a random planner.

    TestSearch();

    TestValidInput();

    return 0;
}