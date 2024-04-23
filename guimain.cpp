#include "guimain.h"
#include "duration.h"
#include <sstream>

#include <mpeg/id3v2/id3v2tag.h>
#include <mpeg/id3v1/id3v1tag.h>
#include <mpeg/mpegfile.h>
#include <mpeg/id3v2/id3v2frame.h>
#include <mpeg/id3v2/id3v2header.h>
#include <mpeg/id3v2/frames/attachedpictureframe.h>
//initialization ma k k hunxa ta??

//using wxLogDebug() for showing output in the debug console of visual studio

bool MyApp::OnInit() {

    // making new frame/Window popup..
    MyFrame* frame = new MyFrame("OOPLAYER", wxPoint(200, 200), wxSize(1080, 600));

    frame->Show(true);
    return true;
}

// ENUM FOR EVENT TABLE.. Dynamic event handeling..
enum IDs {
    PLAY_PAUSE_BUTTON_ID = 2,
    PREV_BUTTON_ID = 3,
    NEXT_BUTTON_ID = 4,
    SHUFFLE_BUTTON_ID = 5,
    VOLUME_ID = 7
};

// DYNAMIC EVENT BINDER...

// Window bhitra k k hunuparxa ta ??
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size) {
    //wxFont* font = new wxFont(12,wxFONTFAMILY_DEFAULT, w, wxFONTWEIGHT_NORMAL, "tahoma");
    //SetFont(*font);
    SetMinSize(wxSize(1080, 600));
    SetMaxSize(wxSize(1080, 600));

    //CreateStatusBar();
    //SetStatusText("Have a Good Music Time");

    // making new panels with splitter ..
    // This order decides the precidence... 1st horizontal,, then after vertical

    wxSplitterWindow* horizontal_splitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxSize(300, 300),
       wxSP_BORDER | wxSP_LIVE_UPDATE);


    wxSplitterWindow* vertical_splitter = new wxSplitterWindow(horizontal_splitter, wxID_ANY, wxDefaultPosition, wxSize(300, 800),
        wxSP_BORDER | wxSP_LIVE_UPDATE);

    //making panels
    wxPanel* left = new wxPanel(vertical_splitter);
    wxPanel* right = new wxPanel(vertical_splitter);
    wxPanel* bottom = new wxPanel(horizontal_splitter);

    /* this sets the background color */
    left->SetBackgroundColour(wxColour(53, 47, 68));
    right->SetBackgroundColour(wxColour(0, 0, 0));
    bottom->SetBackgroundColour(wxColour(53, 21, 93));

    // sets minimun valid sizes
    horizontal_splitter->SetMinimumPaneSize(100);
   
    vertical_splitter->SetMinimumPaneSize(150);
   

    /* decides how to split the columns */

    vertical_splitter->SplitVertically(left, right);
    horizontal_splitter->SplitHorizontally(vertical_splitter, bottom);


    // Resizing windows... 1 to stay same after splitting. 0.5 garyo bhane changed..
    horizontal_splitter->SetSashGravity(1);
    vertical_splitter->SetSashGravity(1 / 3);


    /* BUTTONSSSSSSSSS  */
    int staticTextY = 20;
    int gap = 50;
    int posX = 20;
    wxStaticText* Library_text = new wxStaticText(left, wxID_ANY, "LIBRARY", wxPoint(posX, staticTextY));
    Library_text->SetForegroundColour(wxColor(255, 255, 255));
    
    wxButton* fav_button = new wxButton(left, wxID_ANY, "Favourites", wxPoint(posX+5, staticTextY+gap), wxSize(100, 35));
    wxButton* playlist_button = new wxButton(left, wxID_ANY, "Playlist", wxPoint(posX + 5, staticTextY + 3*gap), wxSize(100, 35));

    wxStaticText* MyComputer_text = new wxStaticText(left, wxID_ANY, "MY COMPUTER", wxPoint(posX + 5, staticTextY + 5*gap));
    MyComputer_text->SetForegroundColour(wxColor(255, 255, 255));
    wxButton* music_button = new wxButton(left, wxID_ANY, "My Music", wxPoint(25, staticTextY + 7*gap), wxSize(100, 35));



    listbox = new wxListBox(right, wxID_ANY, wxPoint(0, 0), wxSize(280, 470), 0, nullptr, wxLB_SINGLE);
    listbox->SetBackgroundColour(wxColour(94, 94, 91));
    listbox->SetForegroundColour(wxColour(255, 255, 255));

    int titleposY = 250;
    int titleposX = 370;
    titleText = new wxStaticText(right, wxID_ANY, "Title: ", wxPoint(300, titleposY));
    titleText->SetForegroundColour(wxColour(255, 255, 255));
    titleText->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    titleText2 = new wxStaticText(right, wxID_ANY, "", wxPoint(titleposX, titleposY));
    titleText2->SetForegroundColour(wxColour(255, 255, 255));
    titleText2->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));


    artistText = new wxStaticText(right, wxID_ANY, "Artist: ", wxPoint(300, titleposY + 50));
    artistText->SetForegroundColour(wxColour(255, 255, 255));
    artistText->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    artistText2 = new wxStaticText(right, wxID_ANY, "", wxPoint(titleposX, titleposY + 50));
    artistText2->SetForegroundColour(wxColour(255, 255, 255));
    artistText2->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));


    albumText = new wxStaticText(right, wxID_ANY, "Album: ", wxPoint(300, titleposY + 100));
    albumText->SetForegroundColour(wxColour(255, 255, 255));
    albumText->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    albumText2 = new wxStaticText(right, wxID_ANY, "", wxPoint(titleposX, titleposY + 100));
    albumText2->SetForegroundColour(wxColour(255, 255, 255));
    albumText2->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));


    yearText = new wxStaticText(right, wxID_ANY, "Year: ", wxPoint(300, titleposY + 150));
    yearText->SetForegroundColour(wxColour(255, 255, 255));
    yearText->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    yearText2 = new wxStaticText(right, wxID_ANY, "", wxPoint(titleposX, titleposY + 150));
    yearText2->SetForegroundColour(wxColour(255, 255, 255));
    yearText2->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    wxInitAllImageHandlers();
    wxImage image(wxT("C:\\Users\\dhira\\Downloads\\Background.png"), wxBITMAP_TYPE_PNG);

    wxBitmap bitmap(image);
    
    
    picture = new wxStaticBitmap(right, wxID_ANY, bitmap, wxPoint(400, 20));
    
    picture->SetBitmap(bitmap);
    //audio time data display
    timeLabel = new wxStaticText(bottom, wxID_ANY, "00:00", wxPoint(90, 20));
    timeLabel->SetForegroundColour(wxColor(255, 255, 255));

    //timer slider.
    timing_slider = new wxSlider(bottom, wxID_ANY, 0, 0, 100, wxPoint(90, 70), wxSize(800, -1));
    timing_slider->SetPageSize(1);
    //timing_slider->SetThumbLength(1);
    // volume slider
    wxSlider* volume_slider = new wxSlider(bottom, VOLUME_ID, 50, 0, 100, wxPoint(930, 70), wxSize(100, -1));
    //volume_slider->SetThumbLength(1);


    //bottom buttons
    wxInitAllImageHandlers();

    //image loading
    isPlaying = false;
    wxBitmap tester;
    tester.LoadFile(wxT("C:\\Users\\dhira\\source\\repos\\Cpp_Project_OOP\\Assets\\play.png"), wxBITMAP_TYPE_PNG);
    if (!tester.IsOk())
        wxLogMessage(wxT("bitmap couldn't be loaded"));
    
    wxButton* m_prev_button = new wxButton(bottom, PREV_BUTTON_ID, "<<", wxPoint(470, 45), wxSize(30, 30));
    m_play_pause_button = new wxBitmapButton(bottom, PLAY_PAUSE_BUTTON_ID, tester, wxPoint(510, 45), wxSize(30, 30));
    wxButton* m_next_button = new wxButton(bottom, NEXT_BUTTON_ID, ">>", wxPoint(550, 45), wxSize(30, 30));
   


    //dynamic binding
    m_prev_button->Bind(wxEVT_BUTTON, &MyFrame::On_Prev_Button_Clicked, this);
    m_play_pause_button->Bind(wxEVT_BUTTON, &MyFrame::On_Play_Pause_Button_Clicked, this);
    m_next_button->Bind(wxEVT_BUTTON, &MyFrame::On_Next_Button_Clicked, this);
  
    volume_slider->Bind(wxEVT_SLIDER, &MyFrame::On_Volume_Slider_Changed, this);


    //closing window
    this->Bind(wxEVT_CLOSE_WINDOW, &MyFrame::On_Close, this);

    left->Bind(wxEVT_LEFT_DOWN, &MyFrame::OnMouseEvent, this);
    right->Bind(wxEVT_LEFT_DOWN, &MyFrame::OnMouseEvent, this);
    bottom->Bind(wxEVT_LEFT_DOWN, &MyFrame::OnMouseEvent, this);

    //Mouse hovering.. display in log

    m_prev_button->SetClientData(new wxString("Previous song ?"));
    m_play_pause_button->SetClientData(new wxString("Play or pause ?"));

    m_next_button->SetClientData(new wxString("Next song ?"));
    


    m_prev_button->Bind(wxEVT_ENTER_WINDOW, &MyFrame::OnButtonMouseEnter, this);
    m_prev_button->Bind(wxEVT_LEAVE_WINDOW, &MyFrame::OnButtonMouseLeave, this);

    m_play_pause_button->Bind(wxEVT_ENTER_WINDOW, &MyFrame::OnButtonMouseEnter, this);
    m_play_pause_button->Bind(wxEVT_LEAVE_WINDOW, &MyFrame::OnButtonMouseLeave, this);


    m_next_button->Bind(wxEVT_ENTER_WINDOW, &MyFrame::OnButtonMouseEnter, this);
    m_next_button->Bind(wxEVT_LEAVE_WINDOW, &MyFrame::OnButtonMouseLeave, this);
    
   


    //opeing folders..
    music_button->Bind(wxEVT_BUTTON, &MyFrame::On_My_Compuer_Clicked, this);


    audiofiles = new AudioFiles();
    audiofile = new AudioFile(audiofiles);
    hasopened = false;
    starting = true;
}


//Event handler..

void MyFrame::OnButtonMouseEnter(wxMouseEvent& event) {
    wxButton* button = dynamic_cast<wxButton*>(event.GetEventObject());
    if (button) {
        wxString* message = static_cast<wxString*>(button->GetClientData());
        if (message) {
            wxLogStatus(*message);
        }
        else {
            wxLogStatus("No message found");
        }
    }
}



void MyFrame::OnButtonMouseLeave(wxMouseEvent& event) {
    wxLogStatus("");
    event.Skip();
}


//          BUTTONS
//          PRESSED


void MyFrame::On_Prev_Button_Clicked(wxCommandEvent& evt) {
    wxLogStatus("Previous");
    audiofile->stop();
    int np = audiofiles->nowPlaying();
    audiofiles->setPlay((np - 1) < 1 ? (np + 4) : (np - 1));
    audiofile->open(audiofiles->nowPlayingPath());
    audiofile->startPlaying();
    //repetitive part, to fix
    
    resetFileMetadata();

    evt.Skip();
}



void MyFrame::On_Play_Pause_Button_Clicked(wxCommandEvent& evt) {
    wxLogDebug("Play Pause Button Clicked");

    wxBitmap tester;

    //overly temporary code
    int currentSelection = listbox->GetSelection();
    wxLogDebug("%d", currentSelection);
    audiofiles->setPlay(currentSelection + 1);

    if (!isPlaying) {
        tester.LoadFile(wxT("C:\\Users\\dhira\\source\\repos\\Cpp_Project_OOP\\Assets\\pause.png"), wxBITMAP_TYPE_PNG);
        if (!tester.IsOk())
            wxLogMessage(wxT("bitmap couldn't be loaded"));
        isPlaying = true;
        if (starting) {
            starting = false;
        }
        else {
            audiofile->playpause();
        }
    }
    else {
        tester.LoadFile(wxT("C:\\Users\\dhira\\source\\repos\\Cpp_Project_OOP\\Assets\\play.png"), wxBITMAP_TYPE_PNG);
        if (!tester.IsOk())
            wxLogMessage(wxT("bitmap couldn't be loaded"));
        audiofile->playpause();
        isPlaying = false;
    }
    m_play_pause_button->SetBitmap(tester);


    if (audiofiles->nowPlaying() != -1 && !hasopened) {
        audiofile->open(audiofiles->nowPlayingPath());
        hasopened = true;
        audiofile->startPlaying();
        
        TagLib::FileRef f(audiofile->getPath().c_str());
        TagLib::Tag* tag = f.tag();
        std::ostringstream str;
        str << tag->year();

        TagLib::MPEG::File mpegfile(audiofile->getPath().c_str());

        if (mpegfile.hasID3v2Tag()) wxLogDebug("TRUEEEEE");
        else wxLogDebug("FALSEEEEE");


        titleText2->SetLabel(wxString(tag->title().toCString(true)));
        artistText2->SetLabel(wxString(tag->artist().toCString(true)));
        albumText2->SetLabel(wxString(tag->album().toCString(true)));
        yearText2->SetLabel(wxString(str.str()));


        double duration = audiofile->getDuration();
        double pauseDuration = 0.0f;
        Time t(duration);
        auto startTime = std::chrono::high_resolution_clock::now();
        while (true) {
            wxYield();
            auto currentTime = std::chrono::high_resolution_clock::now();
            auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count() / 1000.0f;
            
                Time time(elapsedTime);
                std::ostringstream timeText;
                timeText << time.getMinutes() << ":" << std::setfill('0') << std::setw(2) << time.getSeconds();
                timeLabel->SetLabel(wxString(timeText.str()));
           
                timing_slider->SetValue((elapsedTime / duration) * 100);
                if (elapsedTime > duration) break;
            }
            
    }   
    
    //handleaudio(); //yeah okay, but while audio is playing it cannot trigger other events as of now
    evt.Skip();
}


void MyFrame::On_Next_Button_Clicked(wxCommandEvent& evt) {
    wxLogStatus("Next");
    audiofile->stop();
    int np = audiofiles->nowPlaying();

    audiofiles->setPlay((np + 1) > audiofiles->giveCount() ? (np - 4) : (np + 1));

    //repetitive
    audiofile->open(audiofiles->nowPlayingPath());
    audiofile->startPlaying();

    resetFileMetadata();

    evt.Skip();
}
//volume control

void MyFrame::On_Volume_Slider_Changed(wxCommandEvent& evt) {
    int vol = evt.GetInt();
    wxString str = wxString::Format("Volume : %d", vol);
    audiofile->setVolume(static_cast<float>(vol) / 100.0f);
    wxLogDebug(str);
    evt.Skip();
}


void MyFrame::On_Close(wxCloseEvent& evt) {
    wxLogDebug("Window Closed");
    //wxWindow::Destroy(); //online documentation giving me this
    evt.Skip();
}


//Open Files


//In this example, a wxButton is added to the frame, and its click event is connected to the OnOpenButtonClicked function. This function creates a wxDirDialog for selecting a folder. Once a folder is selected, its path is retrieved and can be used as needed

void MyFrame::On_My_Compuer_Clicked(wxCommandEvent& event) {
    wxDirDialog dirDialog(this, "Choose a music folder", "", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);

    if (dirDialog.ShowModal() == wxID_OK) {
        wxString selectedPath = dirDialog.GetPath();
        
        // Now you can use 'selectedPath' to access the selected folder path
        // For example, you can print it to the console
        wxPrintf("Selected folder: %s\n", selectedPath);

        /* for temporary usage, I'm allocating audiofiles pointer jsut here*/

        audiofiles->setDirectory(selectedPath.ToStdString());
        audiofiles->getAudioFiles();
        
        for (auto i : audiofiles->getFilePaths()) {
            std::string fl = AudioFiles::getFileNameFromPath(i);
            listbox->Append(wxString(fl.substr(0, fl.size() - 4)));
        }
        
        //wxLogDebug(selectedPath);
    }
}


//checking positin of mouse..

void MyFrame::OnMouseEvent(wxMouseEvent& evt) {
    wxPoint mousePos = evt.GetPosition();
    wxString message = wxString::Format("Mouse Position (x=%d ,y=%d)", mousePos.x, mousePos.y);
    wxLogDebug(message);
}

void MyFrame::resetFileMetadata() {
    //todo, deal with the exception, tag was nullptr when you try to previous to the first file in the directory
    
    TagLib::FileRef f(audiofiles->nowPlayingPath().c_str());


    TagLib::Tag* tag = f.tag();
    std::ostringstream str;
    str << tag->year();


    /*trying hard to get the audio album art display working*/
    /* but it just isn't, 
    things just right now:
    taglib:;mpeg:;file is not opening properly gotta fix that
    */
    std::string mppath = audiofiles->nowPlayingPath();
    wxLogDebug("%s", mppath);
    TagLib::MPEG::File mpegFile(mppath.c_str());
    //well the error 
    wxLogDebug("%d", mppath.length());
    if (mpegFile.isOpen()) {
        wxLogDebug("HASSSSSSS");
    } else {
        wxLogDebug("HASNTTTTTTT");
    }

    //if (mpegFile.hasID3v2Tag()) {
    //    wxLogDebug("this has id3v2");


    //    TagLib::ID3v2::Tag* id3v2Tag = mpegFile.ID3v2Tag();

    //    TagLib::ID3v2::FrameListMap frameListMap = id3v2Tag->frameListMap();
    //    TagLib::ID3v2::FrameListMap::ConstIterator it = frameListMap.find("APIC");

    //    if (it != frameListMap.end()) {
    //        TagLib::ID3v2::FrameList frameList = it->second;
    //        for (TagLib::ID3v2::FrameList::ConstIterator frameIt = frameList.begin(); frameIt != frameList.end(); ++frameIt) {
    //            TagLib::ID3v2::AttachedPictureFrame* coverFrame = static_cast<TagLib::ID3v2::AttachedPictureFrame*>(*frameIt);
    //            if (coverFrame) {
    //                TagLib::ByteVector imageData = coverFrame->picture();

    //                // Create a wxImage from the TagLib image data
    //                wxMemoryInputStream stream(imageData.data(), imageData.size());
    //                wxImage image(stream, wxBITMAP_TYPE_JPEG);

    //                if (image.IsOk()) {
    //                    // Now you can work with the wxImage, e.g., display it
    //                    // For example:
    //                   
    //                    wxBitmap bitmap(image);
    //                    picture->SetBitmap(bitmap);
    //                }
    //            }
    //        }
    //    }
    //}

    titleText2->SetLabel(wxString(tag->title().toCString(true)));
    artistText2->SetLabel(wxString(tag->artist().toCString(true)));
    albumText2->SetLabel(wxString(tag->album().toCString(true)));
    yearText2->SetLabel(wxString(str.str()));
}





//#include "testGUIwindow.h"
//#include <mpeg/id3v2/id3v2tag.h>
//#include <mpeg/id3v1/id3v1tag.h>
//#include <mpeg/mpegfile.h>
//#include <mpeg/id3v2/id3v2frame.h>
//#include <mpeg/id3v2/id3v2header.h>
//#include <mpeg/id3v2/frames/attachedpictureframe.h>
////set subsystem console
//
//bool myApp::OnInit() {
//	myFrame* frame = new myFrame(wxString("This is a thing for testing"), wxPoint(50, 50), wxSize(500, 500));
//	frame->Show();
//	return true;
//}
//
//myFrame::myFrame(const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame(nullptr, wxID_ANY, title, pos, size) {
//	wxWindow* window = new wxWindow(this, wxID_ANY, wxDefaultPosition, wxSize(500, 500));
//	TagLib::MPEG::File mpegFile("C:\\Users\\dhira\\Downloads\\Pink_Floyd__The_Dark_Side_of_the_Moon_50th_Anniversary/Comfortably_Numb_-_2011_Remaster.mp3");
//   
//    wxInitAllImageHandlers();
//    wxImage image(wxT("C:\\Users\\dhira\\Downloads\\Layer 2.png"));
//    wxBitmap bitmap(image);
//
//
//
//    picture = new wxStaticBitmap(window, wxID_ANY, bitmap, wxPoint(1, 1), wxSize(200, 200));
//
//
//	if (mpegFile.hasID3v2Tag()) {
//        wxLogDebug("this has id3v2");
//
//
//
//        TagLib::ID3v2::Tag* id3v2Tag = mpegFile.ID3v2Tag();
//
//        TagLib::ID3v2::FrameListMap frameListMap = id3v2Tag->frameListMap();
//        
//
//        
//        frameListMap.end();
//
//        /*for (TagLib::ID3v2::FrameListMap::ConstIterator it = frameListMap.begin(); it != frameListMap.end(); ++it) {
//            wxLogDebug("Frame Key: ", it->first);
//        }*/
//        
//        //TagLib::ID3v2::FrameListMap::ConstIterator it = frameListMap.find("APIC");
//
//        
//
//        //if (it != frameListMap.end()) {
//        //    TagLib::ID3v2::FrameList frameList = it->second;
//        //    for (TagLib::ID3v2::FrameList::ConstIterator frameIt = frameList.begin(); frameIt != frameList.end(); ++frameIt) {
//        //        TagLib::ID3v2::AttachedPictureFrame* coverFrame = static_cast<TagLib::ID3v2::AttachedPictureFrame*>(*frameIt);
//        //        if (coverFrame) {
//        //            TagLib::ByteVector imageData = coverFrame->picture();
//
//        //            //  Create a wxImage from the TagLib image data
//        //            wxMemoryInputStream stream(imageData.data(), imageData.size());
//        //            wxImage image(stream, wxBITMAP_TYPE_JPEG);
//
//        //            if (image.IsOk()) {
//        //                // Now you can work with the wxImage, e.g., display it
//        //                // For example:
//        //               
//        //                wxBitmap bitmap(image);
//        //                picture->SetBitmap(bitmap);
//        //            }
//        //        }
//        //    }
//        //}
//    }
//	//text = new wxStaticText(window, wxID_ANY, wxString(thing.c_str()), wxPoint(50, 50), wxSize(100, 50));
//}
