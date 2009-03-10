clear all

x1 = [1 3 5;2 4 6];
x2 = [10 30 50 70 90;20 40 60 80 100];

fid=fopen("loc1.dat","wb");
fwrite(fid,x1,"double");
fclose(fid);

fid=fopen("loc2.dat","wb");
fwrite(fid,x2,"double");
fclose(fid);

