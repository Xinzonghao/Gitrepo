/* Created by Language version: 7.7.0 */
/* NOT VECTORIZED */
#define NRN_VECTORIZED 0
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "scoplib_ansi.h"
#undef PI
#define nil 0
#include "md1redef.h"
#include "section.h"
#include "nrniv_mf.h"
#include "md2redef.h"
 
#if METHOD3
extern int _method3;
#endif

#if !NRNGPU
#undef exp
#define exp hoc_Exp
extern double hoc_Exp(double);
#endif
 
#define nrn_init _nrn_init__ImpedanceFM
#define _nrn_initial _nrn_initial__ImpedanceFM
#define nrn_cur _nrn_cur__ImpedanceFM
#define _nrn_current _nrn_current__ImpedanceFM
#define nrn_jacob _nrn_jacob__ImpedanceFM
#define nrn_state _nrn_state__ImpedanceFM
#define _net_receive _net_receive__ImpedanceFM 
#define impedance impedance__ImpedanceFM 
 
#define _threadargscomma_ /**/
#define _threadargsprotocomma_ /**/
#define _threadargs_ /**/
#define _threadargsproto_ /**/
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *getarg();
 static double *_p; static Datum *_ppvar;
 
#define t nrn_threads->_t
#define dt nrn_threads->_dt
#define _nd_area  *_ppvar[0]._pval
#define vec1	*_ppvar[2]._pval
#define _p_vec1	_ppvar[2]._pval
#define vec2	*_ppvar[3]._pval
#define _p_vec2	_ppvar[3]._pval
 
#if MAC
#if !defined(v)
#define v _mlhv
#endif
#if !defined(h)
#define h _mlhh
#endif
#endif
 
#if defined(__cplusplus)
extern "C" {
#endif
 static int hoc_nrnpointerindex =  2;
 /* external NEURON variables */
 /* declaration of user functions */
 static double _hoc_impedance();
 static int _mechtype;
extern void _nrn_cacheloop_reg(int, int);
extern void hoc_register_prop_size(int, int, int);
extern void hoc_register_limits(int, HocParmLimits*);
extern void hoc_register_units(int, HocParmUnits*);
extern void nrn_promote(Prop*, int, int);
extern Memb_func* memb_func;
 
#define NMODL_TEXT 1
#if NMODL_TEXT
static const char* nmodl_file_text;
static const char* nmodl_filename;
extern void hoc_reg_nmodl_text(int, const char*);
extern void hoc_reg_nmodl_filename(int, const char*);
#endif

 extern Prop* nrn_point_prop_;
 static int _pointtype;
 static void* _hoc_create_pnt(_ho) Object* _ho; { void* create_point_process();
 return create_point_process(_pointtype, _ho);
}
 static void _hoc_destroy_pnt();
 static double _hoc_loc_pnt(_vptr) void* _vptr; {double loc_point_process();
 return loc_point_process(_pointtype, _vptr);
}
 static double _hoc_has_loc(_vptr) void* _vptr; {double has_loc_point();
 return has_loc_point(_vptr);
}
 static double _hoc_get_loc_pnt(_vptr)void* _vptr; {
 double get_loc_point_process(); return (get_loc_point_process(_vptr));
}
 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _p = _prop->param; _ppvar = _prop->dparam;
 }
 static void _hoc_setdata(void* _vptr) { Prop* _prop;
 _prop = ((Point_process*)_vptr)->_prop;
   _setdata(_prop);
 }
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 0,0
};
 static Member_func _member_func[] = {
 "loc", _hoc_loc_pnt,
 "has_loc", _hoc_has_loc,
 "get_loc", _hoc_get_loc_pnt,
 "impedance", _hoc_impedance,
 0, 0
};
 /* declare global and static user variables */
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 0,0
};
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static void nrn_alloc(Prop*);
static void  nrn_init(_NrnThread*, _Memb_list*, int);
static void nrn_state(_NrnThread*, _Memb_list*, int);
 static void _hoc_destroy_pnt(_vptr) void* _vptr; {
   destroy_point_process(_vptr);
}
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"ImpedanceFM",
 0,
 0,
 0,
 "vec1",
 "vec2",
 0};
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
  if (nrn_point_prop_) {
	_prop->_alloc_seq = nrn_point_prop_->_alloc_seq;
	_p = nrn_point_prop_->param;
	_ppvar = nrn_point_prop_->dparam;
 }else{
 	_p = nrn_prop_data_alloc(_mechtype, 0, _prop);
 	/*initialize range parameters*/
  }
 	_prop->param = _p;
 	_prop->param_size = 0;
  if (!nrn_point_prop_) {
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 4, _prop);
  }
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 
}
 static void _initlists();
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, _NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _ImpedanceFM_reg() {
	int _vectorized = 0;
  _initlists();
 	_pointtype = point_register_mech(_mechanism,
	 nrn_alloc,(void*)0, (void*)0, (void*)0, nrn_init,
	 hoc_nrnpointerindex, 0,
	 _hoc_create_pnt, _hoc_destroy_pnt, _member_func);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 0, 4);
  hoc_register_dparam_semantics(_mechtype, 0, "area");
  hoc_register_dparam_semantics(_mechtype, 1, "pntproc");
  hoc_register_dparam_semantics(_mechtype, 2, "pointer");
  hoc_register_dparam_semantics(_mechtype, 3, "pointer");
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 ImpedanceFM /Users/xinzonghao/Desktop/python-programme/NEURON/LFP/x86_64/ImpedanceFM.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "Frequency-dependent impedance";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int impedance(double, double, double, double, double, double, double, double, double, double, double);
 
/*VERBATIM*/
#include <malloc.h>

// calculate impedance for the whole range of frequencies

void calc_impedances(Zr,Zi,fmax,df,rext,rmax,dr,R,sigma1,sigma2,lambda,epsilon,sigmaR)
	double Zr[],Zi[],fmax,df,rext,rmax,dr,R,sigma1,sigma2,lambda,epsilon,sigmaR;
	// vector Z is impedance, Z[0]=real part, Z[1]=imaginary part
   {
        double epsR,sigR,w,w2,sig,eps,den,ReZ,ImZ,r,f;
	float *sigmatab;
	double PI = 3.1415927;
	int j,k,siz;


	// printf("%s\n%g %g %g %g %g %g %g %g %g %g %g\n",\
	// "fmax,df,rext,rmax,dr,R,sigma1,sigma2,lambda,epsilon,sigmaR = ",\
	// fmax,df,rext,rmax,dr,R,sigma1,sigma2,lambda,epsilon,sigmaR);

	// tabulate all values of sigma in a table "sigmatab",
	// which avoids calculating them several times
	siz = fmax/df + 1;
	sigmatab = (float *) malloc(sizeof(float) * siz);
	k = 0;
	for(r=rext; r<=rmax; r=r+dr) {
	  sigmatab[k] = sigma2 + (sigma1-sigma2) * exp(-(r-R)/lambda);
	  k++;
	}

	// calculate the impedances for each frequency
	sigR = sigma1;
	epsR = epsilon;
	j=0;
	for(f=0; f<=fmax; f=f+df) {	// loop on frequencies
	  w = 2*PI*f;
	  w2 = w*w;
	  ReZ=0;
	  ImZ=0;
	  k=0;
	  for(r=rext; r<=rmax; r=r+dr) {	// compute integral
	    /* sig = sigmaF(r,R,sigma1,sigma2,lambda); */
	    sig = sigmatab[k];	// tabulated sigma
	    eps = epsilon;
	    den = r*r * (sig*sig + w2 * eps*eps);
	    ReZ = ReZ + (sig*sigR + w2*eps*epsR) / den;
	    ImZ = ImZ + (sig*epsR - sigR*eps) / den;
	    k++;
	  }
	  Zr[j] = dr/(4*PI*sigmaR) * ReZ;	// impedance (UNITS: Ohm)
	  Zi[j] = w * dr/(4*PI*sigmaR) * ImZ;
          j++;
	  /* printf("last sigma = %g\n",sig); */
	}
	free(sigmatab);
   }


 
static int  impedance (  double _lfmax , double _ldf , double _lrext , double _lrmax , double _ldr , double _lR , double _lsigma1 , double _lsigma2 , double _llambda , double _lepsilon , double _lsigmaR ) {
   
/*VERBATIM*/

  /* printf("argument passed in procedure : f = %g\n",_lf); */

  calc_impedances(&vec1,&vec2,_lfmax,_ldf,_lrext,_lrmax,_ldr,_lR,_lsigma1,\
	_lsigma2,_llambda,_lepsilon,_lsigmaR);

  return 0; }
 
static double _hoc_impedance(void* _vptr) {
 double _r;
    _hoc_setdata(_vptr);
 _r = 1.;
 impedance (  *getarg(1) , *getarg(2) , *getarg(3) , *getarg(4) , *getarg(5) , *getarg(6) , *getarg(7) , *getarg(8) , *getarg(9) , *getarg(10) , *getarg(11) );
 return(_r);
}

static void initmodel() {
  int _i; double _save;_ninits++;
{

}
}

static void nrn_init(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v = _v;
 initmodel();
}}

static double _nrn_current(double _v){double _current=0.;v=_v;{
} return _current;
}

static void nrn_state(_NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; double _v = 0.0; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
 _nd = _ml->_nodelist[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v=_v;
{
}}

}

static void terminal(){}

static void _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
_first = 0;
}

#if NMODL_TEXT
static const char* nmodl_filename = "/Users/xinzonghao/Desktop/python-programme/NEURON/LFP/ImpedanceFM.mod";
static const char* nmodl_file_text = 
  "TITLE Frequency-dependent impedance\n"
  "\n"
  "COMMENT\n"
  "----------------------------------------------------------------------\n"
  "\n"
  "This mod files calculates the impedance of the extracellular medium\n"
  "for the whole frequency range.  \n"
  "\n"
  "There is no parameter to pass to the MOD file; but the procedure \n"
  "\"calc_impedances\" is callable from HOC.  The parameters of this\n"
  "procedure are:\n"
  "- fmax = max frequency at which the impedance must be calculated\n"
  "- df = frequency step to calculate impedances\n"
  "- rext = distance between the source and the electrode\n"
  "- rmax = max distance to integrate\n"
  "- dr = integration step for distance\n"
  "- R = diameter of the current source\n"
  "- sigma1 = extracellular conductivity close to the source (high)\n"
  "	   (normalized value - normally equal to 1)\n"
  "- sigma2 = \"mean\" extracellular conductivity far away (low)\n"
  "	   (normalized value, fraction of the conductivity at the source)\n"
  "- lambda = space constant of the exponential decay of conductivity\n"
  "- epsilon = permittivity (normalized)\n"
  "- sigmaR = absolute value of conductivity in S/um\n"
  "\n"
  "(all distances are in um)\n"
  "\n"
  "The resulting impedances Z are written in the 2 vector vec1 and\n"
  "vec2, with vec1=real part of Z, vec2=imaginary part of Z.  These \n"
  "impedances constitute the \"filter\" of the extracellular space in\n"
  "this model.\n"
  "\n"
  "See details in:\n"
  "\n"
  "  Bedard C, Kroger H & Destexhe A.  Modeling extracellular field \n"
  "  potentials and the frequency-filtering properties of extracellular \n"
  "  space.  Biophysical Journal 86: 1829-1842, 2004.\n"
  "\n"
  "A. Destexhe, CNRS\n"
  "destexhe@iaf.cnrs-gif.fr\n"
  "see http://cns.iaf.cnrs-gif.fr\n"
  "\n"
  "----------------------------------------------------------------------\n"
  "ENDCOMMENT\n"
  "\n"
  "\n"
  "NEURON	{ \n"
  "	POINT_PROCESS ImpedanceFM\n"
  "        POINTER vec1\n"
  "        POINTER vec2\n"
  "}\n"
  "\n"
  "\n"
  "ASSIGNED {\n"
  "	vec1\n"
  "	vec2\n"
  "}\n"
  "\n"
  "\n"
  "VERBATIM\n"
  "#include <malloc.h>\n"
  "\n"
  "// calculate impedance for the whole range of frequencies\n"
  "\n"
  "void calc_impedances(Zr,Zi,fmax,df,rext,rmax,dr,R,sigma1,sigma2,lambda,epsilon,sigmaR)\n"
  "	double Zr[],Zi[],fmax,df,rext,rmax,dr,R,sigma1,sigma2,lambda,epsilon,sigmaR;\n"
  "	// vector Z is impedance, Z[0]=real part, Z[1]=imaginary part\n"
  "   {\n"
  "        double epsR,sigR,w,w2,sig,eps,den,ReZ,ImZ,r,f;\n"
  "	float *sigmatab;\n"
  "	double PI = 3.1415927;\n"
  "	int j,k,siz;\n"
  "\n"
  "\n"
  "	// printf(\"%s\\n%g %g %g %g %g %g %g %g %g %g %g\\n\",\\\n"
  "	// \"fmax,df,rext,rmax,dr,R,sigma1,sigma2,lambda,epsilon,sigmaR = \",\\\n"
  "	// fmax,df,rext,rmax,dr,R,sigma1,sigma2,lambda,epsilon,sigmaR);\n"
  "\n"
  "	// tabulate all values of sigma in a table \"sigmatab\",\n"
  "	// which avoids calculating them several times\n"
  "	siz = fmax/df + 1;\n"
  "	sigmatab = (float *) malloc(sizeof(float) * siz);\n"
  "	k = 0;\n"
  "	for(r=rext; r<=rmax; r=r+dr) {\n"
  "	  sigmatab[k] = sigma2 + (sigma1-sigma2) * exp(-(r-R)/lambda);\n"
  "	  k++;\n"
  "	}\n"
  "\n"
  "	// calculate the impedances for each frequency\n"
  "	sigR = sigma1;\n"
  "	epsR = epsilon;\n"
  "	j=0;\n"
  "	for(f=0; f<=fmax; f=f+df) {	// loop on frequencies\n"
  "	  w = 2*PI*f;\n"
  "	  w2 = w*w;\n"
  "	  ReZ=0;\n"
  "	  ImZ=0;\n"
  "	  k=0;\n"
  "	  for(r=rext; r<=rmax; r=r+dr) {	// compute integral\n"
  "	    /* sig = sigmaF(r,R,sigma1,sigma2,lambda); */\n"
  "	    sig = sigmatab[k];	// tabulated sigma\n"
  "	    eps = epsilon;\n"
  "	    den = r*r * (sig*sig + w2 * eps*eps);\n"
  "	    ReZ = ReZ + (sig*sigR + w2*eps*epsR) / den;\n"
  "	    ImZ = ImZ + (sig*epsR - sigR*eps) / den;\n"
  "	    k++;\n"
  "	  }\n"
  "	  Zr[j] = dr/(4*PI*sigmaR) * ReZ;	// impedance (UNITS: Ohm)\n"
  "	  Zi[j] = w * dr/(4*PI*sigmaR) * ImZ;\n"
  "          j++;\n"
  "	  /* printf(\"last sigma = %g\\n\",sig); */\n"
  "	}\n"
  "	free(sigmatab);\n"
  "   }\n"
  "\n"
  "\n"
  "ENDVERBATIM\n"
  "\n"
  "\n"
  "\n"
  "\n"
  "\n"
  ":\n"
  ": procedure callable from hoc, and which calls the mutual information\n"
  ": algorithm.  The address of the pointed vecors are passed to the\n"
  ": C procedure above.\n"
  ":\n"
  "PROCEDURE impedance(fmax,df,rext,rmax,dr,R,sigma1,sigma2,lambda,epsilon,sigmaR) {\n"
  "\n"
  "VERBATIM\n"
  "\n"
  "  /* printf(\"argument passed in procedure : f = %g\\n\",_lf); */\n"
  "\n"
  "  calc_impedances(&vec1,&vec2,_lfmax,_ldf,_lrext,_lrmax,_ldr,_lR,_lsigma1,\\\n"
  "	_lsigma2,_llambda,_lepsilon,_lsigmaR);\n"
  "\n"
  "ENDVERBATIM\n"
  "}\n"
  "\n"
  ;
#endif
