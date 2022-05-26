//definitions for Waypoint class from Waypoint.h

#include "Waypoint.h"
Waypoint::Waypoint(double ilat, double ilon, double ialt, double ispeed,
	int igps, int ipower, int ipitch, int iroll, int iyaw,
	bool imotorOn, double idist) {}

void Waypoint::setWaypoint(double ilat, double ilon, double ialt, double ispeed,
	int igps, int ipower, int ipitch, int iroll, int iyaw,
	bool imotorOn, double idist) {
	latitude = ilat;
	longitude = ilon;
	altitude = ialt;
	speed = ispeed;
	gps = igps;
	power = ipower;
	pitch = ipitch;
	roll = iroll;
	yaw = iyaw;
	motorOn = imotorOn;
	distance = idist;
}
