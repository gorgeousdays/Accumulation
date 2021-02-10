clear;
clc;

format long;

A=[2,2,2;3,2,4;1,3,9];
b=[1;0.5;2.5];
mine_Gauss(A,b);

A=[2 5 -6;4 13 -19;-6 -3 -6];
b=[10;19;-30];
LU(A,b);

A=[4 -1 1;4 -8 1;-2 1 5];
b=[7;-21;15];
Jacobi(A,b,[1;2;2],1e-9,100)

Gseidel(A,b,[1;2;2],1e-9,100)
%% Gauss消去法
function mine_Gauss(A,b)
    fprintf('Gauss消去法\n');
    n=size(A,1);
    %消元
    for k = 1:n-1
        A(k+1:n,k) = A(k+1:n,k)/A(k,k);
        A(k+1:n,k+1:n) = A(k+1:n,k+1:n)-A(k+1:n,k)*A(k,k+1:n);
    end

    for j=1:n-1
        b(j) = b(j)/1;
        b(j+1:n) = b(j+1:n)-b(j)*A(j+1:n,j);
    end

    %回代
    for j=n:-1:2
        b(j) = b(j)/A(j,j);
        b(1:j-1) = b(1:j-1)-b(j)*A(1:j-1,j);
    end
    b(1) = b(1)/A(1,1);
    disp('x=');disp(b);
end
%% 矩阵的LU分解
function LU(A,b)
    fprintf('矩阵的LU分解\n');
    n=size(A,1);
    L = zeros(n,n);
    y=zeros(n,1);x=zeros(n,1);
    for i = 1:n
        L(i,i) = 1;
    end
    for k = 1:n-1
        for i = k+1:n
            Aki = A(i,k)/A(k,k);
            L(i,k) = Aki;
            for j = k:n
                A(i,j) = A(i,j) - Aki*A(k,j);
            end
        end
    end
    disp('L = ');disp(L)
    disp('U = ');disp(A)
    
    y(1)=b(1);
    for i=2:n
        y(i)=b(i)-L(i,1:i-1)*y(1:i-1);
    end
    x(n)=y(n)/A(n,n);
    for i=n-1:-1:1
        x(i)=(y(i)-A(i,i+1:n)*x(i+1:n))/A(i,i);
    end
    disp('y= ');disp(y);
    disp('x = ');disp(x);
end
%% Jacobi迭代
function Jacobi(A,b,x0,error,N)
    fprintf('Jacobi迭代\n');
    n=size(A,1);
    x=zeros(1,n);
    for k=1:N
        for i=1:n
            x(i)=(b(i)-A(i,[1:i-1,i+1:n])*x0([1:i-1,i+1:n]))/A(i,i);
        end
        error0=abs(norm(x'-x0));
        x0=x';
        if(error0<error)
            break
        end
    end
    if(k==N)
        fprintf('Jacobi迭代对该方程组不适用');
    end
    disp('x= ');disp(x);
    disp('k = ');disp(k);
end
%% Gauss-Seidel迭代法
function Gseidel(A,b,x0,error,N)
    fprintf('Gauss-Seidel迭代\n');
    n=size(A,1);
    x=zeros(n,1);
    
    for k=1:N
        for i=1:n
            x0(i,1) = (b(i)-A(i,[1:i-1,i+1:n])*x0([1:i-1,i+1:n]))/A(i,i);
        end
        error0=abs(norm(x0-x));
        x=x0;
        if (error0<error)
            break;
        end        
    end
    if(k==N)
        fprintf('Gauss-Seidel迭代对该方程组不适用');
    end
    disp('x=');disp(x);
    disp('k=');disp(k);
end