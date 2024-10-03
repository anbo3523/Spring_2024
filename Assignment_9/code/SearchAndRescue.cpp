#include "SearchAndRescue.hpp"
#include <vector>
#include <stack>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;


SearchAndRescue::SearchAndRescue(string fileName)
{
    terrain = new int*[4];
    string line;
    ifstream infile(fileName);
    if (infile.is_open())
    {
        for(int i = 0; getline(infile, line); i++)
        {   
            terrain[i] = new int[4];
            stringstream ss(line);
            string s;
            for (int j = 0; getline(ss, s, ' '); j++)
            {
                terrain[i][j] = stoi(s);
            }
        }
    }
    path = vector<State*>();
}


SearchAndRescue::~SearchAndRescue()
{
    State* to_del = path.back();
    delete to_del;
    path.pop_back();

    for (int i = 0; i < 4; i++)
    {
        delete terrain[i];
    }
    delete terrain;
}


void SearchAndRescue::possibleActions(State* current)
{
    current->possible_actions.clear();
    if (current->y < 3) current->possible_actions.push_back("up");    // Can move up if not on the top edge
    if (current->y > 0) current->possible_actions.push_back("down");  // Can move down if not on the bottom edge
    if (current->x > 0) current->possible_actions.push_back("left");  // Can move left if not on the left edge
    if (current->x < 3) current->possible_actions.push_back("right"); // Can move right if not on the right edge
}
  


State* SearchAndRescue::result(State* current, string action)
{
    int newX = current->x, newY = current->y;

    if (action == "up" && newY < 3) {
        newY++;
    } else if (action == "down" && newY > 0) {
        newY--;
    } else if (action == "left" && newX > 0) {
        newX--;
    } else if (action == "right" && newX < 3) {
        newX++;
    }

    vector<string> newActions = current->possible_actions; // Copy the current action sequence
    newActions.push_back(action); // Add the new action

    State* newState = new State{newX, newY, current->saved_people, action, newActions};

    if (newX >= 0 && newX < 4 && newY >= 0 && newY < 4) {
        if (terrain[newX][newY] == 2) newState->saved_people++;
    }

    return newState;
}


vector<State*> SearchAndRescue::expand(State* current)
{
    possibleActions(current);
    vector<State*> expansion;
    for (const auto& action : current->possible_actions) {
        State* newState = result(current, action);
        // Ensure newState is valid before adding it to expansion.
        if (newState->x >= 0 && newState->x < 4 && newState->y >= 0 && newState->y < 4) {
            expansion.push_back(newState);
        } else {
            delete newState;  // Clean up newState if it's out of bounds.
        }
    }
    return expansion;
}


bool SearchAndRescue::iterativeDeepeningWrapper(State* start)
{
    const int MAX_DEPTH = 20; // Define a maximum depth.
    for (int depth_limit = STARTING_DEPTH; depth_limit <= MAX_DEPTH; ++depth_limit) {
        path.clear(); // Clear the path for each new iteration.
        if (iterativeDeepeningSearch(start, depth_limit)) {
            // Manually reverse the path
            int n = path.size();
            for (int i = 0; i < n / 2; i++) {
                std::swap(path[i], path[n - i - 1]);
            }
            return true; // The goal has been found within the current depth limit.
        }
        // Otherwise, increase the depth limit and try again.
    }
    return false;
}



bool SearchAndRescue::iterativeDeepeningSearch(State* current, int depth_limit)
{
    if (depth_limit == 0) return false; // Depth limit reached, cannot go deeper.

    // Avoid re-adding the starting state or a state that is already on the path
    if (!path.empty() && current->x == path.back()->x && current->y == path.back()->y) {
        return false;
    }

    if (isGoal(current)) {
        path.push_back(current); // Goal state found, add current state to path and return true.
        return true;
    }

    path.push_back(current); // Add the current state to the path.

    vector<State*> successors = expand(current); // Expand the current state to get successors.
    for (State* nextState : successors) {
        // Skip if nextState is the same as the current state, which can happen if expand does not consider the previous action.
        if (nextState->x == current->x && nextState->y == current->y) {
            delete nextState; // This nextState is not a valid move, so delete it.
            continue;
        }

        // Recurse with the new state and a decremented depth limit.
        if (iterativeDeepeningSearch(nextState, depth_limit - 1)) {
            // If you find the goal, there's no need to delete nextState here; it's part of the path now.
            return true; // Success! The goal was found in the subtree rooted at nextState.
        }

        // nextState did not lead to the goal, so delete it.
        delete nextState; // Clean up memory.
    }

    // If none of the successors lead to the goal, remove the current state from the path.
    // This must be a separate step after trying all successors, to avoid deleting the current state prematurely.
    if (!path.empty() && path.back() == current) {
        path.pop_back(); // Remove the last state added to the path, which is current.
    }

    return false;
}





void SearchAndRescue::printPath()
{
    for (const auto& state : path) {
        cout << "x: " << state->x << "\ty: " << state->y << "\tprev_action: " << state->prev_action << "\n";
    }
}



bool SearchAndRescue::isGoal(State* current)
{
    return terrain[current->x][current->y] == 3 && current->saved_people == PEOPLE_TO_SAVE;
}


void SearchAndRescue::printTerrain()
{
    // Transpose and flip vertically
    for (int i = 3; i >= 0; i--) {  // Vertically flipped
        for (int j = 0; j < 4; j++) {  // Transposed
            cout << terrain[j][i] << " ";
        }
        cout << endl;
    }
}
