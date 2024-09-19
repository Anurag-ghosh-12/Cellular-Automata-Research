#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <map>

using namespace std;

/**
 * Function to apply Rule 90 in cellular automata.
 * Rule 90 computes the next state of a cell based on its left and right neighbors.
 * 
 * @param left The state of the left neighbor.
 * @param center The state of the current cell (not used in Rule 90).
 * @param right The state of the right neighbor.
 * @return The new state of the cell (either 0 or 1).
 */
int rule90(int left, int center, int right)
{
    return (left + right) % 2;
}

/**
 * Function to apply Rule 150 in cellular automata.
 * Rule 150 computes the next state of a cell based on its left, center, and right neighbors.
 * 
 * @param left The state of the left neighbor.
 * @param center The state of the current cell.
 * @param right The state of the right neighbor.
 * @return The new state of the cell (either 0 or 1).
 */
int rule150(int left, int center, int right)
{
    return (left + center + right) % 2;
}

/**
 * Simulate the evolution of a cellular automaton over one time step.
 * Applies alternating rules (90 or 150) depending on the index of the cell.
 * 
 * @param initial The initial state of the cellular automaton.
 * @param rules A vector containing two integers representing the alternating rules (90 and 150).
 * @return The new state of the cellular automaton after one iteration.
 */
vector<int> simulateCA(const vector<int> &initial, const vector<int> &rules)
{
    int size = initial.size();      // Size of the automaton (number of cells)
    vector<int> current = initial;  // Current state of the automaton
    vector<int> next(size);         // Stores the next state of the automaton

    // Iterate over each cell in the automaton
    for (int i = 0; i < size; ++i)
    {
        // Get the left, center, and right neighbors (boundary cells have neighbors set to 0)
        int left = (i == 0) ? 0 : current[i - 1];
        int center = current[i];
        int right = (i == size - 1) ? 0 : current[i + 1];

        // Apply Rule 90 or Rule 150 depending on the index (even or odd)
        if (i % 2 == 0)
        {
            next[i] = (rules[0] == 90) ? rule90(left, center, right) : rule150(left, center, right);
        }
        else
        {
            next[i] = (rules[1] == 90) ? rule90(left, center, right) : rule150(left, center, right);
        }
    }

    return next;
}

/**
 * Check if a cellular automaton has maximal length.
 * A cellular automaton is considered "maximal length" if it cycles through all possible
 * unique states before repeating.
 * 
 * @param size The size of the cellular automaton (number of cells).
 * @param rules A vector containing two integers representing the alternating rules (90 and 150).
 * @return A pair containing a boolean indicating whether the automaton is maximal length,
 *         and the total number of unique states visited.
 */
pair<bool, int> isMaximalLength(int size, const vector<int> &rules)
{
    unordered_set<string> uniqueStates;  // Stores unique states of the automaton as strings
    vector<int> initial(size, 0);        // Initial state (all 0s, except the first cell is 1)
    initial[0] = 1;                      // Seed the initial state with a single '1'

    map<string, int> stateIndices;       // Maps state strings to their indices (step count)
    int count = 0;                       // Count of unique states visited

    // Convert the initial state to a string and add it to the set of unique states
    string temp = "";
    for (int cell : initial)
    {
        temp += to_string(cell);
    }
    uniqueStates.insert(temp);

    // Simulate the evolution of the automaton until we revisit a state
    for (int step = 0;; ++step)
    {
        // If all cells are 0, check if we have visited all possible states
        if (initial == vector<int>(size, 0))
        {
            if (count == (1 << size) - 1)
            {
                return {true, (1 << size) - 1};  // Maximal length if all states are visited
            }
            else
            {
                return {false, count};  // Not maximal if not all states are visited
            }
        }

        // Simulate the next state of the automaton
        initial = simulateCA(initial, rules);
        string state = "";
        for (int cell : initial)
        {
            state += to_string(cell);
        }

        // If the state is not all zeros, add it to the set of unique states
        if (state != string(size, '0'))
        {
            if (stateIndices.find(state) != stateIndices.end())
            {
                if (count == (1 << size) - 1)
                {
                    return {true, (1 << size) - 1};  // Maximal length reached
                }
                else
                {
                    return {false, count};  // Repeating state detected before maximal length
                }
            }
            else
            {
                count++;
                stateIndices[state] = step;
                uniqueStates.insert(state);
            }
        }
    }
}

/**
 * Main function that prompts the user for the size of the automaton and
 * checks if various rule sequences lead to a maximal-length automaton.
 */
int main()
{
    int size;
    cout << "Enter the maximum size of the lattice for which record reqd: ";
    cin >> size;

    // Define two rule sequences: alternating starting with Rule 90 or Rule 150
    vector<vector<int>> ruleSequences = {
        {90, 150}, // Alternating starting with Rule 90
        {150, 90}  // Alternating starting with Rule 150
    };

    // Print header for the output table
    cout << "Rule Type\t\tSize\tMaximal Length\tChain Length\n";
    cout << "---------------------------------------------------------\n";

    // Iterate over different lattice sizes and rule sequences
    for (int s = 2; s <= size; s += 2)
    {
        for (const auto &rules : ruleSequences)
        {
            // Check if the cellular automaton is maximal-length
            pair<bool, int> result = isMaximalLength(s, rules);
            bool maximal = result.first;
            int chainLength = result.second;

            // Print the result for each rule sequence
            string ruleType = (rules[0] == 90) ? "90-150-90..." : "150-90-150...";
            cout << ruleType << "\t" << s << "\t" << (maximal ? "Yes" : "No") << "\t\t" << chainLength << "\n";
        }
    }

    return 0;
}
