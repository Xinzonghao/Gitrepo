#include <stdio.h>
#include "hocdec.h"
extern int nrnmpi_myid;
extern int nrn_nobanner_;

extern void _SinClamp_reg(void);
extern void _myClamp_reg(void);
extern void _myClamp2_reg(void);
extern void _myenv_reg(void);

void modl_reg(){
  if (!nrn_nobanner_) if (nrnmpi_myid < 1) {
    fprintf(stderr, "Additional mechanisms from files\n");

    fprintf(stderr," SinClamp.mod");
    fprintf(stderr," myClamp.mod");
    fprintf(stderr," myClamp2.mod");
    fprintf(stderr," myenv.mod");
    fprintf(stderr, "\n");
  }
  _SinClamp_reg();
  _myClamp_reg();
  _myClamp2_reg();
  _myenv_reg();
}
