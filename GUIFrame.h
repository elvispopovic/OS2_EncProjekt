///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUIFRAME_H__
#define __GUIFRAME_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/statusbr.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/radiobox.h>
#include <wx/button.h>
#include <wx/statline.h>
#include <wx/stattext.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

#define idMenuQuit 1000
#define idMenuAbout 1001

///////////////////////////////////////////////////////////////////////////////
/// Class GUIFrame
///////////////////////////////////////////////////////////////////////////////
class GUIFrame : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* mbar;
		wxMenu* fileMenu;
		wxMenu* helpMenu;
		wxStatusBar* statusBar;
		wxTextCtrl* tcUnosLozinke;
		wxCheckBox* chkSol;
		wxRadioBox* radioVelicinaKljuca;
		wxButton* btnGenerirajAES;
		wxButton* btnSnimi;
		wxStaticLine* m_staticline1;
		wxStaticText* m_staticText2;
		wxTextCtrl* tbSol;
		wxStaticText* m_staticText4;
		wxTextCtrl* tbIv;
		wxStaticLine* m_staticline2;
		wxStaticText* m_staticText6;
		wxTextCtrl* tbGeneriraniAES;
		wxTextCtrl* txtPoruka;
		wxButton* btnKriptirajPoruku;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnQuit( wxCommandEvent& event ) { event.Skip(); }
		virtual void UcitajPoruku( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAbout( wxCommandEvent& event ) { event.Skip(); }
		virtual void GenerirajAES( wxCommandEvent& event ) { event.Skip(); }
		virtual void snimiAES( wxCommandEvent& event ) { event.Skip(); }
		virtual void KriptirajPoruku( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUIFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Projekt (Operacijski sustavi 2)"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 512,625 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~GUIFrame();
	
};

#endif //__GUIFRAME_H__
