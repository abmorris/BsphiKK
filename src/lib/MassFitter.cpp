// Standard headers
#include <stdexcept>
// ROOT headers
#include "TCanvas.h"
// RooFit headers
#include "RooAddPdf.h"
#include "RooEffProd.h"
#include "RooFormulaVar.h"
#include "RooProdPdf.h"
#include "RooRealVar.h"
// RooFit PDFs
#include "RooArgusBG.h"
#include "RooBifurGauss.h"
#include "RooBreitWigner.h"
#include "RooCBShape.h"
#include "RooDstD0BG.h"
#include "RooExponential.h"
#include "RooFlatte.h"
#include "RooFFTConvPdf.h"
#include "RooGaussian.h"
#include "RooPolynomial.h"
#include "RooRelBreitWigner.h"
#include "RooUniform.h"
#include "RooVoigtian.h"
// Custom headers
#include "MassFitter.h"
using namespace std;
using namespace RooFit;
/******************************************************************************/
Component::Component(string name, RooAbsPdf* pdf) :
  _name(name)
, _pdf(pdf)
, _style(kDashed)
, _colour(kBlack)
, _hasyieldvar(false)
{
  Rename(_pdf);
}
/******************************************************************************/
Component::~Component()
{
  for(auto thing : _stuff)
    delete thing;
//  delete _yield; // Probably don't want to do this
  delete _pdf;
}
/******************************************************************************/
void Component::AddThing(RooAbsReal* thing)
{
  Rename(thing);
  _stuff.push_back(thing);
}
/******************************************************************************/
void Component::Rename(RooAbsReal* thing)
{
  thing->SetName((_name+thing->GetName()).c_str());
}
/******************************************************************************/
RooAbsReal* Component::GetYieldVar()
{
  if(!_hasyieldvar)
  {
    _yield = new RooRealVar((_name+"N").c_str(),("Auto-generated yield for component "+_name).c_str(),1,0,1e6);
    _hasyieldvar = true;
  }
  return _yield;
}
/******************************************************************************/
void Component::SetYieldVar(RooAbsReal* yield)
{
  _yield = yield;
  Rename(_yield);
  _hasyieldvar = true;
}
/******************************************************************************/
RooAbsReal* Component::GetThing(string name)
{
  for(auto thing : _stuff)
    if((string)thing->GetName() == _name+name)
      return thing;
  if((string)_pdf->GetName() == _name+name)
    return _pdf;
  if(_hasyieldvar)
    if((string)_yield->GetName() == _name+name)
      return _yield;
  throw invalid_argument(("No such parameter: "+name).c_str());
}
/******************************************************************************/
void Component::SetValue(string name, double value)
{
  RooRealVar* thing = (RooRealVar*)GetThing(name);
  thing->setVal(value);
  cout << "Setting " << name << " to " << value << endl;
}
/******************************************************************************/
void Component::SetError(string name, double value)
{
  RooRealVar* thing = (RooRealVar*)GetThing(name);
  thing->setError(value);
  cout << "Setting the error on " << name << " to " << value << endl;
}
/******************************************************************************/
void Component::SetRange(string name, double valmin, double valmax)
{
  RooRealVar* thing = (RooRealVar*)GetThing(name);
  thing->setRange(valmin, valmax);
  cout << "Setting " << name << " range to [" << valmin << "," << valmax << "]" << endl;
}
/******************************************************************************/
void Component::FixValue(string name, double value)
{
  RooRealVar* thing = (RooRealVar*)GetThing(name);
  thing->setVal(value);
  thing->setConstant();
  cout << "Fixing " << name << " to " << value << endl;
}
/******************************************************************************/
void Component::FixShapeTo(RooDataSet* data)
{
  _pdf->fitTo(*data);
  for(auto thing : _stuff)
    if(strcmp(thing->ClassName(),"RooRealVar")==0)
      ((RooRealVar*)thing)->setConstant();
}
/******************************************************************************/
void Component::FixShapeTo(const Component& other)
{
  unsigned int othlen = other._stuff.size(), mylen = _stuff.size();
  if(othlen != mylen)
  {
    cout << "Number of stored objects does not match." << endl;
    return;
  }
  for(unsigned int i = 0; i < mylen; i++)
  {
    string othname = ((string)other._stuff[i]->GetName()).substr(other._name.length())
         , myname  = ((string)_stuff[i]->GetName()).substr(_name.length());
    if(myname != othname)
    {
      cout << "Stored object names do not match." << endl;
      return;
    }
    if(strcmp(other._stuff[i]->ClassName(),_stuff[i]->ClassName())!=0)
    {
      cout << "Stored object classes do not match." << endl;
      return;
    }
    if(strcmp(other._stuff[i]->ClassName(),"RooRealVar")==0 && strcmp(_stuff[i]->ClassName(),"RooRealVar")==0)
    {
      RooRealVar* othvar = (RooRealVar*)other._stuff[i]
               ,* myvar  = (RooRealVar*)_stuff[i];
      cout << "Fixing " << myname << endl;
      myvar->setRange(othvar->getMin(),othvar->getMax());
      myvar->setVal(othvar->getVal());
      myvar->setError(othvar->getError());
      myvar->setConstant();
    }
  }
}
/******************************************************************************/
/******************************************************************************/
MassFitter::MassFitter(RooRealVar* mass) :
  _mass(mass)
{
  init();
}
MassFitter::MassFitter(const MassFitter& input) :
  _mass(input._mass)
{
  init();
}
MassFitter::~MassFitter()
{
  if(_components.size()>1)
    delete _pdf;
  for(auto component : _components)
    delete component;
  if(_hasweightfunction)
    delete _weightfunction;
}
/******************************************************************************/
void MassFitter::init()
{
  _haspdf  = false;
  _hasdata = false;
  _useyieldvars = false;
  _hasweightfunction = false;
  _weighted = false;
  cout << "MassFitter instance initialised" << endl;
}
/******************************************************************************/
Component* MassFitter::AddComponent(string name, RooAbsPdf* thepdf, RooAbsReal* yield)
{
  Component* newpdf = AddComponent(name, thepdf);
  newpdf->SetYieldVar(yield);
  _useyieldvars = true;
  return newpdf;
}
Component* MassFitter::AddComponent(string name, RooAbsPdf* thepdf)
{
  Component* newpdf = new Component(name, thepdf);
  _components.push_back(newpdf);
  return newpdf;
}
Component* MassFitter::AddComponent(string name, string type, RooAbsReal* yield)
{
  Component* newpdf = AddComponent(name, type);
  newpdf->SetYieldVar(yield);
  _useyieldvars = true;
  return newpdf;
}
Component* MassFitter::AddComponent(string name, string type)
{
  Component* newpdf;
  cout << "Will attempt to construct PDF with name " << type << endl;
  newpdf = makeshape(name, type);
  _components.push_back(newpdf);
  return newpdf;
}
/******************************************************************************/
Component* MassFitter::makeshape(string name, string type)
{
  if(type=="Single Gaussian" || type == "Gaussian")
  {
    return singleGaussian(name);
  }
  else if(type=="Double Gaussian")
  {
    return doubleGaussian(name);
  }
  else if(type=="Triple Gaussian")
  {
    return tripleGaussian(name);
  }
  else if(type=="Crystal Ball")
  {
    return CrystalBall(name);
  }
  else if(type=="Crystal Ball + 1 Gaussian" || type=="Crystal Ball + Gaussian")
  {
    return CrystalBall1Gauss(name);
  }
  else if(type=="Crystal Ball + 2 Gaussians")
  {
    return CrystalBall2Gauss(name);
  }
  else if(type=="Breit-Wigner" || type=="Breit Wigner")
  {
    return BreitWigner(name);
  }
  else if(type=="Rel Breit-Wigner" || type=="Rel Breit Wigner")
  {
    return RelBreitWigner(name);
  }
  else if(type=="Voigtian" || type=="Voigt")
  {
    return Voigtian(name);
  }
  else if(type=="BWxGauss" || type=="BW(X)Gauss")
  {
    return BWxGauss(name);
  }
  else if(type=="RBWxGauss" || type=="RBW(X)Gauss")
  {
    return RBWxGauss(name);
  }
  else if(type=="Flatte")
  {
    return Flatte(name);
  }
  else if(type=="RooDstD0BG" || type=="Threshold" || type=="ThresholdShape")
  {
    return ThresholdShape(name);
  }
  else if(type=="Flat")
  {
    return flatfunction(name);
  }
  else if(type=="Exponential")
  {
    return exponential(name);
  }
  else if(type=="Argus")
  {
    return Argus(name);
  }
  else if(type=="ThreeBodyPhaseSpace" || type=="Three Body Phase Space")
  {
    return ThreeBodyPhaseSpace(name);
  }
  else
  {
    throw invalid_argument(("No such PDF " + type).c_str());
  }
}
/******************************************************************************/
void MassFitter::assemble()
{
  RooArgList pdflist;
  RooArgList coeflist;
  RooAbsPdf* tmp_pdf;
//  TODO: https://root.cern.ch/root/html/tutorials/roofit/rf703_effpdfprod.C.html
  switch(_components.size())
  {
    case 0:
      throw runtime_error("Trying to assemble a PDF with no components.");
      break;
    case 1:
      tmp_pdf = _components[0]->GetPDF();
      break;
    default:
      for(auto pdf : _components)
      {
        pdflist.add(*(pdf->GetPDF()));
        if(_useyieldvars)
          coeflist.add(*(pdf->GetYieldVar()));
      }
      tmp_pdf = _useyieldvars ? new RooAddPdf("model","Total PDF",pdflist,coeflist) : new RooAddPdf("model","Total PDF",pdflist) ;
      break;
  }
  if(_hasweightfunction)
    _pdf = new RooEffProd("model_w","Total weighted PDF",*tmp_pdf,*_weightfunction);
  else
    _pdf = tmp_pdf;
  _haspdf = true;
}
/******************************************************************************/
Component* MassFitter::GetComponent(string name)
{
  for(auto pdf : _components)
    if((string)pdf->GetName() == name)
      return pdf;
  throw invalid_argument(("No such component: "+name+".").c_str());
}
/******************************************************************************/
void MassFitter::SetWeighted()
{
  _weighted = true;
}
/******************************************************************************/
void MassFitter::SetData(RooDataSet* data)
{
  _hasdata = true;
  _data    = data;
}
/******************************************************************************/
RooFitResult* MassFitter::Fit()
{
  if(!_haspdf)
    assemble();
  if(_hasdata)
    return _weighted ? _pdf->fitTo(*_data,SumW2Error(kTRUE),Extended()) : _pdf->fitTo(*_data,Extended());
  else
    throw runtime_error("Attempting to fit without a DataSet.");
}
RooFitResult* MassFitter::Fit(RooDataSet* data)
{
  if(!_haspdf)
    assemble();
  cout << "Saving passed RooDataSet in object." << endl;
  SetData(data);
  return Fit();
}
RooFitResult* MassFitter::ConstrainedFit(RooDataSet* data, RooRealVar* constr_var, RooAbsReal& mean, RooAbsReal& sigma)
{
  if(!_haspdf)
    assemble();
  cout << "Saving passed RooDataSet in object." << endl;
  SetData(data);
  return ConstrainedFit(constr_var, mean, sigma);
}
RooFitResult* MassFitter::ConstrainedFit(RooRealVar* constr_var, RooAbsReal& mean, RooAbsReal& sigma)
{
  if(!_haspdf)
    assemble();
  RooGaussian* constraint = new RooGaussian("constraint","constraint",*constr_var,mean,sigma);
  RooProdPdf* _pdf_c = new RooProdPdf("pdf_c","pdf_c",RooArgSet(*_pdf,*constraint));
  if(_hasdata)
    return _weighted ? _pdf_c->fitTo(*_data,SumW2Error(kTRUE),Extended(),Constrain(*constr_var)) : _pdf_c->fitTo(*_data,Extended(),Constrain(*constr_var));
  else
    throw runtime_error("Attempting to fit without a DataSet.");
}
/******************************************************************************/
void MassFitter::Plot(RooPlot* frame)
{
  string trailer = _hasweightfunction ? "_w" : "shape";
  if(_components.size()>1)
    for(auto comp : _components)
      _pdf->plotOn(frame,Components((comp->GetName()+trailer).c_str()),LineStyle(comp->GetStyle()),LineColor(comp->GetColour()));
  _pdf->plotOn(frame,LineStyle(kSolid),LineColor(kRed));
}
/******************************************************************************/
SPlot* MassFitter::GetsPlot(RooRealVar* Nsig, RooRealVar* Nbkg)
{
  return GetsPlot(RooArgList(*Nsig,*Nbkg));
}
SPlot* MassFitter::GetsPlot(RooArgList list)
{
  return new SPlot("sData","An SPlot", *_data, _pdf, list);
}
/******************************************************************************/
void MassFitter::SetWeightFunction(string function)
{
  _hasweightfunction = true;
  _weightfunction = new RooFormulaVar("weight_function",function.c_str(),*_mass);
}
void MassFitter::SetWeightFunction(RooFormulaVar* function)
{
  _hasweightfunction = true;
  _weightfunction = function;
}
/******************************************************************************/
Component* MassFitter::BifurcatedGaussian(string name)
{
  RooRealVar*    mean      = new RooRealVar("mean","Mean mass",5.36815e+03,5360,5380);
  RooRealVar*    sigma1    = new RooRealVar("sigma1","Width of first gaussian",1.29312e+01,10,24);
  RooRealVar*    sigma2    = new RooRealVar("sigma2","Width of second gaussian",3.27034e+01,18,50);
  RooBifurGauss* thepdf    = new RooBifurGauss("shape","Bifurcated Gaussian",*_mass,*mean,*sigma1,*sigma2);
  Component* pdf = new Component(name,thepdf);
  pdf->AddThing(mean);
  pdf->AddThing(sigma1);
  pdf->AddThing(sigma2);
  return pdf;
}
/******************************************************************************/
Component* MassFitter::singleGaussian(string name)
{
  RooRealVar*    mean      = new RooRealVar("mean","Mean mass",5.36815e+03,5360,5380);
  RooRealVar*    sigma1    = new RooRealVar("sigma1","Width of first gaussian",1.29312e+01,10,24);
  RooRealVar*    scalef    = new RooRealVar("scalef","Scale factor",1);
  RooFormulaVar* scsig1    = new RooFormulaVar("scsig1","@0*@1",RooArgList(*scalef,*sigma1));
  RooGaussian*   thepdf    = new RooGaussian("shape","Gaussian",*_mass,*mean,*scsig1);
  Component* pdf = new Component(name,thepdf);
  pdf->AddThing(mean);
  pdf->AddThing(sigma1);
  pdf->AddThing(scalef);
  pdf->AddThing(scsig1);
  return pdf;
}
/******************************************************************************/
Component* MassFitter::doubleGaussian(string name)
{
  RooRealVar*    mean      = new RooRealVar("mean","Mean mass",5.36815e+03,5360,5380);
  RooRealVar*    sigma1    = new RooRealVar("sigma1","Width of first gaussian",1.29312e+01,10,18);
  RooRealVar*    sigma2    = new RooRealVar("sigma2","Width of second gaussian",3.27034e+01,18,50);
  RooRealVar*    scalef    = new RooRealVar("scalef","Scale factor",1);
  RooFormulaVar* scsig1    = new RooFormulaVar("scsig1","@0*@1",RooArgList(*scalef,*sigma1));
  RooFormulaVar* scsig2    = new RooFormulaVar("scsig2","@0*@1",RooArgList(*scalef,*sigma2));
  RooRealVar*    fgaus1    = new RooRealVar("fgaus1","Fraction of first gaussian",0.8,0.5,1.0);
  RooFormulaVar* ominf1    = new RooFormulaVar("ominf1","(1-@0)*(@0<1)",RooArgList(*fgaus1));
  RooGaussian*   gauss1    = new RooGaussian("gauss1","First gaussian",*_mass,*mean,*scsig1);
  RooGaussian*   gauss2    = new RooGaussian("gauss2","Second gaussian",*_mass,*mean,*scsig2);
  RooAddPdf*     thepdf    = new RooAddPdf("shape","Double Gaussian",RooArgList(*gauss1,*gauss2),RooArgList(*fgaus1,*ominf1));
  Component* pdf = new Component(name,thepdf);
  pdf->AddThing(mean);
  pdf->AddThing(sigma1);
  pdf->AddThing(sigma2);
  pdf->AddThing(scalef);
  pdf->AddThing(scsig1);
  pdf->AddThing(scsig2);
  pdf->AddThing(fgaus1);
  pdf->AddThing(ominf1);
  pdf->AddThing(gauss1);
  pdf->AddThing(gauss2);
  return pdf;
}
/******************************************************************************/
Component* MassFitter::tripleGaussian(string name)
{
  RooRealVar*    mean      = new RooRealVar("mean","Mean mass",5.36815e+03,5360,5380);
  RooRealVar*    sigma1    = new RooRealVar("sigma1","Width of first gaussian",1.29312e+01,10,18);
  RooRealVar*    sigma2    = new RooRealVar("sigma2","Width of second gaussian",3.27034e+01,18,50);
  RooRealVar*    sigma3    = new RooRealVar("sigma3","Width of third gaussian",50,40,120);
  RooRealVar*    scalef    = new RooRealVar("scalef","Scale factor",1);
  RooFormulaVar* scsig1    = new RooFormulaVar("scsig1","@0*@1",RooArgList(*scalef,*sigma1));
  RooFormulaVar* scsig2    = new RooFormulaVar("scsig2","@0*@1",RooArgList(*scalef,*sigma2));
  RooFormulaVar* scsig3    = new RooFormulaVar("scsig3","@0*@1",RooArgList(*scalef,*sigma3));
  RooRealVar*    fgaus1    = new RooRealVar("fgaus1","Total fraction of first gaussian",0.5,0.3,1.0);
  RooFormulaVar* ominf1    = new RooFormulaVar("ominf1","(1-@0)*(@0<1)",*fgaus1);
  RooRealVar*    fgaus2    = new RooRealVar("fgaus2","Fraction of second gaussian relative to third",0.5,0.3,1.0);
  RooFormulaVar* ominf2    = new RooFormulaVar("ominf2","(1-@0)*(@0<1)",*fgaus2);
  RooGaussian*   gauss1    = new RooGaussian("gauss1","First gaussian",*_mass,*mean,*scsig1);
  RooGaussian*   gauss2    = new RooGaussian("gauss2","Second gaussian",*_mass,*mean,*scsig2);
  RooGaussian*   gauss3    = new RooGaussian("gauss3","Third gaussian",*_mass,*mean,*scsig3);
  RooAddPdf*     othbit    = new RooAddPdf("othbit","othbit",RooArgList(*gauss2,*gauss3),RooArgList(*fgaus2,*ominf2));
  RooAddPdf*     thepdf    = new RooAddPdf("shape","Triple Gaussian",RooArgList(*gauss1,*othbit),RooArgList(*fgaus1,*ominf1));
  Component* pdf = new Component(name,thepdf);
  pdf->AddThing(mean);
  pdf->AddThing(sigma1);
  pdf->AddThing(sigma2);
  pdf->AddThing(sigma3);
  pdf->AddThing(scalef);
  pdf->AddThing(scsig1);
  pdf->AddThing(scsig2);
  pdf->AddThing(scsig3);
  pdf->AddThing(fgaus1);
  pdf->AddThing(fgaus2);
  pdf->AddThing(ominf1);
  pdf->AddThing(ominf2);
  pdf->AddThing(gauss1);
  pdf->AddThing(gauss2);
  pdf->AddThing(gauss3);
  pdf->AddThing(othbit);
  return pdf;
}
/******************************************************************************/
Component* MassFitter::CrystalBall(string name)
{
  RooRealVar*    mean      = new RooRealVar("mean","Mean mass",5.36815e+03,5360,5380);
  RooRealVar*    alpha     = new RooRealVar("alpha","alpha",3,-10,10);
	RooRealVar*    n         = new RooRealVar("n","n",1.0);
  RooRealVar*    sigma1    = new RooRealVar("sigma1","Width of first gaussian",1.29312e+01,10,24);
  RooRealVar*    scalef    = new RooRealVar("scalef","Scale factor",1);
  RooFormulaVar* scsig1    = new RooFormulaVar("scsig1","@0*@1",RooArgList(*scalef,*sigma1));
  RooCBShape*    thepdf    = new RooCBShape("shape","Crystal Ball",*_mass,*mean,*scsig1,*alpha,*n);
  Component* pdf = new Component(name,thepdf);
  pdf->AddThing(mean);
  pdf->AddThing(alpha);
  pdf->AddThing(n);
  pdf->AddThing(sigma1);
  pdf->AddThing(scalef);
  pdf->AddThing(scsig1);
  return pdf;
}
/******************************************************************************/
Component* MassFitter::CrystalBall1Gauss(string name)
{
  RooRealVar*    mean      = new RooRealVar("mean","Mean mass",5.36815e+03,5360,5380);
  RooRealVar*    alpha     = new RooRealVar("alpha","alpha",3,-10,10);
	RooRealVar*    n         = new RooRealVar("n","n",1.0);
  RooRealVar*    sigma1    = new RooRealVar("sigma1","Width of first gaussian",1.29312e+01,10,18);
  RooRealVar*    sigma2    = new RooRealVar("sigma2","Width of second gaussian",3.27034e+01,18,50);
  RooRealVar*    scalef    = new RooRealVar("scalef","Scale factor",1);
  RooFormulaVar* scsig1    = new RooFormulaVar("scsig1","@0*@1",RooArgList(*scalef,*sigma1));
  RooFormulaVar* scsig2    = new RooFormulaVar("scsig2","@0*@1",RooArgList(*scalef,*sigma2));
  RooRealVar*    fgaus1    = new RooRealVar("fgaus1","Fraction of first gaussian",0.8,0.5,1.0);
  RooFormulaVar* ominf1    = new RooFormulaVar("ominf1","(1-@0)*(@0<1)",RooArgList(*fgaus1));
  RooCBShape*    CBshape   = new RooCBShape("CBshape","Crystal Ball",*_mass,*mean,*scsig1,*alpha,*n);
  RooGaussian*   gauss2    = new RooGaussian("gauss2","First gaussian",*_mass,*mean,*scsig2);
  RooAddPdf*     thepdf    = new RooAddPdf("shape","Crystal Ball + Gaussian",RooArgList(*CBshape,*gauss2),RooArgList(*fgaus1,*ominf1));
  Component* pdf = new Component(name,thepdf);
  pdf->AddThing(mean);
  pdf->AddThing(alpha);
  pdf->AddThing(n);
  pdf->AddThing(sigma1);
  pdf->AddThing(sigma2);
  pdf->AddThing(scalef);
  pdf->AddThing(scsig1);
  pdf->AddThing(scsig2);
  pdf->AddThing(fgaus1);
  pdf->AddThing(ominf1);
  pdf->AddThing(CBshape);
  pdf->AddThing(gauss2);
  return pdf;
}
/******************************************************************************/
Component* MassFitter::CrystalBall2Gauss(string name)
{
  RooRealVar*    mean      = new RooRealVar("mean","Mean mass",5.36815e+03,5360,5380);
  RooRealVar*    alpha     = new RooRealVar("alpha","alpha",3,-10,10);
	RooRealVar*    n         = new RooRealVar("n","n",1.0);
  RooRealVar*    sigma1    = new RooRealVar("sigma1","Width of first gaussian",1.29312e+01,10,18);
  RooRealVar*    sigma2    = new RooRealVar("sigma2","Width of second gaussian",3.27034e+01,18,50);
  RooRealVar*    sigma3    = new RooRealVar("sigma3","Width of third gaussian",50,40,120);
  RooRealVar*    scalef    = new RooRealVar("scalef","Scale factor",1);
  RooFormulaVar* scsig1    = new RooFormulaVar("scsig1","@0*@1",RooArgList(*scalef,*sigma1));
  RooFormulaVar* scsig2    = new RooFormulaVar("scsig2","@0*@1",RooArgList(*scalef,*sigma2));
  RooFormulaVar* scsig3    = new RooFormulaVar("scsig3","@0*@1",RooArgList(*scalef,*sigma3));
  RooRealVar*    fgaus1    = new RooRealVar("fgaus1","Total fraction of first gaussian",0.5,0.3,1.0);
  RooFormulaVar* ominf1    = new RooFormulaVar("ominf1","(1-@0)*(@0<1)",*fgaus1);
  RooRealVar*    fgaus2    = new RooRealVar("fgaus2","Fraction of second gaussian relative to third",0.5,0.3,1.0);
  RooFormulaVar* ominf2    = new RooFormulaVar("ominf2","(1-@0)*(@0<1)",*fgaus2);
  RooCBShape*    CBshape   = new RooCBShape("CBshape","Crystal Ball",*_mass,*mean,*scsig1,*alpha,*n);
  RooGaussian*   gauss2    = new RooGaussian("gauss2","First gaussian ",*_mass,*mean,*scsig2);
  RooGaussian*   gauss3    = new RooGaussian("gauss3","Second gaussian",*_mass,*mean,*scsig3);
  RooAddPdf*     othbit    = new RooAddPdf("othbit","othbit",RooArgList(*gauss2,*gauss3),RooArgList(*fgaus2,*ominf2));
  RooAddPdf*     thepdf    = new RooAddPdf("shape","Crystal Ball + 2 Gaussians",RooArgList(*CBshape,*othbit),RooArgList(*fgaus1,*ominf1));
  Component* pdf = new Component(name,thepdf);
  pdf->AddThing(mean);
  pdf->AddThing(alpha);
  pdf->AddThing(n);
  pdf->AddThing(sigma1);
  pdf->AddThing(sigma2);
  pdf->AddThing(sigma3);
  pdf->AddThing(scalef);
  pdf->AddThing(scsig1);
  pdf->AddThing(scsig2);
  pdf->AddThing(scsig3);
  pdf->AddThing(fgaus1);
  pdf->AddThing(fgaus2);
  pdf->AddThing(ominf1);
  pdf->AddThing(ominf2);
  pdf->AddThing(CBshape);
  pdf->AddThing(gauss2);
  pdf->AddThing(gauss3);
  pdf->AddThing(othbit);
  return pdf;
}
/******************************************************************************/
Component* MassFitter::BreitWigner(string name)
{
  RooRealVar*     mean   = new RooRealVar("mean","Mean mass",1019.461,1018,1021);
  RooRealVar*     width  = new RooRealVar("width","Natural width",4.266,3.5,5);
  RooBreitWigner* thepdf = new RooBreitWigner("shape","Breit Wigner",*_mass,*mean,*width);
  Component* pdf = new Component(name,thepdf);
  pdf->AddThing(mean);
  pdf->AddThing(width);
  return pdf;
}
/******************************************************************************/
Component* MassFitter::RelBreitWigner(string name)
{
  RooRealVar*        mean   = new RooRealVar("mean","Mean mass",1019.461,1018,1021);
  RooRealVar*        width  = new RooRealVar("width","Natural width",4.266,3.5,5);
  RooRealVar*        radius = new RooRealVar("radius","Blatt-Weisskopf barrier factor radius",3.0e-3,1.0e-3,5.0e-3); // 3 GeV^-1 = 0.003 MeV^-1
  RooRealVar*        mK     = new RooRealVar("mK","kaon mass",493.677);
  RooRealVar*        spin   = new RooRealVar("spin","spin",1,0,2);
  RooRelBreitWigner* thepdf = new RooRelBreitWigner("shape","Relativistic Breit Wigner",*_mass,*mean,*width,*radius,*mK,*mK,*spin);
  Component* pdf = new Component(name,thepdf);
  radius->setConstant();
  spin->setConstant();
  pdf->AddThing(mean);
  pdf->AddThing(width);
  pdf->AddThing(radius);
  pdf->AddThing(mK);
  pdf->AddThing(spin);
  return pdf;
}
/******************************************************************************/
Component* MassFitter::BWxGauss(string name)
{
  RooRealVar*     mean   = new RooRealVar("mean","Mean mass",1019.461,1018,1021);
  RooRealVar*     width  = new RooRealVar("width","Natural width",4.266,3.5,5);
  RooRealVar*     zero   = new RooRealVar("zero","Gaussian mean",0);
  RooRealVar*     sigma1 = new RooRealVar("sigma1","Detector resolution",1,0,10);
  RooBreitWigner* bw     = new RooBreitWigner("bw","Breit Wigner",*_mass,*mean,*width);
  RooGaussian*    gauss  = new RooGaussian("gauss","Gaussian",*_mass,*zero,*sigma1);
  _mass->setBins(10000,"cache");
  RooFFTConvPdf*  thepdf = new RooFFTConvPdf("shape","Breit Wigner (X) Gaussian",*_mass,*bw,*gauss);
  thepdf->setBufferStrategy(RooFFTConvPdf::Flat);
  thepdf->setBufferFraction(0.2);
  Component* pdf = new Component(name,thepdf);
  pdf->AddThing(mean);
  pdf->AddThing(width);
  pdf->AddThing(zero);
  pdf->AddThing(sigma1);
  pdf->AddThing(bw);
  pdf->AddThing(gauss);
  return pdf;
}
/******************************************************************************/
Component* MassFitter::RBWxGauss(string name)
{
  RooRealVar*        mean   = new RooRealVar("mean","Mean mass",1019.461,1018,1020);
  RooRealVar*        width  = new RooRealVar("width","Natural width",4.266);
  RooRealVar*        radius = new RooRealVar("radius","Blatt-Weisskopf barrier factor radius",3.0e-3); // 3 GeV^-1 = 0.003 MeV^-1
  RooRealVar*        mK     = new RooRealVar("mK","kaon mass",493.677);
  RooRealVar*        spin   = new RooRealVar("spin","spin",1);
  RooRealVar*        zero   = new RooRealVar("zero","Gaussian mean",0);
  RooRealVar*        sigma1 = new RooRealVar("sigma1","Detector resolution",0.7);
  RooRelBreitWigner* rbw    = new RooRelBreitWigner("rbw","Relativistic Breit Wigner",*_mass,*mean,*width,*radius,*mK,*mK,*spin);
  RooGaussian*       gauss  = new RooGaussian("gauss","Gaussian",*_mass,*zero,*sigma1);
  _mass->setBins(10000,"cache");
  RooFFTConvPdf*  thepdf = new RooFFTConvPdf("shape","Breit Wigner (X) Gaussian",*_mass,*rbw,*gauss);
  thepdf->setBufferStrategy(RooFFTConvPdf::Flat);
  thepdf->setBufferFraction(0.2);
  Component*         pdf = new Component(name,thepdf);
  radius->setConstant();
  spin->setConstant();
  pdf->AddThing(mean);
  pdf->AddThing(width);
  pdf->AddThing(radius);
  pdf->AddThing(mK);
  pdf->AddThing(spin);
  pdf->AddThing(zero);
  pdf->AddThing(sigma1);
  pdf->AddThing(rbw);
  pdf->AddThing(gauss);
  return pdf;
}
/******************************************************************************/
Component* MassFitter::Voigtian(string name)
{
  RooRealVar*  mean   = new RooRealVar("mean","Mean mass", 1019.461,1018,1021);
  RooRealVar*  width  = new RooRealVar("width","Natural width",4.266,3.5,5);
  RooRealVar*  sigma1 = new RooRealVar("sigma1","Detector resolution",1,0,10);
  RooVoigtian* thepdf = new RooVoigtian("shape","Voigtian",*_mass,*mean,*width,*sigma1);
  Component* pdf = new Component(name,thepdf);
  pdf->AddThing(mean);
  pdf->AddThing(width);
  pdf->AddThing(sigma1);
  return pdf;
}
/******************************************************************************/
Component* MassFitter::Flatte(string name)
{
  // I assume that the couplings are to KK and ππ
  RooRealVar* mean   = new RooRealVar("mean","mean",939.9,930,1000); // PDG average is 990, 939.9 comes from J/ψππ and was used in J/ψKK
  RooRealVar* gpipi  = new RooRealVar("gpipi","gpipi",199);
  RooRealVar* gKK    = new RooRealVar("gKK","gKK",199*3);
  RooRealVar* mpi    = new RooRealVar("mpi","mpi",139.57018);
  RooRealVar* mK     = new RooRealVar("mK","mK",493.677);
  RooFlatte*  thepdf = new RooFlatte("shape","Flatte",*_mass,*mean,*gpipi,*mpi,*mpi,*gKK,*mK,*mK);
  Component* pdf = new Component(name,thepdf);
  pdf->AddThing(mean);
  pdf->AddThing(gpipi);
  pdf->AddThing(mpi);
  pdf->AddThing(gKK);
  pdf->AddThing(mK);
  return pdf;
}
/******************************************************************************/
Component* MassFitter::ThresholdShape(string name)
{
  RooRealVar* dm0    = new RooRealVar("dm0","dm0",2*493.677);
  RooRealVar* a      = new RooRealVar("a","A",2,1,3);
  RooRealVar* b      = new RooRealVar("b","B",-3.5,-5,-1);
  RooRealVar* c      = new RooRealVar("c","C",10,1,100);
  RooDstD0BG* thepdf = new RooDstD0BG("shape","Threshold shape",*_mass,*dm0,*c,*a,*b);
  Component* pdf = new Component(name,thepdf);
  pdf->AddThing(dm0);
  pdf->AddThing(a);
  pdf->AddThing(b);
  pdf->AddThing(c);
  return pdf;
}
/******************************************************************************/
Component* MassFitter::Argus(string name)
{
  RooRealVar* m0 = new RooRealVar("m0","Resonance mass",5251);
  RooRealVar* c  = new RooRealVar("c","Slope",0,-10,10);
  RooRealVar* p  = new RooRealVar("p","Power",0.5,0,5);
  RooArgusBG* thepdf = new RooArgusBG("shape","Argus shape",*_mass,*m0,*c,*p);
  Component* pdf = new Component(name,thepdf);
  pdf->AddThing(m0);
  pdf->AddThing(c);
  pdf->AddThing(p);
  return pdf;
}
/******************************************************************************/
Component* MassFitter::flatfunction(string name)
{
  RooUniform* thepdf = new RooUniform("shape","Flat background",*_mass);
  Component* pdf = new Component(name,thepdf);
  return pdf;
}
/******************************************************************************/
Component* MassFitter::exponential(string name)
{
  RooRealVar*     slope  = new RooRealVar("slope","Exponent",0,-1.0,1.0);
  RooExponential* thepdf = new RooExponential("shape","Exponential background",*_mass,*slope);
  Component* pdf = new Component(name,thepdf);
  pdf->AddThing(slope);
  return pdf;
}
/******************************************************************************/
Component* MassFitter::straightline(string name)
{
  RooRealVar*    slope  = new RooRealVar("slope","Gradient",0,-1.0,1.0);
  RooPolynomial* thepdf = new RooPolynomial("shape","Straight line background",*_mass,*slope);
  Component* pdf = new Component(name,thepdf);
  pdf->AddThing(slope);
  return pdf;
}
Component* MassFitter::ThreeBodyPhaseSpace(string name)
{
  RooRealVar* M  = new RooRealVar("M","Parent mass",5366.77);
  RooRealVar* m1 = new RooRealVar("m1","Body 1 mass",493.677);
  RooRealVar* m2 = new RooRealVar("m2","Body 2 mass",493.677);
  RooRealVar* m3 = new RooRealVar("m3","Body 3 mass",1019.461);
  RooThreeBodyPhaseSpace* thepdf = new RooThreeBodyPhaseSpace("shape","Three-body phase space function",*_mass,*M,*m1,*m2,*m3);
  Component* pdf = new Component(name,thepdf);
  pdf->AddThing(M);
  pdf->AddThing(m1);
  pdf->AddThing(m2);
  pdf->AddThing(m3);
  return pdf;
}

