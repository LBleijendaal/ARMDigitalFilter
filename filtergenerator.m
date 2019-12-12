fsr = 96000;
fc = 0;
bw = 3000;
nt = 32;
g = 0.5;

fir = cell(nt, 1);

for i = 1 : nt-1
       a = (1-nt/2) * 2.0 * pi * bw / fsr;
       ys(i) = sin(a)/a;
       
      %ys = ys/sum(ys);
       
       yg(i) = g * (4.0 * bw / fsr);
       
       %yg = yg/sum(yg);
       
       yw(i) = 0.54 - 0.46 * cos(i * 2.0 * pi/nt);
       
       %yw = yw/sum(yw);
       
       yf(i) = cos((i - nt/2) * 2.0*pi*fc/fsr);
       
       %yf = yf/sum(yf);
       
       
end

%ys = ys/sum(ys);
%yg = yg/sum(yg);


for i = 1 : nt-1

    fir{i} = yf(i) * yw(i) * yg(i) * ys(i);
    
end

m = cell2mat(fir);
figure(1);
freqz(m);