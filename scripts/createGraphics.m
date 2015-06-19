clear;
clc;
close all;
% function plotNS2Trace(iTrace, imgPath)
    iTrace = '../onion-path-finder/data/uab-busses-contacts-54000h-5n-sorted.txt';
    img = '../paper/imgs/statistics/contats-duration.eps';
    f = fopen(iTrace, 'r');
    formatSpec = '%f %f %f %f';
    sizeA = [4 Inf];
    A = fscanf(f, formatSpec, sizeA);
    contactTime = A(4,:);
    
    [a,b]=hist(contactTime,unique(contactTime));
    bar(b,a);
    hx = graph2d.constantline(mean(contactTime), 'LineStyle','-', 'Color',[1 0 0]);
    changedependvar(hx,'x');
    
    grid on;
    box on;
    xlabel('Contact duration (s)'); 
    ylabel('Number of nodes');
    
    ax = legend('Contact groups','Contact time mean')
    LEG = findobj(ax,'type','text');
    set(LEG,'FontSize',12);
    set(gcf,'PaperPositionMode','auto');
    print(img,'-deps','-r0');

    fclose(f);
% end