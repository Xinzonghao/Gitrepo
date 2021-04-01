COMMENT
Since this is an electrode current, positive values of i depolarize the cell
and in the presence of the extracellular mechanism there will be a change
in vext since i is not a transmembrane current but a current injected
directly to the inside of the cell.
ENDCOMMENT

NEURON {
        POINT_PROCESS myenv
        RANGE del, dur, amp, freq, phase, bias
        ELECTRODE_CURRENT i
}

UNITS {
        (nA) = (nanoamp)
             }

PARAMETER {
        del=5	(ms)
        dur=3e3	(ms)
        amp=1 (nA)
        freq=10  (Hz)
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
	        i = amp*sin(2*PI*(freq/2)*(t-del)/1000+phase)+bias
            i = fabs(i)
	   }else{  
	        i = 0
}}}