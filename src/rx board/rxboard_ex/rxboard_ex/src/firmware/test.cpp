#include <iostream>
using namespace std;

template<size_t T_width>
class DataContainer : public std::array<double, T_width> 
{
public:


	void fill(int num) {
		for (i = 0; i < DATAROW_LENGTH; i++)
			DataRow[i] = num;
	}
	int Pow(int factor) {
	}
	int Sqrt() {
	}

	DataRow() {};
	DataRow(int);
	DataRow operator + (DataRow);
	DataRow operator - (DataRow);
	DataRow operator / (int);
	DataRow operator += (DataRow);
	DataRow operator -= (DataRow);
};

#define DATAROW_LENGTH 4 

typedef DataContainer< DATAROW_LENGTH > DataRow;

void DataRow::DataRow(int a) {
	for (int i = 0; i < DATAROW_LENGTH; i++)
		DataRow[i] = a;
} 

DataRow DataRow::operator+ (DataRow param) {
	DataRow temp;

	for (int i = 0; i < DATAROW_LENGTH; i++)
		temp[i]= DataRow[i] + param[i];

}


int main(int argc, char** argv)
{
	DataRow d1, d2, d3;
	d1.fill(10); d2.fill(20);
	d3 = d1 + d2;   // Elementwise addition 
	d3 = d1 – d2;   // Elementwise subtraction 
	d3 = d1 / 5     // Divide all elements by a constant 
	d3 += d1;     // Compound assignment 
	d3 -= d2;
	d3 = d1.Pow(2);   // Raise all elements to a constant power(d1 unchanged) 
	d3 = d2.Sqrt();   // Square root of element (d2 unchanged) 
	return 0;
}