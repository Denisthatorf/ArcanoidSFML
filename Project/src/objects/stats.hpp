#include "defines.hpp"

struct Stats
{
private:
    static Sprite* heart_sprite;

public:
    static void initSprites(float k);
    static void destroySprites();

    int score = 0;
    int destroyed_in_row = 0;
    int lives = 1;
    int margin = 0;
	bool isStarted = false;
    vector2d<int> end_position;

    void draw();
    void plusForScore();
    void setBorder(vector2d<int> border_pos, int margin);
};