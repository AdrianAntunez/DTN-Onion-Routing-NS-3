clear;
clc;
close all;
iTrace = '../paper/data/ntime-data.txt';
img = '../paper/imgs/statistics/ntime-data.eps';
f = fopen(iTrace, 'r');
formatSpec = '%f %f %f %f %f %f %f';
sizeA = [7 Inf];
A = fscanf(f, formatSpec, sizeA);
nVal = A(5,:);
finalTVal = A(7,:);

plot(nVal, finalTVal, '-o', 'MarkerFaceColor',[0 0 1]);

grid on;
box on;
xlabel('Path length - n'); 
ylabel('Delivery time (s)');

set(gcf,'PaperPositionMode','auto');
print(img,'-depsc','-r0');

fclose(f);