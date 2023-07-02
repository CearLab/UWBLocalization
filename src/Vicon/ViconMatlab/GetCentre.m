% This function uses the Vicon stream and sphere fitting to find the centre
% of the probe.

[x1, y1, z1, x2, y2, z2, x3, y3, z3] = ViconDataStreamSDK_MATLABTest();

X1 = [x1' y1' z1'];
X2 = [x2' y2' z2'];
X3 = [x3' y3' z3'];

[c1, r1] = sphereFit(X1);
[c2, r2] = sphereFit(X2);
[c3, r3] = sphereFit(X3);

centre = [mean([c1(1) c2(1) c3(1)]) mean([c1(2) c2(2) c3(2)]) mean([c1(3) c2(3) c3(3)])];

fprintf('The centre is located at (%f, %f, %f)', centre(1), centre(2), centre(3));
