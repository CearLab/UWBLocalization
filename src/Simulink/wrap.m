%% positions and velocities
data.v = outv(:,1:3);
data.phat = outp(:,1:3);
data.p = outp(:,4:6);

%% error
for i=1:3
    data.e(:,i) = data.p(:,i) - data.phat(:,i);
    data.e_mu(i) = mean(data.e(:,i));
    data.e_sigma(i) = std(data.e(:,i));
end

%% distances
data.D = outD(:,1:12);

%% clear
clear ans i

