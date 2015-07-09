clear;
clc;
close all;
iTrace = '../paper/data/ktime-data.txt';
img = '../paper/imgs/statistics/ktime-data.eps';
f = fopen(iTrace, 'r');
formatSpec = '%f %f %f %f %f %f %f %f';
sizeA = [8 Inf];
A = fscanf(f, formatSpec, sizeA);
kVal = A(4,:);
finalTVal = A(7,:);

plot(kVal, finalTVal, '-o', 'MarkerFaceColor',[0 0 1]);

grid on;
box on;
xlabel('Number of paths - k'); 
ylabel('Delivery time (s)');

set(gcf,'PaperPositionMode','auto');
print(img,'-depsc','-r0');

fclose(f);