/*
 * Super_voxels.h
 *
 *  Created on: 02/04/2014
 *      Author: oscar
 */

#ifndef SUPER_VOXELS_H_
#define SUPER_VOXELS_H_

#include "Grid.h"
#include "Typedefs.h"

#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

#include <string>

using namespace std;

namespace sv
{
/*
 * Super Voxels Class
 * @author Oscar
 *
 */
class Super_voxels
{
public:
	Super_voxels(Grid* __grid);
	~Super_voxels();

	void read_volume(string __file_name);
	void write_volume(string __file_name);
	void process(); //main method to manage the grid creation and the super voxels extraction
	Super_voxel *&operator[](int __index);


	//setters
	void lambda_0(float __lambda_0);
	void lambda_1(float __lambda_1);
	void threshold(float __threshold);
	void iterations(int __iterations);

private:

	Grid* _grid; //initial grid type
	volume_tp _volume; // itk 3d image
	vector<Super_voxel*> _super_voxels;

	float _lambda_0;
	float _lambda_1;
	float _threshold;
	int _iterations;

	void sutv(); //speeded up turbo voxels, one iteration
	bool k_means_cost_function(Voxel* __v_0, Voxel* __v_1);
	void sv_update();
	void sv_clean();

};

Super_voxel *& Super_voxels::operator[](int __index)
{
	return _super_voxels[__index];
}

void Super_voxels::iterations(int __iterations)
{
	_iterations = __iterations;
}

void Super_voxels::threshold(float __threshold)
{
	_threshold = __threshold;
}

void Super_voxels::lambda_0(float __lambda_0)
{
	_lambda_0 = __lambda_0;
}

void Super_voxels::lambda_1(float __lambda_1)
{
	_lambda_1 = __lambda_1;
}

bool Super_voxels::k_means_cost_function(Voxel* __v_0, Voxel* __v_1)
{
	int l_0 = __v_0->label();
	int l_1 = __v_1->label();

	int m_color_0 = _super_voxels[l_0]->m_color();
	int m_color_1 = _super_voxels[l_1]->m_color();

	int color_0 = __v_0->intensity();

	float c_c_0 = _super_voxels[l_0]->c_column();
	float c_r_0 = _super_voxels[l_0]->c_row();
	float c_s_0 = _super_voxels[l_0]->c_slice();

	float c_c_1 = _super_voxels[l_1]->c_column();
	float c_r_1 = _super_voxels[l_1]->c_row();
	float c_s_1 = _super_voxels[l_1]->c_slice();

	int c = __v_0->column();
	int r = __v_0->row();
	int s = __v_0->slice();

	float cost_0 = 0;
	float cost_1 = 0;

	cost_0 = _lambda_0 * abs(abs(color_0) - abs(m_color_0)) + _lambda_1 * (pow(c - c_c_0, 2) + pow(r - c_r_0, 2) + pow(s - c_s_0, 2));
	cost_1 = _lambda_0 * abs(abs(color_0) - abs(m_color_1)) + _lambda_1 * (pow(c - c_c_1, 2) + pow(r - c_r_1, 2) + pow(s - c_s_1, 2));

	if (cost_1 < cost_0)
	{
		return true; //swap the voxel
	}

	return false; //do not swap the voxel

}
void Super_voxels::sutv()
{
	for (int i = 0; i < _super_voxels.size(); i++)
	{

		int size = (*_super_voxels[i]).size();

		for (int j = 0; j < size; j++) //right
		{
			Voxel*& voxel = (*_super_voxels[i])[j];
			if (voxel)
			{
				if (voxel->swapped())
				{
					continue;
				}
				if (voxel->right())
				{
					if (voxel->right()->label() != voxel->label())
					{
						//kmeans
						if (k_means_cost_function(voxel, voxel->right()))
						{
							voxel->label(voxel->right()->label());
							voxel->swapped(true);
							(*_super_voxels[voxel->label()]).push_back(voxel);
							(*_super_voxels[i])[j] = 0;
						}

					}

				}

			}

		}

		for (int j = 0; j < size; j++) //left
		{
			Voxel*& voxel = (*_super_voxels[i])[j];
			if (voxel)
			{
				if (voxel->swapped())
				{
					continue;
				}
				if (voxel->left())
				{
					if (voxel->left()->label() != voxel->label())
					{

						//kmeans
						if (k_means_cost_function(voxel, voxel->left()))
						{
							voxel->label(voxel->left()->label());
							voxel->swapped(true);
							(*_super_voxels[voxel->label()]).push_back(voxel);
							(*_super_voxels[i])[j] = 0;

						}

					}

				}

			}

		}
		for (int j = 0; j < size; j++) //top
		{
			Voxel*& voxel = (*_super_voxels[i])[j];
			if (voxel)
			{
				if (voxel->swapped())
				{
					continue;
				}
				if (voxel->top())
				{
					if (voxel->top()->label() != voxel->label())
					{

						//kmeans
						if (k_means_cost_function(voxel, voxel->top()))
						{
							voxel->label(voxel->top()->label());
							voxel->swapped(true);
							(*_super_voxels[voxel->label()]).push_back(voxel);
							(*_super_voxels[i])[j] = 0;

						}

					}

				}

			}

		}
////
		for (int j = 0; j < size; j++) //botton
		{
			Voxel*& voxel = (*_super_voxels[i])[j];
			if (voxel)
			{
				if (voxel->swapped())
				{
					continue;
				}
				if (voxel->botton())
				{
					if (voxel->botton()->label() != voxel->label())
					{
						//kmeans
						if (k_means_cost_function(voxel, voxel->botton()))
						{
							voxel->label(voxel->botton()->label());
							voxel->swapped(true);
							(*_super_voxels[voxel->label()]).push_back(voxel);
							(*_super_voxels[i])[j] = 0;

						}

					}

				}

			}

		}
		for (int j = 0; j < size; j++) //back
		{
			Voxel*& voxel = (*_super_voxels[i])[j];
			if (voxel)
			{
				if (voxel->swapped())
				{
					continue;
				}
				if (voxel->back())
				{
					if (voxel->back()->label() != voxel->label())
					{
						//kmeans
						if (k_means_cost_function(voxel, voxel->back()))
						{
							voxel->label(voxel->back()->label());
							voxel->swapped(true);
							(*_super_voxels[voxel->label()]).push_back(voxel);
							(*_super_voxels[i])[j] = 0;

						}

					}

				}

			}

		}
		for (int j = 0; j < size; j++) //front
		{
			Voxel*& voxel = (*_super_voxels[i])[j];
			if (voxel)
			{
				if (voxel->swapped())
				{
					continue;
				}
				if (voxel->front())
				{
					if (voxel->front()->label() != voxel->label())
					{
						//kmeans
						if (k_means_cost_function(voxel, voxel->front()))
						{
							voxel->label(voxel->front()->label());
							voxel->swapped(true);
							(*_super_voxels[voxel->label()]).push_back(voxel);
							(*_super_voxels[i])[j] = 0;

						}

					}

				}

			}

		}

	}
	cout << "sutv [ok]" << endl;

}

void Super_voxels::sv_clean()
{
	for (int i = 0; i < _super_voxels.size(); i++)
	{
		_super_voxels[i]->remove_nulls();

	}
}
void Super_voxels::sv_update()
{
	for (int i = 0; i < _super_voxels.size(); i++)
	{
		_super_voxels[i]->update();

	}
}

void Super_voxels::process()
{
	_grid->process(_volume, &_super_voxels);
	delete _grid;

	for (int i = 0; i < _iterations; i++)
	{
		sv_update();
		sutv();
	}
	sv_update();
	sv_clean();

	cout << "Super Voxels [ok]" << endl;

}

void Super_voxels::write_volume(string __file_name)
{

	volume_t::IndexType v_index;
	volume_t::PixelType v_value;

	v_value = 255;

	for (int i = 0; i < _super_voxels.size(); i++)
	{
		Super_voxel &super_voxel = *(_super_voxels[i]); //alias

		for (int j = 0; j < super_voxel.size(); j++)
		{
			Voxel &voxel = *super_voxel[j];
			v_index[0] = voxel.column();
			v_index[1] = voxel.row();
			v_index[2] = voxel.slice();

			if (voxel.right()) //right
			{
				if (voxel.label() != voxel.right()->label())
				{
					_volume->SetPixel(v_index, v_value);
				}
			}
			if (voxel.left()) //left
			{
				if (voxel.label() != voxel.left()->label())
				{
					_volume->SetPixel(v_index, v_value);
				}
			}
			if (voxel.top()) //top
			{
				if (voxel.label() != voxel.top()->label())
				{
					_volume->SetPixel(v_index, v_value);
				}
			}
			if (voxel.botton()) //botton
			{

				if (voxel.label() != voxel.botton()->label())
				{
					_volume->SetPixel(v_index, v_value);
				}
			}
			if (voxel.front()) //front
			{
				if (voxel.label() != voxel.front()->label())
				{
					_volume->SetPixel(v_index, v_value);
				}
			}
			if (voxel.back()) //back
			{

				if (voxel.label() != voxel.back()->label())
				{
					_volume->SetPixel(v_index, v_value);
				}
			}

		}

	}

	typedef itk::ImageFileWriter<volume_t> WriterType;
	WriterType::Pointer writer = WriterType::New();
	writer->SetFileName(__file_name);
	writer->SetInput(_volume);
	writer->Update();

	cout << "write result [ok]" << endl;

}

void Super_voxels::read_volume(string __file_name)
{

	typedef itk::ImageFileReader<volume_t> reader_t;

	reader_t::Pointer reader = reader_t::New();

	reader->SetFileName(__file_name);

	try
	{
		reader->Update();
	} catch (itk::ExceptionObject & e)
	{
		std::cerr << "exception in file reader " << std::endl;
		std::cerr << e << std::endl;
	}

	_volume = reader->GetOutput();

	cout << "volume read [ok]" << endl;

}

Super_voxels::Super_voxels(Grid* __grid)
{
	_grid = __grid;

	//default values
	_lambda_0 = 1;
	_lambda_1 = 0.5;
	_threshold = 0; //actually is not used
	_iterations = 5;

}

}
#endif /* SUPER_VOXELS_H_ */
