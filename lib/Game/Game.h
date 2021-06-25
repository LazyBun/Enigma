#include <BoxLock.h>

enum State {
    SoundCheck
};

class Game {
    private:
        State gameState;
        BoxLock boxLock;
    public: 
        void startGame();
        void checkState();
};