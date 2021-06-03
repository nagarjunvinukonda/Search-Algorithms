#include "astar.cpp"
#include <fstream>
#include <sstream>
using std::ifstream;
using std::istringstream;


bool TestSearchTestCase(vector<vector<int>> test_case,vector<vector<int>>test_solution){
    if(test_case==test_solution){
        return true;
    }
    else{
        return false;
    }
}


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


void TestHeuristic() {
    cout << "----------------------------------------------------------"
         << "\n";
    cout << "Heuristic Function Test: ";
    path p3;
    if (p3.euclideanDistance(4, 0, 6, 9) != 9) {
        cout << "failed"
             << "\n";
        cout << "\n"
             << "Heuristic(1, 2, 3, 4) = " << p3.euclideanDistance(4, 0, 6, 9) << "\n";
        cout << "Correct result: 4"
             << "\n";
        cout << "\n";
    } else {
        cout << "passed"
             << "\n";
    }

}



void TestSearch(){

    array<int,2>test_start1 = {4, 0};
	array<int,2>test_goal1 = {6, 9};
    array<int,2>test_start2 = {0, 0};
	array<int,2>test_goal2 = {3, 4};

    vector<vector<int>> test_1= ReadBoardFile("C:/Users/NAGARJUN/Desktop/Vinukonda_Nagarjun/1.board");
    vector<vector<int>> test_2= ReadBoardFile("C:/Users/NAGARJUN/Desktop/Vinukonda_Nagarjun/2.board");
    vector<vector<int>> test_3= ReadBoardFile("C:/Users/NAGARJUN/Desktop/Vinukonda_Nagarjun/3.board");


    vector<vector<int>>test_solution_1 = {{4,0},{4,1},{4 ,2},{4 ,3},{5 ,3},{5, 4},{5, 5},{6, 5},{6 ,6},{6 ,7},{5, 7},{5 ,8},{5 ,9},{6 ,9}};
    vector<vector<int>>test_solution_2;
    vector<vector<int>>test_solution_3 = {{0, 0},{0, 1},{0, 2},{0, 3},{1, 3},{1, 4},{2, 4},{3, 4}};

    path p2_1,p2_2,p2_3;

    vector<vector<int>>test_path1 = p2_1.search(test_1,test_start1, test_goal1);
    vector<vector<int>>test_path2 = p2_2.search(test_2,test_start1, test_goal1);
    vector<vector<int>>test_path3 = p2_3.search(test_3,test_start2, test_goal2);

    bool test_case1 = TestSearchTestCase(test_path1,test_solution_1);
    bool test_case2 = TestSearchTestCase(test_path2,test_solution_2);
    bool test_case3 = TestSearchTestCase(test_path3,test_solution_3);


    if(test_case1&& test_case2 && test_case3){
        cout << "----------------------------------------------------------"
        << "\n";
        cout << "Search Function Test: ";
        cout<<"passed"<<endl;

    }
    else{
        cout << "----------------------------------------------------------"<<endl;
        cout<< "Search Function Test: "<<" "<<"failed"<<endl;

        cout<<"test_case1:";
        for(vector<int> i: test_path1){
            cout<<i[0]<<" "<<i[1]<<"|";
        }

        cout<<"\n"<<"test_case2:";
        for(vector<int> i: test_path2){
            cout<<i[0]<<" "<<i[1]<<"|";
        }

        cout<<"\n"<<"test_case3:";
        for(vector<int> i: test_path3){
            cout<<i[0]<<" "<<i[1]<<"|";
        }
    }

}

void TestCompare() {
    cout <<"----------------------------------------------------------"<< "\n";
    cout << "Compare Function Test: ";

    path::node* point1  = new path::node;
    path::node* point2  = new path::node;
    point1->f = 10;
    point2->f = 12;

    path p1;

    p1.open.push(point1);
    p1.open.push(point2);

    path::node* t = p1.open.top();

    if(t->f !=10){

        cout << "failed"
        << "\n";
        cout << "\n"
        << "temp = "<<t->f;
    
    }
    else if(t->f ==10){
        cout << "passed"
        << "\n";

    }
    else{
        cout << "failed"
        << "\n";
        cout << "\n"
        << "temp = "<<t->f;
    }

   
}


void TestInput() {
    cout <<"----------------------------------------------------------"<< "\n";
    cout << "Input Function Test: ";

    vector<vector<int>> test_1= ReadBoardFile("C:/Users/NAGARJUN/Desktop/Vinukonda_Nagarjun/1.board");

    vector<vector<int>> test_2;
    
    int i_1 = 0;
    int j_1 = 5;
    int i_2 = -1;
    int j_2 = 3;

    path p1;
    if(p1.IsValidInput(i_1, j_1, test_1) && !p1.IsValidInput(i_2, j_2, test_2) ){

        cout << "passed"<< "\n";

    }
    else{

        cout<<"failed"<<"\n";
    }
   
}



int main()
{

    TestHeuristic();

    TestSearch();

    TestCompare();

    TestInput();


	return 0; 
	
}



