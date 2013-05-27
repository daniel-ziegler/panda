#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "mm-client.h"

// This is the name that the driver will refer to your bot as.
const char* BOT_NAME = "avgbot";

// Return whether setup was successful, bot dies if 0.
int client_setup(int *argc, char ***argv)
{
	return 1;
}

int tally[MAXCOWS][MAXPLAYERS];
double getprob(int roundnum, int cow, int player) {
	roundnum++;
	return (double)tally[cow][player] / roundnum;
}
double probdp[MAXPLAYERS + 1][MAXPLAYERS + 1];

// This function is called when the game begins, and provides initial player pools via the players array.
void game_setup(const struct player_data* players, unsigned int numplayers)
{

}

// When this function is called, your bot should respond with your move.
int player_turn(unsigned int roundnum, const struct player_data* players, unsigned int numplayers)
{
	int bestcow, cow, p, i, n;
	if(roundnum == 0) {
		bestcow = 0;
		for(i = 1; i < NUMCOWS; i++) {
			if(MILKVALUES[i] > MILKVALUES[bestcow]) {
				bestcow = i;
			}
		}
		return bestcow;
	} else {
		for(cow = 0; cow < NUMCOWS; cow++) {
			memset(probdp, 0.0, sizeof(probdp));
			probdp[0][0] = 1;
			for(p = 0; p < numplayers; p++) {
				if(players[p].id != SELF.id && players[p].milk >= 0) {
					for(n = 0; n <= numplayers; n++) {
						double prob = getprob(roundnum, cow, p);
						probdp[p + 1][n] = prob * probdp[p][n - 1] + (1 - prob) * probdp[p][n];
						fprintf(stderr, "[%d,%d]: %lf\n", p, n, probdp[p + 1][n]);
					}
				}
			}

		}
	}
}

// This function is called at the end of the game, as a courtesy.
void game_end()
{

}

