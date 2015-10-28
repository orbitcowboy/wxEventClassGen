/// @author Dr. Martin Ettl
/// @date   2012-05-25

#include "wxEventClassGen.hpp"
#include "gear.xpm"

#include <wx/statline.h>

// wxEvent Table
BEGIN_EVENT_TABLE(wxEventClassGen, wxFrame)
    EVT_BUTTON(ID_GENERATE_BTN, wxEventClassGen::vOnButton)
    EVT_MENU(ID_ABOUT         , wxEventClassGen::vOnAbout)
    EVT_MENU(ID_QUIT          , wxEventClassGen::vOnQuit)
END_EVENT_TABLE()

wxEventClassGen::wxEventClassGen( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style )
    : wxFrame( parent, id, title, pos, size, style )
{
    // set up the menu bar
    vSetUpMenuBar();

    // set up the status bar
    vSetUpStatusBar();

    this->SetSizeHints( wxDefaultSize, wxDefaultSize );

    wxStaticBoxSizer* bSizer1 = new wxStaticBoxSizer( wxVERTICAL, this, wxT(""));

    wxBoxSizer *userInputSizer = new wxBoxSizer(wxHORIZONTAL);

    // Name of event
    wxStaticBoxSizer* bSizer2 = new wxStaticBoxSizer( wxHORIZONTAL, this, wxT("Name of event:") );
    m_pEventNameTxtCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    bSizer2->Add( m_pEventNameTxtCtrl, 1, wxALIGN_CENTER_VERTICAL | wxALL, 5 );
    userInputSizer->Add( bSizer2, 1, wxEXPAND, 5 );

    // Eventtable entry
    wxStaticBoxSizer* bSizer3 = new wxStaticBoxSizer( wxHORIZONTAL, this, wxT("Name of eventtable entry:") );
    m_pEventTableEntryNameTxtCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    bSizer3->Add( m_pEventTableEntryNameTxtCtrl, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5 );
    userInputSizer->Add( bSizer3, 1, wxEXPAND, 5 );

    // Event id
    wxStaticBoxSizer* bSizer4 = new wxStaticBoxSizer( wxHORIZONTAL, this, wxT("Event id:") );
    m_pEventIdSpinCtrl = new wxSpinCtrl(this, wxID_ANY, wxT("-1"), wxDefaultPosition, wxSize(150, -1), wxSP_ARROW_KEYS, -10000, +10000, -1);
    bSizer4->Add( m_pEventIdSpinCtrl, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5 );
    userInputSizer->Add( bSizer4, 0, wxEXPAND, 5 );

    // Generate button
    m_pGenerateEventBtn = new wxBitmapButton( this, ID_GENERATE_BTN, wxBitmap(gear_xpm), wxDefaultPosition);
    userInputSizer->Add( m_pGenerateEventBtn, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5 );
    bSizer1->Add(userInputSizer, 1, wxALL | wxEXPAND, 5);

    // Output
    wxBoxSizer* bSizer5;
    bSizer5 = new wxBoxSizer( wxVERTICAL );
    wxStaticBoxSizer* sbSizer3;
    sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Output") ), wxVERTICAL );
    m_pOutput = new wxStyledTextCtrl( this, wxID_ANY );

    m_pOutput->StyleClearAll();
    m_pOutput->SetLexer(wxSTC_LEX_CPP);

    m_pOutput->SetMarginWidth (MARGIN_LINE_NUMBERS, 50);
    m_pOutput->StyleSetForeground (wxSTC_STYLE_LINENUMBER, wxColour (75, 75, 75) );
    m_pOutput->StyleSetBackground (wxSTC_STYLE_LINENUMBER, wxColour (220, 220, 220));
    m_pOutput->SetMarginType (MARGIN_LINE_NUMBERS, wxSTC_MARGIN_NUMBER);


    // ---- Enable code folding
    m_pOutput->SetMarginType (MARGIN_FOLD, wxSTC_MARGIN_SYMBOL);
    m_pOutput->SetMarginWidth(MARGIN_FOLD, 15);
    m_pOutput->SetMarginMask (MARGIN_FOLD, wxSTC_MASK_FOLDERS);
    m_pOutput->StyleSetBackground(MARGIN_FOLD, wxColor(200, 200, 200) );
    m_pOutput->SetMarginSensitive(MARGIN_FOLD, true);

    // Properties found from http://www.scintilla.org/SciTEDoc.html
    m_pOutput->SetProperty (wxT("fold"),         wxT("1") );
    m_pOutput->SetProperty (wxT("fold.comment"), wxT("1") );
    m_pOutput->SetProperty (wxT("fold.compact"), wxT("1") );

    wxColor grey( 100, 100, 100 );
    m_pOutput->MarkerDefine (wxSTC_MARKNUM_FOLDER, wxSTC_MARK_ARROW );
    m_pOutput->MarkerSetForeground (wxSTC_MARKNUM_FOLDER, grey);
    m_pOutput->MarkerSetBackground (wxSTC_MARKNUM_FOLDER, grey);

    m_pOutput->MarkerDefine (wxSTC_MARKNUM_FOLDEROPEN,    wxSTC_MARK_ARROWDOWN);
    m_pOutput->MarkerSetForeground (wxSTC_MARKNUM_FOLDEROPEN, grey);
    m_pOutput->MarkerSetBackground (wxSTC_MARKNUM_FOLDEROPEN, grey);

    m_pOutput->MarkerDefine (wxSTC_MARKNUM_FOLDERSUB,     wxSTC_MARK_EMPTY);
    m_pOutput->MarkerSetForeground (wxSTC_MARKNUM_FOLDERSUB, grey);
    m_pOutput->MarkerSetBackground (wxSTC_MARKNUM_FOLDERSUB, grey);

    m_pOutput->MarkerDefine (wxSTC_MARKNUM_FOLDEREND,     wxSTC_MARK_ARROW);
    m_pOutput->MarkerSetForeground (wxSTC_MARKNUM_FOLDEREND, grey);
    m_pOutput->MarkerSetBackground (wxSTC_MARKNUM_FOLDEREND, _T("WHITE"));

    m_pOutput->MarkerDefine (wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_ARROWDOWN);
    m_pOutput->MarkerSetForeground (wxSTC_MARKNUM_FOLDEROPENMID, grey);
    m_pOutput->MarkerSetBackground (wxSTC_MARKNUM_FOLDEROPENMID, _T("WHITE"));

    m_pOutput->MarkerDefine (wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_EMPTY);
    m_pOutput->MarkerSetForeground (wxSTC_MARKNUM_FOLDERMIDTAIL, grey);
    m_pOutput->MarkerSetBackground (wxSTC_MARKNUM_FOLDERMIDTAIL, grey);

    m_pOutput->MarkerDefine (wxSTC_MARKNUM_FOLDERTAIL,    wxSTC_MARK_EMPTY);
    m_pOutput->MarkerSetForeground (wxSTC_MARKNUM_FOLDERTAIL, grey);
    m_pOutput->MarkerSetBackground (wxSTC_MARKNUM_FOLDERTAIL, grey);

    // Connect the event handler for code folding
    m_pOutput->Connect(wxEVT_STC_MARGINCLICK, wxStyledTextEventHandler(wxEventClassGen::OnMarginClick), NULL, this);

    // ---- End of code folding part

    m_pOutput->SetWrapMode (wxSTC_WRAP_WORD); // other choice is wxSCI_WRAP_NONE

    m_pOutput->StyleSetForeground (wxSTC_C_STRING,            wxColour(150, 0, 0));
    m_pOutput->StyleSetForeground (wxSTC_C_PREPROCESSOR,      wxColour(165, 105, 0));
    m_pOutput->StyleSetForeground (wxSTC_C_IDENTIFIER,        wxColour(40, 0, 60));
    m_pOutput->StyleSetForeground (wxSTC_C_NUMBER,            wxColour(0, 150, 0));
    m_pOutput->StyleSetForeground (wxSTC_C_CHARACTER,         wxColour(150, 0, 0));
    m_pOutput->StyleSetForeground (wxSTC_C_WORD,              wxColour(0, 0, 150));
    m_pOutput->StyleSetForeground (wxSTC_C_WORD2,             wxColour(0, 150, 0));
    m_pOutput->StyleSetForeground (wxSTC_C_COMMENT,           wxColour(150, 150, 150));
    m_pOutput->StyleSetForeground (wxSTC_C_COMMENTLINE,       wxColour(150, 150, 150));
    m_pOutput->StyleSetForeground (wxSTC_C_COMMENTDOC,        wxColour(150, 150, 150));
    m_pOutput->StyleSetForeground (wxSTC_C_COMMENTDOCKEYWORD, wxColour(0, 0, 200));
    m_pOutput->StyleSetForeground (wxSTC_C_COMMENTDOCKEYWORDERROR, wxColour(0, 0, 200));
    m_pOutput->StyleSetBold(wxSTC_C_WORD, true);
    m_pOutput->StyleSetBold(wxSTC_C_WORD2, true);
    m_pOutput->StyleSetBold(wxSTC_C_COMMENTDOCKEYWORD, true);

    // Configure keyword highlighting
    m_pOutput->SetKeyWords(0, wxT("return for while break continue if switch define"));
    m_pOutput->SetKeyWords(1, wxT("const int float void char double long"));

    sbSizer3->Add( m_pOutput, 5, wxALL | wxEXPAND, 5 );
    bSizer5->Add( sbSizer3, 5, wxEXPAND, 5 );
    bSizer1->Add( bSizer5, 15, wxEXPAND, 5 );

    this->SetSizer( bSizer1 );
    this->Layout();

    RestoreCurrentProgramSettings();
}

wxEventClassGen::~wxEventClassGen()
{
    SaveCurrentProgramSettings();
}

void wxEventClassGen::SaveCurrentProgramSettings(void)
{
    m_config->Write("wxEventClassGen.m_pEventNameTxtCtrl", m_pEventNameTxtCtrl->GetValue());
    m_config->Write("wxEventClassGen.m_pEventTableEntryNameTxtCtrl", m_pEventTableEntryNameTxtCtrl->GetValue());

    // cleanup
    delete m_config;
}

void wxEventClassGen::RestoreCurrentProgramSettings(void)
{
    m_config = new wxConfig(wxFrame::GetTitle());

    // Restore recent user inputs
    wxString currentValue;
    if( m_config->Read("wxEventClassGen.m_pEventNameTxtCtrl", &currentValue) )
    {
        m_pEventNameTxtCtrl->SetValue(currentValue);
    }
    if( m_config->Read("wxEventClassGen.m_pEventTableEntryNameTxtCtrl", &currentValue) )
    {
        m_pEventTableEntryNameTxtCtrl->SetValue(currentValue);
    }
}

/** Event callback when a margin is clicked, used here for code folding */
void wxEventClassGen::OnMarginClick(wxStyledTextEvent &event)
{
    if (event.GetMargin() == MARGIN_FOLD)
    {
        const int lineClick = m_pOutput->LineFromPosition(event.GetPosition());
        const int levelClick = m_pOutput->GetFoldLevel(lineClick);
        if ((levelClick & wxSTC_FOLDLEVELHEADERFLAG) > 0)
        {
            m_pOutput->ToggleFold(lineClick);
        }
    }
}

void wxEventClassGen::vOnButton(wxCommandEvent &event)
{
    switch(event.GetId())
    {
        case ID_GENERATE_BTN:
        {
            const wxString strEventName(m_pEventNameTxtCtrl->GetValue());
            if(strEventName.IsEmpty())
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

            const wxString strEventTableEntry(m_pEventTableEntryNameTxtCtrl->GetValue());
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

            const wxString strEventId(wxString::Format(wxT("%i"), m_pEventIdSpinCtrl->GetValue()));

            // Ok, now input is here --> generate the class
            const wxString strResult(
                "#ifndef CLASS" + strEventName.Upper() + "__HPP\n"
                "#define CLASS" + strEventName.Upper() + "__HPP\n\n"
                "#include <wx/wx.h>\n"
                "#include <wx/event.h>\n\n"
                "/// @brief Declaration of an custom event type, this is the wxWidgets way to predefine an event class.\n"
                "DECLARE_EVENT_TYPE( " + strEventName + "CommandEvent, -1 )\n"
                "\n\n"
                "///@brief This is a custom event class.\n"
                "///@author Dr. Martin Ettl\n"
                "///@date  " + std::string(__DATE__) + "\n"
                "\n"
                "class " + strEventName + ": public wxCommandEvent\n"
                "{\n"
                "	public:\n"
                "		/// @brief a custom event id, define as many as you want\n"
                "		static const long m_sci" + strEventName + "EventId = " + strEventId + ";\n\n"
                "		/// Constructor of class " + strEventName + "\n"
                "		///\n"
                "		/// @param[in] commandType The event type\n"
                "		/// @param[in] id  		   The event id. The default value is 0.\n"
                "		" + strEventName + "( wxEventType commandType = " + strEventName + "CommandEvent, int id = 0 )\n"
                "			:  wxCommandEvent(commandType, id)\n"
                "		{}\n\n"
                "		/// @brief Copy constructor \n"
                "		///\n"
                "		/// @param[in] event An " + strEventName + "-event object.\n"
                "		" + strEventName + "( const " + strEventName + " &event )\n"
                "			:  wxCommandEvent(event)\n"
                "		{}\n\n"
                "		/// @brief This Clone function is required for sending with wxPostEvent().\n"
                "		wxEvent* Clone(void) const\n"
                "		{\n"
                "			return new " + strEventName + "(*this);\n"
                "		}\n"
                "};\n\n\n"
                "typedef void (wxEvtHandler::*" + strEventName + "EventFunction)(" + strEventName + " &);\n\n"
                "// This #define simplifies the one below, and makes the syntax less\n"
                "// ugly if you want to use Connect() instead of an event table.\n"
                "#define " + strEventName + "Handler(func) \\\n"
                "	(wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)\\\n"
                "	wxStaticCastEvent(" + strEventName + "EventFunction, &func)\n\n\n"
                "// Define the event table entry. Yes, it really *does* end in a comma.\n"
                "#define " + strEventTableEntry + "(id, fn)\\\n"
                "	DECLARE_EVENT_TABLE_ENTRY(" + strEventName + "CommandEvent, id, wxID_ANY,\\\n"
                "							 (wxObjectEventFunction)(wxEventFunction)\\\n"
                "							 (wxCommandEventFunction) wxStaticCastEvent(\\\n"
                "							" + strEventName + "EventFunction, &fn ), (wxObject*) NULL ),\n\n\n"
                "// Optionally, you can do a similar #define for EVT_" + strEventTableEntry + "_RANGE.\n"
                "#define " + strEventTableEntry + "_RANGE(id1,id2, fn) \\\n"
                "	DECLARE_EVENT_TABLE_ENTRY( " + strEventName + "CommandEvent, id1, id2, \\\n"
                "							   " + strEventName + "Handler(fn), (wxObject*) NULL ),\n\n"
                "#endif // class_" + strEventName.Upper() + "__HPP\n");
            m_pOutput->Clear();
            m_pOutput->SetValue(strResult);
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
