/*  High quality lottery draw generator.

    Produces very normalized distributions of random numbers over even
    small sets of draws (~10,000).

    This program selects shuffled numbers from highly random positions
    to simulate drawn objects from a mechanical device.

    In a lottery, distinct, abstract objects are chosen, not numbers.
    A lottery number is an object's identification. Therefore, examining
    order, intervals, primality, evenness, oddness, or any other numeric
    patterns and properties is a waste of time.

    Default 6-49 draw, but can be modified to many other lotteries.
*/

#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include <algorithm>

#define DRAWSIZE 49
#define DRAWNUMS 6
#define DRAWS 10
#define SHUFFLES 3

using namespace std;

int getRandomIndex(int endIndex) {

    mt19937 mt(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> dist(0, endIndex);

    return dist(mt);
}

void shuffleVector(vector<int> &drawNums) {

    for(int i = 1; i <= SHUFFLES; i++) {
        unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
        shuffle(drawNums.begin(), drawNums.end(), default_random_engine(seed));
    }
}

int main() {

    for(int i = 1; i <= DRAWS; i++) {

        int endIndex = DRAWSIZE - 1;
        vector<int> drawNums;
        int drawResult[DRAWNUMS];

        for(int i = 1; i <= DRAWSIZE; i++)
            drawNums.push_back(i);

        for(int i = 1; i <= DRAWNUMS; i++) {

            shuffleVector(drawNums);

            int randIndex = getRandomIndex(endIndex);
            int valAtIndex = drawNums.at(randIndex);
            drawResult[i - 1] = valAtIndex;
            drawNums.erase(drawNums.begin() + randIndex);
            endIndex--;
        }

        sort(drawResult, drawResult + DRAWNUMS);

        for (int i = 0; i < DRAWNUMS; i++)
            cout << drawResult[i] << " ";
        cout << endl;
    }

    return 0;
}
