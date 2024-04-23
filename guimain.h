#include <wx/splitter.h>
#include <wx/wx.h>
#include <wx/log.h>
#include <wx/font.h>
#include <wx/mstream.h>
#include "audiofile.h"

//#include <iostream>

class MyApp : public wxApp
{
public:
    virtual bool OnInit() override;
};
    

wxIMPLEMENT_APP(MyApp);

class MyFrame : public wxFrame
{
private:

    wxBitmapButton* m_play_pause_button;
    wxListBox* listbox;
    wxStaticText* timeLabel;
    wxSlider* timing_slider;
    AudioFiles* audiofiles;
    AudioFile* audiofile;
    wxStaticText* titleText;
    wxStaticText* titleText2;
    wxStaticText* artistText;
    wxStaticText* artistText2;
    wxStaticText* albumText;
    wxStaticText* albumText2;
    wxStaticText* yearText;
    wxStaticText* yearText2;
    wxStaticBitmap* picture;
    bool isPlaying;
    bool starting;
    bool hasopened;
    //event handler
    void resetFileMetadata();
    void OnButtonMouseEnter(wxMouseEvent& event);
    void OnButtonMouseLeave(wxMouseEvent& event);
    void On_Prev_Button_Clicked(wxCommandEvent& evt);
    void On_Play_Pause_Button_Clicked(wxCommandEvent& evt);
    void On_Next_Button_Clicked(wxCommandEvent& evt);
    void On_My_Compuer_Clicked(wxCommandEvent& evt);
    void On_Volume_Slider_Changed(wxCommandEvent& evt);

    void OnMouseEvent(wxMouseEvent& evt);

    void On_Close(wxCloseEvent& evt);
    

    // wxDECLARE_EVENT_TABLE(); // Impliment a Macro ... to bind with event handler
   
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    
};