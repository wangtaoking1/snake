#pragma once

typedef enum
{
	KGameLayer = 0,
	KControlLayer = 1,
	KEndLayer = -1,
}zOrder;


typedef enum
{
	UP = 0,
	RIGHT = 1,
	DOWN = 2,
	LEFT = 3,
}sDirection;


typedef enum
{
	kNONE = 0,
	kFOOD = 1,
	kWALL = 2,
	kBODY = 3,
}CollisionType;

const char Esnake[20][15] = {"", "snake101.png", "snake102.png","snake103.png","snake104.png","snake105.png","snake106.png","snake107.png","snake108.png",
	"snake109.png","snake110.png", "snake111.png","snake112.png","snake113.png", "snake114.png", "snake115.png", "snake116.png", "snake117.png", "snake118.png" };

const char Msnake[20][15] = {"", "snake201.png", "snake202.png","snake203.png","snake204.png","snake205.png","snake206.png","snake207.png","snake208.png",
	"snake209.png","snake210.png", "snake211.png","snake212.png","snake213.png", "snake214.png", "snake215.png", "snake216.png", "snake217.png", "snake218.png" };

const char food[6][10] = {"food1.png", "food2.png", "food3.png", "food4.png", "food5.png"};