#pragma once
//Declaring Waypoint class

class Waypoint {
private:
	double latitude = 0, longitude = 0, altitude = 0, speed = 0;
	int gps = 0, power = 0, pitch = 0, roll = 0, yaw = 0;
	bool motorOn = 0;
	double distance = 0;
public:
	//parameter prefix i stands for input to distinguish from private variables
	//Constructors
	Waypoint() {};
	Waypoint(double ilat, double ilon, double ialt, double ispeed,
		int igps, int ipower, int ipitch, int iroll, int iyaw,
		bool imotorOn, double idist);
	~Waypoint() {};

	//Function to set the data of a waypoint 
	void setWaypoint(double ilat, double ilon, double ialt, double ispeed,
		int igps, int ipower, int ipitch, int iroll, int iyaw,
		bool imotorOn, double idist);

	//get value of private variables
	double getLat() { return latitude; }
	double getLon() { return longitude; }
	double getAlt() { return altitude; }
	double getSpeed() { return speed; }
	int getGps() { return gps; }
	int getPow() { return power; }
	int getPitch() { return pitch; }
	int getRoll() { return roll; }
	int getYaw() { return yaw; }
	bool getMotorOn() { return motorOn; }
	double getDist() { return distance; }

	//set individual values
	void setDist(double idist) { distance = idist; }
};