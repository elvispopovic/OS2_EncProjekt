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
	
	m_menu3 = new wxMenu();
	wxMenuItem* m_menuItem4;
	m_menuItem4 = new wxMenuItem( m_menu3, wxID_ANY, wxString( wxT("AES ključ") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu3->Append( m_menuItem4 );
	
	wxMenuItem* m_menuItem5;
	m_menuItem5 = new wxMenuItem( m_menu3, wxID_ANY, wxString( wxT("RSA par ključeva") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu3->Append( m_menuItem5 );
	
	mbar->Append( m_menu3, wxT("Ključevi") ); 
	
	helpMenu = new wxMenu();
	wxMenuItem* menuHelpAbout;
	menuHelpAbout = new wxMenuItem( helpMenu, idMenuAbout, wxString( wxT("&O programu") ) + wxT('\t') + wxT("F1"), wxT("Projekt iz Operacijskih sustava 2 (FOI)"), wxITEM_NORMAL );
	helpMenu->Append( menuHelpAbout );
	
	mbar->Append( helpMenu, wxT("&Pomoć") ); 
	
	this->SetMenuBar( mbar );
	
	statusBar = this->CreateStatusBar( 3, wxST_SIZEGRIP, wxID_ANY );
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );
	
	biljeznica = new wxAuiNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_scrolledWindow1 = new wxScrolledWindow( biljeznica, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindow1->SetScrollRate( 5, 5 );
	m_scrolledWindow1->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNTEXT ) );
	m_scrolledWindow1->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer10;
	sbSizer10 = new wxStaticBoxSizer( new wxStaticBox( m_scrolledWindow1, wxID_ANY, wxT("AES ključ") ), wxVERTICAL );
	
	wxBoxSizer* bSizer22;
	bSizer22 = new wxBoxSizer( wxVERTICAL );
	
	tbAESKljuc = new wxTextCtrl( sbSizer10->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CHARWRAP|wxTE_MULTILINE|wxTE_NO_VSCROLL|wxTE_READONLY|wxSIMPLE_BORDER|wxVSCROLL );
	tbAESKljuc->SetFont( wxFont( 10, 75, 90, 90, false, wxT("Lucida Console") ) );
	tbAESKljuc->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNTEXT ) );
	tbAESKljuc->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DLIGHT ) );
	tbAESKljuc->SetMinSize( wxSize( -1,36 ) );
	
	bSizer22->Add( tbAESKljuc, 0, wxBOTTOM|wxEXPAND|wxLEFT|wxRIGHT, 5 );
	
	btnAESDijalog = new wxButton( sbSizer10->GetStaticBox(), wxID_ANY, wxT("Generiraj"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer22->Add( btnAESDijalog, 0, wxALL, 5 );
	
	
	sbSizer10->Add( bSizer22, 1, wxEXPAND, 5 );
	
	
	bSizer11->Add( sbSizer10, 0, wxEXPAND|wxLEFT|wxRIGHT, 5 );
	
	wxStaticBoxSizer* sbSizer11;
	sbSizer11 = new wxStaticBoxSizer( new wxStaticBox( m_scrolledWindow1, wxID_ANY, wxT("Inicijalizacijski vektor") ), wxVERTICAL );
	
	tbIv = new wxTextCtrl( sbSizer11->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CHARWRAP|wxTE_MULTILINE|wxTE_NO_VSCROLL|wxTE_READONLY|wxSIMPLE_BORDER|wxVSCROLL );
	tbIv->SetFont( wxFont( 10, 75, 90, 90, false, wxT("Lucida Console") ) );
	tbIv->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DLIGHT ) );
	tbIv->SetMinSize( wxSize( -1,36 ) );
	
	sbSizer11->Add( tbIv, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizer11->Add( sbSizer11, 0, wxALL|wxEXPAND, 5 );
	
	okvirPorukeAES = new wxStaticBoxSizer( new wxStaticBox( m_scrolledWindow1, wxID_ANY, wxT("Poruka") ), wxVERTICAL );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	txtAESPoruka = new wxTextCtrl( okvirPorukeAES->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CHARWRAP|wxTE_MULTILINE|wxTE_READONLY|wxSIMPLE_BORDER );
	txtAESPoruka->SetFont( wxFont( 9, 75, 90, 90, false, wxT("Lucida Console") ) );
	txtAESPoruka->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DLIGHT ) );
	txtAESPoruka->SetMinSize( wxSize( -1,200 ) );
	
	bSizer8->Add( txtAESPoruka, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxVERTICAL );
	
	btnUcitajPorukuAES = new wxButton( okvirPorukeAES->GetStaticBox(), wxID_ANY, wxT("Učitaj"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer15->Add( btnUcitajPorukuAES, 0, wxALL, 5 );
	
	btnKriptirajPorukuAES = new wxButton( okvirPorukeAES->GetStaticBox(), wxID_ANY, wxT("Enkriptiraj"), wxDefaultPosition, wxDefaultSize, 0 );
	btnKriptirajPorukuAES->Enable( false );
	
	bSizer15->Add( btnKriptirajPorukuAES, 0, wxALL, 5 );
	
	
	bSizer9->Add( bSizer15, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( okvirPorukeAES->GetStaticBox(), wxID_ANY, wxT("Sažetak poruke") ), wxVERTICAL );
	
	tbSazetakAES = new wxTextCtrl( sbSizer4->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY|wxSIMPLE_BORDER|wxVSCROLL );
	tbSazetakAES->SetFont( wxFont( 10, 75, 90, 90, false, wxT("Lucida Console") ) );
	tbSazetakAES->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNTEXT ) );
	tbSazetakAES->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DLIGHT ) );
	tbSazetakAES->SetMinSize( wxSize( -1,60 ) );
	
	sbSizer4->Add( tbSazetakAES, 1, wxEXPAND, 5 );
	
	
	bSizer9->Add( sbSizer4, 1, wxEXPAND, 5 );
	
	
	bSizer8->Add( bSizer9, 0, wxEXPAND, 5 );
	
	
	okvirPorukeAES->Add( bSizer8, 1, wxEXPAND, 5 );
	
	
	bSizer11->Add( okvirPorukeAES, 1, wxEXPAND|wxLEFT|wxRIGHT, 5 );
	
	
	m_scrolledWindow1->SetSizer( bSizer11 );
	m_scrolledWindow1->Layout();
	bSizer11->Fit( m_scrolledWindow1 );
	biljeznica->AddPage( m_scrolledWindow1, wxT("a page"), false, wxNullBitmap );
	m_scrolledWindow2 = new wxScrolledWindow( biljeznica, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindow2->SetScrollRate( 5, 5 );
	m_scrolledWindow2->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNTEXT ) );
	m_scrolledWindow2->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	
	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer7;
	sbSizer7 = new wxStaticBoxSizer( new wxStaticBox( m_scrolledWindow2, wxID_ANY, wxT("Ključevi") ), wxVERTICAL );
	
	m_staticText4 = new wxStaticText( sbSizer7->GetStaticBox(), wxID_ANY, wxT("Privatni ključ"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	sbSizer7->Add( m_staticText4, 0, wxLEFT, 5 );
	
	tbRSAPrivatniKljuc = new wxTextCtrl( sbSizer7->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CHARWRAP|wxTE_MULTILINE|wxSIMPLE_BORDER );
	tbRSAPrivatniKljuc->SetFont( wxFont( 9, 75, 90, 90, false, wxT("Lucida Console") ) );
	tbRSAPrivatniKljuc->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DLIGHT ) );
	tbRSAPrivatniKljuc->SetMinSize( wxSize( -1,120 ) );
	
	sbSizer7->Add( tbRSAPrivatniKljuc, 0, wxEXPAND|wxLEFT|wxRIGHT, 5 );
	
	m_staticline3 = new wxStaticLine( sbSizer7->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	sbSizer7->Add( m_staticline3, 0, wxEXPAND | wxALL, 5 );
	
	m_staticText41 = new wxStaticText( sbSizer7->GetStaticBox(), wxID_ANY, wxT("Javni ključ"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText41->Wrap( -1 );
	sbSizer7->Add( m_staticText41, 0, wxLEFT, 5 );
	
	tbRSAJavniKljuc = new wxTextCtrl( sbSizer7->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CHARWRAP|wxTE_MULTILINE|wxSIMPLE_BORDER );
	tbRSAJavniKljuc->SetFont( wxFont( 9, 75, 90, 90, false, wxT("Lucida Console") ) );
	tbRSAJavniKljuc->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DLIGHT ) );
	tbRSAJavniKljuc->SetMinSize( wxSize( -1,80 ) );
	
	sbSizer7->Add( tbRSAJavniKljuc, 0, wxEXPAND|wxLEFT|wxRIGHT, 5 );
	
	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer( wxHORIZONTAL );
	
	wxString radioVelicinaRSAKljucaChoices[] = { wxT("1024"), wxT("2048"), wxT("3072") };
	int radioVelicinaRSAKljucaNChoices = sizeof( radioVelicinaRSAKljucaChoices ) / sizeof( wxString );
	radioVelicinaRSAKljuca = new wxRadioBox( sbSizer7->GetStaticBox(), wxID_ANY, wxT("Veličina ključa"), wxDefaultPosition, wxDefaultSize, radioVelicinaRSAKljucaNChoices, radioVelicinaRSAKljucaChoices, 1, wxRA_SPECIFY_ROWS );
	radioVelicinaRSAKljuca->SetSelection( 0 );
	bSizer17->Add( radioVelicinaRSAKljuca, 0, wxALL, 5 );
	
	wxStaticBoxSizer* sbSizer12;
	sbSizer12 = new wxStaticBoxSizer( new wxStaticBox( sbSizer7->GetStaticBox(), wxID_ANY, wxT("Upravljanje ključevima") ), wxHORIZONTAL );
	
	btnGenerirajRSAKljuc = new wxButton( sbSizer12->GetStaticBox(), wxID_ANY, wxT("Generiraj"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer12->Add( btnGenerirajRSAKljuc, 0, wxRIGHT, 5 );
	
	m_staticline4 = new wxStaticLine( sbSizer12->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	sbSizer12->Add( m_staticline4, 0, wxEXPAND, 5 );
	
	btnSnimiRSAKljuc = new wxButton( sbSizer12->GetStaticBox(), wxID_ANY, wxT("Snimi"), wxDefaultPosition, wxDefaultSize, 0 );
	btnSnimiRSAKljuc->Enable( false );
	
	sbSizer12->Add( btnSnimiRSAKljuc, 0, wxLEFT, 5 );
	
	btnUcitajRSAKljuc = new wxButton( sbSizer12->GetStaticBox(), wxID_ANY, wxT("Učitaj"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer12->Add( btnUcitajRSAKljuc, 0, 0, 5 );
	
	
	bSizer17->Add( sbSizer12, 1, wxRIGHT|wxTOP, 5 );
	
	
	sbSizer7->Add( bSizer17, 1, wxEXPAND, 5 );
	
	
	bSizer16->Add( sbSizer7, 0, wxALL|wxEXPAND, 5 );
	
	okvirPorukeRSA = new wxStaticBoxSizer( new wxStaticBox( m_scrolledWindow2, wxID_ANY, wxT("Poruka") ), wxVERTICAL );
	
	txtRSAPoruka = new wxTextCtrl( okvirPorukeRSA->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CHARWRAP|wxTE_MULTILINE|wxSIMPLE_BORDER );
	txtRSAPoruka->SetFont( wxFont( 9, 75, 90, 90, false, wxT("Lucida Console") ) );
	txtRSAPoruka->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DLIGHT ) );
	txtRSAPoruka->SetMinSize( wxSize( -1,100 ) );
	
	okvirPorukeRSA->Add( txtRSAPoruka, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer91;
	bSizer91 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer151;
	bSizer151 = new wxBoxSizer( wxHORIZONTAL );
	
	btnUcitajPorukuRSA = new wxButton( okvirPorukeRSA->GetStaticBox(), wxID_ANY, wxT("Učitaj"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer151->Add( btnUcitajPorukuRSA, 0, wxALL, 5 );
	
	btnKriptirajPorukuRSA = new wxButton( okvirPorukeRSA->GetStaticBox(), wxID_ANY, wxT("Enkriptiraj"), wxDefaultPosition, wxDefaultSize, 0 );
	btnKriptirajPorukuRSA->Enable( false );
	
	bSizer151->Add( btnKriptirajPorukuRSA, 0, wxALL, 5 );
	
	
	bSizer91->Add( bSizer151, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer41;
	sbSizer41 = new wxStaticBoxSizer( new wxStaticBox( okvirPorukeRSA->GetStaticBox(), wxID_ANY, wxT("Sažetak poruke") ), wxVERTICAL );
	
	tbSazetakRSA = new wxTextCtrl( sbSizer41->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY|wxSIMPLE_BORDER|wxVSCROLL );
	tbSazetakRSA->SetFont( wxFont( 10, 75, 90, 90, false, wxT("Lucida Console") ) );
	tbSazetakRSA->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNTEXT ) );
	tbSazetakRSA->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DLIGHT ) );
	tbSazetakRSA->SetMinSize( wxSize( -1,60 ) );
	
	sbSizer41->Add( tbSazetakRSA, 1, wxEXPAND, 5 );
	
	
	bSizer91->Add( sbSizer41, 1, wxEXPAND, 5 );
	
	
	okvirPorukeRSA->Add( bSizer91, 1, wxEXPAND, 5 );
	
	
	bSizer16->Add( okvirPorukeRSA, 0, wxBOTTOM|wxEXPAND|wxLEFT|wxRIGHT, 5 );
	
	
	m_scrolledWindow2->SetSizer( bSizer16 );
	m_scrolledWindow2->Layout();
	bSizer16->Fit( m_scrolledWindow2 );
	biljeznica->AddPage( m_scrolledWindow2, wxT("a page"), true, wxNullBitmap );
	m_scrolledWindow3 = new wxScrolledWindow( biljeznica, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindow3->SetScrollRate( 5, 5 );
	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer101;
	sbSizer101 = new wxStaticBoxSizer( new wxStaticBox( m_scrolledWindow3, wxID_ANY, wxT("Poruka") ), wxVERTICAL );
	
	txtAESPorukaPotpis = new wxTextCtrl( sbSizer101->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CHARWRAP|wxTE_MULTILINE|wxTE_READONLY|wxSIMPLE_BORDER );
	txtAESPorukaPotpis->SetFont( wxFont( 9, 75, 90, 90, false, wxT("Lucida Console") ) );
	txtAESPorukaPotpis->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DLIGHT ) );
	txtAESPorukaPotpis->SetMinSize( wxSize( -1,200 ) );
	
	sbSizer101->Add( txtAESPorukaPotpis, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizer18->Add( sbSizer101, 1, wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer111;
	sbSizer111 = new wxStaticBoxSizer( new wxStaticBox( m_scrolledWindow3, wxID_ANY, wxT("Digitalni potpis") ), wxVERTICAL );
	
	wxBoxSizer* bSizer181;
	bSizer181 = new wxBoxSizer( wxHORIZONTAL );
	
	btnPotpisi = new wxButton( sbSizer111->GetStaticBox(), wxID_ANY, wxT("Potpiši"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer181->Add( btnPotpisi, 0, wxLEFT, 5 );
	
	btnVerificiraj = new wxButton( sbSizer111->GetStaticBox(), wxID_ANY, wxT("Verificiraj"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer181->Add( btnVerificiraj, 0, wxLEFT, 5 );
	
	
	sbSizer111->Add( bSizer181, 0, wxEXPAND, 5 );
	
	txtAESPorukaPotpis1 = new wxTextCtrl( sbSizer111->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CHARWRAP|wxTE_MULTILINE|wxTE_READONLY|wxSIMPLE_BORDER );
	txtAESPorukaPotpis1->SetFont( wxFont( 9, 75, 90, 90, false, wxT("Lucida Console") ) );
	txtAESPorukaPotpis1->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DLIGHT ) );
	txtAESPorukaPotpis1->SetMinSize( wxSize( -1,130 ) );
	
	sbSizer111->Add( txtAESPorukaPotpis1, 0, wxALL|wxEXPAND, 5 );
	
	lblVerificirano = new wxStaticText( sbSizer111->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	lblVerificirano->Wrap( -1 );
	sbSizer111->Add( lblVerificirano, 0, wxLEFT, 5 );
	
	
	bSizer18->Add( sbSizer111, 1, wxEXPAND|wxLEFT|wxRIGHT, 5 );
	
	
	m_scrolledWindow3->SetSizer( bSizer18 );
	m_scrolledWindow3->Layout();
	bSizer18->Fit( m_scrolledWindow3 );
	biljeznica->AddPage( m_scrolledWindow3, wxT("a page"), false, wxNullBitmap );
	
	bSizer1->Add( biljeznica, 1, wxEXPAND | wxALL, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	this->Connect( menuFileQuit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnQuit ) );
	this->Connect( menuUcitajPoruku->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::UcitajPoruku ) );
	this->Connect( m_menuItem4->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::AESDijalog ) );
	this->Connect( m_menuItem5->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::GenerirajRSA ) );
	this->Connect( menuHelpAbout->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnAbout ) );
	btnAESDijalog->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::AESDijalog ), NULL, this );
	btnUcitajPorukuAES->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::UcitajPorukuAES ), NULL, this );
	btnKriptirajPorukuAES->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::KriptirajPorukuAES ), NULL, this );
	btnGenerirajRSAKljuc->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::GenerirajRSA ), NULL, this );
	btnSnimiRSAKljuc->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::snimiRSAKljuceve ), NULL, this );
	btnUcitajRSAKljuc->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::ucitajRSAKljuceve ), NULL, this );
	btnUcitajPorukuRSA->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::UcitajPorukuRSA ), NULL, this );
	btnKriptirajPorukuRSA->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::KriptirajPorukuRSA ), NULL, this );
	btnPotpisi->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::PotpisiPoruku ), NULL, this );
	btnVerificiraj->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::Verificiraj ), NULL, this );
}

GUIFrame::~GUIFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	this->Disconnect( idMenuQuit, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnQuit ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::UcitajPoruku ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::AESDijalog ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::GenerirajRSA ) );
	this->Disconnect( idMenuAbout, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnAbout ) );
	btnAESDijalog->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::AESDijalog ), NULL, this );
	btnUcitajPorukuAES->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::UcitajPorukuAES ), NULL, this );
	btnKriptirajPorukuAES->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::KriptirajPorukuAES ), NULL, this );
	btnGenerirajRSAKljuc->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::GenerirajRSA ), NULL, this );
	btnSnimiRSAKljuc->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::snimiRSAKljuceve ), NULL, this );
	btnUcitajRSAKljuc->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::ucitajRSAKljuceve ), NULL, this );
	btnUcitajPorukuRSA->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::UcitajPorukuRSA ), NULL, this );
	btnKriptirajPorukuRSA->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::KriptirajPorukuRSA ), NULL, this );
	btnPotpisi->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::PotpisiPoruku ), NULL, this );
	btnVerificiraj->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::Verificiraj ), NULL, this );
	
}

GeneratorAES::GeneratorAES( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
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
	
	wxString radioVelicinaAESKljucaChoices[] = { wxT("128"), wxT("192"), wxT("256") };
	int radioVelicinaAESKljucaNChoices = sizeof( radioVelicinaAESKljucaChoices ) / sizeof( wxString );
	radioVelicinaAESKljuca = new wxRadioBox( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Veličina ključa [bitova]"), wxDefaultPosition, wxDefaultSize, radioVelicinaAESKljucaNChoices, radioVelicinaAESKljucaChoices, 1, wxRA_SPECIFY_ROWS );
	radioVelicinaAESKljuca->SetSelection( 0 );
	bSizer6->Add( radioVelicinaAESKljuca, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizer2->Add( bSizer6, 0, wxEXPAND, 5 );
	
	btnGenerirajAES = new wxButton( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Generiraj ključ"), wxDefaultPosition, wxSize( 150,30 ), 0 );
	bSizer2->Add( btnGenerirajAES, 1, wxBOTTOM|wxEXPAND|wxLEFT|wxRIGHT|wxTOP, 5 );
	
	m_staticline1 = new wxStaticLine( sbSizer1->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer2->Add( m_staticline1, 0, wxEXPAND|wxLEFT|wxRIGHT|wxTOP, 5 );
	
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
	bSizer2->Add( m_staticline2, 0, wxALL|wxEXPAND, 5 );
	
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
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	btnCancel = new wxButton( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Odustani"), wxDefaultPosition, wxSize( 140,30 ), 0 );
	bSizer3->Add( btnCancel, 0, wxLEFT|wxRIGHT|wxTOP, 10 );
	
	btnOK = new wxButton( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Potvrdi"), wxDefaultPosition, wxSize( 140,30 ), 0 );
	btnOK->SetDefault(); 
	bSizer3->Add( btnOK, 0, wxRIGHT|wxTOP, 10 );
	
	
	sbSizer1->Add( bSizer3, 1, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	this->SetSizer( sbSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GeneratorAES::zatvori ) );
	btnGenerirajAES->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GeneratorAES::GenerirajAES ), NULL, this );
	btnCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GeneratorAES::odustani ), NULL, this );
	btnOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GeneratorAES::potvrdi ), NULL, this );
}

GeneratorAES::~GeneratorAES()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GeneratorAES::zatvori ) );
	btnGenerirajAES->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GeneratorAES::GenerirajAES ), NULL, this );
	btnCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GeneratorAES::odustani ), NULL, this );
	btnOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GeneratorAES::potvrdi ), NULL, this );
	
}
