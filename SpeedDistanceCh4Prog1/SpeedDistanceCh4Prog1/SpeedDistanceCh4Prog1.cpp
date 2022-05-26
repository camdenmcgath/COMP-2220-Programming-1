#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include <iomanip>
#include <iostream>


using namespace std; 

double xCoordToFeet(double camAngle, double xPixelVal, double droneHeight) {
	double xCoordInFeet = tan((camAngle / 2.0) * (xPixelVal / 2000.0)) * droneHeight;
	return xCoordInFeet;
}
double yCoordToFeet(double camAngle, double yPixelVal, double droneHeight) {
	double yCoordInFeet = tan((camAngle * 3.0/4.0 / 2.0) * (yPixelVal / 1500.0)) * droneHeight;
	return yCoordInFeet;
}

//add y coordinate conversion 
int main()
{

	char repeatMenu; 

	do {
		//User Decide which calculation
		cout << "Which calculation would you like to perform?\n";
		cout << "   s) " << "Calculate Speed of Sound Through A Medium\n";
		cout << "   d) " << "Calculate Distance Between Two Pixels\n";
		
		char chooseCalc; //user's choice of speed of light or distance between two pixels
		cin >> chooseCalc;

		if (chooseCalc == 's') {

			double materialSpeed; //speed of sound in feet/second through material
			double soundDistance = -1000; //distance sound will travel, from user input
			bool isSelected = false; //tracks if valid material choice was input 
			bool positiveDist = false;
			do{ 

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
					cout << "Input invalid, try again.\n\n";
				}
				if (soundDistance > 0) {
					positiveDist = true;
				}
				else if (!positiveDist) {
					cout << "Input invalid, negative distance, try again.\n\n";
				}
			} 
			while ((!positiveDist) || !isSelected);


			cout << "The Sound will take " << setprecision(4) << fixed << (soundDistance / materialSpeed) << " seconds to travel " << soundDistance << " feet.\n\n";

		}
		else if (chooseCalc == 'd') {
			double droneHeight;
			double x_pixelSource, y_pixelSource; //Starting pixel from user
			double x_pixelDestination, y_pixelDestination; //Ending pixel from user 

			cout << "Input Height of Drone (in feet): ";
			cin >> droneHeight;
			cout << "Input Source X-pixel and Y-pixel (seperated by a space): ";
			cin >> x_pixelSource >> y_pixelSource;
			cout << "Input Destination X-pixel and Y-pixel (they will be seperated by a space): ";
			cin >> x_pixelDestination >> y_pixelDestination;
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
			y_pixelSource = yCoordToFeet(camAngle, y_pixelSource , droneHeight);
			x_pixelDestination = xCoordToFeet(camAngle, x_pixelDestination , droneHeight);
			y_pixelDestination = yCoordToFeet(camAngle, y_pixelDestination, droneHeight);

			//calculate distance between the two pixels in feet
			double finalDistance = sqrt(pow((x_pixelDestination - x_pixelSource), 2) + pow((y_pixelDestination - y_pixelSource), 2));
			
			//output final distance between the two pixels
			cout << "The distance between the two pixels is " << setprecision(2) << fixed << finalDistance << endl;
		}

		cout << "Press \"y\" to perform another calculation, any other key to exit: ";
		cin >> repeatMenu;

	} 
	while (repeatMenu == 'y');
	
	return 0;
}