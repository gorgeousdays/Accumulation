clear;
clc;

format long;

f=@(x)4/(1+x.^2);
trap(f,0,1);
simpson(f,0,1);
comp_trap(f,0,1,3);
comp_simpson(f,0,1,3);

f=@(x)8./(4+(x+1).^2);
sum_error=zeros(10,2);
for n=1:10
    sum_error(n,1)=gaussf(f,n);
    sum_error(n,2)=abs(sum_error(n,1)-pi);
end
disp("         ����ṹ            ������")
disp(sum_error);
%% ���ι�ʽ
function trap(f,a,b)
    disp("���ι�ʽ:");disp(((b-a)/2)*(f(a)+f(b)));    
end
%% Simpson��ʽ
function simpson(f,a,b)
   disp("Simpson��ʽ:");disp(((b-a)/6)*(f(a)+f(b)+4*f((a+b)/2)));  
end

%% �������ι�ʽ
function comp_trap(f,a,b,n)
   h=(b-a)/n;
   T=0;
   for i=1:n-1
       T=T+f(a+i*h);
   end
   disp("�������ι�ʽ:");disp(h*(f(a)/2+T+f(b)/2));
end

%% ����Simpson��ʽ
function comp_simpson(f,a,b,n)
    h=(b-a)/n;
    S=0;
    for i=0:n-1
        S=S+f(a+i*h)+4*f(a+(i+1/2)*h)+f(a+(i+1)*h);
    end
    disp("����Simpson��ʽ:");disp(h*S/6)
end
%% Gauss�ͻ���
function [x,A]=gauss(n)
    beta=.5./sqrt(1-(2*(1:n-1)).^(-2));
    T=diag(beta,1)+diag(beta,-1);
    [V,D]=eig(T);
    x=diag(D);[x,i]=sort(x);
    A=2*V(1,i).^2;
end
function s=gaussf(fun_f,n)
   [x,A]=gauss(n);
   s=A*fun_f(x);
end
