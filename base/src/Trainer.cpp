/*
 * Phoenix2D (RoboCup Soccer Simulation 2D League)
 * Copyright (c) 2013, 2014 Nelson Ivan Gonzalez
 *
 * This file is part of Phoenix2D.
 *
 * Phoenix2D is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Phoenix2D is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Phoenix2D.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @file Trainer.cpp
 *
 * @author Nelson Ivan Gonzalez
 */

#include <vector>
#include <stack>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <boost/regex.hpp>
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include "Trainer.hpp"
#include "Commands.hpp"
#include "Game.hpp"

#define _IF_       0x02
#define _ELSE_     0x03
#define _WHILE_    0x04

#define _ASSTXT_   0x10
#define _EQUAL_    0x12
#define _PLUS_     0x13
#define _MINUS_    0x14
#define _TIMES_    0x15
#define _DIVIDE_   0x16
#define _LESS_     0x17
#define _GREATER_  0x18
#define _LEQ_      0x19
#define _GEQ_      0x1A
#define _ASSGMNT_  0x1B
#define _NEQUAL_   0x1C
#define _CMP_	   0x1D

#define _FUNC_     0x20
#define _CONTROL_  0x21
#define _NODE_     0x23
#define _CONST_    0x24
#define _EXPRS_    0x25

#define _ENDDO_    0x31
#define _ENDIF_    0x32
#define _ENDWHILE_ 0x33

#define _DO_ 	   0x40
#define _WAIT_	   0x41

/***********
 * Structs *
 ***********/

namespace phx {

struct function {
	std::string name;
	std::vector<std::string> tokens;
};

struct expression_node {
	int op;
	std::string node;
};

struct expression {
	std::string root;
	std::vector<expression_node> nodes;
};

struct control {
	int type;
	expression expr;
};

}

BOOST_FUSION_ADAPT_STRUCT(
	phx::function,
	(std::string, name)
	(std::vector<std::string>, tokens)
)

BOOST_FUSION_ADAPT_STRUCT(
	phx::expression_node,
	(int, op)
	(std::string, node)
)

BOOST_FUSION_ADAPT_STRUCT(
	phx::expression,
	(std::string, root)
	(std::vector<phx::expression_node>, nodes)
)

BOOST_FUSION_ADAPT_STRUCT(
	phx::control,
	(int, type)
	(phx::expression, expr)
)

namespace Phoenix {

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

pthread_t thread_trainer = 0;
static bool cycle_flag = false;
static pthread_cond_t cycle_cond = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t cycle_mutex = PTHREAD_MUTEX_INITIALIZER;
static bool running = false;
static bool newExecution = true;
static Commands* commands;

/***********
 * Parsers *
 ***********/

template <typename Iterator>
struct function_parser : qi::grammar<Iterator, phx::function(), ascii::space_type> {
	function_parser() : function_parser::base_type(start) {
		using qi::lexeme;
		using ascii::char_;
		name %= lexeme[+char_("_a-zA-Z")];
		tokens %= *lexeme[+char_("$_a-zA-Z0-9.-")] % ',';
		start %= name >> '(' >> tokens >> ')' >> ';';
	}
	qi::rule<Iterator, std::string(), ascii::space_type> name;
	qi::rule<Iterator, std::vector<std::string>(), ascii::space_type> tokens;
	qi::rule<Iterator, phx::function(), ascii::space_type> start;
};

template <typename Iterator>
struct expression_parser : qi::grammar<Iterator, phx::expression(), ascii::space_type> {
	expression_parser() : expression_parser::base_type(start) {
		using qi::lexeme;
		using ascii::char_;
		using qi::lit;
		using qi::_val;
		start %= var >> +node >> ';';
		node %= op >> var;
		op = lit("=") [_val = _ASSGMNT_] |
			 lit(":") [_val = _ASSTXT_]  |
		     lit(">") [_val = _GREATER_] |
		     lit("<") [_val = _LESS_]    |
		     lit(">=")[_val = _GEQ_]     |
		     lit("<=")[_val = _LEQ_]     |
		     lit("==")[_val = _EQUAL_]   |
		     lit("<>")[_val = _CMP_]     |
		     lit("!=")[_val = _NEQUAL_]  |
		     lit("+") [_val = _PLUS_]    |
		     lit("-") [_val = _MINUS_]   |
		     lit("*") [_val = _TIMES_]   |
		     lit("/") [_val = _DIVIDE_];
		var %= lexeme[+char_("$_a-zA-Z0-9.-")];
	}
	qi::rule<Iterator, phx::expression(), ascii::space_type> start;
	qi::rule<Iterator, phx::expression_node(), ascii::space_type> node;
	qi::rule<Iterator, int(), ascii::space_type> op;
	qi::rule<Iterator, std::string(), ascii::space_type> var;
};

template <typename Iterator>
struct control_parser : qi::grammar<Iterator, phx::control(), ascii::space_type> {
	control_parser() : control_parser::base_type(start) {
		using qi::lit;
		using qi::_val;
		using qi::int_;
		using qi::lexeme;
		using ascii::char_;
		start %= type >> '(' >> expr >>  ')';
		type = lit("if")[_val = _IF_] | lit("while")[_val = _WHILE_];
		expr %= var >> +node;
		node %= op >> var;
		op = lit("=") [_val = _ASSGMNT_] |
			 lit(":") [_val = _ASSTXT_]  |
		     lit("<>")[_val = _CMP_]     |
		     lit(">") [_val = _GREATER_] |
		     lit("<") [_val = _LESS_]    |
		     lit(">=")[_val = _GEQ_]     |
		     lit("<=")[_val = _LEQ_]     |
		     lit("==")[_val = _EQUAL_]   |
		     lit("!=")[_val = _NEQUAL_]  |
		     lit("+") [_val = _PLUS_]    |
		     lit("-") [_val = _MINUS_]   |
		     lit("*") [_val = _TIMES_]   |
		     lit("/") [_val = _DIVIDE_];
		var %= lexeme[+char_("$_a-zA-Z0-9")];
	}
	qi::rule<Iterator, phx::control(), ascii::space_type> start;
	qi::rule<Iterator, int(), ascii::space_type> type;
	qi::rule<Iterator, phx::expression(), ascii::space_type> expr;
	qi::rule<Iterator, phx::expression_node(), ascii::space_type> node;
	qi::rule<Iterator, int(), ascii::space_type> op;
	qi::rule<Iterator, std::string(), ascii::space_type> var;
};

template <typename Iterator>
struct close_parser : qi::grammar<Iterator, int(), ascii::space_type> {
	close_parser() : close_parser::base_type(start) {
		using qi::lit;
		using qi::_val;
		start = lit("_enddo")  [_val = _ENDDO_]    |
			    lit("endif")   [_val = _ENDIF_]    |
			    lit("endwhile")[_val = _ENDWHILE_] |
			    lit("else")    [_val = _ELSE_];
	}
	qi::rule<Iterator, int(), ascii::space_type> start;
};

/***********************
 * Pre-built functions *
 ***********************/

std::map<std::string, char> varsmap;
std::map<std::string, double> vars;
std::map<std::string, std::string> texts;

double getVarValue(std::string varstr) {
	double val = 0.0;
	std::map<std::string, double>::iterator var = vars.find(varstr);
	if (var != vars.end()) {
		val = var->second;
	} else {
		std::cerr << "Variable " << varstr << " has not been defined" << std::endl;
	}
	return val;
}

std::string getTextValue(std::string varstr) {
	std::string str("");
	std::map<std::string, std::string>::iterator var = texts.find(varstr);
	if (var != texts.end()) {
		str = var->second;
	} else {
		std::cerr << "Text " << varstr << " has not been defined" << std::endl;
	}
	return str;
}

void onSleep(int cycles) {
	cycle_flag = false;
	//std::cout << "Sleeping for " << cycles << std::endl;
	for (int i = 0; i < cycles; ++i) {
		int success = pthread_mutex_lock(&cycle_mutex);
		if (success) {
			std::cerr << "Game::nextCycle() -> can not lock mutex" << std::endl;
		}
		while (!cycle_flag) {
			success = pthread_cond_wait(&cycle_cond, &cycle_mutex);
			if (success) {
				std::cerr << "Game::nextCycle() -> can not wait for condition" << std::endl;
			}
		}
		cycle_flag = false;
		success = pthread_mutex_unlock(&cycle_mutex);
		if (success) {
			std::cerr << "Game::nextCycle() -> can not unlock mutex" << std::endl;
		}
	}
}

void onPrint(std::string arg) {
	if (arg[0] == '$') {
		double val = getVarValue(arg);
		std::cout << val << std::endl;
	} else {
		std::cout << arg << std::endl;
	}
}

void onPlayMode(std::string play_mode) {
	Commands::changeMode(play_mode);
}

void onSend() {
	Commands::sendCommands();
}

/*
 * The server only recognizes (ball) although (b), (Ball) and (B) are also defined
 */
void onBall(double x, double y) {
	Commands::moveObject("(ball)", x, y);
}

void onRecover() {
	Commands::recover();
}

void onStart() {
	Commands::start();
}

/***********
 * Runtime *
 ***********/

struct address {
	address() : type(-1), pointer(-1), left_branch(-1), right_branch(-1) {};
	int type;
	int pointer;
	int left_branch;
	int right_branch;
};

std::vector<phx::function> functions;
std::vector<phx::expression> expressions;
std::vector<phx::control> controls;
std::vector<std::vector<address> > branchs;
std::stack<int> branchs_stack;

double evaluateExpressionNode(std::string prev, std::deque<phx::expression_node> queue) {
	double val = 0.0;
	if (prev[0] == '$') {
		val = getVarValue(prev);
	} else {
		val = atof(prev.c_str());
	}
	if (queue.size() > 0) {
		phx::expression_node first = queue.front();
		queue.pop_front();
		switch (first.op) {
		case _PLUS_:
			{
				val += evaluateExpressionNode(first.node, queue);
				break;
			}
		case _MINUS_:
			{
				val -= evaluateExpressionNode(first.node, queue);
				break;
			}
		case _TIMES_:
			{
				val *= evaluateExpressionNode(first.node, queue);
				break;
			}
		case _DIVIDE_:
			{
				double temp = evaluateExpressionNode(first.node, queue);
				if (temp != 0.0) {
					val /= temp;
				} else {
					std::cerr << "Dividing by zero" << std::endl;
					val = 0.0;
				}
				break;
			}
		default:
			{
				std::cerr << "Operator not implemented" << std::endl;
				break;
			}
		}
	}
	return val;
}

int evaluateExpression(phx::expression expression) {
	int return_value = 0;
	if (expression.nodes.size() > 0) {
		std::deque<phx::expression_node> queue(expression.nodes.begin(), expression.nodes.end());
		phx::expression_node first = queue.front();
		queue.pop_front();
		switch (first.op) {
		case _ASSGMNT_:
			{
				vars[expression.root] = evaluateExpressionNode(first.node, queue);
				return_value = 1;
				break;
			}
		case _GREATER_:
			{
				double val = 0.0;
				if (expression.root[0] == '$') {
					val = getVarValue(expression.root);
				} else {
					val = atof(expression.root.c_str());
				}
				if (val > evaluateExpressionNode(first.node, queue)) {
					return_value = 1;
				} else {
					return_value = 0;
				}
				break;
			}
		case _LESS_:
			{
				double val = 0.0;
				if (expression.root[0] == '$') {
					val = getVarValue(expression.root);
				} else {
					val = atof(expression.root.c_str());
				}
				if (val < evaluateExpressionNode(first.node, queue)) {
					return_value = 1;
				} else {
					return_value = 0;
				}
				break;
			}
		case _GEQ_:
			{
				double val = 0.0;
				if (expression.root[0] == '$') {
					val = getVarValue(expression.root);
				} else {
					val = atof(expression.root.c_str());
				}
				if (val >= evaluateExpressionNode(first.node, queue)) {
					return_value = 1;
				} else {
					return_value = 0;
				}
				break;
			}
		case _LEQ_:
			{
				double val = 0.0;
				if (expression.root[0] == '$') {
					val = getVarValue(expression.root);
				} else {
					val = atof(expression.root.c_str());
				}
				if (val > evaluateExpressionNode(first.node, queue)) {
					return_value = 1;
				} else {
					return_value = 0;
				}
				break;
			}
		case _EQUAL_:
			{
				double val = 0.0;
				if (expression.root[0] == '$') {
					val = getVarValue(expression.root);
				} else {
					val = atof(expression.root.c_str());
				}
				if (val == evaluateExpressionNode(first.node, queue)) {
					return_value = 1;
				} else {
					return_value = 0;
				}
				break;
			}
		case _NEQUAL_:
			{
				double val = 0.0;
				if (expression.root[0] == '$') {
					val = getVarValue(expression.root);
				} else {
					val = atof(expression.root.c_str());
				}
				if (val != evaluateExpressionNode(first.node, queue)) {
					return_value = 1;
				} else {
					return_value = 0;
				}
				break;
			}
		case _ASSTXT_:
			{
				texts[expression.root] = first.node;
				break;
			}
		case _CMP_:
			{
				std::string left, right;
				if (expression.root[0] == '$') {
					left = texts[expression.root];
				} else {
					left = expression.root;
				}
				if (first.node[0] == '$') {
					right = texts[first.node];
				} else {
					right = first.node;
				}
				//std::cout << "Comparing " << left << " and " << right << std::endl;
				if (left.compare(right) == 0) {
					return_value = 0;
				} else {
					return_value = 1;
				}
				break;
			}
		default:
			{
				break;
			}
		}
	}
	return return_value;
}

void executeBranch(std::vector<address>* branch) {
	for (std::vector<address>::iterator it = branch->begin(); it != branch->end(); ++it) {
		switch (it->type) {
		case _FUNC_:
			{
				std::vector<std::string> args = functions[it->pointer].tokens;
				if (functions[it->pointer].name.compare("print") == 0) {
					if (args.size() > 0) {
						onPrint(args[0]);
					} else {
						std::cerr << "print function was expecting an argument" << std::endl;
					}
				} else if (functions[it->pointer].name.compare("sleep") == 0) {
					if (args.size() > 0) {
						onSleep(atoi(args[0].c_str()));
					} else {
						std::cerr << "sleep function was expecting an argument" << std::endl;
					}
				} else if (functions[it->pointer].name.compare("playmode") == 0) {
					if (args.size() > 0) {
						onPlayMode(args[0]);
					} else {
						std::cerr << "playmode function was expecting an argument" << std::endl;
					}
				} else if (functions[it->pointer].name.compare("send") == 0) {
					onSend();
				} else if (functions[it->pointer].name.compare("ball") == 0) {
					if (args.size() > 1) {
						onBall(atof(args[0].c_str()), atof(args[1].c_str()));
					} else {
						std::cerr << "ball function was expecting two arguments" << std::endl;
					}
				} else if (functions[it->pointer].name.compare("recover") == 0) {
					onRecover();
				} else if (functions[it->pointer].name.compare("start") == 0) {
					onStart();
				}
				break;
			}
		case _EXPRS_:
			{
				evaluateExpression(expressions[it->pointer]);
				break;
			}
		case _IF_:
			{
				if (evaluateExpression(controls[it->pointer].expr) == 1) {
					executeBranch(&branchs[it->left_branch]);
				} else if (it->right_branch > -1) {
					executeBranch(&branchs[it->right_branch]);
				}
				break;
			}
		case _WHILE_:
			{
				if (evaluateExpression(controls[it->pointer].expr) == 1) {
					executeBranch(&branchs[it->left_branch]);
					--it;
				}
				break;
			}
		default:
			{
				break;
			}
		}
	}
}

void *executeCode(void* arg) {
	executeBranch(&branchs[0]);
	newExecution = false;
	return 0;
}

void parseLine(std::string line);

void onMacro(phx::function macro) {
	if (macro.name.compare("_do") == 0) {
		// To be implemented
	} else if (macro.name.compare("_waitfor") == 0) {
		std::vector<std::string> args = macro.tokens;
		if (args.size() > 1 && args[0].compare("play_mode") == 0) {
			std::string line = "while ($playmode <> " + args[1] + ")";
			parseLine(line);
			line = "sleep(1);";
			parseLine(line);
			line = "endwhile";
			parseLine(line);
		}
	}
}

void parseLine(std::string line) {
	using boost::spirit::ascii::space;
	phx::function phx_function;
	function_parser<std::string::iterator> parser_function;
	bool r = phrase_parse(line.begin(), line.end(), parser_function, space, phx_function);
	if (r) {
		if (phx_function.name[0] == '_') {
			onMacro(phx_function);
			return;
		}
		functions.push_back(phx_function);
		address a;
		a.type = _FUNC_;
		a.pointer = functions.size() - 1;
		branchs[branchs_stack.top()].push_back(a);
		return;
	}
	phx::expression phx_expression;
	expression_parser<std::string::iterator> parser_expression;
	r = phrase_parse(line.begin(), line.end(), parser_expression, space, phx_expression);
	if (r) {
		expressions.push_back(phx_expression);
		address a;
		a.type = _EXPRS_;
		a.pointer = expressions.size() - 1;
		branchs[branchs_stack.top()].push_back(a);
		return;
	}
	phx::control phx_control;
	control_parser<std::string::iterator> parser_control;
	r = phrase_parse(line.begin(), line.end(), parser_control, space, phx_control);
	if (r) {
		controls.push_back(phx_control);
		std::vector<address> new_branch;
		branchs.push_back(new_branch);
		address a;
		a.type = phx_control.type;
		a.pointer = controls.size() - 1;
		a.left_branch = branchs.size() - 1;
		branchs[branchs_stack.top()].push_back(a);
		branchs_stack.push(branchs.size() - 1);
		return;
	}
	int close;
	close_parser<std::string::iterator> parser_close;
	r = phrase_parse(line.begin(), line.end(), parser_close, space, close);
	if (r) {
		branchs_stack.pop();
		switch (close) {
		case _ELSE_:
			{
				if (branchs[branchs_stack.top()].back().type == _IF_) {
					std::vector<address> new_branch;
					branchs.push_back(new_branch);
					branchs[branchs_stack.top()].back().right_branch = branchs.size() - 1;
					branchs_stack.push(branchs.size() - 1);
				} else {
					std::cerr << "IF-control not found" << std::endl;
				}
				break;
			}
		case _ENDIF_:
			{
				if (branchs[branchs_stack.top()].back().type != _IF_) {
					std::cerr << "IF-control not found" << std::endl;
				}
				break;
			}
		case _ENDWHILE_:
			{
				if (branchs[branchs_stack.top()].back().type != _WHILE_) {
					std::cerr << "WHILE-control not found" << std::endl;
				}
				break;
			}
		default:
			{
				break;
			}
		}
		return;
	}
	std::cerr << "Line not parsed " << line << std::endl;
}

bool loadCode(std::string trainer) {
	std::ifstream file(trainer.c_str(), std::ifstream::in);
	std::vector<address> main_branch;
	branchs.push_back(main_branch);
	branchs_stack.push(branchs.size() - 1);
	if (file) {
		std::string line;
		while (std::getline(file, line)) {
			parseLine(line);
		}
		branchs_stack.pop();
		if (branchs_stack.size() > 0) {
			std::cerr << "Program unbalanced, some control close is missing" << std::endl;
		}
	} else {
		std::cerr << "Error opening file" << std::endl;
	}
	file.close();
	return true;
}

bool load(std::string trainer) {
	loadCode(trainer);
	return true;
}

void execute(WorldModel world, std::vector<Message> messages) {
	// We update all the variables
	Ball* ball = world.getBall();
	double bx = ball->getPosition()->getX();
	double by = ball->getPosition()->getY();
	vars["$ball.x"] = bx;
	vars["$ball.y"] = by;
	// It seems we must update the play mode automatically
	if (bx > 52.5 && (by < 7.0 && by > -7.0)) { // left goal
		Game::PLAY_MODE = "goal_l";
	} else if (bx < -52.5 && (by < 7.0 && by > -7.0)) { // right goal
		Game::PLAY_MODE = "goal_r";
	}
	texts["$playmode"] = Game::PLAY_MODE;
	// We launch the thread or update the new cycles
	if (running) {
		int success = pthread_mutex_lock(&cycle_mutex);
		if (success) {
			std::cerr << "Game::updateTimes(int) -> can not lock mutex" << std::endl;
			return;
		}
		cycle_flag = true;
		success = pthread_mutex_unlock(&cycle_mutex);
		if (success) {
			std::cerr << "Game::updateTimes(int) -> can not unlock mutex" << std::endl;
		}
		success = pthread_cond_signal(&cycle_cond);
		if (success) {
			std::cerr << "Game::updateTime(int) -> can not signal to blocked threads" << std::endl;
		}
	} else {
		if (pthread_create(&thread_trainer, 0, executeCode, 0) != 0) {
			std::cerr << "Could not create trainer thread" << std::endl;
		} else {
			running = true;	
		}
	}
}

bool continueExecution() {
	return newExecution;
}

}
