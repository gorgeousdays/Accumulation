%基于概率转移矩阵的时序电路的可靠性分析
%% 清空环境变量
close all; clear; clc;

%% 设定参数初值
p=1e-2;
I_not=[0 1;1 0];

PM_G=[1 0;0 1]; %在当前电路环境下

%% 触发器的PTM计算
%与非门的PTM
P_nand=[p 1-p;p 1-p;p 1-p;1-p p];
P_not=[1-p p;p 1-p];
M_nand=P_nand';
M_not=P_not';

%基本RS与非门锁存器的PTM 
P_rs_latch=semi_tensor(P_nand,P_nand)

%正边沿R-S触发器的PTM
P_rs_FF_e=kron(kron(I_not,eye(2)),I_not)*P_rs_latch
%% 当前电路的输入输出逻辑PTM
PM_F=kron(eye(2),P_not);
PM_Y1=semi_tensor(semi_tensor(generateF(2,1),P_rs_FF_e),PM_G)
PM_Z1=semi_tensor(semi_tensor(kron(generateF(2,1),eye(2)),P_rs_FF_e),PM_F)
PM_S1=PM_Y1
PM_S2=semi_tensor(semi_tensor(generateF(1,2),kron(eye(2),PM_Z1)),PM_Y1)

%% 触发器的ITM计算
p=0;
%与非门的ITM
P_nand=[p 1-p;p 1-p;p 1-p;1-p p];
P_not=[1-p p;p 1-p];
M_nand=P_nand';
M_not=P_not';

%基本RS与非门锁存器的ITM 
P_rs_latch=semi_tensor(P_nand,P_nand)

%正边沿R-S触发器的ITM
P_rs_FF_e=kron(kron(I_not,eye(2)),I_not)*P_rs_latch
%% 当前电路的输入输出逻辑ITM
PM_G=[1 0;0 1];
PM_F=kron(eye(2),P_not);
PM_Y1=semi_tensor(semi_tensor(generateF(2,1),P_rs_FF_e),PM_G)
PM_Z1=semi_tensor(semi_tensor(kron(generateF(2,1),eye(2)),P_rs_FF_e),PM_F)
IM_S1=PM_Y1
IM_S2=semi_tensor(semi_tensor(generateF(1,2),kron(eye(2),PM_Z1)),PM_Y1)

%% 电路可靠度计算
V1=ones(1,8)/8
R1=V1*(PM_S1.*IM_S1)

V2=ones(1,32)/32
R2=V2*(PM_S2.*IM_S2)

sum(R1)
sum(R2)

%% 计算半张量积
function T=semi_tensor(A,B)
  [i,j] = size(A);
  [m,n]=size(B);
  q=lcm(j,m);
  eye(q/j);
  T1=kron(A,eye(q/j));
  T2=kron(B,eye(q/m));
  T=T1*T2;
end

%% 生成F(m,k)
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