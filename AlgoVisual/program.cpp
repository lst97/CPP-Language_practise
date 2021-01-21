#include "splashkit.h"
#include "algovisual.h"
#include <time.h>

#define LIST_SIZE 50
#define HEIGHT 400
#define WIDTH 600
#define RAND_MAX (HEIGHT - TEXT_RESERVED)
// golbal

int main() {
    
    window wind = open_window("AlgoVisual(BubbleSort) - lst97", WIDTH, HEIGHT);
    srand(time(NULL));

    int numlist[LIST_SIZE];

    for (int ecx = 0; ecx < LIST_SIZE; ecx++){
        numlist[ecx] = rand() % RAND_MAX + 1;
    }

    AlgoVisual av(numlist, LIST_SIZE, wind);
    if (av.start() == -1){
        // Error: Not enough screen space.
        return 0;
    }
    return 0;
}

