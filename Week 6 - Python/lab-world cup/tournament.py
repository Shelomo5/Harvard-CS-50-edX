# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []
    # TODO: Read teams into memory from file
    # accessing file using command line argument
    filename = sys.argv[1]
    # opening filename
    with open(filename) as file:
        # use reader to read the file one row at a time treating each row as a dictionary  (a set of key-value pairs)
        # using the first row in the file as the keys for each value team and rating
        reader = csv.DictReader(file)
        # looping over all the data to read teams into memory
        for team in reader:
            # convert rating from string to integer to be stored in dictionary, [] to access value for a particular key inside dictionary
            team["rating"] = int(team["rating"])
            # append adds value to end of list so we add new team to teams dictionary
            teams.append(team)

    counts = {}
    # Simulate N (1000) tournaments and keep track of win counts
    for i in range(N):
        # storing winners of simulated tournament in winner
        winner = simulate_tournament(teams)
        if winner in counts:
            # increase counts by 1 for winner
            counts[winner] += 1
        else:
            counts[winner] = 1

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    # as long as the number of teams is greater than one we need to simulate more rounds, len gives # of items in list
    while len(teams) > 1:
        # simulate round with teams and update teams to just the winners since winners is what round function returns
        teams = simulate_round(teams)
        # teams[0] allows you to access first and only element is teams list
        # "team" allows you to access the name of a team, team column of csv file or team key inside dictionary
    return teams[0]["team"]


if __name__ == "__main__":
    main()
