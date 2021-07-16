%���ڸ���ת�ƾ����ʱ���·�Ŀɿ��Է���
%% ��ջ�������
close all; clear; clc;

%% �趨������ֵ
p=1e-2;
I_not=[0 1;1 0];

PM_G=[1 0;0 1]; %�ڵ�ǰ��·������

%% ��������PTM����
%����ŵ�PTM
P_nand=[p 1-p;p 1-p;p 1-p;1-p p];
P_not=[1-p p;p 1-p];
M_nand=P_nand';
M_not=P_not';

%����RS�������������PTM 
P_rs_latch=semi_tensor(P_nand,P_nand)

%������R-S��������PTM
P_rs_FF_e=kron(kron(I_not,eye(2)),I_not)*P_rs_latch
%% ��ǰ��·����������߼�PTM
PM_F=kron(eye(2),P_not);
PM_Y1=semi_tensor(semi_tensor(generateF(2,1),P_rs_FF_e),PM_G)
PM_Z1=semi_tensor(semi_tensor(kron(generateF(2,1),eye(2)),P_rs_FF_e),PM_F)
PM_S1=PM_Y1
PM_S2=semi_tensor(semi_tensor(generateF(1,2),kron(eye(2),PM_Z1)),PM_Y1)

%% ��������ITM����
p=0;
%����ŵ�ITM
P_nand=[p 1-p;p 1-p;p 1-p;1-p p];
P_not=[1-p p;p 1-p];
M_nand=P_nand';
M_not=P_not';

%����RS�������������ITM 
P_rs_latch=semi_tensor(P_nand,P_nand)

%������R-S��������ITM
P_rs_FF_e=kron(kron(I_not,eye(2)),I_not)*P_rs_latch
%% ��ǰ��·����������߼�ITM
PM_G=[1 0;0 1];
PM_F=kron(eye(2),P_not);
PM_Y1=semi_tensor(semi_tensor(generateF(2,1),P_rs_FF_e),PM_G)
PM_Z1=semi_tensor(semi_tensor(kron(generateF(2,1),eye(2)),P_rs_FF_e),PM_F)
IM_S1=PM_Y1
IM_S2=semi_tensor(semi_tensor(generateF(1,2),kron(eye(2),PM_Z1)),PM_Y1)

%% ��·�ɿ��ȼ���
V1=ones(1,8)/8
R1=V1*(PM_S1.*IM_S1)

V2=ones(1,32)/32
R2=V2*(PM_S2.*IM_S2)

sum(R1)
sum(R2)

%% �����������
function T=semi_tensor(A,B)
  [i,j] = size(A);
  [m,n]=size(B);
  q=lcm(j,m);
  eye(q/j);
  T1=kron(A,eye(q/j));
  T2=kron(B,eye(q/m));
  T=T1*T2;
end

%% ����F(m,k)
function F=generateF(m,k)
    F=zeros(2^m,2^(m*k));
    for i=1:2^m
        sum=0
        for j=0:k-1
            sum=sum+i*(2^m)^j;
        end
        F(i,sum)=1;
    end
end