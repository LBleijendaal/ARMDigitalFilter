step=0.1;
limit = step*50;
c=[]; i = 1;
for x = -limit: step:+limit,
       if abs(x) > 0, c(i) = sin(pi*x)/(pi*x);
       else c(i) = 1;
       end
       i = i+1;
end

N = length(c);
win=[]; cw=[];
for n = 0 : N-1,
        win(n+1) = 0.5* (1-cos(2*pi*n/(N-1)));
        cw(n+1) = c(n+1) * win(n+1);
end

c = c/sum(c);
cw = cw/sum(cw);


w0 = 0.2;

%c0 = (1/cos(pi*(w0-step)) * (1/cos(pi*(w0+step))));

%c0 = (1/cos(pi*w0))^2;

c0 = 2;

for n = 1 : N
       c(n) = c(n) * cos(pi*w0*(n-1)) * c0;
       cw(n) = cw(n) * cos(pi*w0*(n-1)) * c0;
end

figure(2)
freqz(c);

fprintf('{');
for i = 1:length(c)
    fprintf([num2str(c(i)) ', ']);
end
fprintf('}');