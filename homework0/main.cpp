#include<cmath>
#include<eigen3/Eigen/Core>
#include<eigen3/Eigen/Dense>
#include<iostream>


int main(){

    // Basic Example of cpp
    std::cout << "Example of cpp \n";
    float a = 1.0, b = 2.0;
    std::cout << a << std::endl;
    std::cout << a/b << std::endl;
    std::cout << std::sqrt(b) << std::endl;
    std::cout << std::acos(-1) << std::endl;
    std::cout << std::sin(30.0/180.0*acos(-1)) << std::endl;

    // Example of vector
    std::cout << "Example of vector \n";
    // vector definition
    Eigen::Vector3f v(1.0f,2.0f,3.0f);
    Eigen::Vector3f w(1.0f,0.0f,0.0f);
    // vector output
    std::cout << "Example of output \n";
    std::cout << v << std::endl;
    // vector add
    std::cout << "Example of add \n";
    std::cout << v + w << std::endl;
    // vector scalar multiply
    std::cout << "Example of scalar multiply \n";
    std::cout << v * 3.0f << std::endl;
    std::cout << 2.0f * v << std::endl;

    std::cout <<"向量点积"<< v.transpose()*w << std::endl;


    // Example of matrix
    std::cout << "Example of matrix \n";
    // matrix definition
    Eigen::Matrix3f i,j;
    i << 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0;
    j << 2.0, 3.0, 1.0, 4.0, 6.0, 5.0, 9.0, 7.0, 8.0;
    // matrix output
    std::cout << "Example of output \n";
    std::cout << i << std::endl;
    // std::cout<<std::endl;
    // std::cout<<j<<std::endl;
    // matrix add i + j
    std::cout << "Example of matrix add \n";
    std::cout<<i+j<<std::endl;
    // matrix scalar multiply i * 2.0
    std::cout << "Example of matrix scalar multiply \n";
    std::cout<<i*2.0<<std::endl;
    // matrix multiply i * j
    std::cout << "Example of matrix multiply \n";
    std::cout<<i*j<<std::endl;
    // matrix multiply vector i * v
    std::cout << "Example of matrix multiply vector \n";
    std::cout<<i*v<<std::endl;


    // //my test
    // std::cout<<"other\n";
    // std::cout<<"i转置\n"<<i.transpose()<<std::endl;
    // std::cout<<"i共轭\n"<<i.conjugate()<<std::endl;
    // std::cout<<"i共轭转置\n"<<i.adjoint()<<std::endl;


    Eigen::Vector3f p(2.0f,1.0f,1.0f);
    
    //抽取vector3中的元素：可直接用x()或者当作数组用[]
    std::cout<<"this is "<<p.x()<<std::endl;

    float angle=45.0/180.0*acos(-1);
    Eigen::Matrix3f trans;
    trans<<cos(angle),-sin(angle),1,sin(angle),cos(angle),2,0,0,1;
    std::cout<<"旋转矩阵:\n"<<trans<<std::endl;
    std::cout<<"res:\n"<<trans*p<<std::endl;


    Eigen::Vector3d v(1,2,3);
    Eigen::Vector3d w(0,1,2);
 
    std::cout << "Dot product: " << v.dot(w) << std::endl;
    double dp = v.adjoint()*w; // automatic conversion of the inner product to a scalar
    std::cout << "Dot product via a matrix product: " << dp <<std::endl;
    std::cout << "Cross product:\n" << v.cross(w) << std::endl;

    return 0;
}