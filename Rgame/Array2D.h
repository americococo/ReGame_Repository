#pragma once
template <class T>
class Array2D
{
private:
	T * _array;
	int _Weight,_height;

public:
	Array2D(int weight,int height)
	{
		_array = new T[weight*height];
		_Weight = weight;
		_height = height;
	}

	~Array2D()
	{
		if (NULL != _array)
		{
			delete[] _array;
		}

		_array = NULL;
		_Weight = 0,_height;
	}

	T Get(int x,int y)
	{
		return _array[_Weight*y+x];
	}
	//기본연산자 오버로딩

	operator T*()
	{
		return _array;
	}
	//&레퍼런스 != NULL반환


	void Resize(int newWight,int newheight)
	{
		int* newArray = new int[newheight*newWight];
		if (NULL == newArray) return;

		int minhegit = 0;
		minhegit = (!(newheight > _height)) ? newheight: _height;
		
		int minWight = 0;
		minWight = (!(newWight > _Weight)) ? newWight : _Weight;


		for(int y=0;y<minhegit;y++)
			for (int x = 0; x < minWight; x++)
		{
			newArray[y*newWight+x] = _array[_Weight*y+x];
		}

		if (NULL != _array)
			delete[] _array;

		_array = newArray;

		_Weight = newWight;
		_height = newheight;
	}

	bool saveData(const char * fileName)
	{
		FILE *fp = fopen(fileName, "w+b");
		if (NULL == fp) return false;

		int num = fwrite(_array, sizeof(T),_Weight*_height, fp);

		fclose(fp);

		if (num != _size)
			return false;

		return true;
	}

	bool LoadData(const char * fileName)
	{
		FILE *fp = fopen(fileName, "rb");
		if (NULL == fp) return false;

		int num = fread(_array, sizeof(T), _Weight*_height, fp);

		fclose(fp);

		if (num != _size)
			return false;

		return true;
	}
};
 