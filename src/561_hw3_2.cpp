//============================================================================
// Name        : 561_hw3.cpp
// Author      : wangbo
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

//object
class fact{
public:
    string fact_name;
    string arg1;
    string arg2;
};

//data
fact final_target;
int  knowledge_size;
vector<vector<fact> > knowledge_base;

//function
void normalize_string(string str, fact &fc){
	 int first_para=str.find('(');
		    int coma=str.find(',');
		    fc.fact_name=str.substr(0,first_para);
		    if( coma == string::npos ){
		    fc.arg1=str.substr(first_para+1,str.size()-first_para-2);
		    }else{
			    fc.arg1=str.substr(first_para+1,coma-first_para-1);
			    fc.arg2=str.substr(coma+1,str.size()-coma-2);
		    }
}

string UNIFY(fact rhs,fact goal, string sub,bool relation){
	if(rhs.fact_name.compare(goal.fact_name)!=0) return "failure";
	int rhs_arg_num=2,goal_arg_num=2;
	if(rhs.arg2=="") rhs_arg_num=1;
	if(goal.arg2=="") goal_arg_num=1;
	if(rhs_arg_num!=goal_arg_num) return "failure";
    if(sub=="x"){
      if(rhs_arg_num==1){
    	if(goal.arg1=="x"){
    			if(rhs.arg1=="x") return sub;
    			else{
    				if(relation==false)
    					return rhs.arg1;
    				else
    					return sub;
    			}
    			}
    	else{
    			if(rhs.arg1=="x") return goal.arg1;
    			else{
    				if(goal.arg1!=rhs.arg1) return "failure";
    				else return sub;
    			}
    	}}
      else{
    	  if(goal.arg1=="x"&&goal.arg2=="x"&&rhs.arg1=="x"&&rhs.arg2=="x") return sub;
    	  if(goal.arg1=="x"&&goal.arg2=="x"&&rhs.arg1=="x"&&rhs.arg2!="x") return rhs.arg2;
    	  if(goal.arg1=="x"&&goal.arg2=="x"&&rhs.arg1!="x"&&rhs.arg2!="x"){
    		  if(rhs.arg1==rhs.arg2){
    			  if(relation==true){ return sub;
    			  }else{
    			  return rhs.arg1;}
    		  }
    		  else return "failure"; }
    	  if(goal.arg1=="x"&&goal.arg2=="x"&&rhs.arg1!="x"&&rhs.arg2=="x") return rhs.arg1;
    	  if(goal.arg1=="x"&&goal.arg2!="x"&&rhs.arg1=="x"&&rhs.arg2=="x") return goal.arg2;;
    	  if(goal.arg1=="x"&&goal.arg2!="x"&&rhs.arg1=="x"&&rhs.arg2!="x"){if(rhs.arg2==goal.arg2) return sub; else return "failure"; }
    	  if(goal.arg1=="x"&&goal.arg2!="x"&&rhs.arg1!="x"&&rhs.arg2!="x"){
    		  if(rhs.arg2!=goal.arg2)
    			  return "failure";
    		  else{
    			  if(relation==true){
    				  return sub;
    			  }else{
    			      return rhs.arg1;}
    		  }
    	  }
    	  if(goal.arg1=="x"&&goal.arg2!="x"&&rhs.arg1!="x"&&rhs.arg2=="x") return goal.arg2;
    	  if(goal.arg1!="x"&&goal.arg2=="x"&&rhs.arg1=="x"&&rhs.arg2=="x") return goal.arg1;
    	  if(goal.arg1!="x"&&goal.arg2=="x"&&rhs.arg1=="x"&&rhs.arg2!="x"){if(rhs.arg2!=goal.arg1) return "failure"; else return rhs.arg2; }
    	  if(goal.arg1!="x"&&goal.arg2=="x"&&rhs.arg1!="x"&&rhs.arg2!="x"){
    		  if(rhs.arg1!=goal.arg1)
    			  return "failure";
    		  else{
    			  if(relation==true){
    				  return sub;}
    			  else{
    			  return rhs.arg2;}
    		  }
    	  }
    	  if(goal.arg1!="x"&&goal.arg2=="x"&&rhs.arg1!="x"&&rhs.arg2=="x"){if(rhs.arg1!=goal.arg1) return "failure"; else return sub; }
    	  if(goal.arg1!="x"&&goal.arg2!="x"&&rhs.arg1=="x"&&rhs.arg2=="x"){if(goal.arg1!=goal.arg2)return "failure"; else return goal.arg1;}
    	  if(goal.arg1!="x"&&goal.arg2!="x"&&rhs.arg1=="x"&&rhs.arg2!="x"){if(rhs.arg2!=goal.arg2) return "failure"; else return goal.arg1; }
    	  if(goal.arg1!="x"&&goal.arg2!="x"&&rhs.arg1!="x"&&rhs.arg2!="x"){if(rhs.arg1!=goal.arg1) return "failure"; else{ if(rhs.arg2!=goal.arg2)return "failure"; else return sub;} }
    	  if(goal.arg1!="x"&&goal.arg2!="x"&&rhs.arg1!="x"&&rhs.arg2=="x"){if(rhs.arg1!=goal.arg1) return "failure"; else return goal.arg2; }
    	}
    }
    else{
    /*  if(goal.arg1=="x") goal.arg1=sub;  if(goal.arg2=="x") goal.arg2=sub; if(rhs.arg1=="x") rhs.arg1=sub; if(rhs.arg2=="x") rhs.arg2=sub;
       if(goal.arg1!=rhs.arg1) return "failure";
       else{
    	   if(goal.arg2!=rhs.arg2) return "failure";
    	   else return sub;
       }*/
    	if(goal.arg1!=rhs.arg1 && rhs.arg1!="x") return "failure";
    	if(rhs_arg_num==2){
    		if(goal.arg2!=rhs.arg2 && rhs.arg2!="x") return "failure";
    		if(rhs.arg1=="x"&&rhs.arg2=="x"&&goal.arg1!=goal.arg2) return "failure";
    	}
    	if(rhs.arg1=="x") return  goal.arg1;
    	if(rhs_arg_num==2){
    	if(rhs.arg2=="x"){
    		return goal.arg2;
    	}
    	}
    	return sub;
	}
}
fact SUBST(string sub,fact first){
	if(sub=="x") return first;
	fact temp_fact;
	temp_fact.fact_name=first.fact_name; temp_fact.arg1=first.arg1; temp_fact.arg2= first.arg2;
	if(first.arg1=="x") temp_fact.arg1=sub;
	if(first.arg2=="x") temp_fact.arg2=sub;
	return temp_fact;
}
string FOL_BC_AND(vector<fact> goals, string sub);

string FOL_BC_OR(fact goal,string sub){
      for(int i=0;i<knowledge_size;i++){
    	  int temp_last=knowledge_base[i].size();
    	  ////cout<<"check"<<knowledge_base[i][temp_last-1].fact_name<<"-"<<knowledge_base[i][temp_last-1].arg1<<"-"<<knowledge_base[i][temp_last-1].arg2<<endl;
    	  if(knowledge_base[i][temp_last-1].fact_name==goal.fact_name){
                vector<fact> temp_goals;
                                        //cout<<"--------------------"<<endl;
                	                    //cout<<"OR load_in goals"<<endl;
                for(int j=0;j<temp_last-1;j++){
                		temp_goals.push_back(knowledge_base[i][j]);
                		                //cout<<knowledge_base[i][j].fact_name<<"-"<<knowledge_base[i][j].arg1<<"-"<<knowledge_base[i][j].arg2<<endl;
                }
                                         //cout<<"--------------------"<<endl;
            	                         //cout<<"OR:  "<<knowledge_base[i][temp_last-1].fact_name<<"  sub:"<<sub<<"  "<<knowledge_base[i][temp_last-1].fact_name<<"-"<<knowledge_base[i][temp_last-1].arg1<<"-"<<knowledge_base[i][temp_last-1].arg2<<">>"<<goal.fact_name<<"-"<<goal.arg1<<"-"<<goal.arg2<<"   ";
            	string new_sub;
            	if(temp_last!=1){
                	new_sub=UNIFY(knowledge_base[i][temp_last-1],goal,sub,true);
                }else{
                	new_sub=UNIFY(knowledge_base[i][temp_last-1],goal,sub,false);
                }
                //cout<<new_sub<<endl;
                if(new_sub!="failure"&&new_sub!="x"){
                	for(int j=0;j<temp_last-1;j++){
                		if(temp_goals[j].arg1=="x") temp_goals[j].arg1=new_sub;
                		if(temp_goals[j].arg2=="x") temp_goals[j].arg2=new_sub;
                	}
                }
            	 string temp_result=FOL_BC_AND(temp_goals,new_sub);
            	if(temp_result!="not_matched") return temp_result;
    	  }
      }
      return "not_matched";
}

string FOL_BC_AND(vector<fact> goals, string sub){
	if(sub=="failure") return "not_matched";
	if(goals.size()==0) { return sub;}
	                                    //cout<<"--------------------"<<endl;
	                                     //cout<<"AND load_up goals"<<endl;
	                                    for(int k=0;k<goals.size();k++){
		                                   //cout<<goals[k].fact_name<<"-"<<goals[k].arg1<<"-"<<goals[k].arg2<<endl;
	                                     }
	                                      //cout<<"--------------------"<<endl;
	                                      //cout<<"AND_BEFORE_SUBST: "<<"sub:"<<sub<<" "<<goals[goals.size()-1].fact_name<<"-"<<goals[goals.size()-1].arg1<<"-"<<goals[goals.size()-1].arg2<<endl;
	                                      //cout<<"AND_SUBST: "<<"sub:"<<sub<<" "<<SUBST(sub,goals[goals.size()-1]).fact_name<<"-"<<SUBST(sub,goals[goals.size()-1]).arg1<<"-"<<SUBST(sub,goals[goals.size()-1]).arg2<<endl;
	string temp_sub=FOL_BC_OR(SUBST(sub,goals[goals.size()-1]),sub);
	goals.pop_back();
	if(temp_sub!="not_matched"){
		string temp_sub_or=FOL_BC_AND(goals,temp_sub);
		if(temp_sub_or!="not_matched")
			return temp_sub_or;
	}
	return "not_matched";
}
int main() {
	ifstream input;
	input.open("input.txt");
    string temp_line;
	    //input the target data
	    input>>temp_line;
	    normalize_string(temp_line, final_target);
	    //input the size
	    input>>knowledge_size;
	    //input the database
        for(int i=0;i<knowledge_size;i++){
        	input>>temp_line;
            vector<fact> temp_rule;
            fact temp_fact;
             while(temp_line.find('&')!=string::npos){
            	int at_location=temp_line.find('&');
            	normalize_string(temp_line.substr(0,at_location),temp_fact);
             	temp_rule.push_back(temp_fact);
             	temp_fact.fact_name="";temp_fact.arg1="";temp_fact.arg2="";
            	temp_line=temp_line.substr(at_location+1,temp_line.size());
            }
             if(temp_line.find('=>')!=string::npos){
            	 int imply_location=temp_line.find('=>');
            	 normalize_string(temp_line.substr(0,imply_location-1),temp_fact);
            	 temp_rule.push_back(temp_fact);
            	 temp_fact.fact_name="";temp_fact.arg1="";temp_fact.arg2="";
            	 temp_line=temp_line.substr(imply_location+1,temp_line.size());
             }
                 normalize_string(temp_line,temp_fact);
                 temp_rule.push_back(temp_fact);
                 temp_fact.fact_name="";temp_fact.arg1="";temp_fact.arg2="";
                 knowledge_base.push_back(temp_rule);
        }
	    input.close();
                                     /*  for(int i=0;i<knowledge_size;i++){
        	                               int temp_size=knowledge_base[i].size();
        	                               for(int j=0;j<temp_size;j++){
        	                            	   //cout<<knowledge_base[i][j].fact_name<<"-"<<knowledge_base[i][j].arg1<<"-"<<knowledge_base[i][j].arg2<<"  ";
        	                               }
        	                               //cout<<endl;
                                         }*/
	    ofstream output;
	    output.open("output.txt");
	    if(FOL_BC_OR(final_target,"x")!="not_matched")
	    	output<<"TRUE";
	    else
	    	output<<"FALSE";
	    output.close();
	return 0;
}
