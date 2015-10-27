#ifndef __wxEventClassGen_header__
#define __wxEventClassGen_header__

/// @author Dr. Martin Ettl
/// @date   2015-10-20

/// @brief This is a wxEventClass generator.
/// In simpilifies the creation of event classes, by generating a workable and customized event class.
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

/// Use wxStyledTextCtrl to display the generated source code (https://wiki.wxwidgets.org/WxStyledTextCtrl).
#include <wx/stc/stc.h>

class wxEventClassGen : public wxFrame
{
    private:

        enum wxStyledTextCtrl_constants
        {
            MARGIN_LINE_NUMBERS,
            MARGIN_FOLD
        };

        enum wxIDs
        {
            ID_GENERATE_BTN = wxID_HIGHEST + 1,
            ID_QUIT,
            ID_ABOUT
        };

    protected:

        wxTextCtrl       * m_pEventNameTxtCtrl;
        wxStaticText     * m_staticText2;
        wxTextCtrl       * m_pEventTableEntryNameTxtCtrl;
        wxBitmapButton   * m_pGenerateEventBtn;
        wxStyledTextCtrl * m_pOutput;
        wxStaticText     * m_staticText3;
        wxSpinCtrl       * m_pEventIdSpinCtrl;
        wxMenuBar        * m_pMenubar;
        wxMenu           * m_pFileMenu;
        wxMenu           * m_pHelpMenu;
        wxConfig         * m_config;

        void vOnButton(wxCommandEvent&);
        void vOnQuit  (wxCommandEvent&);
        void vOnAbout (wxCommandEvent&);
        void OnMarginClick(wxStyledTextEvent &event);

        void vSetUpMenuBar  (void);
        void vSetUpStatusBar(void);

        void SaveCurrentProgramSettings(void);
        void RestoreCurrentProgramSettings(void);

    public:

        wxEventClassGen( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1200, 800 ), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL );
        ~wxEventClassGen();

        DECLARE_EVENT_TABLE()

};

#endif //__wxEventClassGen_header__
