#include<bits/stdc++.h>
#include<easyx.h>
using namespace std;
#define RED 0x0000AA
#define white RGB(255,255,255)
//������
class Sprite
{
public:
	Sprite() :Sprite(0, 0) {};
	Sprite(int x, int y) :m_x(x), m_y(y), m_color(RED) {};
	// ���ƾ���
	virtual void draw()
	{
		//���������ɫ
		setfillcolor(m_color);
		//���ƾ���
		fillrectangle(m_x, m_y, m_x+10, m_y+10);

	}
	void moveBy(int dx, int dy)
	{
		m_x += dx;
		m_y += dy;
	}
	//��ײ���
	bool collision(const Sprite& other) {
		return m_x == other.m_x && m_y == other.m_y;
	}
protected:
	int m_x;
	int m_y;
	COLORREF m_color; // ��ɫ
};
//����
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
	// �ߵ������ƶ�
	void bodyMove()
	{
		//���������ͷ�ƶ�
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
	// ������һ��
	void incrment()
	{
		nodes.push_back(Sprite());
	}
private:
	vector<Sprite> nodes;
public:
	int dir;  //�ߵķ���
};
//ʳ����
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
	// �ı�ʳ�������
	void changePos()
	{
		m_x = rand() % 64 * 10;
		m_y = rand() % 48 * 10;
	}
};
//������
class Gamescene
{
public:
	Gamescene() {
	};
	void run() {
		BeginBatchDraw(); //˫�����ͼ
		cleardevice();
		snake.draw();
		food.draw();
		EndBatchDraw();
		//�ƶ��ߣ��ı��ߵ�����
		snake.bodyMove();
		//�ı��ߵ��ƶ����� ��ȡ���̰��� _getch()
		snakeEatFood();
		//��ȡ��Ϣ
		ExMessage msg = { 0 };
		while (peekmessage(&msg, EX_KEY))
		{
			onMsg(msg);
		}
	}
	//��Ӧ��Ϣ�������Ϣ ������Ϣ
	void onMsg(const ExMessage& msg)
	{
		//����м�����Ϣ����û�а������£�
		if (msg.message == 0x0100)
		{
			// �жϾ������ĸ��������� virtual key code �������
			if (msg.vkcode == VK_UP || msg.vkcode == VK_LEFT || msg.vkcode == VK_DOWN || msg.vkcode == VK_RIGHT)
			{
				snake.dir = msg.vkcode;
			}
		}
	}
	// �ж����ܷ�Ե�ʳ��
	void snakeEatFood()
	{
		if (snake.collision(food)) //����ߺ�ʳ���������ײ
		{
			//�ߵĽ�������
			snake.incrment();
			//ʳ�����²������˱��λ��
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
	//�������������
	srand(time(nullptr));
	Gamescene scene;
	while (true) {
		scene.run();
		Sleep(100);
	}
	while(1){}

	return 0;
}