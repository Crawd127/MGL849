#include <iostream>
using namespace std;

int main()
{
	float desiredTempValue;
	while(1)
	{
			askForTemperature(&desiredTempValue);
	}
}

void askForTemperature(float * temperature)
{
	cout << "Please enter the desired temperature value: ";
	cin >> temperature;
}