Fs = 10000;
Fa = 0;
Fb = 1000;

M = 51;

Np = (M-1)/2;

Att = 60;

A(1) = 2 * (Fb - Fa)/Fs;

for j = 2:(Np+1)
    A(j) = (sin(2 * j * pi * Fb / Fs) - sin(2 * j * pi * Fa / Fs))/(j*pi);
end


if Att < 21
    alpha = 0;
elseif Att > 50
    alpha = 0.1102 * (Att - 8.7);
else
    alpha = 0.5842 * ((Att - 21)^(0.4)) + 0.07886*(Att-21);
end

d = 0;
ds = 1;
s = 1;

while 1  
    d = d + 2;
    ds = ds * (alpha*alpha)/(d*d);
    s = s +ds;
    
     if ds < s*1e-6
        break
    end
end

 Inoalpha = s;   
 
  for j = 1 : (Np+1)
      
      d = 0;
      ds = 1;
      s = 1;
      
      insideForAlpha = alpha * sqrt(1-(j*j/(Np*Np)));
      
    while 1  
        d = d + 2;
    	ds = ds * (insideForAlpha*insideForAlpha)/(d*d);
        s = s +ds;
    
        if ds < s*1e-6
            break;
        end
    end
      
     H(Np+j-1) = A(j) * s / Inoalpha;
 end
 
 for j = 1 : (Np-1)
     H(j) = H(M-1-j);
 end
 
 freqz(H)
 