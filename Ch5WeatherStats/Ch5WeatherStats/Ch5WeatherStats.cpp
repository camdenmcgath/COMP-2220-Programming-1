//Camden McGath, 03/08/22
//Chapter 5 Project for Programming 1
//Will read in data from columns in a file containing weather statistics
//and output significant data after performing calculations on data gathered from file
//Collaboration: Malachi Tesarick, William Gibson, Kedrick Jones, Justin Fairbanks


#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

//converts month from integer to string (name) form
string namingMonthData(int monthP) { 
	string monthName;
	switch (monthP) {
		case 1: monthName = "January"; 
			break;
		case 2: monthName = "February"; 
			break;
		case 3: monthName = "March";
			break;
		case 4: monthName = "April";
			break;
		case 5: monthName = "May";
			break;
		case 6: monthName = "June";
			break;
		case 7: monthName = "July";
			break;
		case 8: monthName = "August";
			break;
		case 9: monthName = "September";
			break;
		case 10: monthName = "October";
			break;
		case 11: monthName = "November";
			break;
		case 12: monthName = "December";
			break;
	}
	return monthName;
}

int main() {
	
	ifstream inFile;
	string fileName; 

	
	//**Confirm input and validation of local and global paths
	do {
		cout << "Enter the path of the RAWS weather file\n";
		getline(cin, fileName);

		inFile.open(fileName); //open file to read data

		if (!inFile) {
			cout << "ERROR OPENING FILE, PATH COULD NOT BE FOUND\n\n";
		}
	} while (!inFile);

		cout << "File opened successfully!\n\n";
	
	//Declaring varibales needed to read values in from inFile
	int month = 0, day = 0, precip = 0, lowTemp = 0, hiTemp = 0, dummy;

	//Declaring variables necessary for calculating output weather stats
	int startMonth = 0, startDay = 0, endMonth = 0, endDay = 0;//First and last dates in the weather data
	int totalPrecip = 0, countPrecip = 0; //total millimeters of precip., counts number of days with precip.
	int initPrecipDay = 0, initPrecipMonth = 0, lastPrecipDay = 0, lastPrecipMonth = 0; //Dates for first and last days of precip.
	int maxLow = 0, maxLowMonth = 0, maxLowDay = 0;//lowest temp, date lowest temp occured
	int maxHi = 0, maxHiMonth = 0, maxHiDay = 0;//highest temp, date highest temp occured
	int sumLow = 0, sumHi = 0;//total of low temps, high temps, needed for avg. temp.
	int sumDays = 0;// total days, needed for calculating avg. temp.
	int dayCount = 0;//total days in the weather data file

	//read values from inFile
	while (inFile >> month >> day >> precip >> dummy >> dummy >> lowTemp >> hiTemp >> dummy >> dummy >> dummy) {
		dayCount++;
		if (dayCount == 1) {
			startMonth = month;
			startDay = day;
			maxLow = lowTemp;
			maxHi = hiTemp;
		}
		else if (dayCount != 1) {
			endMonth = month;
			endDay = day;
		}
		if (precip != 0) {
			inFile >> dummy >> dummy;
			if (countPrecip == 0) {
				initPrecipDay = day;
				initPrecipMonth = month;
			}

			lastPrecipDay = day;
			lastPrecipMonth = month;

			totalPrecip += precip;
			countPrecip++;

		}
		if (lowTemp <= maxLow) {
			maxLow = lowTemp;
			maxLowMonth = month;
			maxLowDay = day;
		}
		sumLow += lowTemp;
		if (hiTemp >= maxHi) {
			maxHi = hiTemp;
			maxHiMonth = month;
			maxHiDay = day;
		}
		sumHi += hiTemp;
		sumDays++;
	}
	inFile.close();//close file after reading data

	//Declaring variables for month names
	string nameInitPrecipMonth, nameLastPrecipMonth;
	string nameLowMonth, nameHiMonth;
	string nameStartMonth, nameEndMonth;

	//Convert months from integers to string names
	nameHiMonth = namingMonthData(maxHiMonth);
	nameLowMonth = namingMonthData(maxLowMonth);
	nameInitPrecipMonth = namingMonthData(initPrecipMonth);
	nameLastPrecipMonth = namingMonthData(lastPrecipMonth);
	nameStartMonth = namingMonthData(startMonth);
	nameEndMonth = namingMonthData(endMonth);

	//Calculate the average high and low temperatures
	double avgHiTemp = static_cast<double>(sumHi) / sumDays;
	double avgLowTemp = static_cast<double>(sumLow) / sumDays;
		
	//Output weather data 
	cout << "Weather Statistics\n";
	cout << "Range of Dates: " << nameStartMonth << ", " << startDay << " - " << nameEndMonth << ", " << endMonth << endl;
	cout << "Average High Temperature: " << fixed << setprecision(2) << avgHiTemp << " " << "degrees" << endl;
	cout << "Average Low Temperature: " << fixed << setprecision(2) << avgLowTemp << " " << "degrees" << endl;
	cout << "Maximum High Temperature: " << maxHi << " degrees, " << nameHiMonth << ", " << maxHiDay << endl;
	cout << "Maximum Low Temperature: " << maxLow << " degrees, " << nameLowMonth << ", " << maxLowDay << endl; 
	cout << "Total Rainfall: " << totalPrecip << " millimeters" << endl;
	cout << "Total Days With Rainfall: " << countPrecip << endl; 
	cout << "First Day It Rained: " << nameInitPrecipMonth << ", " << initPrecipDay << endl;
	cout << "Last Day It Rained: " << nameLastPrecipMonth << ", " << lastPrecipDay << endl << endl;
	
	cout << "Press enter to close\n";
	cin.get();
	return 0;
}
