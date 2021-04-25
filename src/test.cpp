#include <libsnark/common/default_types/r1cs_gg_ppzksnark_pp.hpp>
#include <libsnark/zk_proof_systems/ppzksnark/r1cs_gg_ppzksnark/r1cs_gg_ppzksnark.hpp>
#include <libsnark/gadgetlib1/pb_variable.hpp>
#include<iostream>
#include<stdio.h>
#include<vector>
#include <string>  
#include <vector>  
#include <fstream>  
#include <sstream>
using namespace libsnark;
using namespace std;
int arr_fc_input[3][12];
int arr_fc_weight[6][12];
int arr_fc_bias[6];
int arr_fc_output[3][6];
int arr_fc_sym[18][12];

class read_parms
{
   public:
      void  read_fc_input();
      void  read_fc_weight();
      void  read_fc_bias();
      void  read_fc_output();
};
void read_parms:: read_fc_input ()
{
    ifstream inFile("./csv/fc1_input_nume.csv", ios::in);  
    string lineStr;  
    vector<vector<string>> strArray;  
    int i,j;
    i=0;
    char* end;
    cout<<"fc1_input_nume"<<endl<<endl;
    if(inFile.fail())
        cout<<"读取文件失败"<<endl;
    while (getline(inFile, lineStr))  
    {  
        j=0;
        // 打印整行字符串  
        // cout << lineStr << endl;  
        // 存成二维表结构  
        stringstream ss(lineStr);  
        string str;  
        vector<string> lineArray;  
        // 按照逗号分隔  
        while (getline(ss, str, ','))  
        {
            arr_fc_input[i][j]=static_cast<int>(strtol(str.c_str(),&end,10));              //string -> int
            j++;
        }
        i++;     
   //     strArray.push_back(lineArray);  
    }  
      for(int i=0;i<3;i++)
      {
          for(int j=0;j<12;j++)
              cout<<arr_fc_input[i][j]<<" ";
          cout<<endl;
      }   
}
void read_parms:: read_fc_weight ()
{
    ifstream inFile("./csv/fc1_weight_nume.csv", ios::in);  
    string lineStr;  
    vector<vector<string>> strArray;  
    int i,j;
    i=0;
    char* end;
    cout<<"fc1_weight_nume"<<endl<<endl;
    if(inFile.fail())
        cout<<"读取文件失败"<<endl;
    while (getline(inFile, lineStr))  
    {  
        j=0;
        // 打印整行字符串  
        // cout << lineStr << endl;  
        // 存成二维表结构  
        stringstream ss(lineStr);  
        string str;  
        vector<string> lineArray;  
        // 按照逗号分隔  
        while (getline(ss, str, ','))  
        {
            arr_fc_weight[i][j]=static_cast<int>(strtol(str.c_str(),&end,10));              //string -> int
            j++;
        }
        i++;     
   //     strArray.push_back(lineArray);  
    }  
      for(int i=0;i<6;i++)
      {
          for(int j=0;j<12;j++)
              cout<<arr_fc_weight[i][j]<<" ";
          cout<<endl;
      }  
}
void read_parms:: read_fc_bias ()
{
    ifstream inFile("./csv/fc1_bias_nume.csv", ios::in);  
    string lineStr;  
    vector<vector<string>> strArray;  
    int i;
    i=0;
    char* end;
     cout<<"fc1_bias_nume"<<endl;
    if(inFile.fail())
        cout<<"读取文件失败"<<endl<<endl;
    while (getline(inFile, lineStr))  
    {  
        // 打印整行字符串  
        // cout << lineStr << endl;  
        // 存成二维表结构  
        stringstream ss(lineStr);  
        string str;  
        vector<string> lineArray;  
        // 按照逗号分隔  
        while (getline(ss, str))  
        {
            arr_fc_bias[i]=static_cast<int>(strtol(str.c_str(),&end,10));              //string -> int
        }
        i++;     
   //     strArray.push_back(lineArray);  
    }  
      for(int i=0;i<6;i++)
      {
            cout<<arr_fc_bias[i]<<" ";
            cout<<endl;
      } 
}
void read_parms:: read_fc_output ()
{
    ifstream inFile("./csv/fc1_output_nume.csv", ios::in);  
    string lineStr;  
    vector<vector<string>> strArray;  
    int i,j;
    i=0;
    char* end;
     cout<<"fc1_output_nume"<<endl<<endl;
    if(inFile.fail())
        cout<<"读取文件失败"<<endl;
    while (getline(inFile, lineStr))  
    {  
        j=0;
        // 打印整行字符串  
        // cout << lineStr << endl;  
        // 存成二维表结构  
        stringstream ss(lineStr);  
        string str;  
        vector<string> lineArray;  
        // 按照逗号分隔  
        while (getline(ss, str, ','))  
        {
            arr_fc_output[i][j]=static_cast<int>(strtol(str.c_str(),&end,10));              //string -> int
            j++;
        }
        i++;     
   //     strArray.push_back(lineArray);  
    }  
      for(int i=0;i<3;i++)
      {
          for(int j=0;j<6;j++)
              cout<<arr_fc_output[i][j]<<" ";
          cout<<endl;
      } 
}

int main () {
    typedef libff::Fr<default_r1cs_gg_ppzksnark_pp> FieldT;

    // Initialize the curve parameters
    default_r1cs_gg_ppzksnark_pp::init_public_params();
  
    // Create protoboard
    protoboard<FieldT> pb;
    //read fc1_params
    read_parms read;
    read.read_fc_input();
    read.read_fc_bias();
    read.read_fc_weight();
    read.read_fc_output();
    // Define variables
    pb_variable<FieldT> fc_output[3][6];
    pb_variable<FieldT> fc_input[3][12];
    pb_variable<FieldT> fc_bias[6];
    pb_variable<FieldT> fc_weight[6][12];
    pb_variable<FieldT> sym[18][12];  //12*(3*6)
    //乘法拍平，input和weight每两个元素相乘,生成新数组
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j <6 ; j++)
        {
            for (int m = 0; m <12; m++)
            {   
                 arr_fc_sym[i*6+j][m] = arr_fc_input[i][m]*arr_fc_weight[j][m];
            }    
        }   
    }
    // Allocate variables to protoboard
    // The strings (like "x") are only for debugging purposes  
    for ( int i = 0; i < 3; i++ )
    {   
        for(int j = 0; j < 6; j++)
        {
        std::string pi = "out" + std::to_string(i)+"_"+std::to_string(j); 
        fc_output[i][j].allocate(pb,pi);
        pb.val(fc_output[i][j]) = arr_fc_output[i][j];
        }
    }
    for ( int i = 0; i < 3; i++ )
    {   
        for(int j = 0; j <12; j++)
        {
        std::string pi = "Sym_input" + std::to_string(i)+"_"+std::to_string(j); 
        fc_input[i][j].allocate(pb,pi);
        pb.val(fc_input[i][j]) = arr_fc_input[i][j]; 
        }
    }
    for ( int i = 0; i < 6; i++ )
    {   
        std::string pi = "Sym_bias" + std::to_string(i);
        fc_bias[i].allocate(pb,pi);
        pb.val(fc_bias[i]) = arr_fc_bias[i];
    }
    for ( int i = 0; i < 6; i++ )
    {   
        for(int j = 0; j < 12; j++)
        {
        std::string pi = "Sym_weight" + std::to_string(i)+"_"+std::to_string(j); 
        fc_weight[i][j].allocate(pb,pi);
        pb.val(fc_weight[i][j]) = arr_fc_weight[i][j];
        }
    }
     for ( int i = 0; i < 18; i++ )
    {   
        for(int j = 0; j < 12; j++)
        {
        std::string pi = "Sym_" + std::to_string(i)+"_"+std::to_string(j); 
        sym[i][j].allocate(pb,pi);
        pb.val(sym[i][j]) = arr_fc_sym[i][j]; 
        }
    }
    
    // This sets up the protoboard variables
    // so that the first one (out) represents the public
    // input and the rest is private input
    pb.set_input_sizes(54);

    // Add R1CS constraints to protoboard
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j <6 ; j++)
        {
            for (int m = 0; m <12; m++)
            {  
                 pb.add_r1cs_constraint(r1cs_constraint<FieldT>(fc_input[i][m], fc_weight[j][m], sym[i*6+j][m]));
            }    
        }   
    }
    //和：对应output上每一个点
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            pb.add_r1cs_constraint(r1cs_constraint<FieldT>(sym[i*6+j][0]+sym[i*6+j][1]+sym[i*6+j][2]+sym[i*6+j][3]+sym[i*6+j][4]+sym[i*6+j][5]+sym[i*6+j][6]+sym[i*6+j][7]+sym[i*6+j][8]+sym[i*6+j][9]+sym[i*6+j][10]+sym[i*6+j][11]+fc_bias[j], 1, fc_output[i][j]));   
        }
    }
    
    const r1cs_constraint_system<FieldT> constraint_system = pb.get_constraint_system();

    // generate keypair
    const r1cs_gg_ppzksnark_keypair<default_r1cs_gg_ppzksnark_pp> keypair = r1cs_gg_ppzksnark_generator<default_r1cs_gg_ppzksnark_pp>(constraint_system);

    // Add public input and witness values
    // generate proof
    const r1cs_gg_ppzksnark_proof<default_r1cs_gg_ppzksnark_pp> proof = r1cs_gg_ppzksnark_prover<default_r1cs_gg_ppzksnark_pp>(keypair.pk, pb.primary_input(), pb.auxiliary_input());

    // verify
    bool verified = r1cs_gg_ppzksnark_verifier_strong_IC<default_r1cs_gg_ppzksnark_pp>(keypair.vk, pb.primary_input(), proof);

    cout << "Number of R1CS constraints: " << constraint_system.num_constraints() << endl;
    cout << "Primary (public) input: " << pb.primary_input() << endl;
    cout << "Auxiliary (private) input: " << pb.auxiliary_input() << endl;
    cout << "Verification status: " << verified << endl;

    return 0;
}
