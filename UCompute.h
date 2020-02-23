//---------------------------------------------------------------------------

#ifndef UComputeH
#define UComputeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Mask.hpp>
#include "CSPIN.h"
#include <ExtCtrls.hpp>
#include "CGRID.h"
#include <Dialogs.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TComputeForm : public TForm
{
__published:	// IDE-managed Components
        TColorDialog *ColorDialog;
        TPanel *InputPanel;
        TLabel *CodeLbl;
        TLabel *AmountLbl;
        TLabel *SecondLbl;
        TLabel *FirstLbl;
        TEdit *SecondEdit;
        TEdit *FirstEdit;
        TComboBox *CodeCmb;
        TComboBox *AmountCmb;
        TButton *MixBtn;
        TPanel *OutPanel;
        TEdit *Edit1;
        TEdit *Edit2;
        TEdit *Edit3;
        TEdit *Edit4;
        TEdit *Edit5;
        TShape *FirstShape;
        TShape *SecondShape;
        TShape *Shape1;
        TShape *Shape2;
        TShape *Shape3;
        TShape *Shape4;
        TShape *Shape5;
        void __fastcall MixBtnClick(TObject *Sender);
        void __fastcall FirstEditChange(TObject *Sender);
        void __fastcall SecondEditChange(TObject *Sender);
        void __fastcall FirstEditExit(TObject *Sender);
        void __fastcall SecondEditExit(TObject *Sender);
        void __fastcall FirstShapeMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall SecondShapeMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Shape1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Shape2MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Shape3MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Shape4MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Shape5MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall CodeCmbChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
int TComputeForm::GetRound(double Round);
void TComputeForm::CopyColor(TShape *NameOfShape);
AnsiString TComputeForm::GetHex(AnsiString Hex);
AnsiString TComputeForm::GetPen(AnsiString Row);
AnsiString TComputeForm::GetAdd(AnsiString Line);
        __fastcall TComputeForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TComputeForm *ComputeForm;
//---------------------------------------------------------------------------
#endif
