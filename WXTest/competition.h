#ifndef COMPETITION_H
#define COMPETITION_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <iterator>
#include <memory>
#include <exception>
#include <sstream>
#include <algorithm>
#include <map>

extern int currentEvent;
extern int currentEvType;
extern std::string datapath;
extern std::map<int, std::string> eventNames;

/*event types:
	1: deadlift
	2: sand sack
	3: farmers walk
	4: truck pull
	5: viking press*/

	// input order: name, first name, completed, weight, distance, time, reps


struct Event {
	int eventType{ 1 };
	std::string eventName;
	bool completed{ 0 };
	Event(std::string, int);
};


class Attempt {  // one attempt for one event for one person
public:
	Attempt();
	int eventType{ 1 };
	int cStartNumber{ 0 };  // starting number of the competitor
	double weight{ 0.0 }; // must be put in kg
	double distance{ 0.0 };  // must be put in m
	double time{ 0.0 };  // must be put in seconds
	int reps{ 0 };
	std::string resultValue;
	bool completed{ 1 };
	double points{ 0.0 };

	void result();

	bool operator<(const Attempt& b) const {
		if (eventType == b.eventType) {
			switch (eventType) {
			case 1:
				if (weight != b.weight) {
					if (((weight > b.weight) && (b.weight - weight < 50)) && ((reps >= 10) && (b.reps == 1))) {  //hardcoded; needs to be corrected
						return 0;
					}
					else return weight > b.weight;
				}
				else if (weight == b.weight) {
					return reps > b.reps;
				}
				break;
			case 2:
				return distance > b.distance;
				break;
			case 3:
				if ((completed == 0 && b.completed == 0) && (weight == b.weight))
					return distance > b.distance;
				else return weight > b.weight;
				break;
			case 4:
				if (completed && b.completed) {
					return time < b.time;
				}
				else if (!completed && b.completed) return 0;
				else if (completed && !b.completed) return 1;
				else if (!completed && !b.completed) return distance > b.distance;
				break;
			case 5:
				if (weight != b.weight) {
					return weight > b.weight;
				}
				else if (weight == b.weight) {
					return reps > b.reps;
				}
				break;
			}
		}
		else return -1;
	}
	bool operator==(const Attempt& b) const {
		if (eventType == b.eventType) {
			switch (eventType) {
			case 1:
				if (weight != b.weight) {
					return 0;
				}
				else if (weight == b.weight) {
					return reps == b.reps;
				}
				break;
			case 2:
				return distance == b.distance;
				break;
			case 3:
				if ((completed == 0 && b.completed == 0) && (weight == b.weight))
					return distance == b.distance;
				else return weight == b.weight;
				break;
			case 4:
				if (completed) {
					return time == b.time;
				}
				else return distance == b.distance;
				break;
			case 5:
				if (weight != b.weight) {
					return 0;
				}
				else if (weight == b.weight) {
					return reps == b.reps;
				}
				break;
			}
		}
		else return -1;
	}
};



class EventResult {  // all attempts for one event for one person
public:
	EventResult();
	int eventType{ 1 };
	int attCount{ 0 };
	std::vector<std::shared_ptr<Attempt>> attempts;  // to simplify, there will be only one attempt now,
	//meaning the new successful attempt will overwrite the last one. For this reason, I added attempts directly to competitor class.
	double points{ 0.0 };
};

//class DeadLift : public Event {
//public:
//	DeadLift(std::vector<double>);
//	std::vector<double> weights;
//	std::vector<std::shared_ptr<Competitor>> competitors;
//	std::vector<EventResult> eventResults;  // vector (for all competitors) of all attempts
//};

class Competitor {
public:
	Competitor();
	int startNum{ 0 };  // starting number of the competitor
	int eventStartNum{ 0 };  // starting number of the competitior for the current event
	std::string name;  // this is Family name
	std::string firstName;
	std::string nationality;
	double bodyWeight{ 0.0 };
	int age{ 0 };
	//std::vector<std::shared_ptr<EventResult>> eventResults;
	std::vector<std::shared_ptr<Attempt>> eventResults;
	double allPoints{ 0.0 };
	bool operator<(const Competitor& b) const {
		return *eventResults[currentEvent] < *b.eventResults[currentEvent];
	}
	bool operator==(const Competitor& b) const {
		return *eventResults[currentEvent] == *b.eventResults[currentEvent];
	}
};


class Competition {
public:
	std::string datapath = "C:/Users/katja/source/repos/WXTest/WXTest/DataAndResults/";
	Competition();
	std::string competitionName;
	std::vector<std::shared_ptr<Competitor>> competitors;
	int numCompetitors{ 0 };
	int numEvents{ 0 };
	std::vector<std::shared_ptr<Event>> events;
	void calculatePoints();
	void printEventResult(std::ofstream&);
	void printResult(std::ofstream&);
	void printDescending(std::ofstream&);
	void readEvents();
	void readCompetitors();
	void inputAttResult(std::string, std::string, bool, double, double, double, int);
	void inputEvResults();
};

bool pComp(const std::shared_ptr<Competitor>&, const std::shared_ptr<Competitor>&);
bool overallComp(const std::shared_ptr<Competitor>&, const std::shared_ptr<Competitor>&);


#endif  // COMPETITION_H#pragma once
