/// @author Dr. Martin Ettl
/// @date   2012-05-25

#include "wxEventClassGen.hpp"
#include "gear.xpm"

#include <wx/statline.h>

// wxEvent Table
BEGIN_EVENT_TABLE(wxEventClassGen, wxFrame)
    EVT_BUTTON(ID_GENERATE_BTN, wxEventClassGen::OnButton)
    EVT_MENU(ID_ABOUT, wxEventClassGen::OnAbout)
    EVT_MENU(ID_QUIT, wxEventClassGen::OnQuit)
END_EVENT_TABLE()

wxEventClassGen::wxEventClassGen( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style )
    : wxFrame( parent, id, title, pos, size, style )
{
    // set up the menu bar
    SetUpMenuBar();

    // set up the status bar
    SetUpStatusBar();

    this->SetSizeHints( wxDefaultSize, wxDefaultSize );

    wxStaticBoxSizer * const topSizer = new wxStaticBoxSizer( wxVERTICAL, this, wxT(""));

    wxBoxSizer * const userInputSizer = new wxBoxSizer(wxHORIZONTAL);

    // Name of event
    wxStaticBoxSizer * const eventNameSizer = new wxStaticBoxSizer( wxHORIZONTAL, this, wxT("Name of event") );
    m_pEventNameTxtCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    eventNameSizer->Add( m_pEventNameTxtCtrl, 1, wxALIGN_CENTER_VERTICAL | wxALL, 5 );
    userInputSizer->Add( eventNameSizer, 1, wxEXPAND, 5 );

    // Event-table entry
    wxStaticBoxSizer * const eventTableMacroNameSizer = new wxStaticBoxSizer( wxHORIZONTAL, this, wxT("Name of event table macro") );
    m_pEventTableEntryNameTxtCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    eventTableMacroNameSizer->Add( m_pEventTableEntryNameTxtCtrl, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5 );
    userInputSizer->Add( eventTableMacroNameSizer, 1, wxEXPAND, 5 );

    // Event id
    wxStaticBoxSizer* const eventIdSizer = new wxStaticBoxSizer( wxHORIZONTAL, this, wxT("Event ID") );
    m_pEventIdSpinCtrl = new wxSpinCtrl(this, wxID_ANY, wxT("-1"), wxDefaultPosition, wxSize(150, -1), wxSP_ARROW_KEYS, -10000, +10000, -1);
    eventIdSizer->Add( m_pEventIdSpinCtrl, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5 );
    userInputSizer->Add( eventIdSizer, 0, wxEXPAND, 5 );

    // Generate button
	wxStaticBoxSizer * const buttonSizer = new wxStaticBoxSizer(wxHORIZONTAL, this, wxEmptyString);
    m_pGenerateEventBtn = new wxBitmapButton( this, ID_GENERATE_BTN, wxBitmap(gear_xpm), wxDefaultPosition);
	buttonSizer->Add(m_pGenerateEventBtn, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5); 
    userInputSizer->Add(buttonSizer, 0, wxEXPAND, 5);

    topSizer->Add(userInputSizer, 1, wxALL | wxEXPAND, 5);

    // Output
	wxBoxSizer* const outputSizer = new wxBoxSizer(wxVERTICAL);
	m_outputNotebook = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
	m_outputHppPanel = new wxPanel(m_outputNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* const outputHppSizer = new wxBoxSizer(wxVERTICAL);
	m_outputHpp = new wxStyledTextCtrl(m_outputHppPanel, ID_HPP_CODE);
	ConfigureTextStyle(m_outputHpp);
	m_outputHpp->Connect(wxEVT_STC_MARGINCLICK, wxStyledTextEventHandler(wxEventClassGen::OnMarginClick), NULL, this);
	outputHppSizer->Add(m_outputHpp, 1, wxALL | wxEXPAND, 5);
	m_outputHppPanel->SetSizer(outputHppSizer);
	m_outputHppPanel->Layout();
	outputHppSizer->Fit(m_outputHppPanel);
	m_outputNotebook->AddPage(m_outputHppPanel, wxT("hpp"), false);

	m_outputCppPanel = new wxPanel(m_outputNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* const outputCppSizer = new wxBoxSizer(wxVERTICAL);
	m_outputCpp = new wxStyledTextCtrl(m_outputCppPanel, ID_CPP_CODE);
	ConfigureTextStyle(m_outputCpp);
	m_outputCpp->Connect(wxEVT_STC_MARGINCLICK, wxStyledTextEventHandler(wxEventClassGen::OnMarginClick), NULL, this);
	outputCppSizer->Add(m_outputCpp, 1, wxALL | wxEXPAND, 5);
	m_outputCppPanel->SetSizer(outputCppSizer);
	m_outputCppPanel->Layout();
	outputCppSizer->Fit(m_outputCppPanel);
	m_outputNotebook->AddPage(m_outputCppPanel, wxT("cpp"), false);

	outputSizer->Add(m_outputNotebook, 1, wxEXPAND | wxALL, 5);
 
    topSizer->Add(outputSizer, 15, wxEXPAND, 5 );

    this->SetSizer( topSizer );
    this->Layout();

    RestoreCurrentProgramSettings();
}

wxEventClassGen::~wxEventClassGen(void)
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

void wxEventClassGen::ConfigureTextStyle(wxStyledTextCtrl* const styledTextCtrl)
{
	if (!styledTextCtrl)
		return;
	styledTextCtrl->StyleClearAll();
	styledTextCtrl->SetLexer(wxSTC_LEX_CPP);

	styledTextCtrl->SetMarginWidth(MARGIN_LINE_NUMBERS, 50);
	styledTextCtrl->StyleSetForeground(wxSTC_STYLE_LINENUMBER, wxColour(75, 75, 75));
	styledTextCtrl->StyleSetBackground(wxSTC_STYLE_LINENUMBER, wxColour(220, 220, 220));
	styledTextCtrl->SetMarginType(MARGIN_LINE_NUMBERS, wxSTC_MARGIN_NUMBER);


	// ---- Enable code folding
	styledTextCtrl->SetMarginType(MARGIN_FOLD, wxSTC_MARGIN_SYMBOL);
	styledTextCtrl->SetMarginWidth(MARGIN_FOLD, 15);
	styledTextCtrl->SetMarginMask(MARGIN_FOLD, wxSTC_MASK_FOLDERS);
	styledTextCtrl->StyleSetBackground(MARGIN_FOLD, wxColor(200, 200, 200));
	styledTextCtrl->SetMarginSensitive(MARGIN_FOLD, true);

	// Properties found from http://www.scintilla.org/SciTEDoc.html
	styledTextCtrl->SetProperty(wxT("fold"), wxT("1"));
	styledTextCtrl->SetProperty(wxT("fold.comment"), wxT("1"));
	styledTextCtrl->SetProperty(wxT("fold.compact"), wxT("1"));

	wxColor grey(100, 100, 100);
	styledTextCtrl->MarkerDefine(wxSTC_MARKNUM_FOLDER, wxSTC_MARK_ARROW);
	styledTextCtrl->MarkerSetForeground(wxSTC_MARKNUM_FOLDER, grey);
	styledTextCtrl->MarkerSetBackground(wxSTC_MARKNUM_FOLDER, grey);

	styledTextCtrl->MarkerDefine(wxSTC_MARKNUM_FOLDEROPEN, wxSTC_MARK_ARROWDOWN);
	styledTextCtrl->MarkerSetForeground(wxSTC_MARKNUM_FOLDEROPEN, grey);
	styledTextCtrl->MarkerSetBackground(wxSTC_MARKNUM_FOLDEROPEN, grey);

	styledTextCtrl->MarkerDefine(wxSTC_MARKNUM_FOLDERSUB, wxSTC_MARK_EMPTY);
	styledTextCtrl->MarkerSetForeground(wxSTC_MARKNUM_FOLDERSUB, grey);
	styledTextCtrl->MarkerSetBackground(wxSTC_MARKNUM_FOLDERSUB, grey);

	styledTextCtrl->MarkerDefine(wxSTC_MARKNUM_FOLDEREND, wxSTC_MARK_ARROW);
	styledTextCtrl->MarkerSetForeground(wxSTC_MARKNUM_FOLDEREND, grey);
	styledTextCtrl->MarkerSetBackground(wxSTC_MARKNUM_FOLDEREND, _T("WHITE"));

	styledTextCtrl->MarkerDefine(wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_ARROWDOWN);
	styledTextCtrl->MarkerSetForeground(wxSTC_MARKNUM_FOLDEROPENMID, grey);
	styledTextCtrl->MarkerSetBackground(wxSTC_MARKNUM_FOLDEROPENMID, _T("WHITE"));

	styledTextCtrl->MarkerDefine(wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_EMPTY);
	styledTextCtrl->MarkerSetForeground(wxSTC_MARKNUM_FOLDERMIDTAIL, grey);
	styledTextCtrl->MarkerSetBackground(wxSTC_MARKNUM_FOLDERMIDTAIL, grey);

	styledTextCtrl->MarkerDefine(wxSTC_MARKNUM_FOLDERTAIL, wxSTC_MARK_EMPTY);
	styledTextCtrl->MarkerSetForeground(wxSTC_MARKNUM_FOLDERTAIL, grey);
	styledTextCtrl->MarkerSetBackground(wxSTC_MARKNUM_FOLDERTAIL, grey);

	// ---- End of code folding part

	styledTextCtrl->SetWrapMode(wxSTC_WRAP_WORD); // other choice is wxSCI_WRAP_NONE

	styledTextCtrl->StyleSetForeground(wxSTC_C_STRING, wxColour(150, 0, 0));
	styledTextCtrl->StyleSetForeground(wxSTC_C_PREPROCESSOR, wxColour(165, 105, 0));
	styledTextCtrl->StyleSetForeground(wxSTC_C_IDENTIFIER, wxColour(40, 0, 60));
	styledTextCtrl->StyleSetForeground(wxSTC_C_NUMBER, wxColour(0, 150, 0));
	styledTextCtrl->StyleSetForeground(wxSTC_C_CHARACTER, wxColour(150, 0, 0));
	styledTextCtrl->StyleSetForeground(wxSTC_C_WORD, wxColour(0, 0, 150));
	styledTextCtrl->StyleSetForeground(wxSTC_C_WORD2, wxColour(0, 150, 0));
	styledTextCtrl->StyleSetForeground(wxSTC_C_COMMENT, wxColour(150, 150, 150));
	styledTextCtrl->StyleSetForeground(wxSTC_C_COMMENTLINE, wxColour(150, 150, 150));
	styledTextCtrl->StyleSetForeground(wxSTC_C_COMMENTDOC, wxColour(150, 150, 150));
	styledTextCtrl->StyleSetForeground(wxSTC_C_COMMENTDOCKEYWORD, wxColour(0, 0, 200));
	styledTextCtrl->StyleSetForeground(wxSTC_C_COMMENTDOCKEYWORDERROR, wxColour(0, 0, 200));
	styledTextCtrl->StyleSetBold(wxSTC_C_WORD, true);
	styledTextCtrl->StyleSetBold(wxSTC_C_WORD2, true);
	styledTextCtrl->StyleSetBold(wxSTC_C_COMMENTDOCKEYWORD, true);

	// Configure keyword highlighting
	styledTextCtrl->SetKeyWords(0, wxT("return for while break continue if switch define"));
	styledTextCtrl->SetKeyWords(1, wxT("const int float void char double long"));
}

/** Event callback when a margin is clicked, used here for code folding */
void wxEventClassGen::OnMarginClick(wxStyledTextEvent &event)
{
	wxStyledTextCtrl* textCtrl;
	switch (event.GetId())
	{
	case ID_CPP_CODE:
	{
		textCtrl = m_outputCpp;
		break;
	}
	case ID_HPP_CODE:
	{
		textCtrl = m_outputHpp;
		break;
	}
	default:
		wxLogError("%s %i", "wxEventClassGen::OnMarginClick was called with an invalid event id:", event.GetId());
		return;
	}

    if (event.GetMargin() == MARGIN_FOLD)
    {
        const int lineClick = textCtrl->LineFromPosition(event.GetPosition());
        const int levelClick = textCtrl->GetFoldLevel(lineClick);
        if ((levelClick & wxSTC_FOLDLEVELHEADERFLAG) > 0)
        {
			textCtrl->ToggleFold(lineClick);
        }
    }
}

void wxEventClassGen::OnButton(wxCommandEvent &event)
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

			m_outputNotebook->SetPageText(0, strEventName+".hpp");
			m_outputNotebook->SetPageText(1, strEventName+".cpp");
            const wxString strEventId(wxString::Format(wxT("%i"), m_pEventIdSpinCtrl->GetValue()));

            // Ok, now input is here --> generate the class
            const wxString codeHpp(
                "#ifndef CLASS" + strEventName.Upper() + "__HPP\n"
                "#define CLASS" + strEventName.Upper() + "__HPP\n\n"
                "#include <wx/wx.h>\n"
                "#include <wx/event.h>\n\n"
                "/// @brief Declaration of an custom event type, this is the wxWidgets way to predefine an event class.\n"
				"/// @brief This is a custom event class.\n"
				"/// @author Dr. Martin Ettl\n"
				"/// @date  " + std::string(__DATE__) + "\n"
				"\n"
				"DECLARE_EVENT_TYPE( " + strEventName + "CommandEvent, -1 )\n"
                "\n\n"
                "class " + strEventName + ": public wxCommandEvent\n"
                "{\n"
                "	public:\n"
                "		/// @brief a custom event id, define as many as you want\n"
                "		static const long m_sci" + strEventName + "EventId = " + strEventId + ";\n\n"
                "		/// Constructor of class " + strEventName + "\n"
                "		/// @param[in] commandType The event type\n"
                "		/// @param[in] id  		   The event id. The default value is 0.\n"
                "		" + strEventName + "( wxEventType commandType = " + strEventName + "CommandEvent, int id = 0 );\n\n"
                "		/// @brief Copy constructor \n"
                "		/// @param[in] event An " + strEventName + "-event object.\n"
                "		" + strEventName + "( const " + strEventName + " &event );\n\n"
                "		/// @brief This Clone function is required for sending with wxPostEvent().\n"
                "		wxEvent* Clone(void) const;\n"
                "};\n\n"
                "typedef void (wxEvtHandler::*" + strEventName + "EventFunction)(" + strEventName + " &);\n"
                "#define " + strEventName + "Handler(func) wxEVENT_HANDLER_CAST(" + strEventName + "EventFunction, func)\n\n"
				"// Define the event table entry. Yes, it really *does* end in a comma.\n"
                "#define " + strEventTableEntry + "(id, fn) wxDECLARE_EVENT_TABLE_ENTRY(" + strEventName + "CommandEvent, (id), wxID_ANY, (wxObjectEventFunction)(wxEventFunction) wxEVENT_HANDLER_CAST( "+ strEventName + "EventFunction, fn ), (wxObject*) NULL ),\n"
                "// Optionally, you can do a similar #define for EVT_" + strEventTableEntry + "_RANGE.\n"
                "#define " + strEventTableEntry + "_RANGE(id1, id2, fn)	wxDECLARE_EVENT_TABLE_ENTRY( " + strEventName + "CommandEvent, (id1), (id2), " + strEventName + "Handler(fn), (wxObject*) NULL ),\n\n"
				"/** @}*/\n"
                "#endif // class_" + strEventName.Upper() + "__HPP\n");
			m_outputHpp->Clear();
			m_outputHpp->SetValue(codeHpp);

			// Generate implementation code
			m_outputCpp->Clear();
			wxString cppCode = "#include \""+strEventName+".hpp\"\n";
			cppCode += "\n\n";
			cppCode +="const wxEventType " + strEventName + "CommandEvent = wxNewEventType();\n\n";
			cppCode += strEventName + "::" + strEventName + "( wxEventType commandType, int id)\n"
				     ": wxCommandEvent(commandType, id)\n"
				     "{}\n\n";
			cppCode += strEventName + "::" + strEventName + "( const " + strEventName + " &event )\n"
				      ": wxCommandEvent(event)\n"
				      "{}\n\n";
			cppCode += "wxEvent* " + strEventName + "::Clone(void) const\n"
				       "{\n"
				       "	return new " + strEventName + "(*this);\n"
				       "}\n";
			m_outputCpp->SetValue(cppCode);
            break;
        }
    }
}

void wxEventClassGen::SetUpMenuBar(void)
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

void wxEventClassGen::SetUpStatusBar(void)
{
#if wxUSE_STATUSBAR
    // create a status bar with some information about the used wxWidgets version
    CreateStatusBar(2);
    SetStatusText(wxEmptyString, 0);
    SetStatusText(wxVERSION_STRING, 1);
#endif // wxUSE_STATUSBAR
}

void wxEventClassGen::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close();
}

void wxEventClassGen::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxAboutDialogInfo AboutDialogInfo;
    AboutDialogInfo.AddDeveloper(wxT("Dr. Martin Ettl"));
    AboutDialogInfo.SetName(wxT("wxEventClassGen"));
    AboutDialogInfo.SetVersion(wxT(__DATE__));
    wxAboutBox(AboutDialogInfo);
}
