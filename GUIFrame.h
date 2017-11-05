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
#include <wx/button.h>
#include <wx/statline.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/scrolwin.h>
#include <wx/stattext.h>
#include <wx/radiobox.h>
#include <wx/aui/auibook.h>
#include <wx/frame.h>
#include <wx/checkbox.h>
#include <wx/dialog.h>

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
		wxMenu* m_menu3;
		wxMenu* m_menu1;
		wxMenu* helpMenu;
		wxStatusBar* statusBar;
		wxAuiNotebook* biljeznica;
		wxScrolledWindow* m_scrolledWindow1;
		wxTextCtrl* tbAESKljuc;
		wxButton* btnAESDijalog;
		wxStaticLine* m_staticline5;
		wxButton* btnSnimiAESKljuc;
		wxButton* btnUcitajAESKljuc;
		wxTextCtrl* tbIv;
		wxStaticBoxSizer* okvirPorukeAES;
		wxTextCtrl* txtAESPoruka;
		wxButton* btnUcitajPorukuAES;
		wxButton* btnUcitajSifratAES;
		wxButton* btnSnimiPorukuAES;
		wxButton* btnSnimiSifratAES;
		wxButton* btnKriptirajPorukuAES;
		wxTextCtrl* tbSazetakAES;
		wxScrolledWindow* m_scrolledWindow2;
		wxStaticText* m_staticText4;
		wxTextCtrl* tbRSAPrivatniKljuc;
		wxStaticLine* m_staticline3;
		wxStaticText* m_staticText41;
		wxTextCtrl* tbRSAJavniKljuc;
		wxRadioBox* radioVelicinaRSAKljuca;
		wxButton* btnGenerirajRSAKljuc;
		wxStaticLine* m_staticline4;
		wxButton* btnSnimiRSAKljuc;
		wxButton* btnUcitajRSAKljuc;
		wxStaticBoxSizer* okvirPorukeRSA;
		wxTextCtrl* txtRSAPoruka;
		wxButton* btnUcitajPorukuRSA;
		wxButton* btnKriptirajPorukuRSA;
		wxTextCtrl* tbSazetakRSA;
		wxScrolledWindow* m_scrolledWindow3;
		wxTextCtrl* txtAESPorukaPotpis;
		wxButton* btnPotpisi;
		wxButton* btnVerificiraj;
		wxTextCtrl* txtAESPorukaPotpis1;
		wxStaticText* lblVerificirano;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnQuit( wxCommandEvent& event ) { event.Skip(); }
		virtual void UcitajPoruku( wxCommandEvent& event ) { event.Skip(); }
		virtual void UcitajSifratAES( wxCommandEvent& event ) { event.Skip(); }
		virtual void AESDijalog( wxCommandEvent& event ) { event.Skip(); }
		virtual void GenerirajRSA( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAbout( wxCommandEvent& event ) { event.Skip(); }
		virtual void snimiAESKljuc( wxCommandEvent& event ) { event.Skip(); }
		virtual void ucitajAESKljuc( wxCommandEvent& event ) { event.Skip(); }
		virtual void UcitajPorukuAES( wxCommandEvent& event ) { event.Skip(); }
		virtual void SnimiPorukuAES( wxCommandEvent& event ) { event.Skip(); }
		virtual void SnimiSifratAES( wxCommandEvent& event ) { event.Skip(); }
		virtual void KriptirajPorukuAES( wxCommandEvent& event ) { event.Skip(); }
		virtual void snimiRSAKljuceve( wxCommandEvent& event ) { event.Skip(); }
		virtual void ucitajRSAKljuceve( wxCommandEvent& event ) { event.Skip(); }
		virtual void UcitajPorukuRSA( wxCommandEvent& event ) { event.Skip(); }
		virtual void KriptirajPorukuRSA( wxCommandEvent& event ) { event.Skip(); }
		virtual void PotpisiPoruku( wxCommandEvent& event ) { event.Skip(); }
		virtual void Verificiraj( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUIFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Projekt (Operacijski sustavi 2)"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 512,636 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~GUIFrame();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GeneratorAES
///////////////////////////////////////////////////////////////////////////////
class GeneratorAES : public wxDialog 
{
	private:
	
	protected:
		wxTextCtrl* tcUnosLozinke;
		wxCheckBox* chkSol;
		wxRadioBox* radioVelicinaAESKljuca;
		wxButton* btnGenerirajAES;
		wxStaticLine* m_staticline1;
		wxStaticText* m_staticText2;
		wxTextCtrl* tbSol;
		wxStaticText* m_staticText4;
		wxTextCtrl* tbIv;
		wxStaticLine* m_staticline2;
		wxStaticText* m_staticText6;
		wxTextCtrl* tbGeneriraniAES;
		wxButton* btnCancel;
		wxButton* btnOK;
		
		// Virtual event handlers, overide them in your derived class
		virtual void zatvori( wxCloseEvent& event ) { event.Skip(); }
		virtual void GenerirajAES( wxCommandEvent& event ) { event.Skip(); }
		virtual void odustani( wxCommandEvent& event ) { event.Skip(); }
		virtual void potvrdi( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GeneratorAES( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 452,342 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~GeneratorAES();
	
};

#endif //__GUIFRAME_H__
