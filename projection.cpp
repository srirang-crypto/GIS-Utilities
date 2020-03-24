#include <iostream>
#include <string>
#include <cmath>

using namespace std;

struct Point
{
	float x;
	float y;
};

struct Segment
{
	Point node1;
	Point node2;
};

struct Polyline
{
	Point nodes[10];
	int nNodes;
};

struct Equation
{
	float m;//slope
	float c;//constant
};

void displayPoint(Point p)
{
	cout << "(" << p.x << ", " << p.y << ")" << endl;
}

void displaySegment(Segment s)
{
	cout << "(" << s.node1.x << ", " << s.node1.y << ")" << "––"
	<< "(" << s.node2.x << ", " << s.node2.y << ")\n"; 
}

void displayPolyline(Polyline p)
{
	for (int i = 0; i < p.nNodes; i++)
	{
		displayPoint(p.nodes[i]);
	}
}

void displayEquation(Equation e)
{
	cout << "y = " << e.m << "x + " << e.c << endl;
}

float getDistance(Point p1, Point p2)//returns distance between given two points.
{
	return sqrt( pow((p2.y - p1.y),2) + pow((p2.x - p1.x),2));
}

Segment createSegment(Point p1, Point p2)//creates segment given two points
{
	Segment s;
	s.node1.x = p1.x;
	s.node1.y = p1.y;
	s.node2.x = p2.x;
	s.node2.y = p2.y;

	return s;
}

bool getPosition(Segment s, Point p)//check whether given point p is on a given segment s (p is on the line that contains s)
{
	bool position = 0;

	if (s.node2.x == s.node1.x){
		if (s.node2.y >= p.y and p.y >= s.node1.y)
			position = 1;
		else if (s.node2.x <= p.x and p.x <= s.node1.x)
			position = 1;
	}
	else{
		if (s.node2.x >= p.x and p.x >= s.node1.x)
			position = 1;

		else if (s.node2.x <= p.x and p.x <= s.node1.x)
			position = 1;
	}
	return position;
}

Point getIntersectionPoint(Equation e1, Equation e2)//return the point of intersection of two lines given their equations.
{
	Point p;
	p.x = (e2.c - e1.c)/(e1.m - e2.m);
	p.y = e1.m*p.x + e1.c;

	return p;
}

Equation getEquation(Segment s)//returns slope and constant of the equation of the line that passes through the given segment.
{
	Equation e;

	if (s.node2.x - s.node1.x != 0)
	{
		e.m = (s.node2.y - s.node1.y)/(s.node2.x - s.node1.x);
		e.c = s.node2.y - e.m*s.node2.x;
	}
	else
	{
		e.m = 2147483646;
		e.c = s.node2.x;
	}
	return e;
}

Equation getPerpendicularEquation(Equation e, Point p)//returns equation of the perpendicular line passing through a given point and line
{
	Equation ePerpendicular;
	ePerpendicular.m = -1/e.m;
	ePerpendicular.c = p.y + (1/e.m)*p.x;

	return ePerpendicular;
}

class Layer
{
private:
	string position;
	int editMode;

public:
	Layer()
	{
		position = "onCanvas";
		editMode = 0;
	}

	int getMode()
	{
		return editMode;
	}
	
};

class Point_Layer : public Layer
{
private:
	int featureCount;
	Point Features[10];

public:
	Point_Layer()
	{
		featureCount = 0;
	}

	Point getFeature(int index)
	{
		return Features[index];
	}

	int getfeatureCount()
	{
		return featureCount;
	}

	void addFeature(Point p_given)
	{
		Features[featureCount].x = p_given.x;
		Features[featureCount].y = p_given.y;
		featureCount += 1;
	}

	void deleteFeature()
	{
		featureCount -= 1;
	}

	void listFeatures()
	{
		for (int i = 0; i < featureCount; i++)
		{
			cout << "Point " << i + 1 << endl;
			cout << "(" << Features[i].x << "," << Features[i].y << ")" << endl;
		}
	}
};

class Polyline_Layer : public Layer
{
private:
	
public:
	int featureCount;
	Polyline Features[10];

	Polyline_Layer()
	{
		featureCount = 0;
	}

	int getfeatureCount()
	{
		return featureCount;
	}

	void addFeature(Polyline p_given)
	{
		Features[featureCount].nNodes = p_given.nNodes;

		for (int i = 0; i < p_given.nNodes; i++)
		{
		Features[featureCount].nodes[i].x = p_given.nodes[i].x;
		Features[featureCount].nodes[i].y = p_given.nodes[i].y;
		}

		featureCount += 1;			
	}

	Polyline getFeature(int index)
	{
		return Features[index];
	}

	void deleteFeature()
	{
		featureCount -= 1;
	}

	void listFeatures()
	{
		for (int i = 0; i < featureCount; i++)
		{
			cout << "Polyline " << i+1 << endl;
			for (int j = 0; j < Features[i].nNodes; j++)
			{
				cout << "(" << Features[i].nodes[j].x << "," << Features[i].nodes[j].y << ")" << "\t";
			}
			cout << endl;
		} 
	}
};

int main(int argc, char const *argv[])
{
	Point_Layer points;
	Polyline_Layer routes;

	Point intersectionPoint;

	Equation eq, eqP;

	int n;
	cout << "How many points do you want to add\n";
	cin >> n;

	for (int i = 0; i < n; i++)
	{
		Point a;
		cout << "Enter coordinates of Point\n";
		cin >> a.x >> a.y;
		points.addFeature(a);
	}
	points.listFeatures();

	int m;
	cout << "How many polylines do you want to add\n";
	cin >> m;

	for (int i = 0; i < m; i++)
	{
		Polyline pl;
		cout << "Enter number of nodes in polyline " << i + 1;
		cin >> pl.nNodes;
		for (int j = 0; j < pl.nNodes; j++)
		{
			cin >> pl.nodes[j].x;
			cin >> pl.nodes[j].y;
		}
		routes.addFeature(pl);
	}
	routes.listFeatures();

	for (int i = 0; i < points.getfeatureCount(); i++)
	{
		Point testPoint, closestPoint;
		float min_distance = 1000;
		testPoint = points.getFeature(i);
		for (int j = 0; j < routes.getfeatureCount(); j++)
		{
			Polyline testPolyline;
			testPolyline = routes.getFeature(j);
			for (int k = 0; k < testPolyline.nNodes - 1; k++)
			{
				Segment testSegment;
				Point intersectionPoint;
				float distance;

				testSegment = createSegment(testPolyline.nodes[k], testPolyline.nodes[k+1]);
				eq = getEquation(testSegment);
				eqP = getPerpendicularEquation(eq, testPoint);

				displayEquation(eq);
				displayEquation(eqP);

				intersectionPoint = getIntersectionPoint(eq, eqP);

				displayPoint(intersectionPoint);

				bool onSegment;

				onSegment = getPosition(testSegment, intersectionPoint);

				cout << onSegment << endl;

				if (onSegment == 0){
					cout << "notonsegment\n";
					if (getDistance(intersectionPoint, testSegment.node1) < getDistance(intersectionPoint, testSegment.node2))
						intersectionPoint = testSegment.node1;
                    else{
                        intersectionPoint = testSegment.node2;}
                }
				displayPoint(intersectionPoint);

				distance = getDistance(testPoint, intersectionPoint);
				if (distance < min_distance)
				{
					min_distance = distance;
					closestPoint = intersectionPoint;
				}
			}
		}
		Segment shift;
		shift = createSegment(testPoint, closestPoint);
		displaySegment(shift);
	}

	return 0;
}
