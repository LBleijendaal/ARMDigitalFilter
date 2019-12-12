h_len = 101;
fc = 0.10;


for i = 1 : h_len-1
    
    t = i + 0.5 - 0.5 * h_len;
    
    s = sin(2*pi*fc*t + 1e-6) / (2 * pi * fc * t + 1e-6);
    
    w = 0.53836 - (0.46164 * cos((2*pi*i)/(h_len -1)));
    
    h(i) = s * w;
end

fprintf('{');
for i = 1:length(h)
    fprintf([num2str(h(i)) ', ']);
end
fprintf('}');