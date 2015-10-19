// --------------------------
/// @author ettl martin
/// @date   2012-05-25
// --------------------------

#include "wxEventClassGen.hpp"
#include "gear.xpm"

#include <wx/statline.h>

// wxEvent Table
BEGIN_EVENT_TABLE(wxEventClassGen, wxFrame)
    EVT_BUTTON(ID_GENERATE_BTN, wxEventClassGen::vOnButton)
    EVT_MENU(ID_ABOUT         , wxEventClassGen::vOnAbout)
    EVT_MENU(ID_QUIT          , wxEventClassGen::vOnQuit)
END_EVENT_TABLE()

wxEventClassGen::wxEventClassGen( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
    // set up the menu bar
    vSetUpMenuBar();

    // set up the status bar
    vSetUpStatusBar();

    this->SetSizeHints( wxDefaultSize, wxDefaultSize );

    wxStaticBoxSizer* bSizer1;
    bSizer1 = new wxStaticBoxSizer( wxVERTICAL, this, wxT(""));

    // Name of event
    wxBoxSizer* bSizer2;
    bSizer2 = new wxBoxSizer( wxHORIZONTAL );
    m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Name of event:"), wxDefaultPosition, wxDefaultSize, 0 );
    m_staticText1->Wrap( -1 );
    bSizer2->Add( m_staticText1, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5 );
    m_pEventNameTxtCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    bSizer2->Add( m_pEventNameTxtCtrl, 1, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    bSizer1->Add( bSizer2, 1, wxEXPAND, 5 );

    // Eventtable entry
    wxBoxSizer* bSizer3 = new wxBoxSizer( wxHORIZONTAL );
    m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Name of eventtable entry:"), wxDefaultPosition, wxDefaultSize, 0 );
    m_staticText2->Wrap( -1 );
    bSizer3->Add( m_staticText2, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5 );
    m_textCtrl2 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    bSizer3->Add( m_textCtrl2, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5 );

    // Event id
    m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("Event id:"), wxDefaultPosition, wxDefaultSize, 0 );
    m_staticText3->Wrap( -1 );
    bSizer3->Add( m_staticText3, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5 );
    m_pEventIdSpinCtrl = new wxSpinCtrl(this, wxID_ANY, wxT("-1"), wxDefaultPosition, wxSize(150, -1), wxSP_ARROW_KEYS, -10000, +10000, -1);
    bSizer3->Add( m_pEventIdSpinCtrl, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5 );
    bSizer1->Add( bSizer3, 1, wxEXPAND, 5 );

    // horizontal line
    bSizer1->Add( new wxStaticLine(this), 1, wxEXPAND, 0 );

    // Generate button
    wxBoxSizer* bSizer4;
    bSizer4 = new wxBoxSizer( wxHORIZONTAL);
    wxBitmap Label(gear_xpm);
    bSizer4->Add( new wxStaticBitmap ( this, wxID_ANY, Label ), 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL, 15 );
    m_pGenerateEventBtn = new wxButton( this, ID_GENERATE_BTN, wxT("Generate"), wxDefaultPosition, wxSize(-1, 40), 5 );
    bSizer4->Add( m_pGenerateEventBtn, 1, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL, 15 );

    bSizer1->Add( bSizer4, 1, wxEXPAND | wxALL, 15 );

    // Output
    wxBoxSizer* bSizer5;
    bSizer5 = new wxBoxSizer( wxVERTICAL );
    wxStaticBoxSizer* sbSizer3;
    sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Output") ), wxVERTICAL );
    m_pOutput = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY );
    sbSizer3->Add( m_pOutput, 5, wxALL | wxEXPAND, 5 );

    bSizer5->Add( sbSizer3, 5, wxEXPAND, 5 );

    bSizer1->Add( bSizer5, 15, wxEXPAND, 5 );

    this->SetSizer( bSizer1 );
    this->Layout();
}

wxEventClassGen::~wxEventClassGen()
{
}

void wxEventClassGen::vOnButton(wxCommandEvent &event)
{
    switch(event.GetId())
    {
        case ID_GENERATE_BTN:
        {
            std::string strEventName(m_pEventNameTxtCtrl->GetValue().mb_str());
            if(strEventName.empty())
            {
                wxString strMessage(wxT("Please enter the name of the event. Without this information the eventclass cannot be generated."));
                wxMessageDialog Dialog(  this
                                         , strMessage
                                         , wxT("Missing input")
                                         , wxICON_HAND
                                         , wxDefaultPosition);
                Dialog.ShowModal();
                break;
            }
            std::string strEventTableEntry(m_textCtrl2->GetValue().mb_str());
            if(strEventTableEntry.empty())
            {
                wxString strMessage(wxT("Please enter the event table macro name, e.g.: EVT_CUSTOM. Without this information the eventclass cannot be generated."));
                wxMessageDialog Dialog(  this
                                         , strMessage
                                         , wxT("Missing input")
                                         , wxICON_HAND
                                         , wxDefaultPosition);
                Dialog.ShowModal();
                break;
            }
            std::string strEventId(wxString::Format(wxT("%i"), m_pEventIdSpinCtrl->GetValue()).mb_str());
            // Ok, now input is here --> generate the class
            std::string strResult(
                "#ifndef __class_" + strEventName + "___\n"
                "#define __class_" + strEventName + "___\n"
                "#include <wx/wx.h>\n"
                "#include <wx/event.h>\n"
                "// declare the custom eventtype, this is the wxWidgets way to predefine an event class\n"
                "DECLARE_EVENT_TYPE( " + strEventName + "CommandEvent, -1 )\n"
                "\n"
                "// ---------------------------------------------------------------------------------\n"
                "///\\brief This is a custom event class.\n"
                "///@author martin ettl (ettl.martin78 (at) googlemail (dot) com)\n"
                "///@date  " + std::string(__DATE__) + "\n"
                "\n"
                "// ---------------------------------------------------------------------------------\n"
                "class " + strEventName + ": public wxCommandEvent\n"
                "{\n"
                "	public:\n"
                "		///\\brief a custom event id, define as many as you want\n"
                "		static const long m_sci" + strEventName + "EventId = " + strEventId + ";\n"
                "		// ----------------------------------------------\n"
                "		/// Ctor of class " + strEventName + "\n"
                "		///\n"
                "		/// \\param commandType --> the event type\n"
                "		/// \\param id  		--> the event id\n"
                "		// ----------------------------------------------\n"
                "		" + strEventName + "( wxEventType commandType = " + strEventName + "CommandEvent, int id = 0 )\n"
                "			:  wxCommandEvent(commandType, id)\n"
                "		{}\n"
                "		// -------------------------------------------------------------\n"
                "		/// copy Ctor\n"
                "		///\n"
                "		/// \\param event --> a " + strEventName + "Event object\n"
                "		// -------------------------------------------------------------\n"
                "		" + strEventName + "( const " + strEventName + " &event )\n"
                "			:  wxCommandEvent(event)\n"
                "		{}\n"
                "		// Required for sending with wxPostEvent()\n"
                "		wxEvent* Clone() const\n"
                "		{\n"
                "			return new " + strEventName + "(*this);\n"
                "		}\n"
                "};\n"
                "typedef void (wxEvtHandler::*" + strEventName + "EventFunction)(" + strEventName + " &); \n"
                "// This #define simplifies the one below, and makes the syntax less 		\n"
                "// ugly if you want to use Connect() instead of an event table. 			\n"
                "#define " + strEventName + "Handler(func) 					    			  \\\n"
                "	(wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)	  \\\n"
                "	wxStaticCastEvent(" + strEventName + "EventFunction, &func)					    \n"
                "// Define the event table entry. Yes, it really *does* end in a comma.		\n"
                "#define " + strEventTableEntry + "(id, fn)									 \\\n"
                "	DECLARE_EVENT_TABLE_ENTRY(" + strEventName + "CommandEvent, id, wxID_ANY,\\\n"
                "							 (wxObjectEventFunction)(wxEventFunction)    \\\n"
                "							 (wxCommandEventFunction) wxStaticCastEvent( \\\n"
                "									   " + strEventName + "EventFunction, &fn ), (wxObject*) NULL ),\n"
                "// Optionally, you can do a similar #define for EVT_" + strEventTableEntry + "_RANGE.\n"
                "#define " + strEventTableEntry + "_RANGE(id1,id2, fn)                         \\\n"
                "	DECLARE_EVENT_TABLE_ENTRY( " + strEventName + "CommandEvent, id1, id2,    \\\n"
                "							   " + strEventName + "Handler(fn), (wxObject*) NULL ),\n"
                "#endif // __class_" + strEventName + "___\n");
            m_pOutput->Clear();
            m_pOutput->SetValue(wxString(strResult.c_str(), wxConvUTF8));
            break;
        }
    }
}

void wxEventClassGen::vSetUpMenuBar(void)
{
#if wxUSE_MENUS

    m_pMenubar = new wxMenuBar();

    // set up the file menu
    m_pFileMenu = new wxMenu(_T(""));
    m_pFileMenu->Append(ID_QUIT, _("&Quit\tAlt-F4"), _("Quit the application"));
    m_pMenubar->Append(m_pFileMenu, _("&File"));

    // set up the help menu
    m_pHelpMenu = new wxMenu(_T(""));
    m_pHelpMenu->Append(ID_ABOUT, _("&About\tF1"), _("Show info about this application"));
    m_pMenubar->Append(m_pHelpMenu, _("&Help"));

    // realize the menu( send it to the window)
    SetMenuBar(m_pMenubar);

#endif // wxUSE_MENUS
}

void wxEventClassGen::vSetUpStatusBar(void)
{
#if wxUSE_STATUSBAR
    // create a status bar with some information about the used wxWidgets version
    CreateStatusBar(2);
    SetStatusText(wxEmptyString, 0);
    SetStatusText(wxVERSION_STRING, 1);
#endif // wxUSE_STATUSBAR   
}

void wxEventClassGen::vOnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close();
}

void wxEventClassGen::vOnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxAboutDialogInfo AboutDialogInfo;
    AboutDialogInfo.AddDeveloper(wxT("Dr.rer.nat Martin Ettl \nTechnical University of Munich\nResearch Department Satellite Geodesy\n-Fundamentalstation Wettzell -\nSackenrieder Str.25\nD-93444 Bad Koetzting\nEmail:ettl@fs.wettzell.de\n "));
    AboutDialogInfo.SetDescription(wxT("wxEventClassGen\nby\nEttl Martin"));
    AboutDialogInfo.SetName(wxT("wxEventClassGen"));
    AboutDialogInfo.SetVersion(wxT(__DATE__));
    wxAboutBox(AboutDialogInfo);
}
