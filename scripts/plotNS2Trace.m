function plotNS2Trace(iTrace, imgPath)
    f = fopen(iTrace);
    formatSpec = '$node_(%d) set X_ %f $node_(%d) set Y_ %f ';
    sizeA = [4 Inf];
    A = fscanf(f, formatSpec, sizeA);

    plot(A(2,:), A(4,:), '.');

    saveas(gcf, imgPath);

    fclose(f);
end