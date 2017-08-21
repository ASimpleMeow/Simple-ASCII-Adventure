#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject {
public:
	GameObject();

	//Getters
	virtual void getPosition(int& x, int&y);

	//Setters
	virtual void setPosition(int x, int y);

protected:
	int m_x;
	int m_y;

};

#endif // !GAMEOBJECT_H

