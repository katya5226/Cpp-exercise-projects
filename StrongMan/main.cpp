#include "Competition.h"


int main(void) {

	std::ofstream outfile;

	std::vector<int> compEvents = { 4, 1, 5, 3, 2 };
	Competition Comp(compEvents);
	Comp.readCompetitors();
	//std::vector<std::shared_ptr<Competitor>>::iterator q = overallComp.competitors.begin();
	//while (q != overallComp.competitors.end()) {
	//	if ((*q)->nationality != "SLO") q = overallComp.competitors.erase(q);
	//	else q++;
	//}
	Comp.competitionName = "Competition";
	Comp.numCompetitors = Comp.competitors.size();
	//int n = Comp.numCompetitors;
	//for (int i = 0; i < n; i++) {
	//	std::shared_ptr<Competitor> c = overallComp.competitors[i];
	//	c->startNum = i + 1;
	//	c->eventStartNum = i + 1;
	//}


	//************************************
	for (int i = 0; i < compEvents.size(); i++) {
		currentEvent = i;
		currentEvType = compEvents[i];
		Comp.events[currentEvent]->completed = 1;
		Comp.inputEvResults();
		Comp.calculatePoints();
		outfile.open(datapath + "e" + std::to_string(currentEvent + 1) + "_" + Comp.events[currentEvent]->eventName + "_result.txt");
		Comp.printEventResult(outfile);
		outfile.close();
		if (currentEvent < Comp.numEvents - 1) {
			outfile.open(datapath + "e" + std::to_string(currentEvent + 2) + "_" + Comp.events[currentEvent + 1]->eventName + "_order.txt");
			Comp.printDescending(outfile);
			outfile.close();
		}
		outfile.open(datapath + "Standing after " + std::to_string(currentEvent + 1) + " events.txt");
		Comp.printResult(outfile);
		outfile.close();
	}

	return 0;
}