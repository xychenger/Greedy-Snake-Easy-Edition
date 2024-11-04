#include<bits/stdc++.h>
#include<easyx.h>
using namespace std;
#define RED 0x0000AA
#define white RGB(255,255,255)
//精灵类
class Sprite
{
public:
	Sprite() :Sprite(0, 0) {};
	Sprite(int x, int y) :m_x(x), m_y(y), m_color(RED) {};
	// 绘制精灵
	virtual void draw()
	{
		//设置填充颜色
		setfillcolor(m_color);
		//绘制矩形
		fillrectangle(m_x, m_y, m_x+10, m_y+10);

	}
	void moveBy(int dx, int dy)
	{
		m_x += dx;
		m_y += dy;
	}
	//碰撞检测
	bool collision(const Sprite& other) {
		return m_x == other.m_x && m_y == other.m_y;
	}
protected:
	int m_x;
	int m_y;
	COLORREF m_color; // 颜色
};
//蛇类
class Snake :public Sprite
{
public:
	Snake(): Snake(0,0) {}
	Snake(int x, int y):Sprite(x, y), dir(0x27){
		nodes.push_back(Sprite(20, 0));
		nodes.push_back(Sprite(10, 0));
		nodes.push_back(Sprite(0, 0));
	}
	void draw() override{
		for (int i = 0; i < nodes.size(); i++) {
			nodes[i].draw();
		}
	}
	// 蛇的身体移动
	void bodyMove()
	{
		//身体跟着蛇头移动
		for (size_t i = nodes.size() - 1; i > 0; i--)
		{
			nodes[i] = nodes[i - 1];
		}
		switch (dir)
		{
		case 0x26 :
			nodes[0].moveBy(0, -10);
			break;
		case 0x28:
			nodes[0].moveBy(0, 10);
			break;
		case 0x25:
			nodes[0].moveBy(-10, 0);
			break;
		case 0x27:
			nodes[0].moveBy(10, 0);
			break;
		default:
			break;
		}
	}
	bool collision(const Sprite& other)
	{
		return nodes[0].collision(other);
	}
	// 蛇增加一节
	void incrment()
	{
		nodes.push_back(Sprite());
	}
private:
	vector<Sprite> nodes;
public:
	int dir;  //蛇的方向
};
//食物类
class Food :public Sprite
{
public:
	Food() :Sprite(0, 0) {
		changePos();
	}
	void draw() override
	{
		setfillcolor(m_color);
		solidellipse(m_x, m_y, m_x + 10, m_y + 10);
	}
	// 改变食物的坐标
	void changePos()
	{
		m_x = rand() % 64 * 10;
		m_y = rand() % 48 * 10;
	}
};
//场景类
class Gamescene
{
public:
	Gamescene() {
	};
	void run() {
		BeginBatchDraw(); //双缓冲绘图
		cleardevice();
		snake.draw();
		food.draw();
		EndBatchDraw();
		//移动蛇，改变蛇的坐标
		snake.bodyMove();
		//改变蛇的移动方向 获取键盘按键 _getch()
		snakeEatFood();
		//获取消息
		ExMessage msg = { 0 };
		while (peekmessage(&msg, EX_KEY))
		{
			onMsg(msg);
		}
	}
	//响应消息：鼠标消息 键盘消息
	void onMsg(const ExMessage& msg)
	{
		//如果有键盘消息（有没有按键按下）
		if (msg.message == 0x0100)
		{
			// 判断具体是哪个按键按下 virtual key code 虚拟键码
			if (msg.vkcode == VK_UP || msg.vkcode == VK_LEFT || msg.vkcode == VK_DOWN || msg.vkcode == VK_RIGHT)
			{
				snake.dir = msg.vkcode;
			}
		}
	}
	// 判断蛇能否吃到食物
	void snakeEatFood()
	{
		if (snake.collision(food)) //如果蛇和食物产生了碰撞
		{
			//蛇的节数增加
			snake.incrment();
			//食物重新产生在了别的位置
			food.changePos();
		}
	}
private:
	Snake snake;
	Food food;
};
int main() {
	initgraph(640, 480, EX_SHOWCONSOLE);
	setbkcolor(RGB(255, 255, 255));
	//设置随机数种子
	srand(time(nullptr));
	Gamescene scene;
	while (true) {
		scene.run();
		Sleep(100);
	}
	while(1){}

	return 0;
}