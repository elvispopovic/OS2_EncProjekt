///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif //WX_PRECOMP

#include "GUIFrame.h"

///////////////////////////////////////////////////////////////////////////

GUIFrame::GUIFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	mbar = new wxMenuBar( 0 );
	fileMenu = new wxMenu();
	wxMenuItem* menuFileQuit;
	menuFileQuit = new wxMenuItem( fileMenu, idMenuQuit, wxString( wxT("&Izlaz") ) + wxT('\t') + wxT("Alt+F4"), wxT("Quit the application"), wxITEM_NORMAL );
	fileMenu->Append( menuFileQuit );
	
	wxMenuItem* menuUcitajPoruku;
	menuUcitajPoruku = new wxMenuItem( fileMenu, wxID_ANY, wxString( wxT("&Učitaj poruku") ) + wxT('\t') + wxT("CTRL+O"), wxT("Učitavanje poruke"), wxITEM_NORMAL );
	fileMenu->Append( menuUcitajPoruku );
	
	mbar->Append( fileMenu, wxT("&Datoteka") ); 
	
	helpMenu = new wxMenu();
	wxMenuItem* menuHelpAbout;
	menuHelpAbout = new wxMenuItem( helpMenu, idMenuAbout, wxString( wxT("&About") ) + wxT('\t') + wxT("F1"), wxT("Show info about this application"), wxITEM_NORMAL );
	helpMenu->Append( menuHelpAbout );
	
	mbar->Append( helpMenu, wxT("&Pomoć") ); 
	
	this->SetMenuBar( mbar );
	
	statusBar = this->CreateStatusBar( 2, wxST_SIZEGRIP, wxID_ANY );
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Kreiranje AES ključa") ), wxVERTICAL );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( sbSizer1->GetStaticBox(), wxID_ANY, wxT("lozinka") ), wxHORIZONTAL );
	
	tcUnosLozinke = new wxTextCtrl( sbSizer2->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,30 ), wxTE_PASSWORD );
	tcUnosLozinke->SetFont( wxFont( 10, 74, 90, 90, false, wxT("Arial Rounded MT Bold") ) );
	tcUnosLozinke->SetForegroundColour( wxColour( 255, 128, 0 ) );
	tcUnosLozinke->SetBackgroundColour( wxColour( 0, 0, 0 ) );
	
	sbSizer2->Add( tcUnosLozinke, 1, wxEXPAND|wxLEFT|wxRIGHT, 5 );
	
	chkSol = new wxCheckBox( sbSizer2->GetStaticBox(), wxID_ANY, wxT("Sol"), wxDefaultPosition, wxDefaultSize, 0|wxTRANSPARENT_WINDOW );
	chkSol->SetValue(true); 
	sbSizer2->Add( chkSol, 0, wxALIGN_BOTTOM, 5 );
	
	
	bSizer6->Add( sbSizer2, 1, wxALL|wxEXPAND, 5 );
	
	wxString radioVelicinaKljucaChoices[] = { wxT("128"), wxT("192"), wxT("256") };
	int radioVelicinaKljucaNChoices = sizeof( radioVelicinaKljucaChoices ) / sizeof( wxString );
	radioVelicinaKljuca = new wxRadioBox( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Veličina ključa [bitova]"), wxDefaultPosition, wxDefaultSize, radioVelicinaKljucaNChoices, radioVelicinaKljucaChoices, 1, wxRA_SPECIFY_ROWS );
	radioVelicinaKljuca->SetSelection( 0 );
	bSizer6->Add( radioVelicinaKljuca, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizer2->Add( bSizer6, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	btnGenerirajAES = new wxButton( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Generiraj ključ"), wxDefaultPosition, wxSize( 150,30 ), 0 );
	bSizer3->Add( btnGenerirajAES, 1, wxLEFT|wxRIGHT|wxTOP, 10 );
	
	btnSnimi = new wxButton( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Snimi"), wxDefaultPosition, wxSize( 140,30 ), 0 );
	bSizer3->Add( btnSnimi, 0, wxLEFT|wxRIGHT|wxTOP, 10 );
	
	
	bSizer2->Add( bSizer3, 1, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( sbSizer1->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer2->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText2 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Sol"), wxDefaultPosition, wxSize( 90,-1 ), 0 );
	m_staticText2->Wrap( -1 );
	bSizer7->Add( m_staticText2, 0, wxTOP, 20 );
	
	tbSol = new wxTextCtrl( sbSizer1->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CHARWRAP|wxTE_MULTILINE|wxTE_NO_VSCROLL|wxTE_READONLY|wxNO_BORDER|wxVSCROLL );
	tbSol->SetFont( wxFont( 10, 75, 90, 90, false, wxT("Lucida Console") ) );
	
	bSizer7->Add( tbSol, 1, wxEXPAND|wxLEFT|wxRIGHT|wxTOP, 5 );
	
	
	bSizer2->Add( bSizer7, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText4 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Inic. vektor"), wxDefaultPosition, wxSize( 90,-1 ), 0 );
	m_staticText4->Wrap( -1 );
	bSizer4->Add( m_staticText4, 0, wxTOP, 20 );
	
	tbIv = new wxTextCtrl( sbSizer1->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CHARWRAP|wxTE_MULTILINE|wxTE_NO_VSCROLL|wxTE_READONLY|wxNO_BORDER|wxVSCROLL );
	tbIv->SetFont( wxFont( 10, 75, 90, 90, false, wxT("Lucida Console") ) );
	
	bSizer4->Add( tbIv, 1, wxEXPAND|wxLEFT|wxRIGHT|wxTOP, 5 );
	
	
	bSizer2->Add( bSizer4, 1, wxEXPAND, 5 );
	
	m_staticline2 = new wxStaticLine( sbSizer1->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer2->Add( m_staticline2, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText6 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Generirani ključ"), wxDefaultPosition, wxSize( 90,-1 ), 0 );
	m_staticText6->Wrap( -1 );
	bSizer5->Add( m_staticText6, 0, wxTOP, 20 );
	
	tbGeneriraniAES = new wxTextCtrl( sbSizer1->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CHARWRAP|wxTE_MULTILINE|wxTE_NO_VSCROLL|wxTE_READONLY|wxNO_BORDER|wxVSCROLL );
	tbGeneriraniAES->SetFont( wxFont( 10, 75, 90, 90, false, wxT("Lucida Console") ) );
	
	bSizer5->Add( tbGeneriraniAES, 1, wxEXPAND|wxLEFT|wxRIGHT, 5 );
	
	
	bSizer2->Add( bSizer5, 1, wxEXPAND, 5 );
	
	
	sbSizer1->Add( bSizer2, 1, wxEXPAND, 5 );
	
	
	bSizer1->Add( sbSizer1, 0, wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Poruka") ), wxVERTICAL );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	txtPoruka = new wxTextCtrl( sbSizer3->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY|wxNO_BORDER );
	txtPoruka->SetFont( wxFont( 9, 75, 90, 90, false, wxT("Lucida Console") ) );
	txtPoruka->SetMinSize( wxSize( -1,200 ) );
	
	bSizer8->Add( txtPoruka, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxHORIZONTAL );
	
	btnKriptirajPoruku = new wxButton( sbSizer3->GetStaticBox(), wxID_ANY, wxT("Enkriptiraj"), wxDefaultPosition, wxDefaultSize, 0 );
	btnKriptirajPoruku->Enable( false );
	
	bSizer9->Add( btnKriptirajPoruku, 0, wxALL, 5 );
	
	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( sbSizer3->GetStaticBox(), wxID_ANY, wxT("Sažetak poruke") ), wxVERTICAL );
	
	tbSazetak = new wxTextCtrl( sbSizer4->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY|wxNO_BORDER|wxVSCROLL );
	tbSazetak->SetFont( wxFont( 10, 75, 90, 90, false, wxT("Lucida Console") ) );
	
	sbSizer4->Add( tbSazetak, 1, wxEXPAND, 5 );
	
	
	bSizer9->Add( sbSizer4, 1, wxEXPAND, 5 );
	
	
	bSizer8->Add( bSizer9, 1, wxEXPAND, 5 );
	
	
	sbSizer3->Add( bSizer8, 1, wxEXPAND, 5 );
	
	
	bSizer1->Add( sbSizer3, 1, wxEXPAND|wxLEFT|wxRIGHT, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	this->Connect( menuFileQuit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnQuit ) );
	this->Connect( menuUcitajPoruku->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::UcitajPoruku ) );
	this->Connect( menuHelpAbout->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnAbout ) );
	btnGenerirajAES->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::GenerirajAES ), NULL, this );
	btnSnimi->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::snimiAES ), NULL, this );
	btnKriptirajPoruku->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::KriptirajPoruku ), NULL, this );
}

GUIFrame::~GUIFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	this->Disconnect( idMenuQuit, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnQuit ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::UcitajPoruku ) );
	this->Disconnect( idMenuAbout, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnAbout ) );
	btnGenerirajAES->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::GenerirajAES ), NULL, this );
	btnSnimi->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::snimiAES ), NULL, this );
	btnKriptirajPoruku->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::KriptirajPoruku ), NULL, this );
	
}
