#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/string.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
#include "competition.h"

#ifndef __BASE_H // Make sure to only declare these classes once
#define __BASE_H
class MainApp : public wxApp // MainApp is the class for our application
{
    // MainApp just acts as a container for the window,
public: // or frame in MainFrame
    virtual bool OnInit();
};

class MainFrame : public wxFrame // MainFrame is the class for our window,
{
    // It contains the window and all objects in it
public:
    MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    wxTextCtrl* LogPath;
    wxButton* LogEvs;
    wxButton* RegisterEvs;
    wxButton* LogCompetits;
    wxButton* RegCompetits;
    std::vector<wxButton*> eventButtons;
    //wxButton* LogEv1;
    //wxButton* CalcEv1;
    void OnExit(wxCommandEvent& event);
    int firstEventCalculateButtonId = 0;
    int firstEventLogButtonId = 0;

    Competition* comp;

    void SavePath(wxCommandEvent&);
    void LogEvents(wxCommandEvent&);
    void RegEvents(wxCommandEvent&);
    void LogCompetitors(wxCommandEvent&);
    void RegCompetitors(wxCommandEvent&);
    void LogEventResult(wxCommandEvent&);
    void CalculateEventResult(wxCommandEvent&);

    DECLARE_EVENT_TABLE()
};

enum
{
    INPUT_path = wxID_HIGHEST + 1,  // declares an id which will be used to call our button
    BUTTON_logevs,
    BUTTON_regevs,
    BUTTON_logcompetitors,
    BUTTON_regcompetitors,
    BUTTON_log_ev1,
    BUTTON_reg_ev1,
    BUTTON_log_ev2,
    BUTTON_reg_ev2,
    BUTTON_log_ev3,
    BUTTON_reg_ev3,
    BUTTON_log_ev4,
    BUTTON_reg_ev4,
    BUTTON_log_ev5,
    BUTTON_reg_ev5,
    BUTTON_log_ev6,
    BUTTON_reg_ev6,
    BUTTON_log_ev7,
    BUTTON_reg_ev7,
    BUTTON_log_ev8,
    BUTTON_reg_ev8,
    BUTTON_log_ev9,
    BUTTON_reg_ev9,
    BUTTON_log_ev10,
    BUTTON_reg_ev10
};

#endif