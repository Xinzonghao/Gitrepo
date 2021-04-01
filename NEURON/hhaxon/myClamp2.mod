COMMENT
Since this is an electrode current, positive values of i depolarize the cell
and in the presence of the extracellular mechanism there will be a change
in vext since i is not a transmembrane current but a current injected
directly to the inside of the cell.
ENDCOMMENT

NEURON {
        POINT_PROCESS MyClamp2
        RANGE del, dur, pkamp1, pkamp2, pkamp3, pkamp4, freq1, freq2, freq3, freq4, phase, bias
        ELECTRODE_CURRENT i
}

UNITS {
        (nA) = (nanoamp)
             }

PARAMETER {
        del=5	(ms)
        dur=3e3	(ms)
        pkamp1=1 (nA)
		pkamp2=1 (nA)
        pkamp3=1 (nA)
        pkamp4=1 (nA)

        freq1=10  (Hz)
		freq2=10  (Hz)
        freq3=10  (Hz)
        freq4=10  (Hz)
        phase=0 (rad)
        bias=0  (nA)
        PI=3.14159265358979323846
}

ASSIGNED {
        i (nA)
}

BREAKPOINT {
       at_time(del)
       at_time(del + dur)
       if (t < del) {
	   i=0	
	}else{  
            if (t < del+dur) {
	        i = pkamp1*sin(2*PI*freq1*(t-del)/1000+phase)+pkamp2*sin(2*PI*freq2*(t-del)/1000+phase)+pkamp3*sin(2*PI*freq3*(t-del)/1000+phase)+pkamp4*sin(2*PI*freq4*(t-del)/1000+phase)+bias
	   }else{  
	        i = 0
}}}
