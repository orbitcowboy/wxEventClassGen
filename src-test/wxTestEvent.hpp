#ifndef CLASSWXTEST__HPP
#define CLASSWXTEST__HPP

#include <wx/wx.h>
#include <wx/event.h>

/// @brief Declaration of an custom event type, this is the wxWidgets way to predefine an event class.
DECLARE_EVENT_TYPE( wxTestCommandEvent, -1 )


///\brief This is a custom event class.
///@author Dr. Martin Ettl
///@date  Oct 28 2015

class wxTest: public wxCommandEvent
{
public:
    /// @brief a custom event id, define as many as you want
    static const long m_sciwxTestEventId = -1;

    /// Constructor of class wxTest
    ///
    /// @param[in] commandType The event type
    /// @param[in] id          The event id. The default value is 0.
    wxTest( wxEventType commandType = wxTestCommandEvent, int id = 0 )
        :  wxCommandEvent(commandType, id)
    {}

    /// @brief Copy constructor
    ///
    /// @param[in] event An wxTest-event object.
    wxTest( const wxTest &event )
        :  wxCommandEvent(event)
    {}

    /// @brief This Clone function is required for sending with wxPostEvent().
    wxEvent* Clone(void) const
    {
        return new wxTest(*this);
    }
};


typedef void (wxEvtHandler::*wxTestEventFunction)(wxTest &);

// This #define simplifies the one below, and makes the syntax less
// ugly if you want to use Connect() instead of an event table.
#define wxTestHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)\
    wxStaticCastEvent(wxTestEventFunction, &func)


// Define the event table entry. Yes, it really *does* end in a comma.
#define EVT_TEST(id, fn)\
    DECLARE_EVENT_TABLE_ENTRY(wxTestCommandEvent, id, wxID_ANY,\
                              (wxObjectEventFunction)(wxEventFunction)\
                              (wxCommandEventFunction) wxStaticCastEvent(\
                                      wxTestEventFunction, &fn ), (wxObject*) NULL ),


// Optionally, you can do a similar #define for EVT_EVT_TEST_RANGE.
#define EVT_TEST_RANGE(id1,id2, fn) \
    DECLARE_EVENT_TABLE_ENTRY( wxTestCommandEvent, id1, id2, \
                               wxTestHandler(fn), (wxObject*) NULL ),

#endif // class_WXTEST__HPP
