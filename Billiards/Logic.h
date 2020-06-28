class Vector
{
private:
	// Значение вектора
	float x = 0;
	float y = 0;
	float length = 1;

public:
	Vector() { x = 0.0; y = 0.0; length = 1.0; }
	Vector(float x, float y) { this->x = x; this->y = y; this->normalization(); }

	void normalization()
	{
		if (x != 0 || y != 0)
		{
			this->length = sqrt(pow(x, 2) + pow(y, 2));
		}
		this->x /= length;
		this->y /= length;
		length = 1;
	}

	void SetVector(float x, float y) { this->x = x; this->y = y; this->normalization();}
	void SetX() { this->x = x; this->normalization(); }
	void SetY() { this->y = y; this->normalization(); }

	float GetX() { return this->x; }
	float GetY() { return this->y; }
	Vector& GetVector() { return *this; }

	Vector operator =(const Vector& other)
	{
		this->x = other.x;
		this->y = other.y;
		this->normalization();
		return *this;
	}
	Vector operator +(const Vector& other)
	{
		this->x += other.x;
		this->y += other.y;
		this->normalization();
		return *this;
	}
	Vector operator -(const Vector& other)
	{
		this->x -= other.x;
		this->y -= other.y;
		this->normalization();
		return *this;
	}
	float operator*(const Vector& other) { return this->x * other.x + this->y * other.y; }

	Vector operator*(const float value)
	{
		this->x *= value;
		this->y *= value;
		this->normalization();
		return *this;
	}
};

/*---------------------Objects--------------------*/

class Ball
{
protected:
	Texture texture;
	Sprite sprite;
private:

	double radius = 14;// В пикселях
	Vector2i position;
	Vector direction;
	float dx = 0;
	float dy = 0;

public:
	int GetX() { return this->position.x; }
	int GetY() { return this->position.y; }

	float GetDx() { return this->dx; }
	float GetDy() { return this->dy; }

	int GetRadius() { return this->radius; }
	
	Vector& GetVector() { return this->direction; }
	Sprite GetSprite() { return this->sprite; }

	void SetX(int x) { this->position.x = x; sprite.setPosition(x, this->position.y); }
	void SetY(int y) { this->position.y = y ; sprite.setPosition(this->position.x, y); }

	void SetPosition(int x, int y) 
	{ 
		sprite.setOrigin(radius, radius);
		this->position.x = x;
		this->position.y = y;
		sprite.setPosition(this->position.x, this->position.y);
	}
	
	void SetVector(Vector& vec)
	{
		this->direction.SetVector(vec.GetX(), vec.GetY());
	}
	
	void SetDiff(float dx, float dy)
	{
		this->dx = dx;
		this->dy = dy;
	}

};
// Классы наследник базового класса Шара
class WhiteBall : public Ball 
{
public: 
	WhiteBall()
	{
		texture.loadFromFile("images/Game/white_ball.png");
		sprite.setTexture(texture);
	}
};

class RedBall : public Ball
{
public:
	RedBall()
	{
		texture.loadFromFile("images/Game/red_ball.png");
		sprite.setTexture(texture);
	}
};

// Шкала силы удара
class Table
{
private:
	Texture table_texture, arrow_texture;
	Sprite table_sprite, arrow_sprite;
	int x;
	int y;

	// Розміри стрілки
	int arrow_width = 93;
	int arrow_heigth = 60;

public:
	Table()
	{
		table_texture.loadFromFile("images/Game/Table.png");
		arrow_texture.loadFromFile("images/Game/Arrow.png");
		table_sprite.setTexture(table_texture);
		arrow_sprite.setTexture(arrow_texture);

		table_sprite.setPosition(42, 130);

	}
	void SetPosition(int x, int y) { this->x = x; this->y = y; arrow_sprite.setPosition(x, y); }
	Sprite Get_Arrow_Sprite() { return arrow_sprite; }
	Sprite Get_Table_Sprite() { return table_sprite; }

	int GetX() { return x; }
	int GetY() { return y; }

	int GetWidth() { return arrow_width; }
	int GetHeigth() { return arrow_heigth; }

	float GetPower()
	{
		return  15*((668.0 - this->GetY()) / 200.0);
	}
};
// Класс кия
class Cue
{
private:
	Texture cue_texture;
	Sprite cue_sprite;

	int x;
	int y;

	double power;

public:
	float rotation;
	Vector2i pixelPos;
	Vector2f pos;
	float vecX = 0;
	float vecY = 0;
	Cue()
	{
		cue_texture.loadFromFile("images/Game/cue.png");
		cue_sprite.setTexture(cue_texture);
	}
	Sprite& GetSprite() { return cue_sprite; }
	
	void SetPosition(int x, int y) { this->x = x; this->y; cue_sprite.setPosition(x, y); }
	void SetRotation(float andle) { cue_sprite.setRotation(andle);}
	void SetPower(double value) { this->power = value; }
};

/*-----------------------------------------------*/
