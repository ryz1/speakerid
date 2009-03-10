clear all


nAmostras1 = 100000;
nAmostras2 = 100000;
x1 = [normrnd(1,2,1,nAmostras1);normrnd(5,2,1,nAmostras1)];
x2 = [normrnd(2,1,1,nAmostras2);normrnd(6,1,1,nAmostras2)];

fid=fopen("loc1.dat","wb");
fwrite(fid,x1,"double");
fclose(fid);

fid=fopen("loc2.dat","wb");
fwrite(fid,x2,"double");
fclose(fid);

