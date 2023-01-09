#include "Framework.h"

#include "defines.hpp"

#include "logger.hpp"

#include "core/vector2d.hpp"
#include "core/collision.hpp"

#include "objects/player.hpp"
#include "objects/ball.hpp"
#include "objects/block_types.hpp"
#include "objects/stats.hpp"
#include "objects/boost.hpp"
#include "objects/map.hpp"

#include <vector>
#include <algorithm>

#include <string>
#include <cstring>

#define BLOCK_ASSET_WIDTH 16.0f
#define BLOCK_ASSET_HEIGHT 8.0f
#define BORDER_ASSET_WIDTH 8.0f

enum Keys
{
	KEY_RIGHT, KEY_LEFT, KEY_DOWN, KEY_UP
};

class MyFramework : public Framework 
{
private:
	bool is_full_screen;

	unsigned int delta;
	unsigned int prev_time;
	unsigned int time_for_boost;

	//TODO: bitset
	bool keyState [5] = {0};
	vector2d<int> mouse;
	int margin;
	float coefficient;

	Player player;
	Ball ball;
	Stats stats;
	Map map;

	bool is_block_destroyed;
	bool is_boost_catched;

	std::vector<Boost> boosts;
	std::vector<Block*> level_blocks;

public:
	MyFramework(int width, int height, int isFullscreen)
		: Framework(width, height, isFullscreen),
		map(width, height, boosts),
		mouse( {0, 0} ),
		margin(0),
		is_full_screen(isFullscreen),
		time_for_boost(0),
		is_block_destroyed(false),
		is_boost_catched(false),
		level_blocks(6 * 11) //TODO: calculate
	{}

	virtual bool Init() override 
	{
		srand(time(0));
		coefficient = map.width / ( 11.0f * BLOCK_ASSET_WIDTH + 2 * BORDER_ASSET_WIDTH);
		margin = 1 * coefficient;

		Player::initSprites(coefficient);
		Ball::initSprites(coefficient);
		Block::initSprites(coefficient);	
		Stats::initSprites(coefficient);
		Boost::initSprites(coefficient);
		Map::initSprites(coefficient);

		stats.setBorder( {map.width - map.getBorder(), map.getBorder() }, margin);

		Reset();
		return true;
	}

	virtual void Close() override {}

	virtual bool Tick() override 
	{
		unsigned int now = getTickCount();
		delta = now - prev_time;
		prev_time = now;

		if(stats.lives <= 0)
			Reset();
		if(level_blocks.size() == 0)
			return true;

		player.update(delta);
		ball.update(delta);
		map.update(delta);
		InputUpdate();

		if(!stats.isStarted)
		{
			SetBallByPlayerPosition();
		}
		else
		{
			CollisionCheck();

			time_for_boost += delta;
			if(time_for_boost > 15000)
			{
				map.spanBoost();
				time_for_boost = 0;
			}
		}
			
		map.draw();
		stats.draw();

		for(auto& block : level_blocks)
			block->draw();

		player.draw();
		ball.draw();

		for(auto& boost : boosts)
		{	
			boost.update(delta);
			boost.draw();
		}

		return false;
	}

	void Reset() 
	{
		if(stats.lives <= 0)
		{
			CLIENT_LOG_DEBUG("Your score is %i", stats.score);

			stats.lives = 1;
			stats.score = 0;

			Level1();
			boosts.clear();
		}

		if(!stats.isStarted)
		{
			// 1/2 of width && 3/4 of height
			vector2d<float> player_pos(map.width / 2.0f, map.height / 4.0f * 3.0f);
			player.setPosition(player_pos);

			Level1();
		}

		stats.isStarted = false;
		stats.destroyed_in_row = 0;

		SetBallByPlayerPosition();
		ball.setVelocity({0,0});
	}

	void SetBallByPlayerPosition()
	{
		int width, height;
		player.getSize(width, height);

		vector2d<float> ball_pos( 
				player.getPosition().x + width / 2.0f,
				player.getPosition().y - height);
				
		ball.setCenterPosition(ball_pos);
	}

	void CollisionCheck()
	{
		CollisionLevelBorder();
		if(collisionPlayerAndBall(&player, &ball))
		{
			stats.destroyed_in_row = 0;
		}

		for(auto& block : level_blocks)
		{
			if( collisionBlockAndBall(block, &ball) )
			{
				stats.plusForScore();
				is_block_destroyed = true;
			}
		}

		for(auto& boost : boosts)
		{
			if(isCollideAABBandAABB(
				boost.position, boost.getMaxPosition(),
				player.getPosition(), player.getMaxPosition())
			  )
			{
				boost.isNeedToDestroy = true;
				is_boost_catched = true;

				switch (boost.type) {
					case HeartMinus:
						stats.lives -= 1;
						CLIENT_LOG_DEBUG("LIVES: %i", stats.lives);
						break;
					case HeartPlus:
						stats.lives += 1;
						CLIENT_LOG_DEBUG("LIVES: %i", stats.lives);
						break;
				}
			}
		}

		if(is_block_destroyed)
		{
			//TODO: optimaze
			level_blocks.erase(
				std::remove_if(level_blocks.begin(), level_blocks.end(),
				[](const Block* block) { return block->isNeedToDestroy(); }),
  						level_blocks.end());
			is_block_destroyed = false;
		}
		
		if(is_boost_catched)
		{
			boosts.erase(
				std::remove_if(boosts.begin(), boosts.end(),
				[](const Boost& boost) { return boost.isNeedToDestroy; }),
 						boosts.end());
			is_boost_catched = false;
		}
	}

	inline void CollisionLevelBorder()
	{
		bool isCollideWithBorders = false;
		vector2d<float> ball_velocity = ball.getVelocity();

		//Collision with bottom
		if(ball.getPosition().y > map.height - margin - ball.getRadius() * 2)
		{
			stats.lives -= 1;
			Reset();
			return;
		}

		//Collision with top
        if (ball.getPosition().y < map.getBorder() + margin)
        {
            ball_velocity.y = - ball_velocity.y;
			isCollideWithBorders = true;
        }

        //Collision with left and right
        if (ball.getPosition().x > map.width - ball.getRadius() * 2 - map.getBorder() - margin
                 || ball.getPosition().x < map.getBorder() + margin)
        {
            ball_velocity.x = - ball_velocity.x;
			isCollideWithBorders = true;
        }

		if(isCollideWithBorders)
		{
			ball.setVelocity(ball_velocity);
			ball.push(ball_velocity);
		}
	}

	void InputUpdate()
	{
		for(uint8_t i = 0; i < 4; i++)
		{
			if(keyState[i])
			{
				switch (i) 
				{
					case KEY_RIGHT:
						if (player.getMaxPosition().x < map.width - map.getBorder() - margin)
							player.move(1);
						break;
					case KEY_LEFT:
						if(player.getPosition().x > map.getBorder() + margin)
							player.move(-1);
						break;
				}
			}
		}
	}

	void Level1()
	{
		level_blocks.clear();

		int block_w, block_h;
		Block::getBlockSize(block_w, block_h);


		for(int i = 0; i < 11; i++)
		{
			vector2d<float> pos (map.getBorder() + margin + block_w * i, 4 * BLOCK_ASSET_HEIGHT * coefficient);
			Block* block = new Undestroyable_Block(pos);
			level_blocks.push_back(block);
		}

		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 11; j++)
			{
				vector2d<float> pos (map.getBorder() + margin + block_w * j, 5 * BLOCK_ASSET_HEIGHT * coefficient + block_h * i);
				Block* block = new Normal_Block(pos , (BlockColor)(i % 5) );
				level_blocks.push_back(block);
			}
		}
	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) override 
	{
		if(!stats.isStarted 
			&& button == FRMouseButton::LEFT
			&& isReleased)
		{
			// vector from ball to mouse
			vector2d<float> mouse_f = {(float)mouse.x, (float)mouse.y};
			vector2d<float> direction = ball.getPosition().dest_vector( mouse_f ).normalize();
			ball.setDirection( direction );
			stats.isStarted = true;
		}
	}	

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) override 
		{ mouse.x = x; mouse.y = y; }

	virtual void onKeyPressed(FRKey k) override 
		{ keyState[(int) k] = true; }

	virtual void onKeyReleased(FRKey k) override 
		{ keyState[(int) k] = false; }
	
	virtual const char* GetTitle() override
		{ return "Arcanoid"; }
};

void getWindowParams(char* argv[], int position, int& width, int& height)
{
	std::vector<char*> params;

	char* ptr;
	ptr = strtok(argv[position + 1], " X ");

  	while (ptr != NULL)  
  	{  
		params.push_back(ptr);
  	    ptr = strtok (NULL, "X");  
  	}  

	if(params.size() == 2)
	{
		width = atoi(params[0]);
		height = atoi(params[1]);
	}
	//TODO: log error
	else
	{}
}

int main(int argc, char *argv[])
{
	int width = -1, height = -1;
	for(int i = 0; i < argc; i++)
	{
		if(strcmp(argv[i], "-window") == 0)
		{
			//TODO: log error
			if(i + 1 > argc)
				continue;

			getWindowParams(argv, i, width, height);
		}
	}

	//TODO: window to small log 
	if(width == -1 || height == -1)
		width = 800, height = 800;

	MyFramework framework(width, height, false);
	return run(&framework);
}
