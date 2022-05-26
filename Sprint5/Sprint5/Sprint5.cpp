// Sprint #5  assignment for Programming 1
// Read waypoint data from the VPU csv file, store data in parallel arrays, sort parallel arrays 
// Create a class that stores data as waypoint objects
// Resources: 
// Help from: Cole McCall
//** fileMenu stuck in infinite loop
//** Possibly break up driver function into read/write functions?
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <math.h>
#include "Waypoint.h"

#define pi 3.14159265358979323846

using namespace std;

//Menu prototypes
void mainMenu();
void latInput(double&);
void longInput(double&);
void outputOptions(double&, double&, Waypoint*);
void rerunMenu(/*int, int, double&, double&, Waypoint**/);
void print(int, Waypoint*);
//void driverMenu();
void driver();

//Working with data prototypes
void readData(int, int, ifstream&, double, double, Waypoint*);
void sortWaypoints(int, Waypoint*);
void swap(Waypoint&, Waypoint&);

//Distance calculation functions prototypes
double distanceCalc(double, double, double, double);
double distanceCalcTrig(double, double, double, double, double);
double xCoordToFeet(double, double, double);
double yCoordToFeet(double, double, double);
std::pair<double, double> CoordinateToCoordinate(double, double, double, double);
double deg2rad(double);
double rad2deg(double);

int main() {
	mainMenu();
	//Exit prgram
	cout << "Press enter to close: \n";
	cin.get();
	return 0;
}
//Menu functions
void mainMenu() {
	cout << "Enter '1' to open the vpu2015.03.12.11.47.13.csv file.\n";
	cout << "Enter '2' to open a file of your choice.\n";
	cout << "Enter '3' to run the driver.\n";
	char fileMenu;
	cin >> fileMenu;
	bool validChoice = false;
	ifstream inFile;
	string fileName;
	do {
		if (fileMenu == '1') {
			inFile.open("vpu2015.03.12.11.47.13.csv");
			validChoice = true;

			double userLat;
			double userLong;
			latInput(userLat);
			longInput(userLong);

			//rerieve number of data rows 
			string rowStr;
			getline(inFile, rowStr, ',');
			int rowTotal = stoi(rowStr);
			//skip the remaining first two lines
			string junk;
			getline(inFile, junk);
			getline(inFile, junk);

			//Dynamically allocate array of Waypoints
			Waypoint* waypointArr = new Waypoint[rowTotal];

			int rowCount = 0;
			readData(rowCount, rowTotal, inFile, userLong, userLat, waypointArr);
			//sort arrays, from slide 23 Ch8 powerpoint
			sortWaypoints(rowTotal, waypointArr);
			outputOptions(userLat, userLong, waypointArr);

			//Close file and clean data
			inFile.close();
			delete[] waypointArr;
			waypointArr = nullptr;

		}
		else if (fileMenu == '2') {
			do { //get file from user
				cout << "Enter the path of the VPU weather file\n";
				getline(cin, fileName);

				inFile.open(fileName); //open file to read data

				if (!inFile) {
					cout << "ERROR OPENING FILE, PATH COULD NOT BE FOUND\n\n";
				}
			} while (!inFile);
			validChoice = true;

			//get user input 
			//Get user's latitude and longitude
			double userLat;
			double userLong;
			latInput(userLat);
			longInput(userLong);

			//rerieve number of data rows 
			string rowStr;
			getline(inFile, rowStr, ',');
			int rowTotal = stoi(rowStr);
			//skip the remaining first two lines
			string junk;
			getline(inFile, junk);
			getline(inFile, junk);

			//Dynamically allocate array of Waypoints
			Waypoint* waypointArr = new Waypoint[rowTotal];

			int rowCount = 0;
			readData(rowCount, rowTotal, inFile, userLong, userLat, waypointArr);
			//sort arrays, from slide 23 Ch8 powerpoint
			sortWaypoints(rowTotal, waypointArr);
			outputOptions(userLat, userLong, waypointArr);

			//Close file and clean data
			inFile.close();
			delete[] waypointArr;
			waypointArr = nullptr;
		}
		else if (fileMenu == '3') {
			driver();
			validChoice = true;
		}
		if (!validChoice) {
			cout << "Please enter '1','2' or '3'.\n\n";
		}
	} while (!validChoice);

	rerunMenu();
}
void latInput(double& lat) {
	bool latValid = true;
	do {
		latValid = true;
		cout << "Enter latitude: ";
		cin >> lat;
		if ((lat < -90) || (lat > 90)) {
			latValid = false;
			cout << "Invalid latitude value. Acceptable values are from -90 to 90.\n\n";
		}
	} while (!latValid);

	cout << endl;
}
void longInput(double& lon) {
	bool longValid = true;
	do {
		longValid = true;
		cout << "Enter longitude: ";
		cin >> lon;
		if ((lon < -180) || (lon > 180)) {
			longValid = false;
			cout << "Invalid longitude value. Acceptable values are from -180 to 180.\n\n";
		}
	} while (!longValid);

	cout << endl;
}
void outputOptions(double& uLat, double& uLon, Waypoint* arr) {
	bool validOption;
	validOption = true;
	do {
		cout << "Enter '1' to print the 100 closest waypoints.\n";
		cout << "Enter '2' to print the single closest waypoint.\n";
		char option;
		cin >> option;

		if (option == '1') {
			print(100, arr);
		}
		else if (option == '2') {
			print(1, arr);

			if ((uLat == (arr)->getLat()) && (uLon == (arr)->getLon())) {
				cout << "Coordintes yielding shortest distance are an exact match to yours!\n";
			}
		}
		else {
			validOption = false;
			cout << "Invalid option. Please enter a valid option.";
		}
	} while (!validOption);
}
void rerunMenu() {
	char rerun = 'y';

	while (rerun == 'y') {
		cout << "Enter 'y' to rerun the menu process: ";
		cin >> rerun;
		if (rerun == 'y') {
			mainMenu();
		}
		else {
			break;
		}
	}
}
void print(int numRows, Waypoint* arr) {
	cout << "         Latitude          Longitude      Altitude(m)    Speed(mph)      Gps       Yaw        MotorOn       Distance\n";
	cout << "-----------------------------------------------------------------------------------------------------------------------\n";
	for (int rowCount = 0; rowCount < numRows; rowCount++) {
		cout << fixed << setprecision(4) << setw(10) << "" << (arr + rowCount)->getLat();
		cout << fixed << setprecision(4) << setw(10) << "" << (arr + rowCount)->getLon();
		cout << fixed << setprecision(0) << setw(10) << "" << setw(2) << (arr + rowCount)->getAlt();
		cout << fixed << setprecision(2) << setw(10) << "" << (arr + rowCount)->getSpeed();
		cout << fixed << setprecision(0) << setw(10) << "" << setw(2) << (arr + rowCount)->getGps();
		cout << fixed << setprecision(0) << setw(10) << "" << (arr + rowCount)->getYaw();
		cout << fixed << setprecision(0) << setw(10) << "" << (arr + rowCount)->getMotorOn();
		cout << fixed << setprecision(2) << setw(10) << "" << (arr + rowCount)->getDist();
		cout << endl;
	}

}
//void driverMenu() {
//	cout << "Enter 'd' to run the driver.\n";
//	cout << "Enter 'c' to run with your own values.\n";
//	char userChoice;
//	cin >> userChoice;
//
//	bool isValid = true;
//	do {
//		if (userChoice == 'd') {
//			driver();
//		}
//		if (userChoice == 'c') {
//			//figure out how to flow main's code
//		}
//		else {
//			isValid = false;
//			cout << "Invalid option.\n\n";
//		}
//	} while (!isValid);
//}
void driver() {
	ifstream inData;
	string inFile = "vpu2015.03.12.11.47.13.csv";
	inData.open(inFile);

	double lat = 43.5803445, lon = -116.7406291;

	//rerieve number of data rows 
	string rowStr;
	getline(inData, rowStr, ',');
	int rowTotal = stoi(rowStr);
	//skip the remaining first two lines
	string junk;
	getline(inData, junk);
	getline(inData, junk);

	//Dynamically allocate array of Waypoints
	Waypoint* waypointArr = new Waypoint[rowTotal];

	int rowCount = 0;
	readData(rowCount, rowTotal, inData, lon, lat, waypointArr);
	//sort arrays, from slide 23 Ch8 powerpoint
	sortWaypoints(rowTotal, waypointArr);
	double altitude = waypointArr->getAlt();

	double pt1Dist = (distanceCalcTrig(altitude, 2000, 1500, 2000, 500));
	double pt2Dist = (distanceCalcTrig(altitude, 2000, 1500, 1000, 1500));
	double pt3Dist = (distanceCalcTrig(altitude, 2000, 1500, 2000, 2500));
	double pt4Dist = (distanceCalcTrig(altitude, 2000, 1500, 3000, 1500));

	int yaw = waypointArr->getYaw();
	int pt1Yaw = yaw;
	int pt2Yaw = (yaw + 90) % 360;
	int pt3Yaw = (yaw + 180) % 360;
	int pt4Yaw = (yaw + 270) % 360;
	
	std::pair<double, double> latlon1 = CoordinateToCoordinate(lat, lon, pt1Yaw, pt1Dist);
	std::pair<double, double> latlon2 = CoordinateToCoordinate(lat, lon, pt2Yaw, pt2Dist);
	std::pair<double, double> latlon3 = CoordinateToCoordinate(lat, lon, pt3Yaw, pt3Dist);
	std::pair<double, double> latlon4 = CoordinateToCoordinate(lat, lon, pt4Yaw, pt4Dist);

	ofstream outData;
	string outFile = "tp.txt";
	outData.open(outFile);

	cout << "Latitude:            " << setw(5) << lat << endl;
	cout << "Longitude:           " << setw(5) << lat << endl;
	cout << "VPU file name:       " << setw(5) << inFile << endl;
	cout << "Tie-point file name: " << setw(5) << inFile << endl;

	outData << "2000, 500, " << latlon1.first <<  " , " << latlon1.second << endl;
	outData << "1000, 1500, " << latlon2.first << " , " << latlon2.second << endl;
	outData << "2000, 2500, " << latlon3.first << " , " << latlon3.second << endl;
	outData << "3000, 1500, " << latlon4.first << " , " << latlon4.second << endl << endl;

	//clean data and close file
	delete[] waypointArr;
	waypointArr = nullptr;
	inData.close();
	outData.close();

	cout << "Data written to " << outFile << " successfully!";

}
//Functions for working with data
void readData(int rowNum, int totalRows, ifstream& fileObject, double uLon, double uLat, Waypoint* arr) {
	string inStr; //Variable to store each input data value before converting
	double inLat, inLon, inAlt, inSpeed;
	int inGps, inPower, inPitch, inRoll, inYaw;
	bool inMotorOn;
	double inDist;

	for (rowNum; rowNum < totalRows; rowNum++) {
		for (int i = 0; i < 17; i++) {
			if (i < 16) {
				getline(fileObject, inStr, ',');
				if (i == 0) {
					inLat = stod(inStr);
				}

				else if (i == 1) {
					inLon = stod(inStr);
				}
				else if (i == 2) {
					inAlt = stod(inStr);
					inAlt *= 0.3084; //converting from feet to meters
				}
				else if (i == 4) {
					inSpeed = stod(inStr);
				}
				else if (i == 11) {
					inGps = stoi(inStr);
				}
				else if (i == 12) {
					inPower = stoi(inStr);
				}
				else if (i == 13) {
					inPitch = stoi(inStr);
				}
				else if (i == 14) {
					inRoll = stoi(inStr);
				}
				else if (i == 15) {
					inYaw = stoi(inStr);
				}
			}

			else {
				getline(fileObject, inStr);
				inMotorOn = stoi(inStr);
			}
		}
		inDist = distanceCalc(uLat, uLon, inLat, inLon);
		(arr + rowNum)->setWaypoint(inLat, inLon, inAlt, inSpeed,
			inGps, inPower, inPitch, inRoll, inYaw,
			inMotorOn, inDist);
	}
}
void sortWaypoints(int totalRows, Waypoint* arr) {
	int minIndex;
	double	minValue;
	for (int start = 0; start < (totalRows - 1); start++) {
		minIndex = start;
		minValue = ((arr + start)->getDist());
		for (int index = start + 1; index < totalRows; index++) {
			if (((arr + index)->getDist()) < minValue) {
				minValue = (arr + index)->getDist();
				minIndex = index;
			}
		}
		swap(*(arr + start), *(arr + minIndex));
	}
}
//Haversine formula for calculating distance between long/lat points
double distanceCalc(double lat1, double lon1, double lat2, double lon2) {
	double theta, dist;
	if ((lat1 == lat2) && (lon1 == lon2)) {
		return 0;
	}
	else {
		theta = lon1 - lon2;
		dist = sin(deg2rad(lat1)) * sin(deg2rad(lat2)) + cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * cos(deg2rad(theta));
		dist = acos(dist);
		dist = rad2deg(dist);
		dist = dist * 60 * 1.1515;
		//Converting to meters, Justin's help
		dist = dist * 1.609344 * 1000;
	}
}
//Distance Calc from Ch4 drone imaging
double distanceCalcTrig(double droneHeight, double x_pixelSource, double y_pixelSource, double x_pixelDestination, double y_pixelDestination) {

	//Calculations
	//Converting to Coordinate System
	x_pixelSource -= 2000;
	y_pixelSource -= 1500;
	x_pixelDestination -= 2000;
	y_pixelDestination -= 1500;
	//Converting Camera Angle to radians
	double camAngle = 94;
	camAngle *= (pi / 180.0);
	//converting coordinates to feet
	x_pixelSource = xCoordToFeet(camAngle, x_pixelSource, droneHeight);
	y_pixelSource = yCoordToFeet(camAngle, y_pixelSource, droneHeight);
	x_pixelDestination = xCoordToFeet(camAngle, x_pixelDestination, droneHeight);
	y_pixelDestination = yCoordToFeet(camAngle, y_pixelDestination, droneHeight);

	//calculate distance between the two pixels in feet
	double finalDistance = sqrt(pow((x_pixelDestination - x_pixelSource), 2) + pow((y_pixelDestination - y_pixelSource), 2));

	return finalDistance;

}
double xCoordToFeet(double camAngle, double xPixelVal, double droneHeight) {
	double xCoordInFeet = tan((camAngle / 2.0) * (xPixelVal / 2000.0)) * droneHeight;
	return xCoordInFeet;
}
double yCoordToFeet(double camAngle, double yPixelVal, double droneHeight) {
	double yCoordInFeet = tan((camAngle * 3.0 / 4.0 / 2.0) * (yPixelVal / 1500.0)) * droneHeight;
	return yCoordInFeet;
}
//function for generating new coordinate from specified lon/lat, angle, distance
// Source: http://www.movable-type.co.uk/scripts/latlong.html
static const double PI = 3.14159265358979323846, earthDiameterMeters =
6371.0 * 2 * 1000;
double degreeToRadian(const double degree) {
	return (degree * PI / 180);
};
double radianToDegree(const double radian) {
	return (radian * 180 / PI);
};
std::pair<double, double> CoordinateToCoordinate(double latitude,
	double longitude,
	double angle,
	double meters)
{
	latitude = degreeToRadian(latitude);
	longitude = degreeToRadian(longitude);
	angle = degreeToRadian(angle);
	meters *= 2 / earthDiameterMeters;
	using namespace std;
	pair<double, double> coordinate;
	coordinate.first = radianToDegree(asin((sin(latitude) * cos(meters))
		+ (cos(latitude) * sin(meters) *
			cos(angle))));
	coordinate.second = radianToDegree(longitude
		+ atan2((sin(angle) * sin(meters) * cos(latitude)),
			cos(meters) - (sin(latitude) *
				sin(coordinate.first))));
	return coordinate;
}
//Degree and radian conversion functions used in Haversine
double deg2rad(double deg) {
	return (deg * pi / 180);
}
double rad2deg(double rad) {
	return (rad * 180 / pi);
}
void swap(Waypoint& point1, Waypoint& point2) {
	Waypoint hold;
	hold = point1;
	point1 = point2;
	point2 = hold;
}
