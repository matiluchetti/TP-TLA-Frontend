#include "../../backend/domain-specific/calculator.h"
#include "../../backend/support/logger.h"
#include "bison-actions.h"
#include <stdio.h>
#include <string.h>
#include "../../backend/support/shared.h"
#include "../../backend/semantic-analysis/symbol-table.h"

/**
 * Implementación de "bison-actions.h".
 */

/**
* Esta función se ejecuta cada vez que se emite un error de sintaxis.
*/
void yyerror(const char * string) {
	LogErrorRaw("[ERROR] Mensaje: '%s', debido a '", string);
	for (int i = 0; i < yyleng; ++i) {
		switch (yytext[i]) {
			case '\n':
				LogErrorRaw("\\n");
			default:
				LogErrorRaw("%c", yytext[i]);
		}
	}
	LogErrorRaw("' (length = %d, linea %d).\n\n", yyleng, yylineno);
}

/**
* Esta acción se corresponde con el no-terminal que representa el símbolo
* inicial de la gramática, y por ende, es el último en ser ejecutado, lo que
* indica que efectivamente el programa de entrada se pudo generar con esta
* gramática, o lo que es lo mismo, que el programa pertenece al lenguaje.
*/
// int ProgramGrammarAction(const int value) {
// 	LogDebug("[Bison] ProgramGrammarAction(%d)", value);
// 	/*
// 	* "state" es una variable global que almacena el estado del compilador,
// 	* cuyo campo "succeed" indica si la compilación fue o no exitosa, la cual
// 	* es utilizada en la función "main".
// 	*/
// 	state.succeed = true;
// 	/*
// 	* Por otro lado, "result" contiene el resultado de aplicar el análisis
// 	* sintáctico mediante Bison, y almacenar el nood raíz del AST construido
// 	* en esta variable. Para el ejemplo de la calculadora, no hay AST porque
// 	* la expresión se computa on-the-fly, y es la razón por la cual esta
// 	* variable es un simple entero, en lugar de un nodo.
// 	*/
// 	state.result = value;
// 	return value;
// }

ProgramNode * ProgramGrammarAction(SportNode * sport){
	ProgramNode * initial = ( ProgramNode *) calloc(1, sizeof( ProgramNode));
	initial->info = sport;
	state.succeed = true;
	state.result = 15;
	state.program = initial;
	return initial;
}


int Return0(){
	return 0;
}

 SportNode * SportGrammarAction(SportType selected_sport,  ProbabilityNode * probabilities,  MatchNode *match){
	SportNode * sport = ( SportNode *) calloc(1, sizeof( SportNode));
	sport->sport = selected_sport;
	sport->probabilities = probabilities;
	sport->match = match;
	return sport;
}

 ProbabilityNode * OddsGrammarAction(char * odds){
	ProbabilityNode * probabilities = ( ProbabilityNode *) calloc(1, sizeof( ProbabilityNode));
	probabilities->type = PROBABILITY;
	if(sscanf(odds, "%2d-%2d-%2d", &probabilities->t1_odds, &probabilities->tie_odds, &probabilities->t2_odds) != 3){
		LogError("Error al parsear las probabilidades");
	}
	return probabilities;
}

 ProbabilityNode * NoOddsGrammarAction(){
	ProbabilityNode * probabilities = ( ProbabilityNode *) calloc(1, sizeof( ProbabilityNode));
	probabilities->type = NO_PROBABILITY;
		LogDebug("hasta aca llegue no odds");

	return probabilities;
}

 MatchNode * MatchGrammarAction( TeamNode * team1,  TeamNode * team2){
	MatchNode * match = ( MatchNode *) calloc(1, sizeof( MatchNode));
	match->team1 = team1;
	match->team2 = team2;
	LogDebug("hasta aca llegue");
	return match;
}

 TeamNode * TeamGrammarAction(TeamNameNode * name,  FormationNode * formation,  PlayerNode * players){
	TeamNode * team = ( TeamNode *) calloc(1, sizeof( TeamNode));
	team->teamName = name;
	team->players = players;
	team->formation = formation;
			LogDebug("hasta aca llegue team");
	addTeam();
	return team;
}

 TeamNameNode * TeamNameGrammarAction(char * name){
	TeamNameNode * teamName = ( TeamNameNode *) calloc(1, sizeof( TeamNameNode));
	teamName->teamName = name;
			LogDebug("hasta aca llegue team name");
	return teamName;
}

FormationNode * FormationGrammarAction(char * formation){
	FormationNode * formationNode = ( FormationNode *) calloc(1, sizeof( FormationNode));
	formationNode->formation = formation;
			LogDebug("hasta aca formation");
	return formationNode;
}

PlayerNode * PlayerListGrammarAction(PlayerNode * firstPlayer){
			LogDebug("hasta aca llegue playerlist");
	return firstPlayer;
}

PlayerNode * PlayerGrammarAction(char * name,  PlayerNode * nextPlayer){
	PlayerNode * playerM = ( PlayerNode *) calloc(1, sizeof( PlayerNode));
	playerM->playerName = name;
	playerM->nextPlayer = nextPlayer;
	LogDebug("Llamo a addPlayer...");
	addPlayer(name);	
	LogDebug("Todo bien en addPlayer");
	return playerM;
}

PlayerNode * LastPlayerGrammarAction(char * name){
	PlayerNode * playerZ = ( PlayerNode *) calloc(1, sizeof( PlayerNode));
	playerZ->playerName = name;
	playerZ->nextPlayer = NULL;
		LogDebug("hasta aca llegue last player");
	addPlayer(name);
	return playerZ;
}