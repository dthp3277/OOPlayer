#include <wx/splitter.h>
#include <wx/wx.h>
#include <wx/log.h>
#include <wx/font.h>
#include <wx/mstream.h>
#include <iostream>

class myApp : public wxApp {
public:
	bool OnInit() override;
};

wxIMPLEMENT_APP(myApp);

class myFrame : public wxFrame {
public:
	void func();
	//wxStaticText* text;
	wxStaticBitmap* picture;
	myFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
};