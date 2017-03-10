// William Thurman        3/9/17
#include <string>

using namespace std;

class ProgotronParser
{
  public:
    char m_token;
	  ProgotronParser()
		{
			get_token(); //Initialize the first token
		}
		
	  void get_token();
		
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
	while(!cin.eof())
	{
		parse.get_token();
	}
  return 0;
}

void ProgotronParser::get_token()
{
	while(m_token == ' ' || m_token == '\n' || m_token == '\0')
	{
	  m_token = cin.get();
		cout << m_token;
	}
	return;
}