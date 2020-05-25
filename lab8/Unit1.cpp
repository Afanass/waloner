//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TF_main *F_main;
//---------------------------------------------------------------------------
__fastcall TF_main::TF_main(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------






void __fastcall TF_main::AnalizeClick(TObject *Sender)
{
	int p;
	int l;
	int m;
	int n;
	dl = 0;
	String text;
	String out;
	text = Chat->Lines->GetText();
	String word;
	int i;
	bool numFound = false;
	char *measureText [] = {"lol","��/�","��/�2","�","��"};
	do {
		p = text.Pos(" ");
		if (p == 0) {
			word = text;
		} else {
			word = text.SubString(1,p-1);
			text = text.SubString(p+1,text.Length());
			l = word.Length();
			n = word.Pos(",");
			m = word.Pos(".");
			if ( l  == m ||  l  == n ) {
				word = word.SubString(1 , word.Length() - 1);
		}
		}

		 if(numFound == true){
		   if(word == "��/�"){
				Data[dl-1].measure = tvelocity;
				numFound = false;
		   }
		   else if (word == "�����" || word == "����" || word == "���" ) {
				Data[dl-1].measure = ttime;
				numFound = false;
		   }
		   else if (word == "��/�2" ) {
				Data[dl-1].measure = tacc;
				numFound = false;
		   }
		   else if (word == "��" ) {
				Data[dl-1].measure = tdistance;
				numFound = false;
		   }
		   }
		Debug->Lines->Add(word);
		try{
			Data[dl].value = word.ToDouble();
			numFound = true;
			dl=dl+1;
			Debug->Lines->Add("����");
		}
			catch ( const Exception& e)
		{
			//�������
		}
		if (word == "���") {
			Data[dl].value = 2;
			numFound = true;
			dl=dl+1;
			Debug->Lines->Add("����");
		}
		if (word == "���") {
			Data[dl].value = 1;
			Data[dl].measure = ttime;
			dl=dl+1;
			Debug->Lines->Add("����");
		}
	}
	while (p);
	for (i = 0; i < dl; i++) {
		out = FloatToStr(Data[i].value);
		Debug->Lines->Add( out + " " + measureText[Data[i].measure]);
	}
}
//---------------------------------------------------------------------------





void __fastcall TF_main::SalveClick(TObject *Sender)
{
	int n;
	int p;
	int i;
	int it = 0;
	int is = 0;
	int iv = 0;
	int j;
	String text;
	text = Chat->Lines->GetText();
	p = text.Pos("������� ������� ��������");
	if (p == 0) {
		Answer->Lines->Add("������� �� �������");
	} else {
		Answer->Lines->Add("������� �������");
 }
	double S = 0;
	double T = 0;
	double V = 0;
	double v[10], s[10], t[10];
	for (i = 0; i < dl; i++) {
		if (Data[i].measure == tvelocity) {
				v[iv] = Data[i].value;
				iv++;
			}
		if (Data[i].measure == tdistance) {
				s[is] = Data[i].value;
				is++;
			}
		if (Data[i].measure == ttime) {
				t[it] = Data[i].value;
				it++;

			}
	}
	if (it > is ) {
		for (n = 0; n < it; n++) {
			T = T + t[n];
			S = S + v[n]*t[n];
		}
	} else {
		for (j = 0; j < is; j++) {
			T = T + s[j]/v[j];
			S = S + s[j];
		}
	}
	if (T == 0 && S == 0) {
		Answer->Lines->Add("��������� ������");
	} else {
		V = S/T;
		Answer->Lines->Add(V);
	}
	}

//---------------------------------------------------------------------------





void __fastcall TF_main::Button1Click(TObject *Sender)
{
ADOQuery1->Close();
ADOQuery1->SQL->Clear();
ADOQuery1->SQL->Add("select * from numbers where Word=:param1");
ADOQuery1->Parameters->ParamByName("param1")->Value = Edit1->Text;
ADOQuery1->Open();
AnsiString str = ADOQuery1->FieldByName("Numbers")->AsString;
Label1->Caption = str;

}
//---------------------------------------------------------------------------

void __fastcall TF_main::DevideClick(TObject *Sender)
{
    int j;
	int i;
	int p;
	int l;
	int m;
	int n;
	String text;
	String punkt = NULL;
	text = Chat->Lines->GetText();
	String word;
	words_number = 0;
	words = (char** ) 0; // ���������� � ���� char**
	words = NULL; // ���� �����, ���������� ��� �� ������������� ������
	char* pc = NULL;
	do{
		p = text.Pos(" ");
			if (p == 0) {
				word = text;
				l = word.Length();
				n = word.Pos(",");
				m = word.Pos(".");
				if ( l == m ||  l == n ) {
				punkt = word.SubString(word.Length(), word.Length());
				word = word.SubString(1 , word.Length() - 1);
				}
			} else {
				word = text.SubString(1,p-1);
				text = text.SubString(p+1,text.Length());
				l = word.Length();
				n = word.Pos(",");
				m = word.Pos(".");
				if ( l  == m ||  l  == n ) {
					punkt = word.SubString(word.Length(), word.Length());
					word = word.SubString(1 , word.Length() - 1);
				}
			}
			pc = (char*) malloc(word.Length() + 1); // +1 ��� �������� ������� � ���������� � ���� char** ����������� �� ���������� void
			if (pc == NULL) {
				return;
			}
			words_number++;
			if (words == NULL) {
				words = (char**) malloc(words_number*sizeof(char *));//sizeof(char *) ���������� ���������� ������ ���������� char * �� �� ��������� ��������� �� char
			} else {
				words = (char**) realloc(words,words_number*sizeof(char *));// �������� ������ � �������� ���������� ������,
				//�� reallock ���������� ������ ��� �������� ������� ��� ���� �������� ������ (� ����� ������ ��������� malloc ��� ������� �����)
			}
			//strcpy(pc,(char *) word.c_str()); // .c_str() ��������� � �� string � char
			WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, word.c_str(), -1, pc, word.Length() + 1, NULL, NULL);
			words[words_number - 1] = pc;
			if ( punkt != 0 ) {
				pc = (char*) malloc(punkt.Length() + 1); // +1 ��� �������� ������� � ���������� � ���� char** ����������� �� ���������� void
				if (pc == NULL) {
					return;
				}
				words_number++;
				if (words == NULL) {
					words = (char**) malloc(words_number*sizeof(char *));//sizeof(char *) ���������� ���������� ������ ���������� char * �� �� ��������� ��������� �� char
				} else {
					words = (char**) realloc(words,words_number*sizeof(char *));// �������� ������ � �������� ���������� ������,
					//�� reallock ���������� ������ ��� �������� ������� ��� ���� �������� ������ (� ����� ������ ��������� malloc ��� ������� �����)
				}
				//strcpy(pc,(char *) word.c_str()); // .c_str() ��������� � �� string � char
				WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, punkt.c_str(), -1, pc, punkt.Length() + 1, NULL, NULL);
				words[words_number - 1] = pc;
				bool numFound = false;
				punkt = NULL;
			}

	} while (p);
	for (i = 0; i < words_number; i++) {
			Array->Lines->Add(words[i]);
	}

}
//---------------------------------------------------------------------------

void __fastcall TF_main::GenerationClick(TObject *Sender)
{
	char *srav = "����������";
	double result;
	int i;
	int j;
	double m = 0;
	double g = 0;
	bool flag = false;
	AnsiString index;
	AnsiString group;
	AnsiString str;
	randomize();

	for (i = 0; i < words_number; i++) {
		j = sscanf(words[i],"%f",&result);
		if (j > 0) {
			Array->Text = Array->Text + rand() %100 + " ";
			} else {
			try{
				ADOQuery1->Close();
				ADOQuery1->SQL->Clear();
				ADOQuery1->SQL->Add("select `group` from `sinonimi` where `sinonim` =:word ");
				ADOQuery1->Parameters->ParamByName("word")->Value = words[i];
				ADOQuery1->Open();
				group = ADOQuery1->FieldByName("group")->AsString;
				g = StrToFloat(group);
				group = FloatToStr(g);


				ADOQuery1->Close();
				ADOQuery1->SQL->Clear();
				ADOQuery1->SQL->Add("select `index` from `sinonimi` where `sinonim` =:word ");
				ADOQuery1->Parameters->ParamByName("word")->Value = words[i];
				ADOQuery1->Open();
				index = ADOQuery1->FieldByName("index")->AsString;
				m = StrToFloat(index) + 1;
				index = FloatToStr(m);

				ADOQuery1->Close();
				ADOQuery1->SQL->Clear();
				ADOQuery1->SQL->Add("select `sinonim` from `sinonimi` where `group`= :group and `index` = :index");
				ADOQuery1->Parameters->ParamByName("group")->Value = group;
				ADOQuery1->Parameters->ParamByName("index")->Value = index;
				ADOQuery1->Open();
				str = ADOQuery1->FieldByName("sinonim")->AsString;
				}
			catch ( const Exception& e)
			{

			}
			if (str == "") {
				Array->Text = Array->Text + words[i] + " ";
			} else {
				Array->Text = Array->Text + str + " ";
				str = "";
			}

		}

	}
}
//---------------------------------------------------------------------------




