//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#include <clipbrd.hpp>
#pragma hdrstop

#include "UCompute.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma link "CGRID"
#pragma resource "*.dfm"
TComputeForm *ComputeForm;
//---------------------------------------------------------------------------
__fastcall TComputeForm::TComputeForm(TComponent* Owner)
        : TForm(Owner)
{

}
//---------------------------------------------------------------------------

void __fastcall TComputeForm::MixBtnClick(TObject *Sender)
{
AnsiString Col1, Col2, Sup1, Sup2;
double Bet1, Bet2, Bet3;
TEdit *Edits[]={Edit1, Edit2, Edit3, Edit4, Edit5};
TShape *Shapes[]={Shape1, Shape2, Shape3, Shape4, Shape5};
int ValO1, ValO2, ValO3, ValT1, ValT2, ValT3,
    DecO1, DecO2, DecO3, DecT1, DecT2, DecT3,
    Less1, Less2, Less3, More1, More2, More3,
    Min1, Min2, Min3, Max1, Max2, Max3, Mean1, Mean2, Mean3,
    AlmMin1, AlmMin2, AlmMin3, AlmMax1, AlmMax2, AlmMax3,
    AlmLess1, AlmLess2, AlmLess3, AlmMore1, AlmMore2, AlmMore3;
Col1=FirstEdit->Text;
Col2=SecondEdit->Text;
//Преобразование в HEX формат
switch (CodeCmb->ItemIndex)
{
  case 0:
  {
    Col1=Col1.SubString(2, 6);
    Col2=Col2.SubString(2, 6);
  }
  break;
  case 1:
  {
    ValO1=StrToInt(Col1.SubString(1, Col1.AnsiPos(",")-1));
    Col1.Delete(1, Col1.AnsiPos(","));
    ValO2=StrToInt(Col1.SubString(1, Col1.AnsiPos(",")-1));
    Col1.Delete(1, Col1.AnsiPos(","));
    ValO3=StrToInt(Col1.SubString(1, Col1.Length()));

    ValT1=StrToInt(Col2.SubString(1, Col2.AnsiPos(",")-1));
    Col2.Delete(1, Col2.AnsiPos(","));
    ValT2=StrToInt(Col2.SubString(1, Col2.AnsiPos(",")-1));
    Col2.Delete(1, Col2.AnsiPos(","));
    ValT3=StrToInt(Col2.SubString(1, Col2.Length()));

    Col1=IntToHex(ValO1,2)+(String)IntToHex(ValO2,2)+(String)IntToHex(ValO3,2);
    Col2=IntToHex(ValT1,2)+(String)IntToHex(ValT2,2)+(String)IntToHex(ValT3,2);
  }
  break;
}
//Перевод из шестнадцатеричной системы в десятичную
DecO1=StrToInt("0x"+((String)Col1[1]+(String)Col1[2]));
DecO2=StrToInt("0x"+((String)Col1[3]+(String)Col1[4]));
DecO3=StrToInt("0x"+((String)Col1[5]+(String)Col1[6]));
DecT1=StrToInt("0x"+((String)Col2[1]+(String)Col2[2]));
DecT2=StrToInt("0x"+((String)Col2[3]+(String)Col2[4]));
DecT3=StrToInt("0x"+((String)Col2[5]+(String)Col2[6]));
//Сброс заданных параметров у объектов
for (int i=0; i<5; i++)
{
  Edits[i]->Text="";
  Edits[i]->Enabled=false;
  Shapes[i]->Brush->Color=clMenu;
  Shapes[i]->Pen->Color=clSilver;
}
//Рассчет промежуточных цветов в зависимости от выбранного значения
switch (AmountCmb->ItemIndex)
{
  case 0:
  {
    Min1=DecO1<DecT1? DecO1: DecT1;
    Min1+=GetRound(abs(DecO1-DecT1)/(double)2);

    Min2=DecO2<DecT2? DecO2: DecT2;
    Min2+=GetRound(abs(DecO2-DecT2)/(double)2);

    Min3=DecO3<DecT3? DecO3: DecT3;
    Min3+=GetRound(abs(DecO3-DecT3)/(double)2);

    Edit1->Enabled=true;

    switch (CodeCmb->ItemIndex)
    {
      case 0:
        Edit1->Text="#"+(String)IntToHex(Min1,2)+(String)IntToHex(Min2,2)+(String)IntToHex(Min3,2);
      break;
      case 1:
        Edit1->Text=(String)Min1+","+(String)Min2+","+(String)Min3;
      break;
    }

    Shape1->Brush->Color=StringToColor(GetHex((String)IntToHex(Min1,2)+
                         (String)IntToHex(Min2,2)+(String)IntToHex(Min3,2)));

    Shape1->Pen->Color=StringToColor(GetHex((String)IntToHex(abs(Min1-50),2)+
                       (String)IntToHex(abs(Min2-50),2)+(String)IntToHex(abs(Min3-50),2)));
  }
  break;
  case 1:
  {
    Min1=DecO1<DecT1? DecO1: DecT1;
    Max1=DecT1>DecO1? DecT1: DecO1;
    Bet1=GetRound(abs(DecO1-DecT1)/(double)3);
    Min1+=Bet1;
    Max1-=Bet1;

    Min2=DecO2<DecT2? DecO2: DecT2;
    Max2=DecT2>DecO2? DecT2: DecO2;
    Bet2=GetRound(abs(DecO2-DecT2)/(double)3);
    Min2+=Bet2;
    Max2-=Bet2;

    Min3=DecO3<DecT3? DecO3: DecT3;
    Max3=DecT3>DecO3? DecT3: DecO3;
    Bet3=GetRound(abs(DecO3-DecT3)/(double)3);
    Min3+=Bet3;
    Max3-=Bet3;

    Less1=DecO1<DecT1? Min1: Max1;
    Less2=DecO2<DecT2? Min2: Max2;
    Less3=DecO3<DecT3? Min3: Max3;
    More1=DecT1>DecO1? Max1: Min1;
    More2=DecT2>DecO2? Max2: Min2;
    More3=DecT3>DecO3? Max3: Min3;

    Edit1->Enabled=true;
    Edit2->Enabled=true;

    switch (CodeCmb->ItemIndex)
    {
      case 0:
      {
        Edit1->Text="#"+(String)IntToHex(Less1,2)+(String)IntToHex(Less2,2)+(String)IntToHex(Less3,2);
        Edit2->Text="#"+(String)IntToHex(More1,2)+(String)IntToHex(More2,2)+(String)IntToHex(More3,2);
      }
      break;
      case 1:
        Edit1->Text=(String)Less1+","+(String)Less2+","+(String)Less3;
        Edit2->Text=(String)More1+","+(String)More2+","+(String)More3;
      break;
    }

    Shape1->Brush->Color=StringToColor(GetHex((String)IntToHex(Less1,2)+
                         (String)IntToHex(Less2,2)+(String)IntToHex(Less3,2)));

    Shape2->Brush->Color=StringToColor(GetHex((String)IntToHex(More1,2)+
                         (String)IntToHex(More2,2)+(String)IntToHex(More3,2)));

    Shape1->Pen->Color=StringToColor(GetHex((String)IntToHex(abs(Less1-50),2)+
                       (String)IntToHex(abs(Less2-50),2)+(String)IntToHex(abs(Less3-50),2)));

    Shape2->Pen->Color=StringToColor(GetHex((String)IntToHex(abs(More1-50),2)+
                       (String)IntToHex(abs(More2-50),2)+(String)IntToHex(abs(More3-50),2)));
  }
  break;
  case 2:
  {
    Min1=DecO1<DecT1? DecO1: DecT1;
    Max1=DecT1>DecO1? DecT1: DecO1;
    Bet1=abs(DecO1-DecT1)/(double)4;
    Mean1=GetRound(Min1+Bet1*2);
    Min1+=GetRound(Bet1);
    Max1-=GetRound(Bet1);

    Min2=DecO2<DecT2? DecO2: DecT2;
    Max2=DecT2>DecO2? DecT2: DecO2;
    Bet2=abs(DecO2-DecT2)/(double)4;
    Mean2=GetRound(Min2+Bet2*2);
    Min2+=GetRound(Bet2);
    Max2-=GetRound(Bet2);

    Min3=DecO3<DecT3? DecO3: DecT3;
    Max3=DecT3>DecO3? DecT3: DecO3;
    Bet3=abs(DecO3-DecT3)/(double)4;
    Mean3=GetRound(Min3+Bet3*2);
    Min3+=GetRound(Bet3);
    Max3-=GetRound(Bet3);

    Less1=DecO1<DecT1? Min1: Max1;
    Less2=DecO2<DecT2? Min2: Max2;
    Less3=DecO3<DecT3? Min3: Max3;
    More1=DecT1>DecO1? Max1: Min1;
    More2=DecT2>DecO2? Max2: Min2;
    More3=DecT3>DecO3? Max3: Min3;

    Edit1->Enabled=true;
    Edit2->Enabled=true;
    Edit3->Enabled=true;

    switch (CodeCmb->ItemIndex)
    {
      case 0:
      {
        Edit1->Text="#"+(String)IntToHex(Less1,2)+(String)IntToHex(Less2,2)+(String)IntToHex(Less3,2);
        Edit2->Text="#"+(String)IntToHex(Mean1,2)+(String)IntToHex(Mean2,2)+(String)IntToHex(Mean3,2);
        Edit3->Text="#"+(String)IntToHex(More1,2)+(String)IntToHex(More2,2)+(String)IntToHex(More3,2);
      }
      break;
      case 1:
        Edit1->Text=(String)Less1+","+(String)Less2+","+(String)Less3;
        Edit2->Text=(String)Mean1+","+(String)Mean2+","+(String)Mean3;
        Edit3->Text=(String)More1+","+(String)More2+","+(String)More3;
      break;
    }

    Shape1->Brush->Color=StringToColor(GetHex((String)IntToHex(Less1,2)+
                         (String)IntToHex(Less2,2)+(String)IntToHex(Less3,2)));

    Shape2->Brush->Color=StringToColor(GetHex((String)IntToHex(Mean1,2)+
                         (String)IntToHex(Mean2,2)+(String)IntToHex(Mean3,2)));
                         
    Shape3->Brush->Color=StringToColor(GetHex((String)IntToHex(More1,2)+
                         (String)IntToHex(More2,2)+(String)IntToHex(More3,2)));

    Shape1->Pen->Color=StringToColor(GetHex((String)IntToHex(abs(Less1-50),2)+
    (String)IntToHex(abs(Less2-50),2)+(String)IntToHex(abs(Less3-50),2)));
    
    Shape2->Pen->Color=StringToColor(GetHex((String)IntToHex(abs(Mean1-50),2)+
    (String)IntToHex(abs(Mean2-50),2)+(String)IntToHex(abs(Mean3-50),2)));

    Shape3->Pen->Color=StringToColor(GetHex((String)IntToHex(abs(More1-50),2)+
    (String)IntToHex(abs(More2-50),2)+(String)IntToHex(abs(More3-50),2)));
  }
  break;
  case 3:
  {
    Min1=DecO1<DecT1? DecO1: DecT1;
    Max1=DecT1>DecO1? DecT1: DecO1;
    Bet1=abs(DecO1-DecT1)/(double)5;
    AlmMin1=GetRound(Min1+Bet1*2);
    AlmMax1=GetRound(Max1-Bet1*2);
    Min1+=GetRound(Bet1);
    Max1-=GetRound(Bet1);

    Min2=DecO2<DecT2? DecO2: DecT2;
    Max2=DecT2>DecO2? DecT2: DecO2;
    Bet2=abs(DecO2-DecT2)/(double)5;
    AlmMin2=GetRound(Min2+Bet2*2);
    AlmMax2=GetRound(Max2-Bet2*2);
    Min2+=GetRound(Bet2);
    Max2-=GetRound(Bet2);

    Min3=DecO3<DecT3? DecO3: DecT3;
    Max3=DecT3>DecO3? DecT3: DecO3;
    Bet3=abs(DecO3-DecT3)/(double)5;
    AlmMin3=GetRound(Min3+Bet3*2);
    AlmMax3=GetRound(Max3-Bet3*2);
    Min3+=GetRound(Bet3);
    Max3-=GetRound(Bet3);

    Less1=DecO1<DecT1? Min1: Max1;
    Less2=DecO2<DecT2? Min2: Max2;
    Less3=DecO3<DecT3? Min3: Max3;
    AlmLess1=DecO1<DecT1? AlmMin1: AlmMax1;
    AlmLess2=DecO2<DecT2? AlmMin2: AlmMax2;
    AlmLess3=DecO3<DecT3? AlmMin3: AlmMax3;
    AlmMore1=DecT1>DecO1? AlmMax1: AlmMin1;
    AlmMore2=DecT2>DecO2? AlmMax2: AlmMin2;
    AlmMore3=DecT3>DecO3? AlmMax3: AlmMin3;
    More1=DecT1>DecO1? Max1: Min1;
    More2=DecT2>DecO2? Max2: Min2;
    More3=DecT3>DecO3? Max3: Min3;

    Edit1->Enabled=true;
    Edit2->Enabled=true;
    Edit3->Enabled=true;
    Edit4->Enabled=true;

    switch (CodeCmb->ItemIndex)
    {
      case 0:
      {
        Edit1->Text="#"+(String)IntToHex(Less1,2)+(String)IntToHex(Less2,2)+(String)IntToHex(Less3,2);
        Edit2->Text="#"+(String)IntToHex(AlmLess1,2)+(String)IntToHex(AlmLess2,2)+(String)IntToHex(AlmLess3,2);
        Edit3->Text="#"+(String)IntToHex(AlmMore1,2)+(String)IntToHex(AlmMore2,2)+(String)IntToHex(AlmMore3,2);
        Edit4->Text="#"+(String)IntToHex(More1,2)+(String)IntToHex(More2,2)+(String)IntToHex(More3,2);
      }
      break;
      case 1:
        Edit1->Text=(String)Less1+","+(String)Less2+","+(String)Less3;
        Edit2->Text=(String)AlmLess1+","+(String)AlmLess2+","+(String)AlmLess3;
        Edit3->Text=(String)AlmMore1+","+(String)AlmMore2+","+(String)AlmMore3;
        Edit4->Text=(String)More1+","+(String)More2+","+(String)More3;
      break;
    }

    Shape1->Brush->Color=StringToColor(GetHex((String)IntToHex(Less1,2)+
                         (String)IntToHex(Less2,2)+(String)IntToHex(Less3,2)));

    Shape2->Brush->Color=StringToColor(GetHex((String)IntToHex(AlmLess1,2)+
                         (String)IntToHex(AlmLess2,2)+(String)IntToHex(AlmLess3,2)));

    Shape3->Brush->Color=StringToColor(GetHex((String)IntToHex(AlmMore1,2)+
                         (String)IntToHex(AlmMore2,2)+(String)IntToHex(AlmMore3,2)));

    Shape4->Brush->Color=StringToColor(GetHex((String)IntToHex(More1,2)+
                         (String)IntToHex(More2,2)+(String)IntToHex(More3,2)));

    Shape1->Pen->Color=StringToColor(GetHex((String)IntToHex(abs(Less1-50),2)+
    (String)IntToHex(abs(Less2-50),2)+(String)IntToHex(abs(Less3-50),2)));

    Shape2->Pen->Color=StringToColor(GetHex((String)IntToHex(abs(AlmLess1-50),2)+
    (String)IntToHex(abs(AlmLess2-50),2)+(String)IntToHex(abs(AlmLess3-50),2)));

    Shape3->Pen->Color=StringToColor(GetHex((String)IntToHex(abs(AlmMore1-50),2)+
    (String)IntToHex(abs(AlmMore2-50),2)+(String)IntToHex(abs(AlmMore3-50),2)));
    
    Shape4->Pen->Color=StringToColor(GetHex((String)IntToHex(abs(More1-50),2)+
    (String)IntToHex(abs(More2-50),2)+(String)IntToHex(abs(More3-50),2)));
  }
  break;
  case 4:
  {
    Min1=DecO1<DecT1? DecO1: DecT1;
    Max1=DecT1>DecO1? DecT1: DecO1;
    Bet1=abs(DecO1-DecT1)/(double)6;
    AlmMin1=GetRound(Min1+Bet1*2);
    Mean1=GetRound(Min1+Bet1*3);
    AlmMax1=GetRound(Max1-Bet1*2);
    Min1+=GetRound(Bet1);
    Max1-=GetRound(Bet1);

    Min2=DecO2<DecT2? DecO2: DecT2;
    Max2=DecT2>DecO2? DecT2: DecO2;
    Bet2=abs(DecO2-DecT2)/(double)6;
    AlmMin2=GetRound(Min2+Bet2*2);
    Mean2=GetRound(Min2+Bet2*3);
    AlmMax2=GetRound(Max2-Bet2*2);
    Min2+=GetRound(Bet2);
    Max2-=GetRound(Bet2);

    Min3=DecO3<DecT3? DecO3: DecT3;
    Max3=DecT3>DecO3? DecT3: DecO3;
    Bet3=abs(DecO3-DecT3)/(double)6;
    AlmMin3=GetRound(Min3+Bet3*2);
    Mean3=GetRound(Min3+Bet3*3);
    AlmMax3=GetRound(Max3-Bet3*2);
    Min3+=GetRound(Bet3);
    Max3-=GetRound(Bet3);

    Less1=DecO1<DecT1? Min1: Max1;
    Less2=DecO2<DecT2? Min2: Max2;
    Less3=DecO3<DecT3? Min3: Max3;
    AlmLess1=DecO1<DecT1? AlmMin1: AlmMax1;
    AlmLess2=DecO2<DecT2? AlmMin2: AlmMax2;
    AlmLess3=DecO3<DecT3? AlmMin3: AlmMax3;
    AlmMore1=DecT1>DecO1? AlmMax1: AlmMin1;
    AlmMore2=DecT2>DecO2? AlmMax2: AlmMin2;
    AlmMore3=DecT3>DecO3? AlmMax3: AlmMin3;
    More1=DecT1>DecO1? Max1: Min1;
    More2=DecT2>DecO2? Max2: Min2;
    More3=DecT3>DecO3? Max3: Min3;

    Edit1->Enabled=true;
    Edit2->Enabled=true;
    Edit3->Enabled=true;
    Edit4->Enabled=true;
    Edit5->Enabled=true;

    switch (CodeCmb->ItemIndex)
    {
      case 0:
      {
        Edit1->Text="#"+(String)IntToHex(Less1,2)+(String)IntToHex(Less2,2)+(String)IntToHex(Less3,2);
        Edit2->Text="#"+(String)IntToHex(AlmLess1,2)+(String)IntToHex(AlmLess2,2)+(String)IntToHex(AlmLess3,2);
        Edit3->Text="#"+(String)IntToHex(Mean1,2)+(String)IntToHex(Mean2,2)+(String)IntToHex(Mean3,2);
        Edit4->Text="#"+(String)IntToHex(AlmMore1,2)+(String)IntToHex(AlmMore2,2)+(String)IntToHex(AlmMore3,2);
        Edit5->Text="#"+(String)IntToHex(More1,2)+(String)IntToHex(More2,2)+(String)IntToHex(More3,2);
      }
      break;
      case 1:
        Edit1->Text=(String)Less1+","+(String)Less2+","+(String)Less3;
        Edit2->Text=(String)AlmLess1+","+(String)AlmLess2+","+(String)AlmLess3;
        Edit3->Text=(String)Mean1+","+(String)Mean2+","+(String)Mean3;
        Edit4->Text=(String)AlmMore1+","+(String)AlmMore2+","+(String)AlmMore3;
        Edit5->Text=(String)More1+","+(String)More2+","+(String)More3;
      break;
    }

    Shape1->Brush->Color=StringToColor(GetHex((String)IntToHex(Less1,2)+
                         (String)IntToHex(Less2,2)+(String)IntToHex(Less3,2)));

    Shape2->Brush->Color=StringToColor(GetHex((String)IntToHex(AlmLess1,2)+
                         (String)IntToHex(AlmLess2,2)+(String)IntToHex(AlmLess3,2)));

    Shape3->Brush->Color=StringToColor(GetHex((String)IntToHex(Mean1,2)+
                         (String)IntToHex(Mean2,2)+(String)IntToHex(Mean3,2)));

    Shape4->Brush->Color=StringToColor(GetHex((String)IntToHex(AlmMore1,2)+
                         (String)IntToHex(AlmMore2,2)+(String)IntToHex(AlmMore3,2)));

    Shape5->Brush->Color=StringToColor(GetHex((String)IntToHex(More1,2)+
                         (String)IntToHex(More2,2)+(String)IntToHex(More3,2)));

    Shape1->Pen->Color=StringToColor(GetHex((String)IntToHex(abs(Less1-50),2)+
    (String)IntToHex(abs(Less2-50),2)+(String)IntToHex(abs(Less3-50),2)));

    Shape2->Pen->Color=StringToColor(GetHex((String)IntToHex(abs(AlmLess1-50),2)+
    (String)IntToHex(abs(AlmLess2-50),2)+(String)IntToHex(abs(AlmLess3-50),2)));

    Shape3->Pen->Color=StringToColor(GetHex((String)IntToHex(abs(Mean1-50),2)+
    (String)IntToHex(abs(Mean2-50),2)+(String)IntToHex(abs(Mean3-50),2)));

    Shape4->Pen->Color=StringToColor(GetHex((String)IntToHex(abs(AlmMore1-50),2)+
    (String)IntToHex(abs(AlmMore2-50),2)+(String)IntToHex(abs(AlmMore3-50),2)));

    Shape5->Pen->Color=StringToColor(GetHex((String)IntToHex(abs(More1-50),2)+
    (String)IntToHex(abs(More2-50),2)+(String)IntToHex(abs(More3-50),2)));
  }
  break;
}
}
//---------------------------------------------------------------------------

void __fastcall TComputeForm::CodeCmbChange(TObject *Sender)
{
static int selEl, prevEl;
int ValO1, ValO2, ValO3, ValT1, ValT2, ValT3;
AnsiString Col1, Col2, Sup1, Sup2;
Col1=FirstEdit->Text;
Col2=SecondEdit->Text;
selEl=CodeCmb->ItemIndex;
//Преобразование первого поля
if (FirstEdit->Text.Length()>1)
{
  //Выполнение действий с цветом в зависимости от выбранной ранее модели
  switch (prevEl)
  {
    case 0:
      Sup1=Col1.SubString(2,7);
    break;
    case 1:
    {
      ValO1=StrToInt(Col1.SubString(1, Col1.AnsiPos(",")-1));
      Col1.Delete(1, Col1.AnsiPos(","));
      ValO2=StrToInt(Col1.SubString(1, Col1.AnsiPos(",")-1));
      Col1.Delete(1, Col1.AnsiPos(","));
      ValO3=StrToInt(Col1.SubString(1, Col1.Length()));

      Sup1=IntToHex(ValO1,2)+(String)IntToHex(ValO2,2)+(String)IntToHex(ValO3,2);
    }
    break;
  }
  //Перевод из шестнадцатеричной системы в десятичную
  ValO1=StrToInt("0x"+Sup1.SubString(1, 2));
  ValO2=StrToInt("0x"+Sup1.SubString(3, 2));
  ValO3=StrToInt("0x"+Sup1.SubString(5, 2));
  //Выполнение действий с цветом в зависимости от выбранной сейчас модели
  switch (selEl)
  {
    case 0:
      FirstEdit->Text=(String)"#"+Sup1;
    break;
    case 1:
      FirstEdit->Text=(String)ValO1+(String)","+ValO2+(String)","+ValO3;
    break;
  }
}
else
  FirstEdit->Clear();

//Преобразование второго поля
if (SecondEdit->Text.Length()>1)
{
  //Выполнение действий с цветом в зависимости от выбранной ранее модели
  switch (prevEl)
  {
    case 0:
      Sup2=Col2.SubString(2,7);
    break;
    case 1:
    {
      ValT1=StrToInt(Col2.SubString(1, Col2.AnsiPos(",")-1));
      Col2.Delete(1, Col2.AnsiPos(","));
      ValT2=StrToInt(Col2.SubString(1, Col2.AnsiPos(",")-1));
      Col2.Delete(1, Col2.AnsiPos(","));
      ValT3=StrToInt(Col2.SubString(1, Col2.Length()));

      Sup2=IntToHex(ValT1,2)+(String)IntToHex(ValT2,2)+(String)IntToHex(ValT3,2);
    }
    break;
  }
  //Перевод из шестнадцатеричной системы в десятичную
  ValT1=StrToInt("0x"+Sup2.SubString(1, 2));
  ValT2=StrToInt("0x"+Sup2.SubString(3, 2));
  ValT3=StrToInt("0x"+Sup2.SubString(5, 2));
  //Выполнение действий с цветом в зависимости от выбранной сейчас модели
  switch (selEl)
  {
    case 0:
      SecondEdit->Text=(String)"#"+Sup2;
    break;
    case 1:
      SecondEdit->Text=(String)ValT1+(String)","+ValT2+(String)","+ValT3;
    break;
  }
}
else
  SecondEdit->Clear();
prevEl=selEl;
}
//---------------------------------------------------------------------------

void __fastcall TComputeForm::FirstEditChange(TObject *Sender)
{
int numSign;
switch (CodeCmb->ItemIndex)
{
  case 0:
    if (FirstEdit->Text.IsEmpty()==false && FirstEdit->Text[1]=='#')
      numSign=2;
    else
      numSign=1;
  break;
  case 1:
    if (FirstEdit->Text.IsEmpty()==false)
      numSign=1;
  break;
}
if (FirstEdit->Text.IsEmpty()==true || FirstEdit->Text.Length()==1 && FirstEdit->Text.AnsiPos("#")==1)
{
  FirstShape->Brush->Color=clMenu;
  FirstShape->Pen->Color=clSilver;
}
if (FirstEdit->Text.Length()>=numSign && SecondEdit->Text.Length()>=numSign)
  MixBtn->Enabled=true;
else
  MixBtn->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TComputeForm::SecondEditChange(TObject *Sender)
{
int numSign;
switch (CodeCmb->ItemIndex)
{
  case 0:
    if (SecondEdit->Text.IsEmpty()==false && SecondEdit->Text[1]=='#')
      numSign=2;
    else
      numSign=1;
  break;
  case 1:
    if (FirstEdit->Text.IsEmpty()==false)
      numSign=1;
  break;
}
if (SecondEdit->Text.IsEmpty()==true || SecondEdit->Text.Length()==1 && SecondEdit->Text.AnsiPos("#")==1)
{
  SecondShape->Brush->Color=clMenu;
  SecondShape->Pen->Color=clSilver;
}
if (FirstEdit->Text.Length()>=numSign && SecondEdit->Text.Length()>=numSign)
  MixBtn->Enabled=true;
else
  MixBtn->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TComputeForm::FirstEditExit(TObject *Sender)
{
AnsiString ColRgb, Col=GetAdd(FirstEdit->Text);
switch (CodeCmb->ItemIndex)
{
  case 0:
    if (Col.IsEmpty()==false)
    {
      FirstEdit->Text="#"+Col;
      FirstShape->Brush->Color=StringToColor(GetHex(Col));
      FirstShape->Pen->Color=StringToColor(GetPen(Col));
    }
  break;
  case 1:
    if (Col.IsEmpty()==false)
    {
      FirstEdit->Text=Col;
      ColRgb+=IntToHex(StrToInt(Col.SubString(1, Col.AnsiPos(",")-1)), 2);
      Col.Delete(1, Col.AnsiPos(","));
      ColRgb+=IntToHex(StrToInt(Col.SubString(1, Col.AnsiPos(",")-1)), 2);
      Col.Delete(1, Col.AnsiPos(","));
      ColRgb+=IntToHex(StrToInt(Col.SubString(1, Col.Length())), 2);
      FirstShape->Brush->Color=StringToColor(GetHex(ColRgb));
      FirstShape->Pen->Color=StringToColor(GetPen(ColRgb));
    }
    else
      FirstEdit->Clear();
  break;
}
}
//---------------------------------------------------------------------------

void __fastcall TComputeForm::SecondEditExit(TObject *Sender)
{
AnsiString ColRgb, Col=GetAdd(SecondEdit->Text);
switch (CodeCmb->ItemIndex)
{
  case 0:
    if (Col.IsEmpty()==false)
    {
      SecondEdit->Text="#"+Col;
      SecondShape->Brush->Color=StringToColor(GetHex(Col));
      SecondShape->Pen->Color=StringToColor(GetPen(Col));
    }
  break;
  case 1:
    if (Col.IsEmpty()==false)
    {
      SecondEdit->Text=Col;
      ColRgb+=IntToHex(StrToInt(Col.SubString(1, Col.AnsiPos(",")-1)), 2);
      Col.Delete(1, Col.AnsiPos(","));
      ColRgb+=IntToHex(StrToInt(Col.SubString(1, Col.AnsiPos(",")-1)), 2);
      Col.Delete(1, Col.AnsiPos(","));
      ColRgb+=IntToHex(StrToInt(Col.SubString(1, Col.Length())), 2);
      SecondShape->Brush->Color=StringToColor(GetHex(ColRgb));
      SecondShape->Pen->Color=StringToColor(GetPen(ColRgb));
    }
    else
      SecondEdit->Clear();
  break;
}
}
//---------------------------------------------------------------------------

void __fastcall TComputeForm::FirstShapeMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
AnsiString ColRgb;
if (Button==mbLeft)
  CopyColor(FirstShape);
if (Shift.Contains(ssDouble) && Button==mbLeft)
  if (ColorDialog->Execute())
    switch (CodeCmb->ItemIndex)
    {
      case 0:
      {
        FirstEdit->Text=GetHex(IntToHex(ColorDialog->Color, 6)).Delete(1, 2);
        FirstShape->Brush->Color=ColorDialog->Color;
        FirstShape->Pen->Color=StringToColor(GetPen(FirstEdit->Text));
        FirstEdit->Text="#"+FirstEdit->Text;
      }
      break;
      case 1:
      {
        ColRgb=GetHex(IntToHex(ColorDialog->Color, 6)).Delete(1, 2);
        FirstShape->Brush->Color=ColorDialog->Color;
        FirstShape->Pen->Color=StringToColor(GetPen(ColRgb));
        FirstEdit->Text=(String)StrToInt("0x"+ColRgb.SubString(1, 2))+","+
                        (String)StrToInt("0x"+ColRgb.SubString(3, 2))+","+
                        (String)StrToInt("0x"+ColRgb.SubString(5, 2));
      }
      break;
    }
}
//---------------------------------------------------------------------------

void __fastcall TComputeForm::SecondShapeMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
AnsiString ColRgb;
if (Button==mbLeft)
  CopyColor(SecondShape);
if (Shift.Contains(ssDouble) && Button==mbLeft)
  if (ColorDialog->Execute())
    switch (CodeCmb->ItemIndex)
    {
      case 0:
      {
        SecondEdit->Text=GetHex(IntToHex(ColorDialog->Color, 6)).Delete(1, 2);
        SecondShape->Brush->Color=ColorDialog->Color;
        SecondShape->Pen->Color=StringToColor(GetPen(SecondEdit->Text));
        SecondEdit->Text="#"+SecondEdit->Text;
      }
      break;
      case 1:
      {
        ColRgb=GetHex(IntToHex(ColorDialog->Color, 6)).Delete(1, 2);
        SecondShape->Brush->Color=ColorDialog->Color;
        SecondShape->Pen->Color=StringToColor(GetPen(ColRgb));
        SecondEdit->Text=(String)StrToInt("0x"+ColRgb.SubString(1, 2))+","+
                         (String)StrToInt("0x"+ColRgb.SubString(3, 2))+","+
                         (String)StrToInt("0x"+ColRgb.SubString(5, 2));
      }
      break;
    }
}
//---------------------------------------------------------------------------

void __fastcall TComputeForm::Shape1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if (Button==mbLeft)
  CopyColor(Shape1);
}
//---------------------------------------------------------------------------

void __fastcall TComputeForm::Shape2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if (Button==mbLeft)
  CopyColor(Shape2);
}
//---------------------------------------------------------------------------

void __fastcall TComputeForm::Shape3MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if (Button==mbLeft)
  CopyColor(Shape3);
}
//---------------------------------------------------------------------------

void __fastcall TComputeForm::Shape4MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if (Button==mbLeft)
  CopyColor(Shape4);
}
//---------------------------------------------------------------------------

void __fastcall TComputeForm::Shape5MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if (Button==mbLeft)
  CopyColor(Shape5);
}
//---------------------------------------------------------------------------

int TComputeForm::GetRound(double Round)
{
return Round+=0.5;
}
//---------------------------------------------------------------------------

AnsiString TComputeForm::GetHex(AnsiString Hex)
{
return Hex="0x"+(String)Hex[5] + (String)Hex[6] + (String)Hex[3] +
                (String)Hex[4] + (String)Hex[1] + (String)Hex[2];
}
//---------------------------------------------------------------------------

AnsiString TComputeForm::GetPen(AnsiString Row)
{
int Dec1, Dec2, Dec3;
Dec1=StrToInt("0x"+((String)Row[5]+(String)Row[6]));
Dec2=StrToInt("0x"+((String)Row[3]+(String)Row[4]));
Dec3=StrToInt("0x"+((String)Row[1]+(String)Row[2]));
return Row="0x"+(String)IntToHex(abs(Dec1-50),2)+
                (String)IntToHex(abs(Dec2-50),2)+(String)IntToHex(abs(Dec3-50),2);
}
//---------------------------------------------------------------------------

void TComputeForm::CopyColor(TShape *NameOfShape)
{
int Dec1, Dec2, Dec3;
AnsiString Col=NameOfShape->Brush->Color;
Col=GetHex(IntToHex(Col.ToInt(), 6)).Delete(1, 2);
Clipboard()->Open();
Clipboard()->Clear();
switch (CodeCmb->ItemIndex)
{
  case 0:
    Clipboard()->AsText="#"+Col;
  break;
  case 1:
  {
    Dec1=StrToInt("0x"+((String)Col[1]+(String)Col[2]));
    Dec2=StrToInt("0x"+((String)Col[3]+(String)Col[4]));
    Dec3=StrToInt("0x"+((String)Col[5]+(String)Col[6]));

    Clipboard()->AsText=(String)Dec1+","+(String)Dec2+","+(String)Dec3;
  }
  break;
}
Clipboard()->Close();
}
//---------------------------------------------------------------------------

AnsiString TComputeForm::GetAdd(AnsiString Line)
{
int i;
while (Line.AnsiPos(" ")!=0)
  Line.Delete(Line.AnsiPos(" "), 1);
switch (CodeCmb->ItemIndex)
{
  case 0:
  {
    if (Line.IsEmpty()==false && Line[1]=='#')
      Line.Delete(1, 1);
    if (Line.Length()>6)
      Line.SetLength(6);
    for (i=1; i<=Line.Length(); i++)
      if (!(Line[i]>='0' && Line[i]<='9' || Line[i]>='A' && Line[i]<='F'))
        Line[i]='0';
    switch (Line.Length())
    {
      case 1:
      {
        for (i=1; i<=5; i++)
          Line+=Line[i];
      }
      break;
      case 2:
      {
        for (i=2; i<=5; i++)
          Line+=Line[i-1];
      }
      break;
      case 3: Line=(String)Line[1]+(String)Line[1]+(String)Line[2]+(String)Line[2]+
                   (String)Line[3]+(String)Line[3];
      break;
      case 4: Line+=(String)Line[3]+(String)Line[4];
      break;
      case 5: Line+=Line[5];
      break;
    }
  }
  break;
  case 1:
  {
    if (Line.IsEmpty()==false)
    {
      int a=0, b=0, c=0, k=0;
      if (Line.AnsiPos(",")==1)
        Line.Insert("0", 1);
      while (Line.AnsiPos(",,")!=0)
        Line.Delete(Line.AnsiPos(",,"), 1);
      for (i=1; i<=Line.Length(); i++)
        if (!(Line[i]>='0' && Line[i]<='9' || Line[i]==','))
          Line[i]='0';
      for (i=1; i<=Line.Length(); i++)
        if (Line[i]==',')
        {
          k++;
          if (k==1)
            a=i;
          if (k==2)
            b=i;
          if (k==3)
            c=i;
        }
      switch (k)
      {
        case 0:
        {
          if (Line.Length()>9)
            Line.SetLength(9);
          switch (Line.Length())
          {
            case 1: Line+=",0,0";
            break;
            case 2:
            {
              Line.Insert(",", 2);
              Line+=",0";
            }
            break;
            case 3:
            {
              Line.Insert(",", 2);
              Line.Insert(",", 4);
            }
            break;
            case 4:
            {
              Line.Insert(",", 3);
              Line.Insert(",", 5);
            }
            break;
            case 5:
            {
              Line.Insert(",", 4);
              Line.Insert(",", 6);
            }
            break;
            case 6:
            {
              Line.Insert(",", 4);
              Line.Insert(",", 7);
            }
            break;
            case 7:
            {
              Line.Insert(",", 4);
              Line.Insert(",", 8);
            }
            break;
            case 8:
            {
              Line.Insert(",", 4);
              Line.Insert(",", 8);
            }
            break;
            case 9:
            {
              Line.Insert(",", 4);
              Line.Insert(",", 8);
            }
            break;
          }
        }
        break;
        case 1:
        {
          if (Line.Length()-Line.AnsiPos(",")==0)
            Line=(String)Line.SubString(1, a-1).ToInt()+",";
          else
            Line=(String)Line.SubString(1, a-1).ToInt()+","+
                 (String)Line.SubString(a+1, Line.Length()-a).ToInt();
          a=Line.AnsiPos(",");
          if (a-1>=Line.Length()-a)
          {
            if (Line.Length()-a>3)
              Line.Delete(a+4, Line.Length()-(a+3));
            if (a>7)
            {
              Line.Delete(7, a-7);
              Line.Insert(",", 4);
              b=8;
              a=4;
            }
            else
              if (a>4)
              {
                Line.Insert(",", 4);
                b=a+1;
                a=4;
              }
          }
          else
          {
            if (a>4)
            {
              Line.Delete(4, a-4);
              a=4;
            }
            if (Line.Length()-a>3)
            {
              b=a+4;
              Line.Insert(",", b);
              if (Line.Length()-b>3)
                Line.Delete(b+4, Line.Length()-(b+3));
            }
          }
          if (Line.Length()-a==0)
          {
            Line+="0,0";
            b=a+2;
          }
          if (a>b && Line.Length()-a<4)
            Line+=",0";          
          if (Line.Length()-b==0)
            Line+="0";
        }
        break;
        case 2:
        {
          if (Line.Length()-b==0)
            Line=(String)Line.SubString(1, a-1).ToInt()+","+
                 (String)Line.SubString(a+1, b-a-1).ToInt()+",";
          else
            Line=(String)Line.SubString(1, a-1).ToInt()+","+
                 (String)Line.SubString(a+1, b-a-1).ToInt()+","+
                 (String)Line.SubString(b+1, Line.Length()-b).ToInt();
          a=Line.AnsiPos(",");
          for (i=Line.Length(); i>=1; i--)
            if (Line[i]==',')
            {
              b=i;
              break;
            }
          if (a>4)
          {
            Line.Delete(4, a-4);
            b-=a-4;
            a=4;
          }
          if (b-a>4)
          {
            Line.Delete(a+4, b-a-4);
            b=8;
          }
          if (Line.Length()-b>3)
            Line.Delete(b+4, Line.Length()-(b+3));
          if (Line.Length()-b==0)
            Line+="0";
        }
        break;
        default: Line.Delete(c, Line.Length()-c+1);
        break;
      }
      a=Line.AnsiPos(",");
      for (i=Line.Length(); i>=1; i--)
        if (Line[i]==',')
        {
          b=i;
          break;
        }
      if (Line.SubString(1, a-1).ToInt()>255)
      {
        Line.Delete(1, a-1);
        Line.Insert("255", 1);
        a=4;
      }
      if (Line.SubString(a+1, b-a-1).ToInt()>255)
      {
        Line.Delete(a+1, b-a-1);
        Line.Insert("255", a+1);
        b=8;
      }
      if (Line.SubString(b+1, Line.Length()-b).ToInt()>255)
      {
        Line.Delete(b+1, Line.Length());
        Line.Insert("255", b+1);
      }
    }
  }
  break;
}
return Line;
}
//---------------------------------------------------------------------------
