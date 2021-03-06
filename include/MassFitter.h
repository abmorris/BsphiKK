#pragma once
// Standard C++ headers
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
// RooFit headers
#include "RooAbsPdf.h"
#include "RooAbsReal.h"
#include "RooArgSet.h"
#include "RooDataSet.h"
#include "RooFitResult.h"
#include "RooPlot.h"
#include "RooRealVar.h"
#include "RooThreeBodyPhaseSpace.h"
// RooStats headers
#include "RooStats/SPlot.h"
using namespace std;
using namespace RooFit;
using namespace RooStats;
class Component
{
  public:
    // *structors
    Component(string,RooAbsPdf*);
    ~Component();
    // Functions for interaction
    void        Rename(RooAbsReal*);
    RooAbsReal* GetThing(string);
    RooArgSet*  GetParameters(RooAbsData* set) { return _pdf->getParameters(set); }
    void        AddThing(RooAbsReal*);
    RooAbsPdf*  GetPDF()                       { return _pdf     ; }
    void        SetPDF(RooAbsPdf* pdf)         { _pdf = pdf      ; }
    string      GetName()                      { return _name    ; }
    void        SetName(string name)           { _name = name    ; }
    RooAbsReal* GetYieldVar();
    void        SetYieldVar(RooAbsReal*);
    int         GetStyle()                     { return _style   ; }
    void        SetStyle(int style)            { _style = style  ; }
    int         GetColour()                    { return _colour  ; }
    void        SetColour(int colour)          { _colour = colour; }
    void        FixShapeTo(RooDataSet* data);
    void        FixShapeTo(const Component&);
    // Parameter values
    double      GetValue(string name) { return (double)((RooRealVar*)GetThing(name))->getVal(); }
    void        SetValue(string, double);
    void        FixValue(string, double);
    void        FloatPar(string name) { ((RooRealVar*)GetThing(name))->setConstant(false); }
    void        SetError(string, double);
    double      GetError(string name) { return (double)((RooRealVar*)GetThing(name))->getError(); }
    void        SetRange(string, double, double);
  protected:
    // Pointers to components and parameters
    vector<RooAbsReal*> _stuff;
    // Unique name
    string _name;
    // Pointer to the yield
    RooAbsReal* _yield;
    // Pointer to the PDF
    RooAbsPdf* _pdf;
    // Line style and colour
    int _style;
    int _colour;
    // Flags
    bool _hasyieldvar;
};
struct parameter
{
  parameter(string _n, string _l, Component* _c) : name(_c->GetName()+_n), latex(_l)
  {
    value = _c->GetValue(_n);
    error = _c->GetError(_n);
  }
  string name;
  string latex;
  double value;
  double error;
  string safename()
  {
    string temp = name;
    replace(temp.begin(),temp.end(),'1','A'); // Numbers can't go in LaTeX macros
    replace(temp.begin(),temp.end(),'2','B');
    replace(temp.begin(),temp.end(),'3','C');
    return temp;
  }
};
class MassFitter
{
  public:
    // *structors
    MassFitter(RooRealVar*);
    MassFitter(const MassFitter&);
    ~MassFitter();
    // Fit model and dataset
    Component*          GetComponent(string);
    Component*          AddComponent(string,string);
    Component*          AddComponent(string,string,RooAbsReal*);
    Component*          AddComponent(string,RooAbsPdf*);
    Component*          AddComponent(string,RooAbsPdf*,RooAbsReal*);
    RooDataSet*         GetData() { return _data; }
    void                SetData(RooDataSet*);
    // Command functions
    RooFitResult*       Fit();
    RooFitResult*       Fit(RooDataSet*);
    RooFitResult*       ConstrainedFit(RooDataSet*, RooRealVar*, RooAbsReal&, RooAbsReal&);
    RooFitResult*       ConstrainedFit(RooRealVar*, RooAbsReal&, RooAbsReal&);
    void                Plot(RooPlot*);
    SPlot*              GetsPlot(RooRealVar*,RooRealVar*);
    SPlot*              GetsPlot(RooArgList);
    void                SetWeighted();
    void                SetWeightFunction(string);
    void                SetWeightFunction(RooFormulaVar*);
  private:
    vector<Component*>  _components;
    Component*          makeshape(string,string);
    RooAbsPdf*          _pdf;
    RooFormulaVar*      _weightfunction;
    RooDataSet*         _data;
    RooRealVar*         _mass;
    void                init();
    void                assemble();
    // Flags
    bool                _haspdf;
    bool                _hasweightfunction;
    bool                _hasdata;
    bool                _useyieldvars;
    bool                _weighted;
    // Signal models
    Component*          BifurcatedGaussian(string);
    Component*          singleGaussian(string);
    Component*          doubleGaussian(string);
    Component*          tripleGaussian(string);
    Component*          CrystalBall(string);
    Component*          CrystalBall1Gauss(string);
    Component*          CrystalBall2Gauss(string);
    Component*          BreitWigner(string);
    Component*          RelBreitWigner(string);
    Component*          Voigtian(string);
    Component*          BWxGauss(string);
    Component*          RBWxGauss(string);
    Component*          Flatte(string);
    Component*          ThresholdShape(string);
    // Background models
    Component*          Argus(string);
    Component*          flatfunction(string);
    Component*          exponential(string);
    Component*          straightline(string);
    // Other models
    Component*          ThreeBodyPhaseSpace(string);
};
