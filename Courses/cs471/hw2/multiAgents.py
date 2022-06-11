# multiAgents.py
# --------------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
# 
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


from util import manhattanDistance
from game import Directions
import random, util

from game import Agent

class ReflexAgent(Agent):
    """
      A reflex agent chooses an action at each choice point by examining
      its alternatives via a state evaluation function.

      The code below is provided as a guide.  You are welcome to change
      it in any way you see fit, so long as you don't touch our method
      headers.
    """


    def getAction(self, gameState):
        """
        You do not need to change this method, but you're welcome to.

        getAction chooses among the best options according to the evaluation function.

        Just like in the previous project, getAction takes a GameState and returns
        some Directions.X for some X in the set {North, South, West, East, Stop}
        """
        # Collect legal moves and successor states
        legalMoves = gameState.getLegalActions()

        # Choose one of the best actions
        scores = [self.evaluationFunction(gameState, action) for action in legalMoves]
        bestScore = max(scores)
        bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
        chosenIndex = random.choice(bestIndices) # Pick randomly among the best

        "Add more of your code here if you want to"

        return legalMoves[chosenIndex]

    def evaluationFunction(self, currentGameState, action):
        """
        Design a better evaluation function here.

        The evaluation function takes in the current and proposed successor
        GameStates (pacman.py) and returns a number, where higher numbers are better.

        The code below extracts some useful information from the state, like the
        remaining food (newFood) and Pacman position after moving (newPos).
        newScaredTimes holds the number of moves that each ghost will remain
        scared because of Pacman having eaten a power pellet.

        Print out these variables to see what you're getting, then combine them
        to create a masterful evaluation function.
        """
        # Useful information you can extract from a GameState (pacman.py)
        successorGameState = currentGameState.generatePacmanSuccessor(action)
        newPos = successorGameState.getPacmanPosition()
        newFood = successorGameState.getFood()
        newGhostStates = successorGameState.getGhostStates()
        newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]

        "*** YOUR CODE HERE ***"
        
        currentFood = currentGameState.getFood()
        Foods = currentFood.asList()

        score = util.manhattanDistance(newPos, Foods[0])
        GhostPos = [Ghost.getPosition() for Ghost in newGhostStates]

        dist = util.manhattanDistance(newPos, GhostPos[len(GhostPos)-1])
        if dist == 0 :
          return float('-inf')
        else:
          GScore = 2*(-1.0) / dist
        if score == 0: 
          endScore = float('inf')
        else: 
          endScore = GScore + 1.0 / score
        return endScore

def scoreEvaluationFunction(currentGameState):
    """
      This default evaluation function just returns the score of the state.
      The score is the same one displayed in the Pacman GUI.

      This evaluation function is meant for use with adversarial search agents
      (not reflex agents).
    """
    return currentGameState.getScore()

class MultiAgentSearchAgent(Agent):
    """
      This class provides some common elements to all of your
      multi-agent searchers.  Any methods defined here will be available
      to the MinimaxPacmanAgent, AlphaBetaPacmanAgent & ExpectimaxPacmanAgent.

      You *do not* need to make any changes here, but you can if you want to
      add functionality to all your adversarial search agents.  Please do not
      remove anything, however.

      Note: this is an abstract class: one that should not be instantiated.  It's
      only partially specified, and designed to be extended.  Agent (game.py)
      is another abstract class.
    """

    def __init__(self, evalFn = 'scoreEvaluationFunction', depth = '2'):
        self.index = 0 # Pacman is always agent index 0
        self.evaluationFunction = util.lookup(evalFn, globals())
        self.depth = int(depth)

class MinimaxAgent(MultiAgentSearchAgent):
    """
      Your minimax agent (question 2)
    """

    def getAction(self, gameState):
        """
          Returns the minimax action from the current gameState using self.depth
          and self.evaluationFunction.

          Here are some method calls that might be useful when implementing minimax.

          gameState.getLegalActions(agentIndex):
            Returns a list of legal actions for an agent
            agentIndex=0 means Pacman, ghosts are >= 1

          gameState.generateSuccessor(agentIndex, action):
            Returns the successor game state after an agent takes an action

          gameState.getNumAgents():
            Returns the total number of agents in the game
        """
        "*** YOUR CODE HERE ***"
        numAgent = gameState.getNumAgents()
        actionScore = []

        def miniMax(state, counter):
          count = counter % numAgent
          if counter >= self.depth*numAgent or state.isWin() or state.isLose():
            return self.evaluationFunction(state)
          if count != 0:
            result = float('inf')
            for a in state.getLegalActions(count):
              if a == 'Stop':
                continue
              succGen = state.generateSuccessor(count,a)
              result = min(result, miniMax(succGen, counter+1))
            return result
          else:
            result = float('-inf')
            for a in state.getLegalActions(count):
              if a == 'Stop':
                continue
              succGen = state.generateSuccessor(count,a)
              result = max(result, miniMax(succGen, counter+1))
              if counter == 0:
                actionScore.append(result)
            return result
          
        result = miniMax(gameState, 0);
        end = [x for x in gameState.getLegalActions(0) if x != 'Stop']
        final = end[actionScore.index(max(actionScore))]
        return final
        

class AlphaBetaAgent(MultiAgentSearchAgent):
    """
      Your minimax agent with alpha-beta pruning (question 3)
    """

    def getAction(self, gameState):
        """
          Returns the minimax action using self.depth and self.evaluationFunction
        """
        "*** YOUR CODE HERE ***"
        numAgent = gameState.getNumAgents()
        actionScore = []

        def alphaBeta(state, counter, alpha, beta):
          count = counter % numAgent
          if counter >= self.depth*numAgent or state.isWin() or state.isLose():
            return self.evaluationFunction(state)
          if count != 0:
            result = float('inf')
            for a in state.getLegalActions(count):
              if a == 'Stop':
                continue
              succGen = state.generateSuccessor(count,a)
              result = min(result, alphaBeta(succGen, counter+1, alpha, beta))
              beta = min(beta, result)
              if beta < alpha:
                break
            return result
          else:
            result = float('-inf')
            for a in state.getLegalActions(count):
              if a == 'Stop':
                continue
              succGen = state.generateSuccessor(count,a)
              result = max(result, alphaBeta(succGen, counter+1, alpha, beta))
              alpha = max(alpha, result)
              if counter == 0:
                actionScore.append(result)
              if beta < alpha:
                break
            return result

        result = alphaBeta(gameState, 0, float('-inf'), float('inf'))
        end = [x for x in gameState.getLegalActions(0) if x != 'Stop']
        final = end[actionScore.index(max(actionScore))]
        return final

class ExpectimaxAgent(MultiAgentSearchAgent):
    """
      Your expectimax agent (question 4)
    """

    def getAction(self, gameState):
        """
          Returns the expectimax action using self.depth and self.evaluationFunction

          All ghosts should be modeled as choosing uniformly at random from their
          legal moves.
        """
        "*** YOUR CODE HERE ***"
        numAgent = gameState.getNumAgents()
        actionScore = []

        def expectMax(state, counter):
          count = counter % numAgent
          if counter >= self.depth*numAgent or state.isWin() or state.isLose():
            return self.evaluationFunction(state)
          if count != 0:
            successorScore = []
            for a in state.getLegalActions(count):
              if a == 'Stop':
                continue
              succGen = state.generateSuccessor(count,a)
              result = expectMax(succGen, counter+1)
              successorScore.append(result)
            averageScore = sum([ float(x)/len(successorScore) for x in successorScore])
            return averageScore
          else:
            result = float('-inf')
            for a in state.getLegalActions(count):
              if a == 'Stop':
                continue
              succGen = state.generateSuccessor(count,a)
              result = max(result, expectMax(succGen, counter+1))
              if counter == 0:
                actionScore.append(result)
            return result
          
        result = expectMax(gameState, 0);
        end = [x for x in gameState.getLegalActions(0) if x != 'Stop']
        final = end[actionScore.index(max(actionScore))]
        return final


def betterEvaluationFunction(currentGameState):
    """
      Your extreme ghost-hunting, pellet-nabbing, food-gobbling, unstoppable
      evaluation function (question 5).

      DESCRIPTION: <write something here so we know what you did>
    """
    "*** YOUR CODE HERE ***"
    pacmanPos = currentGameState.getPacmanPosition()
    ghostPosList = currentGameState.getGhostPositions()

    foodList = currentGameState.getFood().asList()
    score = currentGameState.getScore()
    foodDistList = [util.manhattanDistance(pacmanPos, foodPos) for foodPos in foodList]

    food = 1
    if len(foodList) > 0:
      food = min(foodDistList)

    for ghostPos in ghostPosList:
      ghostDist = util.manhattanDistance(pacmanPos, ghostPos)
      if ghostDist < 1:
        food = float('inf')

    values = [3.0 / food, score, len(foodList), len(currentGameState.getCapsules())]

    return sum(values)

# Abbreviation
better = betterEvaluationFunction

