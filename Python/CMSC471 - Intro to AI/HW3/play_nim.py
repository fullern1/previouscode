#! /usr/bin/python

""" A program to play Nim with any number of heaps that assumes we are using the aima-python
games.py framework. Usage examples:

python play_nim 
  Runs a standard set of tests using different initial states and players

python play_nim <heaps> [<player1> [<player2>]]
  Runs a nim game with initial state <heaps> between <player1> and <player2>

  <heaps> should be a string that will evaluate to a list of one or 
    more positive integers, e.g., [5,4,3] or [1,1,1] or "[3, 4, 5]"

  <player1> and <player2> are optional and if not given default to a
    random player, i.e., one that selects possible modes at random. Predefined
    player names include:

      me for a player that takes input for each move

      abN, where N is an integer between 1 and 20, for a player that
       uses alphabeta and generates a lookahead tree for each move to
       depth N.  Example: ab3 always looks ahead three plys

"""

import argparse
import sys
import games
import nim

infinity = float('inf')

def make_alphabeta_player(N=0):
    """ Returns a player function that uses alpha_beta search to depth N """
    if N==0:
        return lambda g, s: games.alphabeta_search(s, g)
    else:
          return lambda g, s: games.alphabeta_cutoff_search(s, g, d=N)      



# PLAYERS is a dictionary mapping player names to the python functions
# that implement them.
PLAYERS = {'me':games.query_player,
           'random':games.random_player,
           'ab':lambda g, s: games.alphabeta_search(s, g)}

# add to the PLAYERS dictionary player function named ab1,ab2,...ab20
# that use alpha_beta search with depth cutoffs between 1 and 20
for i in range(1,21):
    PLAYERS['ab'+str(i)] = make_alphabeta_player(i)


# NIM problems for testing
tests = [
    ([1], 'random', 'random'),
    ([3], 'random', 'random'),    
    ([1,1], 'ab', 'ab'),
    ([1,1,1], 'ab', 'ab'),
    ([1,1,1,1], 'ab', 'ab'),    
    ([2,2], 'ab', 'ab'),
    ([5,4,3,2,1], 'ab2', 'ab3'),
    ([5,4,3,2,1], 'ab3', 'ab2'),
    ([7,6,5,4,3,2,1], 'ab2', 'ab3'),
    ([7,6,5,4,3,2,1], 'ab3', 'ab2'),
    ([7,6,5,4,3,2,1,1,1,1], 'ab2', 'ab3'),
    ([7,6,5,4,3,2,1,1,1,1], 'ab3', 'ab2'),
    ([7,6,5,4,3,2,1,2,3,4,5,6,7], 'ab2', 'ab2'),
    ([7,6,5,4,3,2,1,2,3,4,5,6,7], 'ab3', 'ab3'),
    ([7,6,5,4,3,2,1,2,3,4,5,6,7], 'ab2', 'ab3'),
    ([7,6,5,4,3,2,1,2,3,4,5,6,7], 'ab3', 'ab2') ]


def run_tests(tests):
    """ run all of the NIM tests """
    for heaps, player1, player2 in tests:
        play_nim(heaps, player1, player2)
        print()

def play_nim(heaps, player1, player2):

    """ Play a NIM game uing player1 and player 2 with an initial
    state having the heaps heaps.  Returns True if the play was
    successful and False if there was some problem, e.g., bad input or
    a draw, whuch shiould never happen.  """

    print("NIM with heaps {} using players {} and {}".format(heaps, player1, player2))

    # test heaps
    if not (isinstance(heaps, list) and
            all((isinstance(item, int) and item > 0)
                for item in heaps)):
        print("First argument must be a list of positive integers")
        return False

    # get player1 and player2 functions
    if isinstance(player1, str):
        if player1 in PLAYERS:
            player1 = PLAYERS[player1]
        else:
            print("I don't know what kind of player", player1, "is")
            return False
    if isinstance(player2, str):
        if player2 in PLAYERS:
            player2 = PLAYERS[player2]
        else:
            print("I don't know what kind of player", player2, "is")
            return False

    # play the game
    game = nim.Nim(heaps=heaps)
    result = game.play_game(player1, player2)

    # report the results and return True
    if result == infinity:
        print('Player 1 wins')
        return True
    elif result == - infinity:
        print('Player 2 wins')
        return True
    else:
        print('No one wins?')
        return False


# if called from the command line, invoke main using the optional
# arguments for the intial and goal states if provided
if __name__ == "__main__" :
  a = argparse.ArgumentParser()
  argparse.ArgumentParser(description='Play NIM given heaps and two players')
  a.add_argument('heaps', nargs="?", default = None, help='Python list of heaps')
  a.add_argument('player1', nargs="?", default = 'random', help='first player')
  a.add_argument('player2', nargs="?", default = 'random', help='second player')
  args = a.parse_args()
  if not args.heaps:
      run_tests(tests)
  else:
      play_nim(eval(args.heaps), args.player1, args.player2)
