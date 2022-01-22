//  Lottery draw generator.

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
