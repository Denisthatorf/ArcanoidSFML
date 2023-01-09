#include "defines.hpp"
#include <memory>

struct Stats
{
private:
    static std::unique_ptr<Sprite> heart_sprite;

public:
    static void initSprites(float k);

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
