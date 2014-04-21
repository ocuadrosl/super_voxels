/*
 * Regular_grid.h
 *
 *  Created on: 02/04/2014
 *      Author: oscar
 */

#ifndef REGULAR_GRID_H_
#define REGULAR_GRID_H_

#include "Grid.h"
#include <iostream>

using namespace std;
namespace sv
{

class Regular_grid: public Grid
{
public:
	volume_t::IndexType voxel_index;

	Regular_grid();

	~Regular_grid();
	void process(volume_tp __volume, vector<Super_voxel*>* __super_voxels);

	void sv_size(int __sv_size);

	int mean_sv_size();


private:
	u_int _sv_size; //super voxel size def value 10
	u_int _rows; //auxiliary parameter
	u_int _columns; //auxiliary parameter
	u_int _slices; //aux param

	vector<vector<int> > sv_sizes; //auxiliary vector

	void link_voxels(vector<Super_voxel*>* __super_voxels);

};

int Regular_grid::mean_sv_size()
{
	return _sv_size;
}

void Regular_grid::sv_size(int __sv_size)
{
	_sv_size = __sv_size;
}

Regular_grid::Regular_grid()
{
	_sv_size = 10; //default value
	_rows = 0;
	_columns = 0;
	_slices = 0;
}
Regular_grid::~Regular_grid()
{

//	for(int i=0;i<sv_sizes.size();i++)
//	{
//		sv_sizes[i].clear();
//		vector<int> ith;
//		ith.swap(sv_sizes[i]);
//	}

	sv_sizes.clear();
	vector<vector<int> >().swap(sv_sizes);
	//cout << "destruido" << endl;

}

void Regular_grid::process(volume_tp __volume, vector<Super_voxel*>* __super_voxels)
{
	volume_t::RegionType region = __volume->GetLargestPossibleRegion();

	volume_t::SizeType size = region.GetSize();

	int columns = size[0];
	int rows = size[1];
	int slices = size[2];

	_columns = columns / _sv_size;
	_rows = rows / _sv_size;
	_slices = slices / _sv_size;

	/*some auxiliary declarations*/
	int img_columns_begin = 0;
	int img_rows_begin = 0;
	int sv_columns = 0;
	int sv_rows = 0;
	int sv_slices = 0;
	int img_columns_end = 0;
	int img_rows_end = 0;
	int img_slices_end = 0;
	int img_slices_begin = 0;

	int img_column = 0;
	int img_row = 0;
	int img_slice = 0;

	for (int column = 1; column <= _columns; column++)
	{
		img_columns_end = (column * columns) / _columns;

		for (int row = 1; row <= _rows; row++)
		{
			img_rows_end = (row * rows) / _rows;

			for (int slice = 1; slice <= _slices; slice++)
			{
				img_slices_end = (slice * slices) / _slices;

				sv_columns = img_columns_end - img_columns_begin;
				sv_rows = img_rows_end - img_rows_begin;
				sv_slices = img_slices_end - img_slices_begin;

				Super_voxel *super_voxel = new Super_voxel();
				vector<int> sv_size;
				sv_size.push_back(sv_columns);
				sv_size.push_back(sv_rows);
				sv_size.push_back(sv_slices);
				sv_sizes.push_back(sv_size);

				for (img_column = img_columns_begin; img_column < img_columns_end; img_column++)
				{
					for (img_row = img_rows_begin; img_row < img_rows_end; img_row++)
					{
						for (img_slice = img_slices_begin; img_slice < img_slices_end; img_slice++)
						{

							Voxel *voxel = new Voxel();
							voxel->column(img_column);
							voxel->row(img_row);
							voxel->slice(img_slice);

							voxel_index[0] = img_column;
							voxel_index[1] = img_row;
							voxel_index[2] = img_slice;

							voxel->intensity((int) __volume->GetPixel(voxel_index));
							voxel->label(__super_voxels->size());
							super_voxel->push_back(voxel);

						}

					}

				}
				img_slices_begin = img_slices_end;

				super_voxel->label(__super_voxels->size());
				__super_voxels->push_back(super_voxel);

			}
			img_rows_begin = img_rows_end;
			img_slices_begin = 0;
		}
		img_columns_begin = img_columns_end;
		img_rows_begin = 0;

	}

	link_voxels(__super_voxels);
	cout << "Regular Grid [ok]" << endl;

}

void Regular_grid::link_voxels(vector<Super_voxel*>* __super_voxels)
{

	int columns = 0;
	int rows = 0;
	int slices = 0;
	int index = 0; // voxel index
	int n_index = 0; //neighbor index

	for (int i = 0; i < __super_voxels->size(); i++)
	{
		Super_voxel& super_voxel = *(*__super_voxels)[i]; //alias

		columns = sv_sizes[i][0];
		rows = sv_sizes[i][1];
		slices = sv_sizes[i][2];

		for (int c = 0; c < columns; c++)
		{
			for (int r = 0; r < rows; r++)
			{
				for (int s = 0; s < slices; s++)
				{
					index = (((c * rows) + r) * slices) + s;
					//right
					if (c < columns - 1)
					{
						n_index = ((((c + 1) * rows) + r) * slices) + s;
						super_voxel[index]->right(super_voxel[n_index]);
					}
					else if (i + (_rows * _slices) < __super_voxels->size())
					{

						Super_voxel& super_voxel_n = *(*__super_voxels)[i + (_rows * _slices)]; //alias
						super_voxel[index]->right(super_voxel_n[(r * slices) + s]);

					}

					//left
					if (c > 0)
					{
						n_index = ((((c - 1) * rows) + r) * slices) + s;
						super_voxel[index]->left(super_voxel[n_index]);
					}
					else if ((int) (i - (_rows * _slices)) >= 0)
					{
						Super_voxel& super_voxel_n = *(*__super_voxels)[i - (_rows * _slices)]; //alias
						int left_col = sv_sizes[i - (_rows * _slices)][0];
						super_voxel[index]->left(super_voxel_n[((left_col - 1) * rows + r) * slices + s]);

					}

					//top
					if (r > 0)
					{
						n_index = (((c * rows) + (r - 1)) * slices) + s;
						super_voxel[index]->top(super_voxel[n_index]);

					}
					else if (i - 1 >= 0 && (i - (i % _slices)) % (_rows * _slices) != 0)
					{
						Super_voxel& super_voxel_n = *(*__super_voxels)[i - _slices]; //alias
						int top_row = sv_sizes[i - _slices][1];
						int top_col = sv_sizes[i - _slices][0];

						super_voxel[index]->top(super_voxel_n[top_row * top_col * c + ((top_row - 1) * top_row) + s]);
					}

					//botton
					if (r + 1 < rows)
					{
						n_index = (((c * rows) + (r + 1)) * slices) + s;
						super_voxel[index]->botton(super_voxel[n_index]);
					}
					else if (i + 1 < __super_voxels->size() && (i - (i % _slices)) % (_rows * _slices) != ((_rows - 1) * _slices))
					{
						Super_voxel& super_voxel_n = *(*__super_voxels)[i + _slices]; //alias
						int bot_row = sv_sizes[i + _slices][1];
						int bot_sli = sv_sizes[i + _slices][2];

						super_voxel[index]->botton(super_voxel_n[(c * bot_row * bot_sli) + s]);
					}

					//back
					if (s + 1 < slices)
					{
						n_index = (((c * rows) + (r)) * (slices)) + s + 1;
						super_voxel[index]->back(super_voxel[n_index]);

					}
					else if (i + 1 < __super_voxels->size() && ((i - (i % _slices)) + (_slices - 1)) != i)
					{
						Super_voxel& super_voxel_n = *(*__super_voxels)[i + 1]; //alias
						int back_row = sv_sizes[i + 1][1];
						int back_sli = sv_sizes[i + 1][2];

						super_voxel[index]->back(super_voxel_n[c * back_row * back_sli + (r * back_sli)]);

					}

					//front
					if (s > 0)
					{
						n_index = (((c * rows) + (r)) * (slices)) + s - 1;
						super_voxel[index]->front(super_voxel[n_index]);

					}
					else if (i - 1 >= 0 && (i - (i % _slices)) != i)
					{
						Super_voxel& super_voxel_n = *(*__super_voxels)[i - 1]; //alias
						int front_row = sv_sizes[i - 1][1];
						int front_sli = sv_sizes[i - 1][2];

						super_voxel[index]->front(super_voxel_n[(c * front_row * front_sli + (r * front_sli)) + front_sli - 1]);

					}

				}

			}

		}

	}

}

} /* namespace sv */

#endif /* REGULAR_GRID_H_ */
