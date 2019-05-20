//---------------------------------------------------------------------------

#ifndef calculH
#define calculH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------

typedef char nompoint[15];

class TFormVoisinages : public TForm
{
__published:	// Composants gérés par l'EDI
	TOpenDialog *OpenDialogNomFicEntree;
	TLabel *Label1;
	TEdit *EditNomFicEntree;
	TButton *ButtonNomFicEntree;
	TComboBox *cb_depart;
	TComboBox *cb_arrivee;
	TComboBox *cb_valeur;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TButton *ButtonCalculer;
	TLabel *Label7;
	TEdit *EditNomFicSortie;
	TSaveDialog *SaveDialogNomFicSortie;
	TButton *ButtonNomFicSortie;
	TRadioGroup *RadioGroupMinimiser;
	TRadioGroup *RadioGroupOriente;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TRadioGroup *RadioGroupOrdreMax;
	TLabel *Label11;
	TLabel *Label12;
	TRadioGroup *RadioGroupValMax;
	TLabel *Label13;
	TLabel *Label14;
	TEdit *EditValMax;
	TLabel *Label15;
	TUpDown *UpDownOrdreMax;
	TLabel *Label16;
	TEdit *EditOrdMax;
	TProgressBar *ProgressBar1;
	TLabel *Label17;
	TLabel *Label18;
	TComboBox *cb_coupimp;
	TRadioGroup *RadioGroupvirgule;
	TLabel *Label19;
	TLabel *Label20;
	TComboBox *cb_couplim;
	TLabel *Label21;
	TLabel *Label22;
	TLabel *Label23;
	TLabel *Label24;
	TLabel *Label25;
	TLabel *Label26;
	void __fastcall ButtonNomFicEntreeClick(TObject *Sender);
	void __fastcall ButtonCalculerClick(TObject *Sender);
	void __fastcall ButtonNomFicSortieClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
private:	// Déclarations utilisateur
public:		// Déclarations utilisateur
	__fastcall TFormVoisinages(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormVoisinages *FormVoisinages;
//---------------------------------------------------------------------------
#endif
