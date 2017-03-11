// William Thurman        3/9/17
#include<string>
#include<iostream>

using namespace std;

class ProgotronParser
{
  public:
    char m_token;
    char m_next;
    
    ProgotronParser()
    {
      m_next = cin.peek();
    }
		
	  void get_token();
    void skip_whitespace();
		
    bool parse_int(); 
    bool parse_dec();
    bool parse_str();
    bool parse_id();
    
    bool parse_rel();    // Relation :=   < | > | = | #  
    bool parse_add_op(); // AddOperator :=   + | - | OR | &
    bool parse_mul_op(); // MulOperator :=   * | / | AND
		
    bool parse_exp();    // Expression := SimpleExpression [ Relation SimpleExpression ]
    bool parse_sim_exp();// SimpleExpression := Term { AddOperator Term }
    bool parse_term();   // Term := Factor { MulOperator Factor }
    bool parse_fact();   // Factor :=  integer | decimal | string | identifier | ( Expression ) | ~ Factor

    bool parse_assign(); // Assignment := identifier := Expression !
    bool parse_print();  // PrintStatement := PRINT ( Expression )!
    bool parse_ret();    // RetStatement := RET identifier !
    bool parse_if();     // IfStatement := IF ( Expression ) StatementSequence [ ELSE StatementSequence ] FI
    bool parse_loop();   // LoopStatement := LOOP ( Expression ) StatementSequence POOL

		bool parse_statement();     // Statement := Assignment | PrintStatement | RetStatement | IfStatement | LoopStatement
	  bool parse_statement_seq(); // StatementSequence := Statement { Statement }

    bool parse_param_seq(); // ParamSequence :=  identifier  { , identifier }
    bool parse_func_dec();  // FunctionDeclaration := FUNC identifier ( [ ParamSequence ] ) BEGIN StatementSequence END.

    bool parse_func_seq();  // FunctionSequence := FunctionDeclaration { FunctionDeclaration }
};

int main()
{
  ProgotronParser parse;
  if(parse.parse_dec())
    cout << "DEC" << endl;
  cout << endl;
  return 0;
}


bool ProgotronParser::parse_int()
{
  
  if(m_next == '+' || m_next == '-')
  {
    get_token();
  }
  
  if(isdigit(m_next))
  {
    while(isdigit(m_next))
      get_token();
    
    if(isspace(m_next))
      return true;
    
  }
  return false;
}

bool ProgotronParser::parse_dec()
{
  if(m_next == '+' || m_next == '-')
  {
    get_token();
  }
  
  if(isdigit(m_next))
  {
    while(isdigit(m_next))
      get_token();
    
    if(m_next == '.')
      get_token();
    
    if(isdigit(m_next))
    {
      while(isdigit(m_next))
      {
        get_token();
      }
      
      if(isspace(m_next))
      {
        return true;
      }
    }
  }
  return false;
}

void ProgotronParser::get_token()
{
  m_token = cin.get();
  m_next = cin.peek();
  cout << m_token;
  return;
}

void ProgotronParser::skip_whitespace()
{
  if(isspace(m_next))
  {
    while(isspace(m_next))
    {
      m_token = cin.get();
      m_next = cin.peek();
    }
  }
  return;
}

// bool ProgotronParser::
