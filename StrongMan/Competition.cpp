#include "Competition.h"

int currentEvent = 0;
int currentEvType = 1;
std::string datapath = "D:/OneDrive/SSM 2022/StrongMan/DataAndResults/";
extern std::map<int, std::string> eventNames = {
    {1, "DEADLIFT"},
    {2, "SAND SACK"},
    {3, "FARMERS WALK"},
    {4, "TRUCK PULL"},
    {5, "VIKING PRESS"} };

Event::Event(std::string eN, int eT) : eventName{ eN }, eventType{eT} {}

Attempt::Attempt() {}
EventResult::EventResult() {}
Competitor::Competitor() {}

Competition::Competition(std::vector<int> evs) {
    numEvents = evs.size();
    for (int i = 0; i < numEvents; i++) {
        events.push_back(std::make_shared<Event>(eventNames[evs[i]], evs[i]));
    }
}

void Attempt::result() {
    std::ostringstream streamObjWeight;
    streamObjWeight << std::fixed; streamObjWeight << std::setprecision(2);
    streamObjWeight << weight;
    std::ostringstream streamObjDistance;
    streamObjDistance << std::fixed; streamObjDistance << std::setprecision(2);
    streamObjDistance << distance;
    std::ostringstream streamObjTime;
    streamObjTime << std::fixed; streamObjTime << std::setprecision(2);
    streamObjTime << time;
    std::string weight = streamObjWeight.str();
    std::string distance = streamObjDistance.str();
    std::string time = streamObjTime.str();

    switch (eventType) {
    case 1:
        resultValue = std::to_string(reps) + " * " + weight;
        break;
    case 2:
        resultValue = distance;
        break;
    case 3:
        if(completed) resultValue = weight + " kg";
        else resultValue = weight + " kg,  " + distance + " m";
        break;
    case 4:
        if (completed) resultValue = time;
        else resultValue = distance + " m";
        break;
    case 5:
        resultValue = std::to_string(reps) + " * " + weight;
        break;
    }
}

void Competition::calculatePoints() {
    int i = currentEvent;
    if (events[i]->completed == 1) {
        //currentEvType = events[i]->eventType;
        std::cout << "Inside first" << std::endl;
        std::sort(competitors.begin(), competitors.end(), pComp);
        std::cout << "sorted" << std::endl;
        for (int j = 0; j < numCompetitors; j++) {
            std::cout << competitors[j]->name << "\t" << competitors[j]->eventResults[0]->resultValue << std::endl;;
        }
        for (int j = 0; j < numCompetitors; j++) {
            competitors[j]->eventResults[i]->points = numCompetitors - j;
        }
        int count = 1;
        double sum = 0;
        int j = 0;
        while (j < numCompetitors - 1) {
            std::cout << j << std::endl;
            count = 1;
            sum = competitors[j]->eventResults[i]->points;
            while (j + count < numCompetitors) {
                if (*competitors[j + count] == *competitors[j]) {  // Change this to comparing results for god's sake!
                    sum += competitors[j + count]->eventResults[i]->points;
                    count++;
                }
                else break;
            }
            std::cout << count << std::endl;
            if (count > 1) {
                double newPoints = sum / count;
                for (int c = j; c < j + count; c++) {
                    competitors[c]->eventResults[i]->points = newPoints;
                }
            }
            j = j + count;
        }
        for (int j = 0; j < numCompetitors; j++) {
            competitors[j]->allPoints += competitors[j]->eventResults[i]->points;
        }
    }
}

void Competition::inputAttResult(std::string name, std::string fName, bool cmpl, double wt, double dist, double t, int rs) {
    std::shared_ptr<Competitor> competitor;
    for (std::shared_ptr<Competitor> c : competitors) {
        if (c->name == name && c->firstName == fName) {
            competitor = c;
            competitor->eventResults.push_back(std::make_shared<Attempt>());
            int attSz = competitor->eventResults.size();
            std::shared_ptr<Attempt> att = competitor->eventResults[attSz - 1];
            att->eventType = currentEvType;
            att->completed = cmpl;
            att->weight = wt;
            att->distance = dist;
            att->time = t;
            att->reps = rs;
            att->result();
            break;
        }
    }
}

void Competition::inputEvResults() {
    std::ifstream inFile(datapath + "e" + std::to_string(currentEvent + 1) + ".txt");
    std::string entry;
    std::string name;
    std::string fName;
    bool cmpl;
    double wt;
    double dist;
    double t;
    int rs;
    int i = 0;
    while (std::getline(inFile, entry))
    {
        std::istringstream iss(entry);
        std::getline(iss,name, '\t');
        std::getline(iss, fName, '\t');
        iss >> cmpl >> wt >> dist >> t >> rs;
        inputAttResult(name, fName, cmpl, wt, dist, t, rs);
        i++;
    }
    
}

void Competition::readCompetitors() {
    std::ifstream inFile(datapath + "CompetitorList.txt");
    std::string entry;
    int i = 0;
    while (std::getline(inFile, entry))
    {   
        std::istringstream iss(entry);
        competitors.push_back(std::make_shared<Competitor>());
        std::getline(iss, competitors[i]->name, '\t');
        std::getline(iss, competitors[i]->firstName, '\t');
        std::getline(iss, competitors[i]->nationality, '\t');
        i++;
    }
}
void Competition::printEventResult(std::ofstream& log) {
    log << events[currentEvent]->eventName << "\n\n";
    for (std::shared_ptr<Competitor> competitor : competitors) {
        log << competitor->name << "\t\t" <<
            competitor->eventResults[currentEvent]->resultValue << "\t\t" <<
            std::fixed << std::setprecision(2) <<
            competitor->eventResults[currentEvent]->points << std::endl;
    }
}

void Competition::printResult(std::ofstream& log) {
    std::sort(competitors.begin(), competitors.end(), overallComp);
    log << "Name" << "\t\t" << "First name";
    for (int i = 0; i <= currentEvent; i++) {
        log << "\t\t" << events[i]->eventName + " pts";
    }
    log << "\t\tAll pts" << std::endl;
    for (std::shared_ptr<Competitor> competitor : competitors) {
        log << competitor->name << "\t\t" << competitor->firstName;
        for (std::shared_ptr<Attempt> a : competitor->eventResults) {
            log << "\t\t" << std::fixed << std::setprecision(2) << a->points;
        }
        log << "\t\t" << std::fixed << std::setprecision(2) << competitor->allPoints << std::endl;
    }
}

void Competition::printDescending(std::ofstream& log) {
    if (currentEvent == numEvents - 2) {
        std::sort(competitors.begin(), competitors.end(), overallComp);
    }
    log << events[currentEvent + 1]->eventName << "\n\n";
    log << "Name" << "\t" << "First name" << "\t" << "Completed" << "\t" << "Weight"
        << "\t" << "Distance" << "\t" << "Time" << "\t" << "Reps" << std::endl;
    for (int i = numCompetitors - 1; i >= 0; i--) {
        log << competitors[i]->name << "\t" << competitors[i]->firstName << std::endl;
    }
}

bool pComp(const std::shared_ptr<Competitor>& c1, const std::shared_ptr<Competitor>& c2) { return *c1 < *c2; }
bool overallComp(const std::shared_ptr<Competitor>& c1, const std::shared_ptr<Competitor>& c2) { return c1->allPoints > c2->allPoints; }