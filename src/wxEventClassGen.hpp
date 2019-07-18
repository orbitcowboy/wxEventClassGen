#ifndef __wxEventClassGen_header__
#define WX_EVENT_CLASS_GEN_HPP

/// @author Dr. Martin Ettl
/// @date   2015-10-20

/// @brief This is a wxEventClass generator.
/// In simplifies the creation of event classes, by generating a workable and customized event class.
/// Before the generation can be started, the user must enter two values. The name of the EventClass and
/// the EVT_-Macro name. For instance:
///
///   wxCustomEvent and EVT_CUSTOM.
///
/// After generating the C++-class, it can be further extended about customized member variables in order to transfer
/// information based on wxWidgets events.

#include <wx/wx.h>
#include <wx/aboutdlg.h>
#include <wx/spinctrl.h>
#include <wx/config.h>
#include <wx/notebook.h>

/// Use wxStyledTextCtrl to display the generated source code (https://wiki.wxwidgets.org/WxStyledTextCtrl).
#include <wx/stc/stc.h>

class wxEventClassGen : public wxFrame
{
    public:

	wxEventClassGen(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(1200, 800), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);
	~wxEventClassGen(void);

protected:

        enum wxStyledTextCtrl_constants
        {
            MARGIN_LINE_NUMBERS,
            MARGIN_FOLD
        };

        enum wxIDs
        {
            ID_GENERATE_BTN = wxID_HIGHEST + 1,
			ID_CPP_CODE,
			ID_HPP_CODE,
            ID_QUIT,
            ID_ABOUT
        };

        wxTextCtrl       * m_pEventNameTxtCtrl;
        wxStaticText     * m_staticText2;
        wxTextCtrl       * m_pEventTableEntryNameTxtCtrl;
        wxBitmapButton   * m_pGenerateEventBtn;

		wxNotebook* m_outputNotebook;
		wxPanel* m_outputHppPanel;
		wxStyledTextCtrl* m_outputHpp;
		wxPanel* m_outputCppPanel;
		wxStyledTextCtrl* m_outputCpp;

        wxStaticText     * m_staticText3;
        wxSpinCtrl       * m_pEventIdSpinCtrl;
        wxMenuBar        * m_pMenubar;
        wxMenu           * m_pFileMenu;
        wxMenu           * m_pHelpMenu;
        wxConfig         * m_config;

        void OnButton(wxCommandEvent&);
        void OnQuit  (wxCommandEvent&);
        void OnAbout (wxCommandEvent&);
        void OnMarginClick(wxStyledTextEvent &event);
        void SetUpMenuBar(void);
        void SetUpStatusBar(void);
        void SaveCurrentProgramSettings(void);
        void RestoreCurrentProgramSettings(void);
		static void ConfigureTextStyle(wxStyledTextCtrl* const styledTextCtrl);
        DECLARE_EVENT_TABLE()
};

#endif //__wxEventClassGen_header__
