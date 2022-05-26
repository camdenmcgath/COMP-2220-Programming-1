//Camden McGath 03/15/22 Ch6 Speed and Distance and Functions
//Breaks up Ch4 program calculating speed of sound or distance between pixels into functions
//Collab: Justin Fairbanks, Cole McCall



#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include <iomanip>
#include <iostream>


using namespace std;

//Function prototypes

//Connversions for pixels to feet
double xCoordToFeet(double, double, double);
double yCoordToFeet(double, double, double);

//Speed
double speedCalc(double, double);

//Distance 
double distanceCalc(double, double, double, double, double);

//Test driver
void driver();

int main()
{

	char repeatMenu;

	do {
		//User Decide which calculation
		cout << "\n Which calculation would you like to perform?\n";
		cout << "   s) " << "Calculate Speed of Sound Through A Medium\n";
		cout << "   d) " << "Calculate Distance Between Two Pixels\n";
		cout << "   t) " << "Run test driver\n";

		char chooseCalc; //user's choice of speed of light or distance between two pixels
		cin >> chooseCalc;
		cout << endl; 

		if (chooseCalc == 's') {

			double materialSpeed; //speed of sound in feet/second through material
			double soundDistance = -1000; //distance sound will travel, from user input
			bool isSelected = false; //tracks if valid material choice was input 
			bool positiveDist = false;
			do {

				cout << "   Select A Material\n";
				cout << "      a) Air\n";
				cout << "      s) Steel\n";
				cout << "      w) Water\n";

				char chooseMaterial; //user's choice of material for sound to travel through 
				cin >> chooseMaterial;

				if (chooseMaterial == 'a') {
					materialSpeed = 1100;
					cout << "Input Distance for Sound to Travel (in feet): ";
					cin >> soundDistance;
				}
				else if (chooseMaterial == 's') {
					materialSpeed = 16400;
					cout << "Input Distance for Sound to Travel (in feet): ";
					cin >> soundDistance;
				}
				else if (chooseMaterial == 'w') {
					materialSpeed = 4900;
					cout << "Input Distance for Sound to Travel (in feet): ";
					cin >> soundDistance;
				}

				if ((chooseMaterial == 'a') || (chooseMaterial == 's') || (chooseMaterial == 'w')) {
					isSelected = true;
				}
				else if (!isSelected) {
					cout << "\nInput invalid, try again.\n\n";
					continue;
				}
				if (soundDistance > 0) {
					positiveDist = true;
				}
				else if (!positiveDist) {
					cout << "\nInput invalid, negative distance, try again.\n\n";
					continue;
				}
			} while ((!positiveDist) || !isSelected);

			double soundResult = speedCalc(materialSpeed, soundDistance);
			cout << "The Sound will take " << setprecision(4) << fixed << soundResult << " seconds to travel " << soundDistance << " feet.\n\n";

		}
		else if (chooseCalc == 'd') {
			//declaring varibales for user input
			double in_droneHeight;
			double in_x_pixelSource, in_y_pixelSource; //Initial pixel cordinates from user 
			double in_x_pixelDest, in_y_pixelDest; //Final pixel coordinates from user

			cout << "Input Height of Drone (in feet): ";
			cin >> in_droneHeight;
			cout << "Input Source X-pixel and Y-pixel (seperated by a space): ";
			cin >> in_x_pixelSource >> in_y_pixelSource;
			cout << "Input Destination X-pixel and Y-pixel (they will be seperated by a space): ";
			cin >> in_x_pixelDest >> in_y_pixelDest;
			double distResult = distanceCalc(in_droneHeight, in_x_pixelSource, in_y_pixelSource, in_x_pixelDest, in_y_pixelDest);
			cout << "The distance between the two pixels is " << setprecision(2) << fixed << distResult << endl << endl;
		}
		else if (chooseCalc == 't') {
			driver();
		}
		cout << "Enter \"y\" to perform another calculation, any other key to exit: ";
		cin >> repeatMenu;

	} while (repeatMenu == 'y');

	return 0;
}

//Conversions for pixels to feet
double xCoordToFeet(double camAngle, double xPixelVal, double droneHeight) {
	double xCoordInFeet = tan((camAngle / 2.0) * (xPixelVal / 2000.0)) * droneHeight;
	return xCoordInFeet;
}
double yCoordToFeet(double camAngle, double yPixelVal, double droneHeight) {
	double yCoordInFeet = tan((camAngle * 3.0 / 4.0 / 2.0) * (yPixelVal / 1500.0)) * droneHeight;
	return yCoordInFeet;
}

//Speed calculation
double speedCalc(double materialSpeedPar, double soundDistancePar) {
	double speedResult = soundDistancePar / materialSpeedPar;
	return speedResult;
}

//Distance calculation
double distanceCalc(double droneHeight, double x_pixelSource, double y_pixelSource, double x_pixelDestination, double y_pixelDestination) { 

	//Calculations
	//Converting to Coordinate System
	x_pixelSource -= 2000;
	y_pixelSource -= 1500;
	x_pixelDestination -= 2000;
	y_pixelDestination -= 1500;
	//Converting Camera Angle to radians
	double camAngle = 94;
	camAngle *= (M_PI / 180.0);
	//converting coordinates to feet
	x_pixelSource = xCoordToFeet(camAngle, x_pixelSource, droneHeight);
	y_pixelSource = yCoordToFeet(camAngle, y_pixelSource, droneHeight);
	x_pixelDestination = xCoordToFeet(camAngle, x_pixelDestination, droneHeight);
	y_pixelDestination = yCoordToFeet(camAngle, y_pixelDestination, droneHeight);

	//calculate distance between the two pixels in feet
	double finalDistance = sqrt(pow((x_pixelDestination - x_pixelSource), 2) + pow((y_pixelDestination - y_pixelSource), 2));
	
	return finalDistance;
	
}

//Driver tests
void driver() {
	//Change function inputs to test
	//Pay attention to cout statements

	//Speed calulation tests
	double airTest = speedCalc(1100, 8000);
	cout << "It will take the sound " << setprecision(4) << fixed << airTest << " seconds to travel 8000 feet through air.\n";
	double steelTest = speedCalc(16400, 30000);
	cout << "It will take the sound " << setprecision(4) << fixed << steelTest << " seconds to travel 30,000 feet through steel.\n";
	double waterTest = speedCalc(490, 900);
	cout << "It will take the sound " << setprecision(4) << fixed << waterTest << " seconds to travel 900 feet through water.\n\n";
	
	//Pixel distance calculation tests
	double test1 = distanceCalc(300, 527, 1306, 638, 1273); //length of smaller shed parallel to track
	cout << "The distance between the pixels is " << setprecision(2) << fixed << test1 << endl;
	double test2 = distanceCalc(300, 674, 1278, 696, 1344); //length of smaller shed perpendicular to track 
	cout << "The distance between the pixels is " << setprecision(2) << fixed << test2 << endl;
	double test3 = distanceCalc(300, 121, 1308, 353, 1294); //length of larger shed parallel to track
	cout << "The distance between the pixels is " << setprecision(2) << fixed << test3 << endl;
	double test4 = distanceCalc(300, 409, 1188, 420, 1396); //length of larger shed perpendicular to track
	cout << "The distance between the pixels is " << setprecision(2) << fixed << test4 << endl << endl;
}