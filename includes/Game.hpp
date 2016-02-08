#ifndef GAME_HPP_
# define GAME_HPP_

/*
** Start config
*/
# define MAP_SIDE	10
# define SPEED		3
# define START_LEN	4

/*
** Key codes
*/
# define LEFT_KEY	0
# define RIGHT_KEY	1
# define ESC_KEY	2

/*
** Sprite codes
*/
# define EMPTY		0
# define SNAKE		1
# define FOOD		2
# define WALL		3

# include <map>
# include <utility>

typedef std::map<std::pair<int, int>, int> nibble_map;

#endif
