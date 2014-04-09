/*
 * Super_voxel.h
 *
 *  Created on: 04/04/2014
 *      Author: oscar
 */

#ifndef SUPER_VOXEL_H_
#define SUPER_VOXEL_H_
#include "Voxel.h"

using namespace std;

namespace sv
{

class Super_voxel
{
public:
	Super_voxel();
	~Super_voxel();
	Voxel *&operator[](int __index);
	void push_back(Voxel* __voxel);
	void label(int __label);

	//getters
	int label();
	int size();
	int m_color(); // mean color
	int c_column();
	int c_row();
	int c_slice(); //centroid

	//others
	void update();
	void remove_nulls();

private:

	std::vector<Voxel*> _voxels;

	//centroids
	int _c_column;
	int _c_row;
	int _c_slice;

	//mean color
	int _m_color;

	int _label;

};

void Super_voxel::update()
{
	int c_sum = 0;
	int r_sum = 0;
	int s_sum = 0;
	float cl_sum = 0; //color

	float count = 0;

	for (int i = 0; i < size(); i++)
	{
		if (_voxels[i])
		{
			_voxels[i]->swapped(false);
			cl_sum += _voxels[i]->intensity();
			c_sum += _voxels[i]->column();
			r_sum += _voxels[i]->row();
			s_sum += _voxels[i]->slice();
			count++;
		}
	}
	_m_color = cl_sum / count;
	_c_column = c_sum / count;
	_c_row = r_sum / count;
	_c_slice = s_sum / count;

	//cout<<_m_color<<endl;

}

void Super_voxel::remove_nulls()
{
	vector<Voxel*> voxels;
	for (int i = 0; i < _voxels.size(); i++)
	{
		if (_voxels[i])
		{
			voxels.push_back(_voxels[i]);
		}

	}
	_voxels = voxels;
}

int Super_voxel::c_column()
{
	return _c_column;
}

int Super_voxel::c_row()
{
	return _c_row;
}

int Super_voxel::c_slice()
{
	return _c_slice;
}

int Super_voxel::m_color()
{
	return _m_color;
}
int Super_voxel::size()
{
	return _voxels.size();
}

Voxel *& Super_voxel::operator[](int __index)
{
	return _voxels[__index];
}
Super_voxel::Super_voxel()
{

}
void Super_voxel::label(int __label)
{
	_label = __label;
}

int Super_voxel::label()
{
	return _label;
}

void Super_voxel::push_back(Voxel* __voxel)
{
	_voxels.push_back(__voxel);
}

} /* namespace sv */

#endif /* SUPER_VOXEL_H_ */
