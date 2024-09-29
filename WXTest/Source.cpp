#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif

#include "base.h"
#include <fstream>

IMPLEMENT_APP(MainApp) // Initializes the MainApp class and tells our program
  // to run it
    bool MainApp::OnInit()
{
    // Create an instance of our frame, or window
    MainFrame* MainWin = new MainFrame(_T("StrongMan"), wxPoint(200, 200), wxSize(400, 800));
    MainWin->Show(TRUE); // show the window
    SetTopWindow(MainWin); // and finally, set it as the main window

    return TRUE;
}

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_TEXT_ENTER(INPUT_path, MainFrame::SavePath)
EVT_BUTTON(BUTTON_logevs, MainFrame::LogEvents)
EVT_BUTTON(BUTTON_regevs, MainFrame::RegEvents)
EVT_BUTTON(BUTTON_logcompetitors, MainFrame::LogCompetitors)
EVT_BUTTON(BUTTON_regcompetitors, MainFrame::RegCompetitors)
EVT_BUTTON(BUTTON_log_ev1, MainFrame::LogEventResult)
EVT_BUTTON(BUTTON_log_ev2, MainFrame::LogEventResult)
EVT_BUTTON(BUTTON_log_ev3, MainFrame::LogEventResult)
EVT_BUTTON(BUTTON_log_ev4, MainFrame::LogEventResult)
EVT_BUTTON(BUTTON_log_ev5, MainFrame::LogEventResult)
EVT_BUTTON(BUTTON_log_ev6, MainFrame::LogEventResult)
EVT_BUTTON(BUTTON_log_ev7, MainFrame::LogEventResult)
EVT_BUTTON(BUTTON_log_ev8, MainFrame::LogEventResult)
EVT_BUTTON(BUTTON_log_ev9, MainFrame::LogEventResult)
EVT_BUTTON(BUTTON_log_ev10, MainFrame::LogEventResult)
EVT_BUTTON(BUTTON_reg_ev1, MainFrame::CalculateEventResult)
EVT_BUTTON(BUTTON_reg_ev2, MainFrame::CalculateEventResult)
EVT_BUTTON(BUTTON_reg_ev3, MainFrame::CalculateEventResult)
EVT_BUTTON(BUTTON_reg_ev4, MainFrame::CalculateEventResult)
EVT_BUTTON(BUTTON_reg_ev5, MainFrame::CalculateEventResult)
EVT_BUTTON(BUTTON_reg_ev6, MainFrame::CalculateEventResult)
EVT_BUTTON(BUTTON_reg_ev7, MainFrame::CalculateEventResult)
EVT_BUTTON(BUTTON_reg_ev8, MainFrame::CalculateEventResult)
EVT_BUTTON(BUTTON_reg_ev9, MainFrame::CalculateEventResult)
EVT_BUTTON(BUTTON_reg_ev10, MainFrame::CalculateEventResult)
END_EVENT_TABLE()

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize
    & size) : wxFrame((wxFrame*)NULL, -1, title, pos, size)
{

    LogPath = new wxTextCtrl(this, INPUT_path, _T("Input path to folder"), wxPoint(100, 10), wxSize(200, 20), wxTE_PROCESS_ENTER);
    
    LogEvs = new wxButton(this, BUTTON_logevs, _T("Log events"),
        wxPoint(100, 50), wxDefaultSize, 0);
    LogEvs->SetBackgroundColour(*wxYELLOW);

    RegisterEvs = new wxButton(this, BUTTON_regevs, _T("Register events"),
        wxPoint(100, 90), wxDefaultSize, 0);

    LogCompetits = new wxButton(this, BUTTON_logcompetitors, _T("Log competitors"),
        wxPoint(100, 130), wxDefaultSize, 0);

    RegCompetits = new wxButton(this, BUTTON_regcompetitors, _T("Register competitors"),
        wxPoint(100, 170), wxDefaultSize, 0);

    firstEventLogButtonId = BUTTON_log_ev1;
    firstEventCalculateButtonId = BUTTON_reg_ev1;

    comp = new Competition();
    comp->competitionName = "Strongman Slovenia";

    std::ofstream afile;
    //for (int i = 0; i < comp->numEvents; i++) {
    //    int id_log = firstEventLogButtonId + 2 * i;
    //    int id_reg = firstEventCalculateButtonId + 2 * i;
    //    eventButtons.push_back(new wxButton(this, id_log, _T("Log " + comp->events[i]->eventName + " results"),
    //        wxPoint(100, 170 + i * 80), wxDefaultSize, 0));
    //    eventButtons.push_back(new wxButton(this, id_reg, _T("Calculate " + comp->events[i]->eventName),
    //        wxPoint(100, 210 + i * 80), wxDefaultSize, 0));
    //}
    //comp->readCompetitors();
    //comp->competitionName = "Competition";
    //comp->numCompetitors = comp->competitors.size();
}

void MainFrame::SavePath(wxCommandEvent& event) {
    comp->datapath = static_cast<std::string>(LogPath->GetLineText(0));
    std::ofstream outfile;
    outfile.open(comp->datapath + "HELLO.txt");
    outfile.close();
    LogPath->Disable();
}

void MainFrame::LogEvents(wxCommandEvent& event) {
    LogEvs->SetBackgroundColour(*wxGREEN);
    RegisterEvs->SetBackgroundColour(*wxYELLOW);
}

void MainFrame::LogCompetitors(wxCommandEvent& event) {
    LogCompetits->SetBackgroundColour(*wxGREEN);
    RegCompetits->SetBackgroundColour(*wxYELLOW);
}

void MainFrame::RegEvents(wxCommandEvent& event)
{
    comp->readEvents();
    for (int i = 0; i < comp->numEvents; i++) {
        int id_log = firstEventLogButtonId + 2 * i;
        int id_reg = firstEventCalculateButtonId + 2 * i;
        eventButtons.push_back(new wxButton(this, id_log, _T("Log " + comp->events[i]->eventName + " results"),
            wxPoint(100, 210 + i * 80), wxDefaultSize, 0));
        eventButtons.push_back(new wxButton(this, id_reg, _T("Calculate " + comp->events[i]->eventName),
            wxPoint(100, 250 + i * 80), wxDefaultSize, 0));
    }
    RegisterEvs->SetBackgroundColour(*wxGREEN);
    LogCompetits->SetBackgroundColour(*wxYELLOW);
}

void MainFrame::RegCompetitors(wxCommandEvent& event)
{
    comp->readCompetitors();
    comp->numCompetitors = comp->competitors.size();
    RegCompetits->SetBackgroundColour(*wxGREEN);
    eventButtons[0]->SetBackgroundColour(*wxYELLOW);
}

void MainFrame::LogEventResult(wxCommandEvent& event) {
    int i = event.GetId() - firstEventLogButtonId;
    eventButtons[i]->SetBackgroundColour(*wxGREEN);
    eventButtons[i + 1]->SetBackgroundColour(*wxYELLOW);
}


void MainFrame::CalculateEventResult(wxCommandEvent& event) {
    std::ofstream outfile;
    int i = (event.GetId() - firstEventCalculateButtonId) / 2;
    currentEvent = i;
    currentEvType = comp->events[i]->eventType;
    comp->events[currentEvent]->completed = 1;
    comp->inputEvResults();
    comp->calculatePoints();
    outfile.open(comp->datapath + "e" + std::to_string(currentEvent + 1) + "_" + comp->events[currentEvent]->eventName + "_result.txt");
    comp->printEventResult(outfile);
    outfile.close();
    if (currentEvent < comp->numEvents - 1) {
        outfile.open(comp->datapath + "e" + std::to_string(currentEvent + 2) + "_" + comp->events[currentEvent + 1]->eventName + "_order.txt");
        comp->printDescending(outfile);
        outfile.close();
    }
    outfile.open(comp->datapath + "Standing after " + std::to_string(currentEvent + 1) + " events.txt");
    comp->printResult(outfile);
    outfile.close();

    int b_id = event.GetId() - firstEventCalculateButtonId + 1;
    eventButtons[b_id]->SetBackgroundColour(*wxGREEN);
    if (b_id < eventButtons.size() - 1) {
        eventButtons[b_id + 1]->SetBackgroundColour(*wxYELLOW);
    }

    //std::ofstream afile;
    //afile.open("output.txt", std::ios_base::app);
    //afile << (event.GetId() - firstEventCalculateButtonId) / 2 << "\n";
    //afile.close();
}

void MainFrame::OnExit(wxCommandEvent& event)
{
    delete comp;
    Close(TRUE); // Tells the OS to quit running this process
}