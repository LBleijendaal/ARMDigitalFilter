M = 54;

%M = 40 + 1;

for nindex = 1 : M
   h(nindex) =  (0.54 - 0.46*cos((2*nindex*pi)/M)) * (0.15*sinc((nindex-27)/2));
end

freqz(h)

fprintf('{');
for i = 1:length(h)
    fprintf([num2str(h(i)) ', ']);
end
fprintf('}');