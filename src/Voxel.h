/*
 * Voxel.h
 *
 *  Created on: 04/04/2014
 *      Author: oscar
 */

#ifndef VOXEL_H_
#define VOXEL_H_

namespace sv
{

class Voxel
{

public:

	Voxel();

	//setters
	void column(int __column);
	void row(int __row);
	void slice(int __slice);
	void label(int __label);

	void top(Voxel* __top);
	void botton(Voxel* __botton);
	void left(Voxel* __left);
	void right(Voxel* __right);
	void back(Voxel* __back);
	void front(Voxel* __front);

	void swapped(bool __swapped);

	void intensity(int __color);

	//getters
	int column();
	int row();
	int slice();
	int label();
	bool swapped();
	int intensity();
//
	Voxel* top();
	Voxel* botton();
	Voxel* left();
	Voxel* right();
	Voxel* back();
	Voxel* front();

private:

	int _intensity;
	int _label;

	//axis
	u_short _column;
	u_short _row;
	u_short _slice;

//	//pointers to neighbors
	Voxel* _top;
	Voxel* _botton;
	Voxel* _left;
	Voxel* _right;
	Voxel* _back;
	Voxel* _front;

	bool _swapped;

};

void Voxel::swapped(bool __swapped)
{
	_swapped = __swapped;
}
bool Voxel::swapped()
{
	return _swapped;
}
int Voxel::label()
{
	return _label;
}
int Voxel::column()
{
	return _column;
}
int Voxel::row()
{
	return _row;
}
int Voxel::slice()
{
	return _slice;
}
Voxel* Voxel::right()
{
	return _right;
}
Voxel* Voxel::left()
{
	return _left;
}
Voxel* Voxel::top()
{
	return _top;
}
Voxel* Voxel::botton()
{
	return _botton;
}

Voxel* Voxel::front()
{
	return _front;
}
Voxel* Voxel::back()
{
	return _back;
}

void Voxel::right(Voxel* __right)
{
	_right = __right;
}

void Voxel::left(Voxel* __left)
{
	_left = __left;
}

void Voxel::top(Voxel* __top)
{
	_top = __top;
}
void Voxel::botton(Voxel* __botton)
{
	_botton = __botton;
}
void Voxel::front(Voxel* __front)
{
	_front = __front;
}

void Voxel::back(Voxel* __back)
{
	_back = __back;
}

void Voxel::label(int __label)
{
	_label = __label;
}

void Voxel::column(int __column)
{
	_column = __column;

}

void Voxel::row(int __row)
{
	_row = __row;
}

void Voxel::slice(int __slice)
{
	_slice = __slice;
}

void Voxel::intensity(int __intensity)
{
	_intensity = __intensity;
}
int Voxel::intensity()
{
	return _intensity;
}
Voxel::Voxel()
{
	_column = 0;
	_row = 0;
	_slice = 0;

	_top = 0;
	_botton = 0;
	_left = 0;
	_right = 0;
	_back = 0;
	_front = 0;

	_intensity = 0;
	_label = 0;
	_swapped = false;

}
} /* namespace sv */

#endif /* VOXEL_H_ */
