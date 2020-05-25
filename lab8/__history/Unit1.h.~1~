//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include <alloc.h>
//---------------------------------------------------------------------------
class TF_main : public TForm
{
__published:	// IDE-managed Components
	TEdit *E_Message;
	TMemo *Chat;
	TButton *B_Send;
	TButton *Analize;
	TButton *Salve;
	TMemo *Debug;
	TMemo *Answer;
	TDataSource *DataSource1;
	TADOTable *ADOTable;
	TDBGrid *lab5;
	TADOQuery *ADOQuery1;
	TButton *Button1;
	TEdit *Edit1;
	TLabel *Label1;
	TButton *Devide;
	TButton *Output;
	TMemo *Array;
	void __fastcall AnalizeClick(TObject *Sender);
	void __fastcall SalveClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall DevideClick(TObject *Sender);




private:	// User declarations
public:		// User declarations
	__fastcall TF_main(TComponent* Owner);
	enum Tmeasure {tvelocity = 1, tacc = 2, ttime = 3, tdistance = 4};//перечисление
	int dl;
	int words_number;
	char **words; //объявление двойного указателя (двумерный массив)

	struct TinputData {
		double value;
		Tmeasure measure;
	} Data [10]; // объявления массива для структуры так же как и для других классов (тип(класс).имя.размер)
				//struct TinputData t[10]; либо так, а не при создание самой структуры
	struct TinputData t;
};
//---------------------------------------------------------------------------
extern PACKAGE TF_main *F_main;
//---------------------------------------------------------------------------
#endif
