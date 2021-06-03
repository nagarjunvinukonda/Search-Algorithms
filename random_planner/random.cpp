#include <array>
#include <random>
#include <queue>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

/*
*Design of random search planner
* @param world_state, robot_pose, goal_pose
*/

//Time complexity = opeartions*(sqrt(max_number_of_steps)^1.5)
// It depends on max_no.of steps

vector<array<int, 2>> search(vector<vector<int>> world_state, array<int, 2> robot_pose, array<int, 2> goal_pose) {
    int rows = world_state.size();
    int cols = world_state[0].size();

    deque<array<int, 2>> history;
    queue<array<int, 2>> q;
    q.push(robot_pose);

    // considering max_number_of_steps to plan the path
    // create a history memory to plan within max no.of steps. 
    int max_number_of_steps = 10;
    int max_history = static_cast<int>(sqrt(max_number_of_steps));

    vector<array<int, 2>> path;
    path.push_back(robot_pose);

    vector<array<int, 2>> moves = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
    while (max_number_of_steps--) {
        array<int, 2> u = path[path.size() - 1];

        if (u[0] == goal_pose[0] && u[1] == goal_pose[1]) {
            return path;
        }

        vector<array<int, 2>> options;

        // making options in for all the four direction. 
        for (const array<int, 2> &move : moves) {
            array<int, 2> neighbor = {move[0] + u[0], move[1] + u[1]};
           
            if (neighbor[0] < 0 || neighbor[0] >= rows || neighbor[1] < 0 || neighbor[1] >= cols) {
                continue;
            }
            if (world_state[neighbor[0]][neighbor[1]] == 0) {
                options.push_back(neighbor);
            }
        }

        // checking if the neighbour is already avaible in history memory, if not then add into avilable options to move ahead.

        vector<array<int, 2>> available_options;
        for (const array<int, 2> &option : options) {
            bool flag = true;
            for (const array<int, 2> &cell : history) {
                if (option[0] == cell[0] && option[1] == cell[1]) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                available_options.push_back(option);
            }
        }

        // moving in random direction with the avilable options and adding them into history. If the history size is more than max size then pop the old history.

        if (available_options.size() > 0) {
            shuffle(available_options.begin(), available_options.end(), std::mt19937{std::random_device{}()});
            history.push_back(available_options[0]);
            if (history.size() > max_history) {
                history.pop_front();
            }

            path.push_back(available_options[0]);
        } else {
            if (options.size() == 0) {
                return {};
            } else {
                shuffle(options.begin(), options.end(), std::mt19937{std::random_device{}()});
                history.push_back(options[0]);
                if (history.size() > max_history) {
                    history.pop_front();
                }
                path.push_back(options[0]);
            }
        }


    }
    return {};
}


// int main(int argc, char *argv[]) {
//     vector<vector<int>> world_state = {{0,0,1,0,0},
//                                         {0,0,1,0,0},
//                                         {0,0,0,0,1},
//                                         {0,0,1,0,0}};  

//     array<int, 2> start = {0, 0};
// 	array<int, 2> goal = {3, 4};
//     vector<array<int, 2>> path = search(world_state, start, goal);
    
//     for (const array<int, 2> &cell : path) {
//         cout << cell[0] << ' ' << cell[1] << '\n';
//     }

//     return 0;
// }